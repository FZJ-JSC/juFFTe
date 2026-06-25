! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module kernel_m

use, intrinsic :: iso_fortran_env
implicit none

private
public :: fft2, fft2_r32, fft3a, fft3a_r32, fft3b, fft3b_r32
public :: fft4a, fft4a_r32, fft4b, fft4b_r32
public :: fft5a, fft5a_r32, fft5b, fft5b_r32
public :: fft8a, fft8a_r32, fft8b, fft8b_r32

contains

subroutine fft2(a, b, m)
    implicit none
    complex(real64), intent(inout) :: a(m,*), b(m,*)
    integer, intent(in) :: m
    complex(real64) :: c0, c1
    integer :: i

!DIR$ VECTOR ALIGNED
    do i = 1, m
        c0 = a(i, 1)
        c1 = a(i, 2)
        b(i, 1) = c0 + c1
        b(i, 2) = c0 - c1
    end do
    return
end subroutine fft2

subroutine fft3a(a, b, w, l)
    implicit none
    complex(real64), intent(inout) :: a(l,*), b(3,*), w(2,*)
    integer, intent(in) :: l
    complex(real64) :: c0, c1, c2, d0, d1, d2, w1, w2
    real(real64), parameter :: c31 = 0.86602540378443865d0, c32 = 0.5d0
    integer :: j

!DIR$ VECTOR ALIGNED
    do j = 1, l
        w1 = w(1, j)
        w2 = w(2, j)
        c0 = a(j, 1)
        c1 = a(j, 2)
        c2 = a(j, 3)
        d0 = c1 + c2
        d1 = c0 - c32*d0
        d2 = (0.0d0, -1.0d0)*c31*(c1 - c2)
        b(1, j) = c0 + d0
        b(2, j) = w1*(d1 + d2)
        b(3, j) = w2*(d1 - d2)
    end do
    return
end subroutine fft3a


subroutine fft3b(a, b, w, m, l)
    implicit none
    complex(real64), intent(inout) :: a(m,l,*), b(m,3,*), w(2,*)
    integer, intent(in) :: l
    complex(real64) :: c0, c1, c2, d0, d1, d2, w1, w2
    real, parameter :: c31 = 0.86602540378443865d0, c32 = 0.5d0
    integer :: i, m, j

!DIR$ VECTOR ALIGNED
    do i = 1, m
        c0 = a(i, 1, 1)
        c1 = a(i, 1, 2)
        c2 = a(i, 1, 3)
        d0 = c1 + c2
        d1 = c0 - c32*d0
        d2 = (0.0d0, -1.0d0)*c31*(c1 - c2)
        b(i, 1, 1) = c0 + d0
        b(i, 2, 1) = d1 + d2
        b(i, 3, 1) = d1 - d2
    end do
    do j = 2, l
        w1 = w(1, j)
        w2 = w(2, j)
!DIR$ VECTOR ALIGNED
        do i = 1, m
            c0 = a(i, j, 1)
            c1 = a(i, j, 2)
            c2 = a(i, j, 3)
            d0 = c1 + c2
            d1 = c0 - c32*d0
            d2 = (0.0d0, -1.0d0)*c31*(c1 - c2)
            b(i, 1, j) = c0 + d0
            b(i, 2, j) = w1*(d1 + d2)
            b(i, 3, j) = w2*(d1 - d2)
        end do
    end do
    return
end subroutine fft3b

subroutine fft4a(a, b, w, l)
    implicit none
    complex(real64), intent(inout) :: a(l,*), b(4,*), w(3,*)
    integer, intent(in) :: l
    complex(real64) :: c0, c1, c2, c3, d0, d1, d2, d3, w1, w2, w3
    integer :: j

!DIR$ VECTOR ALIGNED
    do j = 1, l
        w1 = w(1, j)
        w2 = w(2, j)
        w3 = w(3, j)
        c0 = a(j, 1)
        c1 = a(j, 2)
        c2 = a(j, 3)
        c3 = a(j, 4)
        d0 = c0 + c2
        d1 = c0 - c2
        d2 = c1 + c3
        d3 = (0.0d0, -1.0d0)*(c1 - c3)
        b(1, j) = d0 + d2
        b(2, j) = w1*(d1 + d3)
        b(3, j) = w2*(d0 - d2)
        b(4, j) = w3*(d1 - d3)
    end do
    return
