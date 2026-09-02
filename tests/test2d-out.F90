! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

program test2d_out

    use juffte
    use test_utils_m

    implicit none

    complex(real64), allocatable :: a(:), a_out(:)
    integer                      :: nx, ny, num_args
    character(len=100)           :: args
    character(len=20)            :: exe
    complex(real64)              :: a_in

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

    allocate(a(nx*ny), a_out(nx*ny))
    call init(a, nx*ny)
    print*, "before FFT a"
    call dump(a, nx*ny)

    a_in = a(nx*ny)
    call zfft2d(a, nx, ny, juffte_init, a_out)

    call zfft2d(a, nx, ny, juffte_fw, a_out)

    print*, "After FFT fw a_out"
    call dump(a_out, nx*ny)

    call zfft2d(a_out, nx, ny, juffte_bw, a)

    print*, "after bw a"
    call dump(a, nx*ny)

    call getarg(0, args)
    read(args, "(A15)") exe

    if (abs(real(a_in) - real(a(nx*ny))) < errtol) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if

    stop

end program test2d_out