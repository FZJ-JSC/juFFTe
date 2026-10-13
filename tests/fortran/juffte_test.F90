! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------
!
! Checks one juFFTe transform, called from Fortran, against a reference:
!
!   juffte_test_f [-t complex|real] [-d fw|bw] [-a native|fftw|simple] n1 [n2 [n3]]
!
! Options as in tests/c/juffte_test.c (defaults complex, fw, native); the number of sizes
! is the dimension, n1 is contiguous. "-t real -d fw" is r2c, "-t real -d bw" c2r. The
! native API is checked in FP64 and FP32, in place and out of place; "-a fftw" drives the
! FFTW-compatible interface the way FFTW code would, "-a simple" fft_init/fft_execute
! (1-D complex); both FP64 only.
!
! Every variant runs on the same random input and is compared with the reference: FFTW
! when built with USE_REFERENCE_FFTW, otherwise a direct DFT for N = n1 n2 n3 < 4000.
! Exit status: 0 pass, 1 fail, 2 usage, 77 no reference at this size.

module reference_m

    use, intrinsic :: iso_c_binding
    use, intrinsic :: iso_fortran_env, only: real64
    implicit none
    private
    public :: reference_name, have_reference, reference_bound, fft_bound
    public :: reference_c2c, reference_r2c, reference_c2r

#ifdef USE_REFERENCE_FFTW
#include "fftw3.f03"
#else
    ! The direct DFT is only used below this total size.
    integer, parameter :: dense_limit = 4000
    real(real64), parameter :: pi = 3.14159265358979323846_real64
#endif

contains

    ! Rounding error of an FFT of length nt: 2 log2(nt) eps.
    real(real64) function fft_bound(nt, eps)
        integer, intent(in) :: nt
        real(real64), intent(in) :: eps
        fft_bound = 2.0_real64 * log(real(max(nt, 2), real64)) / log(2.0_real64) * eps
    end function fft_bound

#ifdef USE_REFERENCE_FFTW

    character(len=16) function reference_name()
        reference_name = 'FFTW'
    end function reference_name

    logical function have_reference(n)
        integer, intent(in) :: n(:)
        have_reference = .true.
    end function have_reference

    real(real64) function reference_bound(n)
        integer, intent(in) :: n(:)
        reference_bound = fft_bound(product(n), epsilon(1.0_real64))
    end function reference_bound

    ! FFTW takes its dimensions slowest first.
    function fftw_dims(n) result(nr)
        integer, intent(in) :: n(:)
        integer(C_INT) :: nr(size(n))
        nr = int(n(size(n):1:-1), C_INT)
    end function fftw_dims

    ! Unnormalised, in place.
    subroutine reference_c2c(x, n, sign)
        complex(real64), intent(inout) :: x(:)
        integer, intent(in) :: n(:), sign
        complex(C_DOUBLE_COMPLEX), allocatable :: y(:)
        type(C_PTR) :: plan
        allocate(y(size(x)))
        plan = fftw_plan_dft(size(n, kind=C_INT), fftw_dims(n), x, y, int(sign, C_INT), FFTW_ESTIMATE)
        call fftw_execute_dft(plan, x, y)
        call fftw_destroy_plan(plan)
        x = y
    end subroutine reference_c2c

    subroutine reference_r2c(x, n, y)
        real(real64), intent(in) :: x(:)
        integer, intent(in) :: n(:)
        complex(real64), intent(out) :: y(:)
        real(C_DOUBLE), allocatable :: in(:)
        type(C_PTR) :: plan
        in = x
        plan = fftw_plan_dft_r2c(size(n, kind=C_INT), fftw_dims(n), in, y, FFTW_ESTIMATE)
        call fftw_execute_dft_r2c(plan, in, y)
        call fftw_destroy_plan(plan)
    end subroutine reference_r2c

    ! Unnormalised.
    subroutine reference_c2r(x, n, y)
        complex(real64), intent(in) :: x(:)
        integer, intent(in) :: n(:)
        real(real64), intent(out) :: y(:)
        complex(C_DOUBLE_COMPLEX), allocatable :: in(:)
        type(C_PTR) :: plan
        in = x  ! c2r overwrites its input
        plan = fftw_plan_dft_c2r(size(n, kind=C_INT), fftw_dims(n), in, y, FFTW_ESTIMATE)
        call fftw_execute_dft_c2r(plan, in, y)
        call fftw_destroy_plan(plan)
    end subroutine reference_c2r

