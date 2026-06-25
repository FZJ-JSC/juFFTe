! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module fft235s_m

use, intrinsic :: iso_fortran_env
use, intrinsic :: iso_c_binding
use factor_m

implicit none

private
public  :: fft235, fft235_o, fft3, fft4, fft5, fft8
public  :: fft235_r32, fft235_o_r32, fft3_r32, fft4_r32, fft5_r32, fft8_r32
public  :: settbl, settbl2
public  :: settbl_r32, settbl2_r32

contains

subroutine fft235_o(a, b, w, n, ip, a_out)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    complex(real64), intent(out)   :: a_out(*)

    integer, intent(in) :: ip(*), n
    integer :: j, k, key, kp4, kp8, l, m

    key = 1
    j = 1
    l = n
    m = 1
    do k = 1, ip(16)
        l = l/16
        if (l >= 2) then
            if (key >= 0) then
                call fft16(a, b, w(j), m, l)
            else
                call fft16(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft16(a, a_out, w(j), m, l)
            else
                call fft16(b, a_out, w(j), m, l)
            end if
        end if
        m = m*16
        j = j + l*15
    end do
    do k = 1, ip(15)
        l = l/15
        if (l >= 2) then
            if (key >= 0) then
                call fft15(a, b, w(j), m, l)
            else
                call fft15(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft15(a, a_out, w(j), m, l)
            else
                call fft15(b, a_out, w(j), m, l)
            end if
        end if
        m = m*15
        j = j + l*14
    end do
    do k = 1, ip(12)
        l = l/12
        if (l >= 2) then
            if (key >= 0) then
                call fft12(a, b, w(j), m, l)
            else
                call fft12(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft12(a, a_out, w(j), m, l)
            else
                call fft12(b, a_out, w(j), m, l)
            end if
        end if
        m = m*12
        j = j + l*11
    end do
    do k = 1, ip(10)
        l = l/10
        if (l >= 2) then
            if (key >= 0) then
                call fft10(a, b, w(j), m, l)
            else
                call fft10(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft10(a, a_out, w(j), m, l)
            else
                call fft10(b, a_out, w(j), m, l)
            end if
        end if
        m = m*10
        j = j + l*9
    end do
    do k = 1, ip(9)
        l = l/9
        if (l >= 2) then
            if (key >= 0) then
                call fft9(a, b, w(j), m, l)
            else
                call fft9(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft9(a, a_out, w(j), m, l)
            else
                call fft9(b, a_out, w(j), m, l)
            end if
        end if
        m = m*9
        j = j + l*8
    end do
    do k = 1, ip(8)
        l = l/8
        if (l >= 2) then
            if (key >= 0) then
                call fft8(a, b, w(j), m, l)
            else
                call fft8(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft8(a, a_out, w(j), m, l)
            else
                call fft8(b, a_out, w(j), m, l)
            end if
        end if
        m = m*8
        j = j + l*7
    end do
    do k = 1, ip(6)
        l = l/6
        if (l >= 2) then
            if (key >= 0) then
                call fft6(a, b, w(j), m, l)
            else
                call fft6(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft6(a, a_out, w(j), m, l)
            else
                call fft6(b, a_out, w(j), m, l)
            end if
        end if
        m = m*6
        j = j + l*5
    end do
    do k = 1, ip(5)
        l = l/5
        if (l >= 2) then
            if (key >= 0) then
                call fft5(a, b, w(j), m, l)
            else
                call fft5(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft5(a, a_out, w(j), m, l)
            else
                call fft5(b, a_out, w(j), m, l)
            end if
        end if
        m = m*5
        j = j + l*4
    end do
    do k = 1, ip(4)
        l = l/4
        if (l >= 2) then
            if (key >= 0) then
                call fft4(a, b, w(j), m, l)
            else
                call fft4(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft4(a, a_out, w(j), m, l)
            else
                call fft4(b, a_out, w(j), m, l)
            end if
        end if
        m = m*4
        j = j + l*3
    end do
    do k = 1, ip(3)
        l = l/3
        if (l >= 2) then
            if (key >= 0) then
                call fft3(a, b, w(j), m, l)
            else
                call fft3(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft3(a, a_out, w(j), m, l)
            else
                call fft3(b, a_out, w(j), m, l)
            end if
        end if
        m = m*3
        j = j + l*2
    end do
    do k = 1, ip(2)
        l = l/2
        if (l >= 2) then
            if (key >= 0) then
                call fft2(a, b, w(j), m, l)
            else
                call fft2(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft2(a, a_out, w(j), m, l)
            else
                call fft2(b, a_out, w(j), m, l)
            end if
        end if
        m = m*2
        j = j + l
    end do
    return
end subroutine fft235_o

subroutine fft235(a, b, w, n, ip)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: ip(*), n
    integer :: j, k, key, kp4, kp8, l, m

    key = 1
    j = 1
    l = n
    m = 1
    do k = 1, ip(16)
        l = l/16
        if (l >= 2) then
            if (key >= 0) then
                call fft16(a, b, w(j), m, l)
            else
                call fft16(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft16(a, a, w(j), m, l)
            else
                call fft16(b, a, w(j), m, l)
            end if
        end if
        m = m*16
        j = j + l*15
    end do
    do k = 1, ip(15)
        l = l/15
        if (l >= 2) then
            if (key >= 0) then
                call fft15(a, b, w(j), m, l)
            else
                call fft15(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft15(a, a, w(j), m, l)
            else
                call fft15(b, a, w(j), m, l)
            end if
        end if
        m = m*15
        j = j + l*14
    end do
    do k = 1, ip(12)
        l = l/12
        if (l >= 2) then
            if (key >= 0) then
                call fft12(a, b, w(j), m, l)
            else
                call fft12(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft12(a, a, w(j), m, l)
            else
                call fft12(b, a, w(j), m, l)
            end if
        end if
        m = m*12
        j = j + l*11
    end do
    do k = 1, ip(10)
        l = l/10
        if (l >= 2) then
            if (key >= 0) then
                call fft10(a, b, w(j), m, l)
            else
                call fft10(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft10(a, a, w(j), m, l)
            else
                call fft10(b, a, w(j), m, l)
            end if
        end if
        m = m*10
        j = j + l*9
    end do
    do k = 1, ip(9)
        l = l/9
        if (l >= 2) then
            if (key >= 0) then
                call fft9(a, b, w(j), m, l)
            else
                call fft9(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft9(a, a, w(j), m, l)
            else
                call fft9(b, a, w(j), m, l)
            end if
        end if
        m = m*9
        j = j + l*8
    end do
    do k = 1, ip(8)
        l = l/8
        if (l >= 2) then
            if (key >= 0) then
                call fft8(a, b, w(j), m, l)
            else
                call fft8(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft8(a, a, w(j), m, l)
            else
                call fft8(b, a, w(j), m, l)
            end if
        end if
        m = m*8
        j = j + l*7
    end do
    do k = 1, ip(6)
        l = l/6
        if (l >= 2) then
            if (key >= 0) then
                call fft6(a, b, w(j), m, l)
            else
                call fft6(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft6(a, a, w(j), m, l)
            else
                call fft6(b, a, w(j), m, l)
            end if
        end if
        m = m*6
        j = j + l*5
    end do
    do k = 1, ip(5)
        l = l/5
        if (l >= 2) then
            if (key >= 0) then
                call fft5(a, b, w(j), m, l)
            else
                call fft5(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft5(a, a, w(j), m, l)
            else
                call fft5(b, a, w(j), m, l)
            end if
        end if
        m = m*5
        j = j + l*4
    end do
    do k = 1, ip(4)
        l = l/4
        if (l >= 2) then
            if (key >= 0) then
                call fft4(a, b, w(j), m, l)
            else
                call fft4(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft4(a, a, w(j), m, l)
            else
                call fft4(b, a, w(j), m, l)
            end if
        end if
        m = m*4
        j = j + l*3
    end do
    do k = 1, ip(3)
        l = l/3
        if (l >= 2) then
            if (key >= 0) then
                call fft3(a, b, w(j), m, l)
            else
                call fft3(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft3(a, a, w(j), m, l)
            else
                call fft3(b, a, w(j), m, l)
            end if
        end if
        m = m*3
        j = j + l*2
    end do
    do k = 1, ip(2)
        l = l/2
        if (l >= 2) then
            if (key >= 0) then
                call fft2(a, b, w(j), m, l)
            else
                call fft2(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft2(a, a, w(j), m, l)
            else
                call fft2(b, a, w(j), m, l)
            end if
        end if
        m = m*2
        j = j + l
    end do
    return
end subroutine fft235

subroutine fft2(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft2a(b, a, w, l)
    else
        call dft2c(b, a, l, m)
        call dft2b(b, a, w, l, m)
    end if
    return
end subroutine fft2

subroutine fft3(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft3a(b, a, w, l)
    else
        call dft3c(b, a, l, m)
        call dft3b(b, a, w, l, m)
    end if
    return
end subroutine fft3

subroutine fft4(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft4a(b, a, w, l)
    else
        call dft4c(b, a, l, m)
        call dft4b(b, a, w, l, m)
    end if
    return
end subroutine fft4

subroutine fft5(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft5a(b, a, w, l)
    else
        call dft5c(b, a, l, m)
        call dft5b(b, a, w, l, m)
    end if
    return
end subroutine fft5

subroutine fft6(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft6a(b, a, w, l)
    else
        call dft6c(b, a, l, m)
        call dft6b(b, a, w, l, m)
    end if
    return
end subroutine fft6

subroutine fft8(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft8a(b, a, w, l)
    else
        call dft8c(b, a, l, m)
        call dft8b(b, a, w, l, m)
    end if
    return
end subroutine fft8

subroutine fft9(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft9a(b, a, w, l)
    else
        call dft9c(b, a, l, m)
        call dft9b(b, a, w, l, m)
    end if
    return
end subroutine fft9

subroutine fft10(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft10a(b, a, w, l)
    else
        call dft10c(b, a, l, m)
        call dft10b(b, a, w, l, m)
    end if
    return
end subroutine fft10

subroutine fft12(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft12a(b, a, w, l)
    else
        call dft12c(b, a, l, m)
        call dft12b(b, a, w, l, m)
    end if
    return
end subroutine fft12

subroutine fft15(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft15a(b, a, w, l)
    else
        call dft15c(b, a, l, m)
        call dft15b(b, a, w, l, m)
    end if
    return
end subroutine fft15

subroutine fft16(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft16a(b, a, w, l)
    else
        call dft16c(b, a, l, m)
        call dft16b(b, a, w, l, m)
    end if
    return
end subroutine fft16

subroutine settbl(w, n)
    implicit none

    complex(real64), intent(inout) :: w(*)
    integer, intent(in) :: n
    integer :: ip(16), kp4, kp8, j, k, l

    call factor2(n, ip)

    j = 1
    l = n
    do k = 1, ip(16)
        l = l/16
        call settbl0(w(j), 16, l)
        j = j + l*15
    end do
    do k = 1, ip(15)
        l = l/15
        call settbl0(w(j), 15, l)
        j = j + l*14
    end do
    do k = 1, ip(12)
        l = l/12
        call settbl0(w(j), 12, l)
        j = j + l*11
    end do
    do k = 1, ip(10)
        l = l/10
        call settbl0(w(j), 10, l)
        j = j + l*9
    end do
    do k = 1, ip(9)
        l = l/9
        call settbl0(w(j), 9, l)
        j = j + l*8
    end do
    do k = 1, ip(8)
        l = l/8
        call settbl0(w(j), 8, l)
        j = j + l*7
    end do
    do k = 1, ip(6)
        l = l/6
        call settbl0(w(j), 6, l)
        j = j + l*5
    end do
    do k = 1, ip(5)
        l = l/5
        call settbl0(w(j), 5, l)
        j = j + l*4
    end do
    do k = 1, ip(4)
        l = l/4
        call settbl0(w(j), 4, l)
        j = j + l*3
    end do
    do k = 1, ip(3)
        l = l/3
        call settbl0(w(j), 3, l)
        j = j + l*2
    end do
    do k = 1, ip(2)
        l = l/2
        call settbl0(w(j), 2, l)
        j = j + l
    end do
    return
end subroutine settbl

subroutine settbl0(w, m, l)
    implicit none

    complex(real64), intent(inout) :: w(m - 1,*)
    integer, intent(in) :: m, l
    real(real64) :: pi2, px, temp
    integer :: i, j

    pi2 = 8.0d0*datan(1.0d0)
    px = (-pi2)/(dble(m)*dble(l))
    do j = 1, l
!DIR$ VECTOR ALIGNED
        do i = 1, m - 1
            temp = px*dble(i)*dble(j - 1)
            w(i, j) = dcmplx(dcos(temp), dsin(temp))
        end do
    end do
    return
end subroutine settbl0

subroutine settbl2(w, nx, ny)
    implicit none

    complex(real64), intent(inout) :: w(nx,*)
    integer, intent(in) :: nx, ny
    real(real64) :: pi2, px, temp
    integer :: i, j

    pi2 = 8.0d0*datan(1.0d0)
    px = (-pi2)/(dble(nx)*dble(ny))
!$OMP PARALLEL DO PRIVATE(TEMP)
    do j = 1, ny
!DIR$ VECTOR ALIGNED
        do i = 1, nx
            temp = px*dble(i - 1)*dble(j - 1)
            w(i, j) = dcmplx(dcos(temp), dsin(temp))
        end do
    end do
    return
end subroutine settbl2

subroutine fft235_o_r32(a, b, w, n, ip, a_out)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    complex(real32), intent(out)   :: a_out(*)

    integer, intent(in) :: ip(*), n
    integer :: j, k, key, kp4, kp8, l, m

    key = 1
    j = 1
    l = n
    m = 1
    do k = 1, ip(16)
        l = l/16
        if (l >= 2) then
            if (key >= 0) then
                call fft16_r32(a, b, w(j), m, l)
            else
                call fft16_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft16_r32(a, a_out, w(j), m, l)
            else
                call fft16_r32(b, a_out, w(j), m, l)
            end if
        end if
        m = m*16
        j = j + l*15
    end do
    do k = 1, ip(15)
        l = l/15
        if (l >= 2) then
            if (key >= 0) then
                call fft15_r32(a, b, w(j), m, l)
            else
                call fft15_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft15_r32(a, a_out, w(j), m, l)
            else
                call fft15_r32(b, a_out, w(j), m, l)
            end if
        end if
        m = m*15
        j = j + l*14
    end do
    do k = 1, ip(12)
        l = l/12
        if (l >= 2) then
            if (key >= 0) then
                call fft12_r32(a, b, w(j), m, l)
            else
                call fft12_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft12_r32(a, a_out, w(j), m, l)
            else
                call fft12_r32(b, a_out, w(j), m, l)
            end if
        end if
        m = m*12
        j = j + l*11
    end do
    do k = 1, ip(10)
        l = l/10
        if (l >= 2) then
            if (key >= 0) then
                call fft10_r32(a, b, w(j), m, l)
            else
                call fft10_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft10_r32(a, a_out, w(j), m, l)
            else
                call fft10_r32(b, a_out, w(j), m, l)
            end if
        end if
        m = m*10
        j = j + l*9
    end do
    do k = 1, ip(9)
        l = l/9
        if (l >= 2) then
            if (key >= 0) then
                call fft9_r32(a, b, w(j), m, l)
            else
                call fft9_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft9_r32(a, a_out, w(j), m, l)
            else
                call fft9_r32(b, a_out, w(j), m, l)
            end if
        end if
        m = m*9
        j = j + l*8
    end do
    do k = 1, ip(8)
        l = l/8
        if (l >= 2) then
            if (key >= 0) then
                call fft8_r32(a, b, w(j), m, l)
            else
                call fft8_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft8_r32(a, a_out, w(j), m, l)
            else
                call fft8_r32(b, a_out, w(j), m, l)
            end if
        end if
        m = m*8
        j = j + l*7
    end do
    do k = 1, ip(6)
        l = l/6
        if (l >= 2) then
            if (key >= 0) then
                call fft6_r32(a, b, w(j), m, l)
            else
                call fft6_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft6_r32(a, a_out, w(j), m, l)
            else
                call fft6_r32(b, a_out, w(j), m, l)
            end if
        end if
        m = m*6
        j = j + l*5
    end do
    do k = 1, ip(5)
        l = l/5
        if (l >= 2) then
            if (key >= 0) then
                call fft5_r32(a, b, w(j), m, l)
            else
                call fft5_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft5_r32(a, a_out, w(j), m, l)
            else
                call fft5_r32(b, a_out, w(j), m, l)
            end if
        end if
        m = m*5
        j = j + l*4
    end do
    do k = 1, ip(4)
        l = l/4
        if (l >= 2) then
            if (key >= 0) then
                call fft4_r32(a, b, w(j), m, l)
            else
                call fft4_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft4_r32(a, a_out, w(j), m, l)
            else
                call fft4_r32(b, a_out, w(j), m, l)
            end if
        end if
        m = m*4
        j = j + l*3
    end do
    do k = 1, ip(3)
        l = l/3
        if (l >= 2) then
            if (key >= 0) then
                call fft3_r32(a, b, w(j), m, l)
            else
                call fft3_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft3_r32(a, a_out, w(j), m, l)
            else
                call fft3_r32(b, a_out, w(j), m, l)
            end if
        end if
        m = m*3
        j = j + l*2
    end do
    do k = 1, ip(2)
        l = l/2
        if (l >= 2) then
            if (key >= 0) then
                call fft2_r32(a, b, w(j), m, l)
            else
                call fft2_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft2_r32(a, a_out, w(j), m, l)
            else
                call fft2_r32(b, a_out, w(j), m, l)
            end if
        end if
        m = m*2
        j = j + l
    end do
    return
end subroutine fft235_o_r32

subroutine fft235_r32(a, b, w, n, ip)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: ip(*), n
    integer :: j, k, key, kp4, kp8, l, m

    key = 1
    j = 1
    l = n
    m = 1
    do k = 1, ip(16)
        l = l/16
        if (l >= 2) then
            if (key >= 0) then
                call fft16_r32(a, b, w(j), m, l)
            else
                call fft16_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft16_r32(a, a, w(j), m, l)
            else
                call fft16_r32(b, a, w(j), m, l)
            end if
        end if
        m = m*16
        j = j + l*15
    end do
    do k = 1, ip(15)
        l = l/15
        if (l >= 2) then
            if (key >= 0) then
                call fft15_r32(a, b, w(j), m, l)
            else
                call fft15_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft15_r32(a, a, w(j), m, l)
            else
                call fft15_r32(b, a, w(j), m, l)
            end if
        end if
        m = m*15
        j = j + l*14
    end do
    do k = 1, ip(12)
        l = l/12
        if (l >= 2) then
            if (key >= 0) then
                call fft12_r32(a, b, w(j), m, l)
            else
                call fft12_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft12_r32(a, a, w(j), m, l)
            else
                call fft12_r32(b, a, w(j), m, l)
            end if
        end if
        m = m*12
        j = j + l*11
    end do
    do k = 1, ip(10)
        l = l/10
        if (l >= 2) then
            if (key >= 0) then
                call fft10_r32(a, b, w(j), m, l)
            else
                call fft10_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft10_r32(a, a, w(j), m, l)
            else
                call fft10_r32(b, a, w(j), m, l)
            end if
        end if
        m = m*10
        j = j + l*9
    end do
    do k = 1, ip(9)
        l = l/9
        if (l >= 2) then
            if (key >= 0) then
                call fft9_r32(a, b, w(j), m, l)
            else
                call fft9_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft9_r32(a, a, w(j), m, l)
            else
                call fft9_r32(b, a, w(j), m, l)
            end if
        end if
        m = m*9
        j = j + l*8
    end do
    do k = 1, ip(8)
        l = l/8
        if (l >= 2) then
            if (key >= 0) then
                call fft8_r32(a, b, w(j), m, l)
            else
                call fft8_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft8_r32(a, a, w(j), m, l)
            else
                call fft8_r32(b, a, w(j), m, l)
            end if
        end if
        m = m*8
        j = j + l*7
    end do
    do k = 1, ip(6)
        l = l/6
        if (l >= 2) then
            if (key >= 0) then
                call fft6_r32(a, b, w(j), m, l)
            else
                call fft6_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft6_r32(a, a, w(j), m, l)
            else
                call fft6_r32(b, a, w(j), m, l)
            end if
        end if
        m = m*6
        j = j + l*5
    end do
    do k = 1, ip(5)
        l = l/5
        if (l >= 2) then
            if (key >= 0) then
                call fft5_r32(a, b, w(j), m, l)
            else
                call fft5_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft5_r32(a, a, w(j), m, l)
            else
                call fft5_r32(b, a, w(j), m, l)
            end if
        end if
        m = m*5
        j = j + l*4
    end do
    do k = 1, ip(4)
        l = l/4
        if (l >= 2) then
            if (key >= 0) then
                call fft4_r32(a, b, w(j), m, l)
            else
                call fft4_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft4_r32(a, a, w(j), m, l)
            else
                call fft4_r32(b, a, w(j), m, l)
            end if
        end if
        m = m*4
        j = j + l*3
    end do
    do k = 1, ip(3)
        l = l/3
        if (l >= 2) then
            if (key >= 0) then
                call fft3_r32(a, b, w(j), m, l)
            else
                call fft3_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft3_r32(a, a, w(j), m, l)
            else
                call fft3_r32(b, a, w(j), m, l)
            end if
        end if
        m = m*3
        j = j + l*2
    end do
    do k = 1, ip(2)
        l = l/2
        if (l >= 2) then
            if (key >= 0) then
                call fft2_r32(a, b, w(j), m, l)
            else
                call fft2_r32(b, a, w(j), m, l)
            end if
            key = -key
        else
            if (key >= 0) then
                call fft2_r32(a, a, w(j), m, l)
            else
                call fft2_r32(b, a, w(j), m, l)
            end if
        end if
        m = m*2
        j = j + l
    end do
    return
end subroutine fft235_r32

subroutine fft2_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft2a_r32(b, a, w, l)
    else
        call dft2c_r32(b, a, l, m)
        call dft2b_r32(b, a, w, l, m)
    end if
    return
end subroutine fft2_r32

subroutine fft3_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft3a_r32(b, a, w, l)
    else
        call dft3c_r32(b, a, l, m)
        call dft3b_r32(b, a, w, l, m)
    end if
    return
end subroutine fft3_r32

subroutine fft4_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft4a_r32(b, a, w, l)
    else
        call dft4c_r32(b, a, l, m)
        call dft4b_r32(b, a, w, l, m)
    end if
    return
end subroutine fft4_r32

subroutine fft5_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft5a_r32(b, a, w, l)
    else
        call dft5c_r32(b, a, l, m)
        call dft5b_r32(b, a, w, l, m)
    end if
    return
end subroutine fft5_r32

subroutine fft6_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft6a_r32(b, a, w, l)
    else
        call dft6c_r32(b, a, l, m)
        call dft6b_r32(b, a, w, l, m)
    end if
    return
end subroutine fft6_r32

subroutine fft8_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft8a_r32(b, a, w, l)
    else
        call dft8c_r32(b, a, l, m)
        call dft8b_r32(b, a, w, l, m)
    end if
    return
end subroutine fft8_r32

subroutine fft9_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft9a_r32(b, a, w, l)
    else
        call dft9c_r32(b, a, l, m)
        call dft9b_r32(b, a, w, l, m)
    end if
    return
end subroutine fft9_r32

subroutine fft10_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft10a_r32(b, a, w, l)
    else
        call dft10c_r32(b, a, l, m)
        call dft10b_r32(b, a, w, l, m)
    end if
    return
end subroutine fft10_r32

subroutine fft12_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft12a_r32(b, a, w, l)
    else
        call dft12c_r32(b, a, l, m)
        call dft12b_r32(b, a, w, l, m)
    end if
    return
end subroutine fft12_r32

subroutine fft15_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft15a_r32(b, a, w, l)
    else
        call dft15c_r32(b, a, l, m)
        call dft15b_r32(b, a, w, l, m)
    end if
    return
end subroutine fft15_r32

subroutine fft16_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call dft16a_r32(b, a, w, l)
    else
        call dft16c_r32(b, a, l, m)
        call dft16b_r32(b, a, w, l, m)
    end if
    return
end subroutine fft16_r32

subroutine settbl_r32(w, n)
    implicit none

    complex(real32), intent(inout) :: w(*)
    integer, intent(in) :: n
    integer :: ip(16), kp4, kp8, j, k, l

    call factor2(n, ip)

    j = 1
    l = n
    do k = 1, ip(16)
        l = l/16
        call settbl0_r32(w(j), 16, l)
        j = j + l*15
    end do
    do k = 1, ip(15)
        l = l/15
        call settbl0_r32(w(j), 15, l)
        j = j + l*14
    end do
    do k = 1, ip(12)
        l = l/12
        call settbl0_r32(w(j), 12, l)
        j = j + l*11
    end do
    do k = 1, ip(10)
        l = l/10
        call settbl0_r32(w(j), 10, l)
        j = j + l*9
    end do
    do k = 1, ip(9)
        l = l/9
        call settbl0_r32(w(j), 9, l)
        j = j + l*8
    end do
    do k = 1, ip(8)
        l = l/8
        call settbl0_r32(w(j), 8, l)
        j = j + l*7
    end do
    do k = 1, ip(6)
        l = l/6
        call settbl0_r32(w(j), 6, l)
        j = j + l*5
    end do
    do k = 1, ip(5)
        l = l/5
        call settbl0_r32(w(j), 5, l)
        j = j + l*4
    end do
    do k = 1, ip(4)
        l = l/4
        call settbl0_r32(w(j), 4, l)
        j = j + l*3
    end do
    do k = 1, ip(3)
        l = l/3
        call settbl0_r32(w(j), 3, l)
        j = j + l*2
    end do
    do k = 1, ip(2)
        l = l/2
        call settbl0_r32(w(j), 2, l)
        j = j + l
    end do
    return
end subroutine settbl_r32

subroutine settbl0_r32(w, m, l)
    implicit none

    complex(real32), intent(inout) :: w(m - 1,*)
    integer, intent(in) :: m, l
    real(real32) :: pi2, px, temp
    integer :: i, j

    pi2 = 8.0_real32*atan(1.0_real32)
    px = (-pi2)/(real(m)*real(l))
    do j = 1, l
!DIR$ VECTOR ALIGNED
        do i = 1, m - 1
            temp = px*real(i)*real(j - 1)
            w(i, j) = cmplx(cos(temp), sin(temp))
        end do
    end do
    return
end subroutine settbl0_r32

subroutine settbl2_r32(w, nx, ny)
    implicit none

    complex(real32), intent(inout) :: w(nx,*)
    integer, intent(in) :: nx, ny
    real(real32) :: pi2, px, temp
    integer :: i, j

    pi2 = 8.0_real32*atan(1.0_real32)
    px = (-pi2)/(real(nx)*real(ny))
!$OMP PARALLEL DO PRIVATE(TEMP)
    do j = 1, ny
!DIR$ VECTOR ALIGNED
        do i = 1, nx
            temp = px*real(i - 1)*real(j - 1)
            w(i, j) = cmplx(cos(temp), sin(temp))
        end do
    end do
    return
end subroutine settbl2_r32

end module fft235s_m