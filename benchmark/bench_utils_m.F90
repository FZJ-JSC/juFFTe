! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module bench_utils_m
use, intrinsic :: iso_fortran_env
    implicit none

    integer :: dim = 1
    integer, allocatable :: size(:)
    character(len=32) :: fft_type = "c2c"

    interface init
        module procedure init_r
        module procedure init_c
    end interface

contains

    subroutine parse_args()
        implicit none

        integer :: i, j, nargs, nsize
        integer, allocatable :: tmp_size(:)
        character(len=256) :: arg

        nargs = command_argument_count()

        ! No arguments → defaults + help
        if (nargs == 0) then
            allocate(size(1))
            size(1) = 256
            call print_help()
            return
        end if

        allocate(tmp_size(nargs))
        nsize = 0
        i = 1

        do while (i <= nargs)
            call get_command_argument(i, arg)

            select case (trim(arg))

            case ("-h", "--help")
                call print_help()
                stop 0

            case ("-dim")
                call require_value(i, nargs, "-dim")
                call get_command_argument(i+1, arg)
                read(arg, *) dim
                i = i + 2

            case ("-type")
                call require_value(i, nargs, "-type")
                call get_command_argument(i+1, arg)
                fft_type = trim(arg)
                i = i + 2

            case ("-size")
                j = i + 1
                do while (j <= nargs)
                    call get_command_argument(j, arg)
                    if (arg(1:1) == "-") exit
                    nsize = nsize + 1
                    read(arg, *) tmp_size(nsize)
                    j = j + 1
                end do
                i = j

            case default
                print *, "Warning: unknown argument:", trim(arg)
                i = i + 1
            end select
        end do

        call finalize_sizes(tmp_size, nsize)
        deallocate(tmp_size)

    end subroutine parse_args


    subroutine finalize_sizes(tmp_size, nsize)
        implicit none
        integer, intent(in) :: tmp_size(:)
        integer, intent(in) :: nsize
        integer :: k

        if (dim <= 0) then
            print *, "Error: dim must be > 0"
            stop 1
        end if

        allocate(size(dim))

        ! No -size → default
        if (nsize == 0) then
            size = 256
            return
        end if

        if (nsize > dim) then
            print *, "Error: too many size values (expected", dim, ")"
            stop 1
        end if

        ! Copy provided sizes
        do k = 1, nsize
            if (tmp_size(k) <= 0) then
                print *, "Error: size values must be > 0"
                stop 1
            end if
            size(k) = tmp_size(k)
        end do

        ! Repeat last value if needed
        if (nsize < dim) then
            size(nsize+1:dim) = tmp_size(nsize)
        end if

    end subroutine finalize_sizes


    subroutine require_value(i, nargs, opt)
        implicit none
        integer, intent(in) :: i, nargs
        character(len=*), intent(in) :: opt

        if (i + 1 > nargs) then
            print *, "Error:", trim(opt), "requires a value"
            stop 1
        end if
    end subroutine require_value


    subroutine print_help()
        implicit none

        print *, ""
        print *, "Usage: ./fftbench [options]"
        print *, ""
        print *, "Options:"
        print *, "  -dim N           Number of dimensions (default: 1)"
        print *, "  -size s1 [s2..]  Size per dimension (default: 256)"
        print *, "                   auto-filled"
        print *, "  -type TYPE       FFT type: c2c, r2c (default: c2c)"
        print *, "  -h, --help       Print this help"
        print *, ""
        print *, "Size rules:"
        print *, "  -dim 3 -size 128        -> 128 128 128"
        print *, "  -dim 3 -size 64 128     -> 64 128 128"
        print *, ""
        print *, "Example:"
        print *, "  ./fftbench -dim 3 -size 64 128 -type r2c"
        print *, ""
    end subroutine print_help

    subroutine init_c(a, n)
        implicit none
        complex(real64), intent(inout) :: a(:)
        integer, intent(in) :: n
        integer :: i

!$OMP PARALLEL DO SIMD
!DIR$ VECTOR ALIGNED
        do i = 1, n
            a(i) = dcmplx(dble(i), dble(n - i + 1))
        end do
        return
    end subroutine init_c
    
    subroutine init_r(a, n)
        implicit none
        real(real64), intent(inout) :: a(:)
        integer, intent(in) :: n
        integer :: i

!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
        do i = 1, n
            a(i) = dble(i)
        end do
        return
    end subroutine init_r
end module bench_utils_m
