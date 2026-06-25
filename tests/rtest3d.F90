! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

program rtest3d

    use juffte
    use test_utils_m
    implicit none

    real(real64), allocatable    :: a(:)
    complex(real64), allocatable :: a_c(:)
    real(real32), allocatable    :: a_r32(:)
    complex(real32), allocatable :: a_c_r32(:)
    real(real64)                 :: a_in
    real(real32)                 :: a_in_r32
    integer                      :: nx, ny, nz, num_args
    character(len=100)           :: args
    character(len=20)            :: exe

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

allocate (a(nx*ny*nz), a_c(nx*ny*nz))

    write(6, *) " "
    write(6, *) " Running FP64 test..."
    write(6, *) " "

    print*, "a before FFT."
    call init(a, nx*ny*nz)
    call dump(a, nx*ny*nz)
    a_in = a(nx*ny*nz)
    call dzfft3d(a, a_c, nx, ny, nz, juffte_init)
    call dzfft3d(a, a_c, nx, ny, nz, juffte_fw)

    print*, "a_c after fw FFT."
    call dump(a_c, (nx/2 + 1)*ny*nz)

    call zdfft3d(a_c, a, nx, ny, nz, juffte_init)
    call zdfft3d(a_c, a, nx, ny, nz, juffte_bw)

    print*, "a after bw FFT."
    call dump(a, nx*ny*nz)

    call getarg(0, args)
    read(args, "(A20)") exe

    if (abs(a_in - a(nx*ny*nz)) < errtol) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if

   deallocate (a, a_c)

   allocate (a_r32(nx*ny*nz), a_c_r32(nx*ny*nz))

    write(6, *) " "
    write(6, *) " Running FP32 test..."
    write(6, *) " "

    print*, "a_r32 before FFT."
    call init(a_r32, nx*ny*nz)
    call dump(a_r32, nx*ny*nz)
    a_in_r32 = a_r32(nx*ny*nz)
    call dzfft3d(a_r32, a_c_r32, nx, ny, nz, juffte_init)
    call dzfft3d(a_r32, a_c_r32, nx, ny, nz, juffte_fw)

    print*, "a_c_r32 after fw FFT."
    call dump(a_c_r32, (nx/2 + 1)*ny*nz)

    call zdfft3d(a_c_r32, a_r32, nx, ny, nz, juffte_init)
    call zdfft3d(a_c_r32, a_r32, nx, ny, nz, juffte_bw)

    print*, "a_r32 after bw FFT."
    call dump(a_r32, nx*ny*nz)

    call getarg(0, args)
    read(args, "(A20)") exe

    if (abs(a_in_r32 - a_r32(nx*ny*nz)) < errtol_r32) then
        print *, exe, "PASS"

    else
        print *, exe, "FAIL"
        stop 1
    end if
    deallocate (a_r32, a_c_r32)
    stop

end program rtest3d