end subroutine fft4a

subroutine fft4b(a, b, w, m, l)
    implicit none
    complex(real64), intent(inout) :: a(m,l,*), b(m,4,*), w(3,*)
    integer, intent(in) :: m, l
    complex(real64) :: c0, c1, c2, c3, d0, d1, d2, d3, w1, w2, w3
    integer :: i, j

!DIR$ VECTOR ALIGNED
    do i = 1, m
        c0 = a(i, 1, 1)
        c1 = a(i, 1, 2)
        c2 = a(i, 1, 3)
        c3 = a(i, 1, 4)
        d0 = c0 + c2
        d1 = c0 - c2
        d2 = c1 + c3
        d3 = (0.0d0, -1.0d0)*(c1 - c3)
        b(i, 1, 1) = d0 + d2
        b(i, 2, 1) = d1 + d3
        b(i, 3, 1) = d0 - d2
        b(i, 4, 1) = d1 - d3
    end do
    do j = 2, l
        w1 = w(1, j)
        w2 = w(2, j)
        w3 = w(3, j)
!DIR$ VECTOR ALIGNED
        do i = 1, m
            c0 = a(i, j, 1)
            c1 = a(i, j, 2)
            c2 = a(i, j, 3)
            c3 = a(i, j, 4)
            d0 = c0 + c2
            d1 = c0 - c2
            d2 = c1 + c3
            d3 = (0.0d0, -1.0d0)*(c1 - c3)
            b(i, 1, j) = d0 + d2
            b(i, 2, j) = w1*(d1 + d3)
            b(i, 3, j) = w2*(d0 - d2)
            b(i, 4, j) = w3*(d1 - d3)
        end do
    end do
    return
end subroutine fft4b

subroutine fft5a(a, b, w, l)
    implicit none

    complex(real64), intent(inout) :: a(l,*), b(5,*), w(4,*)
    integer, intent(in) :: l
    complex(real64) :: c0, c1, c2, c3, c4, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10
    complex(real64) :: w1, w2, w3, w4
    real(real64) :: c51 = 0.95105651629515357d0, c52 = 0.61803398874989485d0
    real(real64) :: c53 = 0.55901699437494742d0, c54 = 0.25d0
    integer :: j

!DIR$ VECTOR ALIGNED
    do j = 1, l
        w1 = w(1, j)
        w2 = w(2, j)
        w3 = w(3, j)
        w4 = w(4, j)
        c0 = a(j, 1)
        c1 = a(j, 2)
        c2 = a(j, 3)
        c3 = a(j, 4)
        c4 = a(j, 5)
        d0 = c1 + c4
        d1 = c2 + c3
        d2 = c51*(c1 - c4)
        d3 = c51*(c2 - c3)
        d4 = d0 + d1
        d5 = c53*(d0 - d1)
        d6 = c0 - c54*d4
        d7 = d6 + d5
        d8 = d6 - d5
        d9 = (0.0d0, -1.0d0)*(d2 + c52*d3)
        d10 = (0.0d0, -1.0d0)*(c52*d2 - d3)
        b(1, j) = c0 + d4
        b(2, j) = w1*(d7 + d9)
        b(3, j) = w2*(d8 + d10)
        b(4, j) = w3*(d8 - d10)
        b(5, j) = w4*(d7 - d9)
    end do
    return
end subroutine fft5a


subroutine fft5b(a, b, w, m, l)
    implicit none
    complex(real64), intent(inout) :: a(m,l,*), b(m,5,*), w(4,*)
    integer, intent(in) :: m, l
    complex(real64) :: c0, c1, c2, c3, c4, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10
    complex(real64) :: w1, w2, w3, w4
    real(real64) :: c51 = 0.95105651629515357d0, c52 = 0.61803398874989485d0
    real(real64) :: c53 = 0.55901699437494742d0, c54 = 0.25d0
    integer :: i, j

