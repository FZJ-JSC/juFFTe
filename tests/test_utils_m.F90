! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module test_utils_m
use, intrinsic :: iso_fortran_env
implicit none

    integer, parameter :: tollconst = 10

private
public :: init, dump, geterrtol

    interface geterrtol
        module procedure :: geterrtol_r32
        module procedure :: geterrtol_r64
    end interface


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

    real(real32) function geterrtol_r32(r, n)
        real(real32) :: r
        integer      :: n

        geterrtol_r32 = real(tollconst, real32) * epsilon(r) * (log(real(n, real32))/ log(2.0_real32))
    
    end function geterrtol_r32
    
    real(real64) function geterrtol_r64(r, n)
        real(real64) :: r
        integer      :: n

        geterrtol_r64 = real(tollconst, real64) * epsilon(r) * (log(real(n, real64))/ log(2.0_real64))
    
    end function geterrtol_r64

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
