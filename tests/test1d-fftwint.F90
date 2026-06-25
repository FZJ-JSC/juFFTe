! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

program test1d
    use, intrinsic :: iso_c_binding
    use juffte
    use test_utils_m
    implicit none
    
    complex(real64),allocatable    :: a(:), a_out(:)
    integer                   :: N, num_args
    complex(real64)                :: a_in
    character(len=100)        :: args
    character(len=20)         :: exe
    type(C_PTR)               :: plan

    num_args = command_argument_count()
    if (num_args < 1) then

        write(6, *) " n ="
        read(5, *) n
    else
        call getarg(1, args)
        read(args, "(I10)") n
    end if

    allocate(a(n), a_out(n),)
    call init(a, n)
    print*, "before FFT a"
    call dump(a, n)

    a_in = a(n)
    plan = fftw_plan_dft_1d(N, a, a_out, FFTW_FORWARD, FFTW_ESTIMATE)
   call fftw_execute_dft(plan, a, a_out)
    print*, "after forward a_out"  
    call dump(a_out, n)
    plan = fftw_plan_dft_1d( N, a, a_out, FFTW_BACKWARD, FFTW_ESTIMATE)
   call fftw_execute_dft(plan, a_out, a)
    print*, "after backrward a"
    call dump(a, n)
    !call dfftw_destroy_plan(plan)
    call getarg(0, args)
    read(args, "(A20)") exe

    if (abs(real(a_in) - real(a(n))) < errtol) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if

    stop

end program test1d