!DIR$ VECTOR ALIGNED
    do i = 1, m
        c0 = a(i, 1, 1)
        c1 = a(i, 1, 2)
        c2 = a(i, 1, 3)
        c3 = a(i, 1, 4)
        c4 = a(i, 1, 5)
        d0 = c1 + c4
        d1 = c2 + c3
        d2 = c51*(c1 - c4)
        d3 = c51*(c2 - c3)
        d4 = d0 + d1
        d5 = c53*(d0 - d1)
        d6 = c0 - c54*d4
        d7 = d6 + d5
        d8 = d6 - d5
        d9 = (0.0d0, -1.0d0)*(d2 + c52*d3)
        d10 = (0.0d0, -1.0d0)*(c52*d2 - d3)
        b(i, 1, 1) = c0 + d4
        b(i, 2, 1) = d7 + d9
        b(i, 3, 1) = d8 + d10
        b(i, 4, 1) = d8 - d10
        b(i, 5, 1) = d7 - d9
    end do
    do j = 2, l
        w1 = w(1, j)
        w2 = w(2, j)
        w3 = w(3, j)
        w4 = w(4, j)
!DIR$ VECTOR ALIGNED
        do i = 1, m
            c0 = a(i, j, 1)
            c1 = a(i, j, 2)
            c2 = a(i, j, 3)
            c3 = a(i, j, 4)
            c4 = a(i, j, 5)
            d0 = c1 + c4
            d1 = c2 + c3
            d2 = c51*(c1 - c4)
            d3 = c51*(c2 - c3)
            d4 = d0 + d1
            d5 = c53*(d0 - d1)
            d6 = c0 - c54*d4
            d7 = d6 + d5
            d8 = d6 - d5
            d9 = (0.0d0, -1.0d0)*(d2 + c52*d3)
            d10 = (0.0d0, -1.0d0)*(c52*d2 - d3)
            b(i, 1, j) = c0 + d4
            b(i, 2, j) = w1*(d7 + d9)
            b(i, 3, j) = w2*(d8 + d10)
            b(i, 4, j) = w3*(d8 - d10)
            b(i, 5, j) = w4*(d7 - d9)
        end do
    end do
    return
end subroutine fft5b


subroutine fft8a(a, b, w, l)
    implicit none
    complex(real64), intent(inout) :: a(l,*), b(8,*), w(7,*)
    integer, intent(in) :: l
    complex(real64) :: c0, c1, c2, c3, c4, c5, c6, c7, d0, d1, d2, d3, d4, d5, d6, d7
    complex(real64) :: e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, w1, w2, w3, w4, w5, w6, w7
    real(real64) :: c81 = 0.70710678118654752d0
    integer :: j

!DIR$ VECTOR ALIGNED
    do j = 1, l
        w1 = w(1, j)
        w2 = w(2, j)
        w3 = w(3, j)
        w4 = w(4, j)
        w5 = w(5, j)
        w6 = w(6, j)
        w7 = w(7, j)
        c0 = a(j, 1)
        c1 = a(j, 2)
        c2 = a(j, 3)
        c3 = a(j, 4)
        c4 = a(j, 5)
        c5 = a(j, 6)
        c6 = a(j, 7)
        c7 = a(j, 8)
        d0 = c0 + c4
        d1 = c0 - c4
        d2 = c2 + c6
        d3 = (0.0d0, -1.0d0)*(c2 - c6)
        d4 = c1 + c5
        d5 = c1 - c5
        d6 = c3 + c7
        d7 = c3 - c7
        e0 = d0 + d2
        e1 = d0 - d2
        e2 = d4 + d6
        e3 = (0.0d0, -1.0d0)*(d4 - d6)
        e4 = c81*(d5 - d7)
        e5 = (0.0d0, -1.0d0)*c81*(d5 + d7)
        e6 = d1 + e4
        e7 = d1 - e4
        e8 = d3 + e5
        e9 = d3 - e5
        b(1, j) = e0 + e2
        b(2, j) = w1*(e6 + e8)
        b(3, j) = w2*(e1 + e3)
        b(4, j) = w3*(e7 - e9)
        b(5, j) = w4*(e0 - e2)
        b(6, j) = w5*(e7 + e9)
        b(7, j) = w6*(e1 - e3)
        b(8, j) = w7*(e6 - e8)
    end do
    return