#else

    character(len=16) function reference_name()
        reference_name = 'direct DFT'
    end function reference_name

    logical function have_reference(n)
        integer, intent(in) :: n(:)
        have_reference = product(n) < dense_limit
    end function have_reference

    ! The direct DFT's rounding error grows like sqrt(n) per dimension.
    real(real64) function reference_bound(n)
        integer, intent(in) :: n(:)
        reference_bound = 2.0_real64 * sum(sqrt(real(n, real64))) * epsilon(1.0_real64)
    end function reference_bound

    ! Unnormalised DFT along each dimension in turn, in place. The DFT matrix is never
    ! formed: one row of twiddle factors per dimension, indexed by p*q mod n.
    subroutine reference_c2c(x, n, sign)
        complex(real64), intent(inout) :: x(:)
        integer, intent(in) :: n(:), sign
        complex(real64), allocatable :: w(:), line(:)
        complex(real64) :: acc
        integer :: dims(3), axis, len, stride, outer, o, i, p, q, k, base

        dims = 1
        dims(1:size(n)) = n
        do axis = 1, size(n)
            len = dims(axis)
            stride = product(dims(1:axis - 1))
            outer = product(dims(axis + 1:3))
            allocate(w(0:len - 1), line(0:len - 1))
            do k = 0, len - 1
                w(k) = cmplx(cos(2.0_real64*pi*k/len), sign*sin(2.0_real64*pi*k/len), real64)
            end do
            do o = 0, outer - 1
                do i = 0, stride - 1
                    base = 1 + i + o*stride*len
                    line = x(base:base + (len - 1)*stride:stride)
                    do q = 0, len - 1
                        acc = 0
                        k = 0  ! p*q mod len
                        do p = 0, len - 1
                            acc = acc + line(p)*w(k)
                            k = k + q
                            if (k >= len) k = k - len
                        end do
                        x(base + q*stride) = acc
                    end do
                end do
            end do
            deallocate(w, line)
        end do
    end subroutine reference_c2c

    subroutine reference_r2c(x, n, y)
        real(real64), intent(in) :: x(:)
        integer, intent(in) :: n(:)
        complex(real64), intent(out) :: y(:)
        complex(real64), allocatable :: full(:)
        integer :: h, r

        h = n(1)/2 + 1
        full = cmplx(x, 0.0_real64, real64)
        call reference_c2c(full, n, -1)
        do r = 0, size(x)/n(1) - 1
            y(1 + r*h:(r + 1)*h) = full(1 + r*n(1):r*n(1) + h)
        end do
    end subroutine reference_r2c

    ! Rebuilds the full spectrum from the half one by Hermitian symmetry.
    subroutine reference_c2r(x, n, y)
        complex(real64), intent(in) :: x(:)
        integer, intent(in) :: n(:)
        real(real64), intent(out) :: y(:)
        complex(real64), allocatable :: full(:)
        integer :: dims(3), h, i, j, k

        dims = 1
        dims(1:size(n)) = n
        h = dims(1)/2 + 1
        allocate(full(product(dims)))
        do k = 0, dims(3) - 1
            do j = 0, dims(2) - 1
                do i = 0, dims(1) - 1
                    if (i < h) then
                        full(1 + i + dims(1)*(j + dims(2)*k)) = x(1 + i + h*(j + dims(2)*k))
                    else
                        full(1 + i + dims(1)*(j + dims(2)*k)) = conjg(x(1 + (dims(1) - i) + &
                            h*(mod(dims(2) - j, dims(2)) + dims(2)*mod(dims(3) - k, dims(3)))))
                    end if
                end do
            end do
        end do
        call reference_c2c(full, n, 1)
        y = real(full, real64)
    end subroutine reference_c2r

#endif

end module reference_m


