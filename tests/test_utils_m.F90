! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module test_utils_m
use, intrinsic :: iso_fortran_env
implicit none
real(real64), parameter :: errtol = 0.00001
real(real32), parameter :: errtol_r32 = 0.0001

private
public :: init, dump, errtol, errtol_r32


    interface init
        module procedure :: init_r32
        module procedure :: init_r64
        module procedure :: init_r_r32
        module procedure :: init_r_r64
    end interface

    interface dump
        module procedure :: dump_r32
        module procedure :: dump_r64
        module procedure :: dump_r_r32
        module procedure :: dump_r_r64      
    end interface

contains

    subroutine init_r32(a, n)
        complex(real32), intent(inout), contiguous :: a(:)
        integer, intent(in) :: n
        integer :: i

!$OMP PARALLEL DO SIMD
!DIR$ VECTOR ALIGNED
        do i = 1, n
            a(i) = cmplx(real(i,real32), real(n-i+1,real32), kind=real32)
        end do
    end subroutine init_r32

    subroutine init_r64(a, n)
        real(real64), intent(inout), contiguous :: a(:)
        integer, intent(in) :: n
        integer :: i

!$OMP PARALLEL DO SIMD
!DIR$ VECTOR ALIGNED
        do i = 1, n
            a(i) = dble(i)
        end do
    end subroutine init_r64

    subroutine init_r_r32(a, n)
        real(real32), intent(inout), contiguous :: a(:)
        integer, intent(in) :: n
        integer :: i

!$OMP PARALLEL DO SIMD
!DIR$ VECTOR ALIGNED
        do i = 1, n
            a(i) = real(i)
        end do
    end subroutine init_r_r32

    subroutine init_r_r64(a, n)
        complex(real64), intent(inout), contiguous :: a(:)
        integer, intent(in) :: n
        integer :: i

!$OMP PARALLEL DO SIMD
!DIR$ VECTOR ALIGNED
        do i = 1, n
            a(i) = cmplx(real(i,real64), real(n-i+1,real64), kind=real64)
        end do
    end subroutine init_r_r64

    subroutine dump_r32(a, n)
        complex(real32), intent(in) :: a(*)
        integer, intent(in) :: n
        integer :: i

        do i = 1, n
            write(*,*) i, a(i)
        end do
    end subroutine dump_r32

    subroutine dump_r64(a, n)

        complex(real64), intent(in) :: a(*)
        integer, intent(in) :: n
        integer :: i

        do i = 1, n
            write(*,*) i, a(i)
        end do
    end subroutine dump_r64

    subroutine dump_r_r32(a, n)
        real(real32), intent(in) :: a(*)
        integer, intent(in) :: n
        integer :: i

        do i = 1, n
            write(*,*) i, a(i)
        end do
    end subroutine dump_r_r32

    subroutine dump_r_r64(a, n)

        real(real64), intent(in) :: a(*)
        integer, intent(in) :: n
        integer :: i

        do i = 1, n
            write(*,*) i, a(i)
        end do
    end subroutine dump_r_r64

end module test_utils_m
