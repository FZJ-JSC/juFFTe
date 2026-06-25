! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

program test3d

    use juffte
    use test_utils_m

    implicit none
    complex(real64), allocatable :: a(:)
    complex(real32), allocatable :: a_32(:)
    complex(real64) :: a_in
    complex(real32) :: a_32_in
    integer :: nx, ny, nz, num_args
    character(len=100) :: args
    character(len=20) :: exe


    num_args = command_argument_count()
    if (num_args < 3) then

        write(6, *) " NX ="
        read(5, *) nx
        write(6, *) " NY ="
        read(5, *) ny
        write(6, *) " NZ ="
        read(5, *) nz
    else
        call getarg(1, args)
        read(args, "(I10)") nx
        call getarg(2, args)
        read(args, "(I10)") ny
        call getarg(3, args)
        read(args, "(I10)") nz

    end if

    write(6, *) " "
    write(6, *) " Running FP64 test..."
    write(6, *) " "

    allocate(a(nx*ny*nz))
    call init(a, nx*ny*nz)
    call dump(a, nx*ny*nz)
    call zfft3d(a, nx, ny, nz, juffte_init)
    a_in = a(nx*ny*nz)

    call zfft3d(a, nx, ny, nz, juffte_fw)
    call dump(a, nx*ny*nz)

    call zfft3d(a, nx, ny, nz, juffte_bw)
    call dump(a, nx*ny*nz)

    call getarg(0, args)
    read(args, "(A10)") exe

    if (abs(dble(a_in) - dble(a(nx*ny*nz))) < errtol) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if

    deallocate(a)

    write(6, *) " "
    write(6, *) " Running FP32 test..."
    write(6, *) " "

    allocate(a_32(nx*ny*nz))
    call init(a_32, nx*ny*nz)
    call dump(a_32, nx*ny*nz)
    call zfft3d(a_32, nx, ny, nz, juffte_init)
    a_32_in = a_32(nx*ny*nz)

    call zfft3d(a_32, nx, ny, nz, juffte_fw)
    call dump(a_32, nx*ny*nz)

    call zfft3d(a_32, nx, ny, nz, juffte_bw)
    call dump(a_32, nx*ny*nz)


    if (abs(real(a_32_in) - real(a_32(nx*ny*nz))) < errtol_r32) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if

    deallocate(a_32)

    stop

end program test3d