end subroutine fft8a

subroutine fft8b(a, b, w, m, l)
    implicit none
    complex(real64), intent(inout) :: a(m,l,*), b(m,8,*), w(7,*)
    integer, intent(in) :: m, l
    complex(real64) :: c0, c1, c2, c3, c4, c5, c6, c7, d0, d1, d2, d3, d4, d5, d6, d7
    complex(real64) :: e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, w1, w2, w3, w4, w5, w6, w7
    real(real64) :: c81 = 0.70710678118654752d0
    integer :: i, j

!DIR$ VECTOR ALIGNED
    do i = 1, m
        c0 = a(i, 1, 1)
        c1 = a(i, 1, 2)
        c2 = a(i, 1, 3)
        c3 = a(i, 1, 4)
        c4 = a(i, 1, 5)
        c5 = a(i, 1, 6)
        c6 = a(i, 1, 7)
        c7 = a(i, 1, 8)
        d0 = c0 + c4
        d1 = c0 - c4
        d2 = c2 + c6
        d3 = (0.0d0, -1.0d0)*(c2 - c6)
        d4 = c1 + c5
        d5 = c1 - c5
        d6 = c3 + c7
        d7 = c3 - c7
        e0 = d0 + d2
        e1 = d0 - d2
        e2 = d4 + d6
        e3 = (0.0d0, -1.0d0)*(d4 - d6)
        e4 = c81*(d5 - d7)
        e5 = (0.0d0, -1.0d0)*c81*(d5 + d7)
        e6 = d1 + e4
        e7 = d1 - e4
        e8 = d3 + e5
        e9 = d3 - e5
        b(i, 1, 1) = e0 + e2
        b(i, 2, 1) = e6 + e8
        b(i, 3, 1) = e1 + e3
        b(i, 4, 1) = e7 - e9
        b(i, 5, 1) = e0 - e2
        b(i, 6, 1) = e7 + e9
        b(i, 7, 1) = e1 - e3
        b(i, 8, 1) = e6 - e8
    end do
    do j = 2, l
        w1 = w(1, j)
        w2 = w(2, j)
        w3 = w(3, j)
        w4 = w(4, j)
        w5 = w(5, j)
        w6 = w(6, j)
        w7 = w(7, j)
!DIR$ VECTOR ALIGNED
        do i = 1, m
            c0 = a(i, j, 1)
            c1 = a(i, j, 2)
            c2 = a(i, j, 3)
            c3 = a(i, j, 4)
            c4 = a(i, j, 5)
            c5 = a(i, j, 6)
            c6 = a(i, j, 7)
            c7 = a(i, j, 8)
            d0 = c0 + c4
            d1 = c0 - c4
            d2 = c2 + c6
            d3 = (0.0d0, -1.0d0)*(c2 - c6)
            d4 = c1 + c5
            d5 = c1 - c5
            d6 = c3 + c7
            d7 = c3 - c7
            e0 = d0 + d2
            e1 = d0 - d2
            e2 = d4 + d6
            e3 = (0.0d0, -1.0d0)*(d4 - d6)
            e4 = c81*(d5 - d7)
            e5 = (0.0d0, -1.0d0)*c81*(d5 + d7)
            e6 = d1 + e4
            e7 = d1 - e4
            e8 = d3 + e5
            e9 = d3 - e5
            b(i, 1, j) = e0 + e2
            b(i, 2, j) = w1*(e6 + e8)
            b(i, 3, j) = w2*(e1 + e3)
            b(i, 4, j) = w3*(e7 - e9)
            b(i, 5, j) = w4*(e0 - e2)
            b(i, 6, j) = w5*(e7 + e9)
            b(i, 7, j) = w6*(e1 - e3)
            b(i, 8, j) = w7*(e6 - e8)
        end do
    end do
    return
