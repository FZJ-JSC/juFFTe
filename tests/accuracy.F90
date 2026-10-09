! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

! Checks the FP64 forward transform against a direct DFT, element by element.
!
! The round-trip tests cannot see errors that a forward/backward pair cancels,
! such as a wrong sign convention or a consistent scaling error; this can.

program accuracy

    use juffte
    use, intrinsic :: iso_fortran_env
    implicit none

    real(real64), parameter :: tol = 1.0d-11
    integer :: dims(3), ndim, i
    character(len=16) :: arg
    logical :: ok

    ! One size per process: initialising a second size in the same process hits
    ! the single-live-plan limitation (module-level work arrays).
    ndim = command_argument_count()
    if (ndim < 1 .or. ndim > 3) then
        print *, "usage: accuracy n | nx ny | nx ny nz"
        stop 2
    end if
    do i = 1, ndim
        call get_command_argument(i, arg)
        read(arg, *) dims(i)
    end do

    ok = .true.
    select case (ndim)
    case (1); call check1d(dims(1), ok)
    case (2); call check2d(dims(1), dims(2), ok)
    case (3); call check3d(dims(1), dims(2), dims(3), ok)
    end select

    if (ok) then
        print *, "accuracy PASS"
    else
        print *, "accuracy FAIL"
        stop 1
    end if

contains

    subroutine init(x, n)
        complex(real64), intent(out) :: x(:)
        integer, intent(in) :: n
        integer :: i
        do i = 1, n
            x(i) = cmplx(sin(0.37d0*i), cos(0.11d0*i*i), real64)
        end do
    end subroutine init

    ! Direct DFT along one axis of an nx*ny*nz array (x fastest), sign -1.
    subroutine dft_axis(x, nx, ny, nz, axis)
        complex(real64), intent(inout) :: x(:)
        integer, intent(in) :: nx, ny, nz, axis
        complex(real64), allocatable :: line(:), res(:)
        real(real64), parameter :: pi = acos(-1.0d0)
        integer :: n, stride, i, j, k, p, q, base

        select case (axis)
        case (1); n = nx; stride = 1
        case (2); n = ny; stride = nx
        case default; n = nz; stride = nx*ny
        end select
        allocate(line(n), res(n))

        do k = 0, merge(nz - 1, 0, axis /= 3)
            do j = 0, merge(ny - 1, 0, axis /= 2)
                do i = 0, merge(nx - 1, 0, axis /= 1)
                    base = 1 + i + j*nx + k*nx*ny
                    do p = 0, n - 1
                        line(p + 1) = x(base + p*stride)
                    end do
                    do q = 0, n - 1
                        res(q + 1) = (0.0d0, 0.0d0)
                        do p = 0, n - 1
                            res(q + 1) = res(q + 1) + line(p + 1) * &
                                exp(cmplx(0.0d0, -2.0d0*pi*dble(mod(p*q, n))/dble(n), real64))
                        end do
                    end do
                    do p = 0, n - 1
                        x(base + p*stride) = res(p + 1)
                    end do
                end do
            end do
        end do
    end subroutine dft_axis

    subroutine report(label, a, ref, ok)
        character(len=*), intent(in) :: label
        complex(real64), intent(in) :: a(:), ref(:)
        logical, intent(inout) :: ok
        real(real64) :: err
        err = maxval(abs(a - ref)) / maxval(abs(ref))
        if (err < tol) then
            print '(a,a,es10.3)', label, '  rel.err ', err
        else
            print '(a,a,es10.3,a)', label, '  rel.err ', err, '  FAIL'
            ok = .false.
        end if
    end subroutine report

    subroutine check1d(n, ok)
        integer, intent(in) :: n
        logical, intent(inout) :: ok
        complex(real64), allocatable :: a(:), ref(:)
        character(len=40) :: label
        allocate(a(n), ref(n))
        call init(a, n)
        ref = a
        call dft_axis(ref, n, 1, 1, 1)
        call zfft1d(a, n, juffte_init)
        call zfft1d(a, n, juffte_fw)
        write(label, '(a,i0)') '1-D ', n
        call report(label, a, ref, ok)
    end subroutine check1d

    subroutine check2d(nx, ny, ok)
        integer, intent(in) :: nx, ny
        logical, intent(inout) :: ok
        complex(real64), allocatable :: a(:), ref(:)
        character(len=40) :: label
        allocate(a(nx*ny), ref(nx*ny))
        call init(a, nx*ny)
        ref = a
        call dft_axis(ref, nx, ny, 1, 1)
        call dft_axis(ref, nx, ny, 1, 2)
        call zfft2d(a, nx, ny, juffte_init)
        call zfft2d(a, nx, ny, juffte_fw)
        write(label, '(a,i0,a,i0)') '2-D ', nx, 'x', ny
        call report(label, a, ref, ok)
    end subroutine check2d

    subroutine check3d(nx, ny, nz, ok)
        integer, intent(in) :: nx, ny, nz
        logical, intent(inout) :: ok
        complex(real64), allocatable :: a(:), ref(:)
        character(len=40) :: label
        allocate(a(nx*ny*nz), ref(nx*ny*nz))
        call init(a, nx*ny*nz)
        ref = a
        call dft_axis(ref, nx, ny, nz, 1)
        call dft_axis(ref, nx, ny, nz, 2)
        call dft_axis(ref, nx, ny, nz, 3)
        call zfft3d(a, nx, ny, nz, juffte_init)
        call zfft3d(a, nx, ny, nz, juffte_fw)
        write(label, '(a,i0,a,i0,a,i0)') '3-D ', nx, 'x', ny, 'x', nz
        call report(label, a, ref, ok)
    end subroutine check3d

end program accuracy
