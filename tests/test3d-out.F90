! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

program test3d_out

    use juffte
    use test_utils_m

    implicit none

    complex(real64), allocatable :: a(:), a_out(:)
    integer                      :: nx, ny, nz, num_args
    character(len=100)           :: args
    character(len=20)            :: exe
    complex(real64)              :: a_in

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
        call getarg(2, args)
        read(args, "(I10)") nz
    end if

    allocate(a(nx*ny*nz), a_out(nx*ny*nz))
    call init(a, nx*ny*nz)
    print*, "before FFT a"
    call dump(a, nx*ny*nz)

    a_in = a(nx*ny*nz)
    call zfft3d(a, nx, ny, nz, juffte_init, a_out)

    call zfft3d(a, nx, ny, nz, juffte_fw, a_out)

    print*, "After FFT fw a_out"
    call dump(a_out, nx*ny*nz)

    call zfft3d(a_out, nx, ny, nz, juffte_bw, a)

    print*, "after bw a"
    call dump(a, nx*ny*nz)

    call getarg(0, args)
    read(args, "(A15)") exe

    if (abs(real(a_in) - real(a(nx*ny*nz))) < errtol) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if

    stop

end program test3d_out