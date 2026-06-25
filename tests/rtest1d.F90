! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

program rtest1d

    use juffte
    use test_utils_m 
    implicit none

    real(real64), allocatable    :: a(:)
    complex(real64), allocatable :: a_c(:)
    real(real32), allocatable    :: a_r32(:)
    complex(real32), allocatable :: a_c_r32(:)
    real(real64)                 :: a_in
    real(real32)                 :: a_in_r32
    integer                      :: n, num_args
    character(len=100)           :: args
    character(len=20)            :: exe

    num_args = command_argument_count()
    if (num_args < 1) then

        write(6, *) " N ="
        read(5, *) n
    else
        call getarg(1, args)
        read(args, "(I10)") n
    end if

allocate (a(n), a_c(n))

    write(6, *) " "
    write(6, *) " Running FP64 test..."
    write(6, *) " "

    print*, "a befor FFT."
    call init(a, n)
    call dump(a, n)
    a_in = a(n)
    call dzfft1d(a, a_c, n, juffte_init)
    call dzfft1d(a, a_c, n, juffte_fw)

    print*, "a_c after fw FFT."
    call dump(a_c, (n/2 + 1))

    call zdfft1d(a_c, a, n, juffte_init)
    call zdfft1d(a_c, a, n, juffte_bw)

    print*, "a after bw FFT."
    call dump(a, n)

    call getarg(0, args)
    read(args, "(A15)") exe

    if (abs(a_in - a(n)) < errtol) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if

   deallocate (a, a_c)

   allocate (a_r32(n), a_c_r32(n))

    write(6, *) " "
    write(6, *) " Running FP32 test..."
    write(6, *) " "

    print*, "a_r32 befor FFT."
    call init(a_r32, n)
    call dump(a_r32, n)
    a_in_r32 = a_r32(n)
    call dzfft1d(a_r32, a_c_r32, n, juffte_init)
    call dzfft1d(a_r32, a_c_r32, n, juffte_fw)

    print*, "a_c_r32 after fw FFT."
    call dump(a_c_r32, (n/2 + 1))

    call zdfft1d(a_c_r32, a_r32, n, juffte_init)
    call zdfft1d(a_c_r32, a_r32, n, juffte_bw)

    print*, "a_r32 after bw FFT."
    call dump(a_r32, n)

    call getarg(0, args)
    read(args, "(A15)") exe

    if (abs(a_in_r32 - a_r32(n)) < errtol_r32) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if 
    deallocate (a_r32, a_c_r32)
    stop

end program rtest1d