program juffte_test

    use, intrinsic :: iso_c_binding, only: c_ptr
    use, intrinsic :: iso_fortran_env, only: real32, real64
    use juffte, only: zfft1d, zfft2d, zfft3d, dzfft1d, dzfft2d, dzfft3d, zdfft1d, zdfft2d, zdfft3d, &
                      fft_init, fft_execute, juffte_init, juffte_fw, juffte_bw, FFTW_ESTIMATE, &
                      api_plan_dft_1d => fftw_plan_dft_1d, api_plan_dft_2d => fftw_plan_dft_2d, &
                      api_plan_dft_3d => fftw_plan_dft_3d, api_execute_dft => fftw_execute_dft
    use reference_m
    implicit none

    ! The ways of calling a transform; see run().
    integer, parameter :: C2C_IN = 1, C2C_OUT = 2, R2C = 3, C2R = 4, API_OUT = 5, API_IN = 6, &
                          SIMPLE = 7

    ! One way of calling the transform; init: call it with juffte_init first.
    type :: variant
        character(len=16) :: name
        integer :: how
        logical :: init
    end type variant

    logical :: is_complex = .true.
    character(len=8) :: api = 'native'
    integer :: rank = 0, n(3) = 1, nt, nh, dir = juffte_fw, failures = 0
    type(c_ptr) :: plan

    call parse_args()
    nt = product(n(1:rank))
    nh = nt/n(1)*(n(1)/2 + 1)
    call header()
    if (.not. have_reference(n(1:rank))) then
        print '(a)', 'SKIP: no reference at this size'
        stop 77
    end if
    call seed()

    if (api == 'fftw') then
        call run_variants(64, [variant('out of place', API_OUT, .true.), &
                               variant('in place', API_IN, .true.)])
    else if (api == 'simple') then
        call run_variants(64, [variant('fft_execute', SIMPLE, .true.)])
    else if (is_complex) then
        call both_precisions([variant('in place', C2C_IN, .true.), &
                              variant('out of place', C2C_OUT, .false.)])
    else if (dir == juffte_fw) then
        call both_precisions([variant('r2c', R2C, .true.)])
    else
        call both_precisions([variant('c2r', C2R, .true.)])
    end if

    if (failures > 0) then
        print '(a)', 'FAIL'
        stop 1
    end if
    print '(a)', 'PASS'

