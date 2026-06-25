! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

program test2d

    use juffte
    use test_utils_m

    implicit none

    complex(real64),allocatable :: a(:)
    complex(real32),allocatable :: a_32(:)
    complex(real64)             :: a_in
    complex(real32)             :: a_32_in
    integer                     :: nx, ny, num_args
    character(len=100)          :: args
    character(len=20)           :: exe

    num_args = command_argument_count()
    if (num_args < 2) then

        write(6, *) " nx ="
        read(5, *) nx
        write(6, *) " ny ="
        read(5, *) ny
    else
        call getarg(1, args)
        read(args, "(I10)") nx
        call getarg(2, args)
        read(args, "(I10)") ny

    end if

    write(6, *) " "
    write(6, *) " Running FP64 test..."
    write(6, *) " "

    allocate(a(nx*ny))
    call init(a, nx*ny)
    call dump(a, nx*ny)
    call zfft2d(a, nx, ny, juffte_init)
    a_in = a(nx*ny)

    call zfft2d(a, nx, ny, juffte_fw)
    call dump(a, nx*ny)

    call zfft2d(a, nx, ny, juffte_bw)
    call dump(a, nx*ny)

    call getarg(0, args)
    read(args, "(A10)") exe

    if (abs(dble(a_in) - dble(a(nx*ny))) < errtol) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if

    deallocate(a)

    write(6, *) " "
    write(6, *) " Running FP32 test..."
    write(6, *) " "

    allocate(a_32(nx*ny))
    call init(a_32, nx*ny)
    call dump(a_32, nx*ny)
    call zfft2d(a_32, nx, ny, juffte_init)
    a_32_in = a_32(nx*ny)

    call zfft2d(a_32, nx, ny, juffte_fw)
    call dump(a_32, nx*ny)

    call zfft2d(a_32, nx, ny, juffte_bw)
    call dump(a_32, nx*ny)


    if (abs(real(a_32_in) - real(a_32(nx*ny))) < errtol_r32) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if

    deallocate(a_32)

    stop

end program test2d