end subroutine fft8b

subroutine fft2_r32(a, b, m)
    implicit none
    complex(real32), intent(inout) :: a(m,*), b(m,*)
    integer, intent(in) :: m
    complex(real32) :: c0, c1
    integer :: i

!DIR$ VECTOR ALIGNED
    do i = 1, m
        c0 = a(i, 1)
        c1 = a(i, 2)
        b(i, 1) = c0 + c1
        b(i, 2) = c0 - c1
    end do
    return
end subroutine fft2_r32

subroutine fft3a_r32(a, b, w, l)
    implicit none
    complex(real32), intent(inout) :: a(l,*), b(3,*), w(2,*)
    integer, intent(in) :: l
    complex(real32) :: c0, c1, c2, d0, d1, d2, w1, w2
    real(real32), parameter :: c31 = 0.86602540378443865_real32, c32 = 0.5_real32
    integer :: j

!DIR$ VECTOR ALIGNED
    do j = 1, l
        w1 = w(1, j)
        w2 = w(2, j)
        c0 = a(j, 1)
        c1 = a(j, 2)
        c2 = a(j, 3)
        d0 = c1 + c2
        d1 = c0 - c32*d0
        d2 = (0.0_real32, -1.0_real32)*c31*(c1 - c2)
        b(1, j) = c0 + d0
        b(2, j) = w1*(d1 + d2)
        b(3, j) = w2*(d1 - d2)
    end do
    return
end subroutine fft3a_r32


subroutine fft3b_r32(a, b, w, m, l)
    implicit none
    complex(real32), intent(inout) :: a(m,l,*), b(m,3,*), w(2,*)
    integer, intent(in) :: l
    complex(real32) :: c0, c1, c2, d0, d1, d2, w1, w2
    real, parameter :: c31 = 0.86602540378443865_real32, c32 = 0.5_real32
    integer :: i, m, j

!DIR$ VECTOR ALIGNED
    do i = 1, m
        c0 = a(i, 1, 1)
        c1 = a(i, 1, 2)
        c2 = a(i, 1, 3)
        d0 = c1 + c2
        d1 = c0 - c32*d0
        d2 = (0.0_real32, -1.0_real32)*c31*(c1 - c2)
        b(i, 1, 1) = c0 + d0
        b(i, 2, 1) = d1 + d2
        b(i, 3, 1) = d1 - d2
    end do
    do j = 2, l
        w1 = w(1, j)
        w2 = w(2, j)
!DIR$ VECTOR ALIGNED
        do i = 1, m
            c0 = a(i, j, 1)
            c1 = a(i, j, 2)
            c2 = a(i, j, 3)
            d0 = c1 + c2
            d1 = c0 - c32*d0
            d2 = (0.0_real32, -1.0_real32)*c31*(c1 - c2)
            b(i, 1, j) = c0 + d0
            b(i, 2, j) = w1*(d1 + d2)
            b(i, 3, j) = w2*(d1 - d2)
        end do
    end do
    return
end subroutine fft3b_r32

subroutine fft4a_r32(a, b, w, l)
    implicit none
    complex(real32), intent(inout) :: a(l,*), b(4,*), w(3,*)
    integer, intent(in) :: l
    complex(real32) :: c0, c1, c2, c3, d0, d1, d2, d3, w1, w2, w3
    integer :: j

!DIR$ VECTOR ALIGNED
    do j = 1, l
        w1 = w(1, j)
        w2 = w(2, j)
        w3 = w(3, j)
        c0 = a(j, 1)
        c1 = a(j, 2)
        c2 = a(j, 3)
        c3 = a(j, 4)
        d0 = c0 + c2
        d1 = c0 - c2
        d2 = c1 + c3
        d3 = (0.0_real32, -1.0_real32)*(c1 - c3)
        b(1, j) = d0 + d2
        b(2, j) = w1*(d1 + d3)
        b(3, j) = w2*(d0 - d2)
        b(4, j) = w3*(d1 - d3)
    end do
    return
end subroutine fft4a_r32

