! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

program test1d

    use juffte
    use test_utils_m
    
    implicit none

    complex(real64), allocatable   :: a(:), output(:)
    integer            :: n, num_args
    complex(real64)         :: a_in
    character(len=100) :: args
    character(len=20)  :: exe

    num_args = command_argument_count()
    if (num_args < 1) then

        write(6, *) " n ="
        read(5, *) n
    else
        call getarg(1, args)
        read(args, "(I10)") n
    end if

    allocate (a(n),output(n))

    call init(a, n)
    call dump(a, n)
    a_in = a(n)
    
    call fft_init(a)

    call fft_execute(a, juffte_fw)
    
    call dump(a, n)

    call fft_execute(a, juffte_bw)

    call dump(a, n)

    call getarg(0, args)
    read(args, "(A15)") exe

    if (abs(real(a_in) - real(a(n))) < 0.00001) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if

    stop

end program test1d
