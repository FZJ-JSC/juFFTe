! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

program test3d
    use, intrinsic :: iso_c_binding
    use, intrinsic :: iso_fortran_env
#ifndef FFTW
    use juffte
#endif
    use test_utils_m

    implicit none
#ifdef FFTW
      include 'fftw3.f03'
#endif
    complex(real64),allocatable    :: a(:), a_out(:)
    integer                   :: nx, ny, nz, n, num_args
    complex(real64)                :: a_in
    character(len=100)        :: args
    character(len=20)         :: exe
    type(C_PTR)               :: plan

    num_args = command_argument_count()
    if (num_args < 3) then

        write(6, *) " nx ="
        read(5, *) nx
        write(6, *) " ny ="
        read(5, *) ny
        write(6, *) " nz ="
        read(5, *) nz
    else
        call getarg(1, args)
        read(args, "(I10)") nx
        call getarg(2, args)
        read(args, "(I10)") ny
        call getarg(3, args)
        read(args, "(I10)") nz
    end if

    n = nx * ny * nz
    allocate(a(n), a_out(n))
    call init(a, n)
    print*, "before FFT a"
    call dump(a, n)

    a_in = a(n)
    plan = fftw_plan_dft_3d(nx, ny, nz, a, a_out, FFTW_FORWARD, FFTW_ESTIMATE)
   call fftw_execute_dft(plan, a, a_out)
    call fftw_destroy_plan(plan)
    print*, "after forward a_out"
    call dump(a_out, n)
    plan = fftw_plan_dft_3d(nx, ny, nz, a_out, a, FFTW_BACKWARD, FFTW_ESTIMATE)
   call fftw_execute_dft(plan, a_out, a)
#ifdef FFTW
    a = a/n
#endif
    print*, "after backrward a"
    call dump(a, n)
    call fftw_destroy_plan(plan)
    call getarg(0, args)
    read(args, "(A20)") exe

    if (abs(real(a_in) - real(a(n))) < errtol) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if

    stop

end program test3d