contains

    subroutine usage()
        print '(a)', 'usage: juffte_test_f [-t complex|real] [-d fw|bw] [-a native|fftw|simple] ' // &
                     'n1 [n2 [n3]]'
        stop 2
    end subroutine usage

    ! The options of tests/c/juffte_test.c, which uses getopt: each takes a value, and
    ! they may come before or after the sizes.
    subroutine parse_args()
        character(len=32) :: arg, val
        integer :: i, argc, stat

        argc = command_argument_count()
        i = 1
        do while (i <= argc)
            call get_command_argument(i, arg)
            if (arg(1:1) == '-') then
                if (i == argc .or. len_trim(arg) /= 2) call usage()
                call get_command_argument(i + 1, val)
                select case (arg(2:2) // ' ' // val)
                case ('t complex'); is_complex = .true.
                case ('t real');    is_complex = .false.
                case ('d fw');      dir = juffte_fw
                case ('d bw');      dir = juffte_bw
                case ('a native', 'a fftw', 'a simple'); api = val
                case default;       call usage()
                end select
                i = i + 2
            else
                rank = rank + 1
                if (rank > 3) call usage()
                read(arg, *, iostat=stat) n(rank)
                if (stat /= 0 .or. n(rank) < 1) call usage()
                i = i + 1
            end if
        end do
        if (rank < 1) call usage()
        if (api /= 'native' .and. .not. is_complex) then
            print '(a)', 'Only the native API has real transforms.'
            stop 2
        end if
        if (api == 'simple' .and. rank /= 1) then
            print '(a)', 'fft_init/fft_execute are 1-D only.'
            stop 2
        end if
    end subroutine parse_args

    subroutine header()
        character(len=64) :: dims, tmp
        character(len=16) :: ref_name
        integer :: d
        write(dims, '(i0)') n(1)
        do d = 2, rank
            write(tmp, '(a,"x",i0)') trim(dims), n(d)
            dims = tmp
        end do
        ref_name = 'none'
        if (have_reference(n(1:rank))) ref_name = reference_name()
        print '(10a)', trim(merge('complex', 'real   ', is_complex)), ' ', &
                       trim(merge('fw', 'bw', dir == juffte_fw)), ' ', trim(dims), ', ', &
                       trim(api), ' API, reference: ', trim(ref_name)
    end subroutine header

    subroutine seed()
        integer :: k, j
        integer, allocatable :: s(:)
        call random_seed(size=k)
        allocate(s(k))
        s = [(104729*j + 7, j = 1, k)]
        call random_seed(put=s)
    end subroutine seed

    ! Random values in [-1, 1), exactly representable in precision prec.
    function random_real(count, prec) result(x)
        integer, intent(in) :: count, prec
        real(real64) :: x(count)
        call random_number(x)
        x = 2*x - 1
        if (prec == 32) x = real(real(x, real32), real64)
    end function random_real

    real(real64) function eps(prec)
        integer, intent(in) :: prec
        eps = merge(real(epsilon(1.0_real32), real64), epsilon(1.0_real64), prec == 32)
    end function eps

    ! ||a - ref||_2 / ||ref||_2
    real(real64) function relerr(a, ref)
        complex(real64), intent(in) :: a(:), ref(:)
        relerr = norm2(abs(a - ref)) / norm2(abs(ref))
    end function relerr

    subroutine check(what, err, bound)
        character(len=*), intent(in) :: what
        real(real64), intent(in) :: err, bound
        character(len=24) :: w
        logical :: ok
        w = what
        ok = err <= bound  ! false for NaN
        print '(2x,a,1x,"rel. error ",es9.2,"   bound ",es9.2,3x,a)', w, err, bound, &
              trim(merge('ok  ', 'FAIL', ok))
        if (.not. ok) failures = failures + 1
    end subroutine check

    subroutine check_unchanged(what, ok)
        character(len=*), intent(in) :: what
        logical, intent(in) :: ok
        character(len=24) :: w
        w = what
        print '(2x,a,1x,a)', w, trim(merge('unchanged   ok ', 'modified   FAIL', ok))
        if (.not. ok) failures = failures + 1
    end subroutine check_unchanged

    ! ------------------------------------------------------------------------ the harness

    subroutine both_precisions(vs)
        type(variant), intent(in) :: vs(:)
        call run_variants(64, vs)
        call run_variants(32, vs)
    end subroutine both_precisions

    ! Runs every variant on the same input and compares it with the reference.
    subroutine run_variants(prec, vs)
        integer, intent(in) :: prec
        type(variant), intent(in) :: vs(:)
        complex(real64), allocatable :: x(:), ref(:), a(:), b(:)
        character(len=24) :: name
        real(real64) :: bound
        integer :: i

        call make_input(prec, x, ref)
        bound = fft_bound(nt, eps(prec)) + reference_bound(n(1:rank))
        allocate(b(size(ref)))
        do i = 1, size(vs)
            write(name, '("fp",i0," ",a)') prec, trim(vs(i)%name)
            if (vs(i)%init) then
                a = x
                call run(prec, vs(i)%how, a, b, juffte_init)
            end if
            a = x
            b = 0
            call run(prec, vs(i)%how, a, b, dir)
            if (any(vs(i)%how == [C2C_IN, API_IN, SIMPLE])) then
                call check(name, relerr(a, ref), bound)
            else
                call check(name, relerr(b, ref), bound)
            end if
            if (any(vs(i)%how == [C2C_OUT, R2C, API_OUT])) &
                call check_unchanged(trim(name) // ', input', all(a == x))
        end do
    end subroutine run_variants

    ! Random input, exactly representable in precision prec, and the expected output in
    ! juFFTe's convention: the native backward transform is normalised, the FFTW layer's
    ! is not. Real arrays are held as complex with zero imaginary part. A c2r input must
    ! be the half spectrum of a real array, so it is the reference r2c of random data.
    subroutine make_input(prec, x, ref)
        integer, intent(in) :: prec
        complex(real64), allocatable, intent(out) :: x(:), ref(:)
        real(real64), allocatable :: r(:)

        if (is_complex) then
            x = cmplx(random_real(nt, prec), random_real(nt, prec), real64)
            ref = x
            call reference_c2c(ref, n(1:rank), dir)
        else if (dir == juffte_fw) then
            x = cmplx(random_real(nt, prec), 0, real64)
            allocate(ref(nh))
            call reference_r2c(real(x), n(1:rank), ref)
        else
            allocate(x(nh), r(nt))
            call reference_r2c(random_real(nt, 64), n(1:rank), x)
            if (prec == 32) x = cmplx(cmplx(x, kind=real32), kind=real64)
            call reference_c2r(x, n(1:rank), r)
            ref = cmplx(r, 0, real64)
        end if
        if (dir == juffte_bw .and. api /= 'fftw') ref = ref/nt
    end subroutine make_input

    ! Calls the transform under test on x, into y or in place, in precision prec.
    subroutine run(prec, how, x, y, iopt)
        integer, intent(in) :: prec, how, iopt
        complex(real64), intent(inout) :: x(:), y(:)

        select case (how)
        case (C2C_IN)
            call juffte_c2c(prec, x, iopt)
        case (C2C_OUT)
            call juffte_c2c(prec, x, iopt, y)
        case (R2C)
            call juffte_r2c(prec, x, y, iopt)
        case (C2R)
            call juffte_c2r(prec, x, y, iopt)
        case (API_OUT)
            if (iopt == juffte_init) then
                plan = api_plan(x, y)
            else
                call api_execute_dft(plan, x, y)
            end if
        case (API_IN)
            if (iopt == juffte_init) then
                plan = api_plan(x, x)
            else
                call api_execute_dft(plan, x, x)
            end if
        case (SIMPLE)
            if (iopt == juffte_init) then
                call fft_init(x)
            else
                call fft_execute(x, iopt)
            end if
        end select
    end subroutine run

    ! ------------------------------------------------------------------------ juFFTe calls
    ! These hold the data in FP64 and convert to and from FP32 around the call, and
    ! copy the input back afterwards, so that the caller sees whether it was modified.

    subroutine c2c64(a, iopt, out)
        complex(real64), intent(inout) :: a(:)
        integer, intent(in) :: iopt
        complex(real64), intent(out), optional :: out(:)
        select case (rank)
        case (1); call zfft1d(a, n(1), iopt, out)
        case (2); call zfft2d(a, n(1), n(2), iopt, out)
        case (3); call zfft3d(a, n(1), n(2), n(3), iopt, out)
        end select
    end subroutine c2c64

    subroutine c2c32(a, iopt, out)
        complex(real32), intent(inout) :: a(:)
        integer, intent(in) :: iopt
        complex(real32), intent(out), optional :: out(:)
        select case (rank)
        case (1); call zfft1d(a, n(1), iopt, out)
        case (2); call zfft2d(a, n(1), n(2), iopt, out)
        case (3); call zfft3d(a, n(1), n(2), n(3), iopt, out)
        end select
    end subroutine c2c32

    subroutine juffte_c2c(prec, a, iopt, out)
        integer, intent(in) :: prec, iopt
        complex(real64), intent(inout) :: a(:)
        complex(real64), intent(out), optional :: out(:)
        complex(real32), allocatable :: a32(:), out32(:)
        if (prec == 64) then
            call c2c64(a, iopt, out)
            return
        end if
        a32 = cmplx(a, kind=real32)
        if (present(out)) then
            allocate(out32(size(out)))
            call c2c32(a32, iopt, out32)
            out = out32
        else
            call c2c32(a32, iopt)
        end if
        a = a32
    end subroutine juffte_c2c

    ! x holds the real input as complex.
    subroutine juffte_r2c(prec, x, c, iopt)
        integer, intent(in) :: prec, iopt
        complex(real64), intent(inout) :: x(:)
        complex(real64), intent(out) :: c(:)
        real(real64), allocatable :: a(:)
        real(real32), allocatable :: a32(:)
        complex(real32), allocatable :: c32(:)
        if (prec == 64) then
            a = real(x)
            select case (rank)
            case (1); call dzfft1d(a, c, n(1), iopt)
            case (2); call dzfft2d(a, c, n(1), n(2), iopt)
            case (3); call dzfft3d(a, c, n(1), n(2), n(3), iopt)
            end select
            x = a
            return
        end if
        a32 = real(x, real32)
        allocate(c32(size(c)))
        select case (rank)
        case (1); call dzfft1d(a32, c32, n(1), iopt)
        case (2); call dzfft2d(a32, c32, n(1), n(2), iopt)
        case (3); call dzfft3d(a32, c32, n(1), n(2), n(3), iopt)
        end select
        x = a32
        c = c32
    end subroutine juffte_r2c

    ! The real output goes to x as complex.
    subroutine juffte_c2r(prec, c, x, iopt)
        integer, intent(in) :: prec, iopt
        complex(real64), intent(inout) :: c(:)
        complex(real64), intent(out) :: x(:)
        real(real64), allocatable :: a(:)
        real(real32), allocatable :: a32(:)
        complex(real32), allocatable :: c32(:)
        if (prec == 64) then
            allocate(a(size(x)))
            select case (rank)
            case (1); call zdfft1d(c, a, n(1), iopt)
            case (2); call zdfft2d(c, a, n(1), n(2), iopt)
            case (3); call zdfft3d(c, a, n(1), n(2), n(3), iopt)
            end select
            x = a
            return
        end if
        c32 = cmplx(c, kind=real32)
        allocate(a32(size(x)))
        select case (rank)
        case (1); call zdfft1d(c32, a32, n(1), iopt)
        case (2); call zdfft2d(c32, a32, n(1), n(2), iopt)
        case (3); call zdfft3d(c32, a32, n(1), n(2), n(3), iopt)
        end select
        c = c32
        x = a32
    end subroutine juffte_c2r

    ! The FFTW layer as FFTW code would call it: dimensions slowest first.
    type(c_ptr) function api_plan(a, b)
        complex(real64), intent(inout) :: a(:), b(:)
        select case (rank)
        case (1); api_plan = api_plan_dft_1d(n(1), a, b, dir, FFTW_ESTIMATE)
        case (2); api_plan = api_plan_dft_2d(n(2), n(1), a, b, dir, FFTW_ESTIMATE)
        case (3); api_plan = api_plan_dft_3d(n(3), n(2), n(1), a, b, dir, FFTW_ESTIMATE)
        end select
    end function api_plan

end program juffte_test
