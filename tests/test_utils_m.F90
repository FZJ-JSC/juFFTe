! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module test_utils_m
use, intrinsic :: iso_fortran_env
implicit none

private
public :: init, dump, roundtrip_check

    ! Checks a forward + backward round trip x -> xhat over the whole array, against
    ! the rounding-error bound  ||x - xhat||_2 <= 2 log2(n) eps ||x||_2.
    interface roundtrip_check
        module procedure :: roundtrip_check_c32
        module procedure :: roundtrip_check_c64
        module procedure :: roundtrip_check_r32
        module procedure :: roundtrip_check_r64
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

    logical function roundtrip_check_c32(x, xhat, n)
        complex(real32), intent(in) :: x(:), xhat(:)
        integer, intent(in)         :: n
        roundtrip_check_c32 = report(real(norm2(abs(x(1:n) - xhat(1:n))) / norm2(abs(x(1:n))), real64), &
                                     real(epsilon(1.0_real32), real64), n)
    end function roundtrip_check_c32

    logical function roundtrip_check_c64(x, xhat, n)
        complex(real64), intent(in) :: x(:), xhat(:)
        integer, intent(in)         :: n
        roundtrip_check_c64 = report(norm2(abs(x(1:n) - xhat(1:n))) / norm2(abs(x(1:n))), &
                                     epsilon(1.0_real64), n)
    end function roundtrip_check_c64

    logical function roundtrip_check_r32(x, xhat, n)
        real(real32), intent(in) :: x(:), xhat(:)
        integer, intent(in)      :: n
        roundtrip_check_r32 = report(real(norm2(x(1:n) - xhat(1:n)) / norm2(x(1:n)), real64), &
                                     real(epsilon(1.0_real32), real64), n)
    end function roundtrip_check_r32

    logical function roundtrip_check_r64(x, xhat, n)
        real(real64), intent(in) :: x(:), xhat(:)
        integer, intent(in)      :: n
        roundtrip_check_r64 = report(norm2(x(1:n) - xhat(1:n)) / norm2(x(1:n)), &
                                     epsilon(1.0_real64), n)
    end function roundtrip_check_r64

    logical function report(err, eps, n)
        real(real64), intent(in) :: err, eps
        integer, intent(in)      :: n
        real(real64)             :: bound
        bound = 2.0_real64 * log(real(n, real64)) / log(2.0_real64) * eps
        print '(a,es10.3,a,es10.3)', '  relative 2-norm error ', err, '   bound 2 log2(n) eps ', bound
        report = err <= bound
    end function report

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