subroutine fft4b_r32(a, b, w, m, l)
    implicit none
    complex(real32), intent(inout) :: a(m,l,*), b(m,4,*), w(3,*)
    integer, intent(in) :: m, l
    complex(real32) :: c0, c1, c2, c3, d0, d1, d2, d3, w1, w2, w3
    integer :: i, j

!DIR$ VECTOR ALIGNED
    do i = 1, m
        c0 = a(i, 1, 1)
        c1 = a(i, 1, 2)
        c2 = a(i, 1, 3)
        c3 = a(i, 1, 4)
        d0 = c0 + c2
        d1 = c0 - c2
        d2 = c1 + c3
        d3 = (0.0_real32, -1.0_real32)*(c1 - c3)
        b(i, 1, 1) = d0 + d2
        b(i, 2, 1) = d1 + d3
        b(i, 3, 1) = d0 - d2
        b(i, 4, 1) = d1 - d3
    end do
    do j = 2, l
        w1 = w(1, j)
        w2 = w(2, j)
        w3 = w(3, j)
!DIR$ VECTOR ALIGNED
        do i = 1, m
            c0 = a(i, j, 1)
            c1 = a(i, j, 2)
            c2 = a(i, j, 3)
            c3 = a(i, j, 4)
            d0 = c0 + c2
            d1 = c0 - c2
            d2 = c1 + c3
            d3 = (0.0_real32, -1.0_real32)*(c1 - c3)
            b(i, 1, j) = d0 + d2
            b(i, 2, j) = w1*(d1 + d3)
            b(i, 3, j) = w2*(d0 - d2)
            b(i, 4, j) = w3*(d1 - d3)
        end do
    end do
    return
end subroutine fft4b_r32

subroutine fft5a_r32(a, b, w, l)
    implicit none

    complex(real32), intent(inout) :: a(l,*), b(5,*), w(4,*)
    integer, intent(in) :: l
    complex(real32) :: c0, c1, c2, c3, c4, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10
    complex(real32) :: w1, w2, w3, w4
    real(real32) :: c51 = 0.95105651629515357_real32, c52 = 0.61803398874989485_real32
    real(real32) :: c53 = 0.55901699437494742_real32, c54 = 0.25_real32
    integer :: j

!DIR$ VECTOR ALIGNED
    do j = 1, l
        w1 = w(1, j)
        w2 = w(2, j)
        w3 = w(3, j)
        w4 = w(4, j)
        c0 = a(j, 1)
        c1 = a(j, 2)
        c2 = a(j, 3)
        c3 = a(j, 4)
        c4 = a(j, 5)
        d0 = c1 + c4
        d1 = c2 + c3
        d2 = c51*(c1 - c4)
        d3 = c51*(c2 - c3)
        d4 = d0 + d1
        d5 = c53*(d0 - d1)
        d6 = c0 - c54*d4
        d7 = d6 + d5
        d8 = d6 - d5
        d9 = (0.0_real32, -1.0_real32)*(d2 + c52*d3)
        d10 = (0.0_real32, -1.0_real32)*(c52*d2 - d3)
        b(1, j) = c0 + d4
        b(2, j) = w1*(d7 + d9)
        b(3, j) = w2*(d8 + d10)
        b(4, j) = w3*(d8 - d10)
        b(5, j) = w4*(d7 - d9)
    end do
    return
end subroutine fft5a_r32


subroutine fft5b_r32(a, b, w, m, l)
    implicit none
    complex(real32), intent(inout) :: a(m,l,*), b(m,5,*), w(4,*)
    integer, intent(in) :: m, l
    complex(real32) :: c0, c1, c2, c3, c4, d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10
    complex(real32) :: w1, w2, w3, w4
    real(real32) :: c51 = 0.95105651629515357_real32, c52 = 0.61803398874989485_real32
    real(real32) :: c53 = 0.55901699437494742_real32, c54 = 0.25_real32
    integer :: i, j

