! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

program test1d

    use juffte
    use test_utils_m
    implicit none

    complex(real64), allocatable    :: a(:)
    complex(real32), allocatable    :: a_32(:)
    integer            :: N, num_args
    complex(real64)         :: a_in
    complex(real32)         :: a_32_in
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

    write(6, *) " "
    write(6, *) " Running FP64 test..."
    write(6, *) " "

    allocate(a(n))

    call init(a, n)
    call dump(a, n)
    a_in = a(n)
    call zfft1d(a, n, juffte_init)

    call zfft1d(a, n, juffte_fw)
    call dump(a, n)

    call zfft1d(a, n, juffte_bw)
    call dump(a, n)

    call getarg(0, args)
    read(args, "(A10)") exe

    if (abs(dble(a_in) - dble(a(n))) < errtol) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if

    deallocate(a)

    write(6, *) " "
    write(6, *) " Running FP32 test..."
    write(6, *) " "

    allocate(a_32(n))

    call init(a_32, n)
    call dump(a_32, n)
    a_32_in = a_32(n)
    call zfft1d(a_32, n, juffte_init)

    call zfft1d(a_32, n, juffte_fw)
    call dump(a_32, n)

    call zfft1d(a_32, n, juffte_bw)
    call dump(a_32, n)


    if (abs(real(a_32_in) - real(a_32(n))) < errtol_r32) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if

    deallocate(a_32)
    
    stop
end program test1d
