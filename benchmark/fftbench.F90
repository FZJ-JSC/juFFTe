! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

program fftbench
    use omp_lib
    use bench_utils_m
    use juffte

#ifdef USE_REFERENCE_FFTW
use fftw_m
#endif

    implicit none

    complex(c_double_complex), pointer         :: a(:), b(:)
    real(c_double), pointer                    :: a_r(:)
    integer :: lnx(3), lny(3), lnz(3), nx, ny, nz, total, iopt
    real(real64) :: time0
    integer(c_intptr_t) :: addr

    call parse_args()

    print *, "Parsed arguments:"
    print *, "  dim        =", dim
    print *, "  type       =         ", trim(fft_type)
    if (fft_type == "c2c") then
        print *, "  direction  =         ", trim(direction)
        print *, "  placement  =         ", trim(placement)
    end if
    print *, "  size       =", size

    print *, "Total points =", product(size)
    total = product(size)
    call aligned_allocate(a,total,ALN)
    call aligned_allocate(b,product(size),ALN)
    call aligned_allocate(a_r,product(size),ALN)

    addr = transfer(c_loc(A(1)), addr)

if (mod(addr,ALN) == 0) then
    print *, "Arrays are,", ALN,"byte aligned"
else
    print *, "Array are NOT,", ALN, " aligned"
endif
    print *, ""
    call init_arrays()

    iopt = juffte_fw
    if (fft_type == "c2r" .or. (fft_type == "c2c" .and. direction == "bw")) iopt = juffte_bw
    call transform(juffte_init)
    call transform(iopt)
    time0 = time_per_call(.false.)

    write(6, *) "Results:"
    write(6, *) "  TIME       =", time0
    write(6, *) "  MFLOPS     =", mflops(time0)
    write(6, *) ""
#ifdef USE_REFERENCE_FFTW
    call fftw_bench_plan(fft_type, direction, placement, size, fftw_planner, wisdom_file, a, b, a_r)
    call init_arrays()
    call fftw_bench_run()
    time0 = time_per_call(.true.)
    call fftw_bench_destroy()

    write(6, *) "FFTW Results:"
    write(6, *) "  FFTW TIME  =", time0
    write(6, *) "  FFTW MFLOPS=", mflops(time0)
    write(6, *) ""
#endif

    call aligned_deallocate(a)
    call aligned_deallocate(b)
    call aligned_deallocate(a_r)

contains
  subroutine init_arrays()

    nx = size(1)
    ny = 1
    nz = 1
    lny = 0
    lnz = 0
    call factor(nx, lnx) ! needed for the flops estimate
    if (dim >= 2) then
        ny = size(2)
        call factor(ny, lny)
    endif
    if (dim >= 3) then
        nz = size(3)
        call factor(nz, lnz)
    endif
    if (fft_type == "r2c") then
        call init(a_r, total)
    else
        call init(a, total)
    endif
  end subroutine init_arrays

  ! FFTE's operation count for a transform of radices 2, 3 and 5, in Mflop/s.
  real(real64) function mflops(t)
    real(real64), intent(in) :: t
    integer :: l(3)

    l = lnx + lny + lnz
    mflops = (2.5d0*dble(l(1)) + 4.66666666666666d0*dble(l(2)) + 6.8d0*dble(l(3))) &
             *dble(total)/t/1.0d6
    if (fft_type == "c2c") mflops = 2.0d0*mflops
  end function mflops

  ! Seconds per transform, juFFTe's or FFTW's: runs it in batches, doubling the batch,
  ! until one batch takes at least min_time.
  real(real64) function time_per_call(fftw) result(t)
    logical, intent(in) :: fftw
    real(real64) :: t0
    integer :: loop, i

    loop = 1
    do
        t0 = omp_get_wtime()
        do i = 1, loop
            if (fftw) then
#ifdef USE_REFERENCE_FFTW
                call fftw_bench_run()
#endif
            else
                call transform(iopt)
            endif
        end do
        t = omp_get_wtime() - t0
        if (t >= min_time) exit
        loop = loop*2
    end do
    t = t/dble(loop)
  end function time_per_call

  subroutine transform(iopt)
    integer, intent(in) :: iopt

    if (fft_type == "r2c") then
        select case (dim)
        case (1); call dzfft1d(a_r, a, nx, iopt)
        case (2); call dzfft2d(a_r, a, nx, ny, iopt)
        case default; call dzfft3d(a_r, a, nx, ny, nz, iopt)
        end select
    elseif (fft_type == "c2r") then
        select case (dim)
        case (1); call zdfft1d(a, a_r, nx, iopt)
        case (2); call zdfft2d(a, a_r, nx, ny, iopt)
        case default; call zdfft3d(a, a_r, nx, ny, nz, iopt)
        end select
    elseif (placement == "out" .and. iopt /= juffte_init) then
        select case (dim)
        case (1); call zfft1d(a, nx, iopt, b)
        case (2); call zfft2d(a, nx, ny, iopt, b)
        case default; call zfft3d(a, nx, ny, nz, iopt, b)
        end select
    else
        select case (dim)
        case (1); call zfft1d(a, nx, iopt)
        case (2); call zfft2d(a, nx, ny, iopt)
        case default; call zfft3d(a, nx, ny, nz, iopt)
        end select
    endif
  end subroutine transform

end program fftbench