!DIR$ VECTOR ALIGNED
    do i = 1, m
        c0 = a(i, 1, 1)
        c1 = a(i, 1, 2)
        c2 = a(i, 1, 3)
        c3 = a(i, 1, 4)
        c4 = a(i, 1, 5)
        d0 = c1 + c4
        d1 = c2 + c3
        d2 = c51*(c1 - c4)
        d3 = c51*(c2 - c3)
        d4 = d0 + d1
        d5 = c53*(d0 - d1)
        d6 = c0 - c54*d4
        d7 = d6 + d5
        d8 = d6 - d5
        d9 = (0.0_real32, -1.0_real32)*(d2 + c52*d3)
        d10 = (0.0_real32, -1.0_real32)*(c52*d2 - d3)
        b(i, 1, 1) = c0 + d4
        b(i, 2, 1) = d7 + d9
        b(i, 3, 1) = d8 + d10
        b(i, 4, 1) = d8 - d10
        b(i, 5, 1) = d7 - d9
    end do
    do j = 2, l
        w1 = w(1, j)
        w2 = w(2, j)
        w3 = w(3, j)
        w4 = w(4, j)
!DIR$ VECTOR ALIGNED
        do i = 1, m
            c0 = a(i, j, 1)
            c1 = a(i, j, 2)
            c2 = a(i, j, 3)
            c3 = a(i, j, 4)
            c4 = a(i, j, 5)
            d0 = c1 + c4
            d1 = c2 + c3
            d2 = c51*(c1 - c4)
            d3 = c51*(c2 - c3)
            d4 = d0 + d1
            d5 = c53*(d0 - d1)
            d6 = c0 - c54*d4
            d7 = d6 + d5
            d8 = d6 - d5
            d9 = (0.0_real32, -1.0_real32)*(d2 + c52*d3)
            d10 = (0.0_real32, -1.0_real32)*(c52*d2 - d3)
            b(i, 1, j) = c0 + d4
            b(i, 2, j) = w1*(d7 + d9)
            b(i, 3, j) = w2*(d8 + d10)
            b(i, 4, j) = w3*(d8 - d10)
            b(i, 5, j) = w4*(d7 - d9)
        end do
    end do
    return
end subroutine fft5b_r32


subroutine fft8a_r32(a, b, w, l)
    implicit none
    complex(real32), intent(inout) :: a(l,*), b(8,*), w(7,*)
    integer, intent(in) :: l
    complex(real32) :: c0, c1, c2, c3, c4, c5, c6, c7, d0, d1, d2, d3, d4, d5, d6, d7
    complex(real32) :: e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, w1, w2, w3, w4, w5, w6, w7
    real(real32) :: c81 = 0.70710678118654752_real32
    integer :: j

!DIR$ VECTOR ALIGNED
    do j = 1, l
        w1 = w(1, j)
        w2 = w(2, j)
        w3 = w(3, j)
        w4 = w(4, j)
        w5 = w(5, j)
        w6 = w(6, j)
        w7 = w(7, j)
        c0 = a(j, 1)
        c1 = a(j, 2)
        c2 = a(j, 3)
        c3 = a(j, 4)
        c4 = a(j, 5)
        c5 = a(j, 6)
        c6 = a(j, 7)
        c7 = a(j, 8)
        d0 = c0 + c4
        d1 = c0 - c4
        d2 = c2 + c6
        d3 = (0.0_real32, -1.0_real32)*(c2 - c6)
        d4 = c1 + c5
        d5 = c1 - c5
        d6 = c3 + c7
        d7 = c3 - c7
        e0 = d0 + d2
        e1 = d0 - d2
        e2 = d4 + d6
        e3 = (0.0_real32, -1.0_real32)*(d4 - d6)
        e4 = c81*(d5 - d7)
        e5 = (0.0_real32, -1.0_real32)*c81*(d5 + d7)
        e6 = d1 + e4
        e7 = d1 - e4
        e8 = d3 + e5
        e9 = d3 - e5
        b(1, j) = e0 + e2
        b(2, j) = w1*(e6 + e8)
        b(3, j) = w2*(e1 + e3)
        b(4, j) = w3*(e7 - e9)
        b(5, j) = w4*(e0 - e2)
        b(6, j) = w5*(e7 + e9)
        b(7, j) = w6*(e1 - e3)
        b(8, j) = w7*(e6 - e8)
    end do
    return
end subroutine fft8a_r32

subroutine fft8b_r32(a, b, w, m, l)
    implicit none
    complex(real32), intent(inout) :: a(m,l,*), b(m,8,*), w(7,*)
    integer, intent(in) :: m, l
    complex(real32) :: c0, c1, c2, c3, c4, c5, c6, c7, d0, d1, d2, d3, d4, d5, d6, d7
    complex(real32) :: e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, w1, w2, w3, w4, w5, w6, w7
    real(real32) :: c81 = 0.70710678118654752_real32
    integer :: i, j

!DIR$ VECTOR ALIGNED
    do i = 1, m
        c0 = a(i, 1, 1)
        c1 = a(i, 1, 2)
        c2 = a(i, 1, 3)
        c3 = a(i, 1, 4)
        c4 = a(i, 1, 5)
        c5 = a(i, 1, 6)
        c6 = a(i, 1, 7)
        c7 = a(i, 1, 8)
        d0 = c0 + c4
        d1 = c0 - c4
        d2 = c2 + c6
        d3 = (0.0_real32, -1.0_real32)*(c2 - c6)
        d4 = c1 + c5
        d5 = c1 - c5
        d6 = c3 + c7
        d7 = c3 - c7
        e0 = d0 + d2
        e1 = d0 - d2
        e2 = d4 + d6
        e3 = (0.0_real32, -1.0_real32)*(d4 - d6)
        e4 = c81*(d5 - d7)
        e5 = (0.0_real32, -1.0_real32)*c81*(d5 + d7)
        e6 = d1 + e4
        e7 = d1 - e4
        e8 = d3 + e5
        e9 = d3 - e5
        b(i, 1, 1) = e0 + e2
        b(i, 2, 1) = e6 + e8
        b(i, 3, 1) = e1 + e3
        b(i, 4, 1) = e7 - e9
        b(i, 5, 1) = e0 - e2
        b(i, 6, 1) = e7 + e9
        b(i, 7, 1) = e1 - e3
        b(i, 8, 1) = e6 - e8
    end do
    do j = 2, l
        w1 = w(1, j)
        w2 = w(2, j)
        w3 = w(3, j)
        w4 = w(4, j)
        w5 = w(5, j)
        w6 = w(6, j)
        w7 = w(7, j)
!DIR$ VECTOR ALIGNED
        do i = 1, m
            c0 = a(i, j, 1)
            c1 = a(i, j, 2)
            c2 = a(i, j, 3)
            c3 = a(i, j, 4)
            c4 = a(i, j, 5)
            c5 = a(i, j, 6)
            c6 = a(i, j, 7)
            c7 = a(i, j, 8)
            d0 = c0 + c4
            d1 = c0 - c4
            d2 = c2 + c6
            d3 = (0.0_real32, -1.0_real32)*(c2 - c6)
            d4 = c1 + c5
            d5 = c1 - c5
            d6 = c3 + c7
            d7 = c3 - c7
            e0 = d0 + d2
            e1 = d0 - d2
            e2 = d4 + d6
            e3 = (0.0_real32, -1.0_real32)*(d4 - d6)
            e4 = c81*(d5 - d7)
            e5 = (0.0_real32, -1.0_real32)*c81*(d5 + d7)
            e6 = d1 + e4
            e7 = d1 - e4
            e8 = d3 + e5
            e9 = d3 - e5
            b(i, 1, j) = e0 + e2
            b(i, 2, j) = w1*(e6 + e8)
            b(i, 3, j) = w2*(e1 + e3)
            b(i, 4, j) = w3*(e7 - e9)
            b(i, 5, j) = w4*(e0 - e2)
            b(i, 6, j) = w5*(e7 + e9)
            b(i, 7, j) = w6*(e1 - e3)
            b(i, 8, j) = w7*(e6 - e8)
        end do
    end do
    return
end subroutine fft8b_r32

end module kernel_m
