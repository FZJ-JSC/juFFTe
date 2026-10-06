! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module fft235_m

use, intrinsic :: iso_fortran_env
use factor_m
use kernel_m

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
    complex(real64), intent(out) :: a_out(*)
    integer, intent(in) :: ip(*), n
    integer :: j, k, key, kp4, kp8, l, m, nleft

    if (ip(1) /= 1) then
        kp4 = 2 - mod(ip(1) + 2, 3)
        kp8 = (ip(1) - kp4*2)/3
    else
        kp4 = 0
        kp8 = 0
    end if

    ! The input a is only read, by the first stage. The other stages alternate
    ! between b and a_out, arranged so that the last stage reads b and writes a_out.
    ! key: where the data is now (0 = a, 1 = b, 2 = a_out).
    ! nleft: stages still to run, including the current one.
    nleft = kp8 + ip(3) + kp4 + ip(2)
    if (ip(1) == 1) nleft = nleft + 1
    key = 0
    j = 1
    l = n
    m = 1
    do k = 1, kp8
        l = l/8
        call stage(8)
        m = m*8
        j = j + l*7
    end do
    do k = 1, ip(3)
        l = l/5
        call stage(5)
        m = m*5
        j = j + l*4
    end do
    do k = 1, kp4
        l = l/4
        call stage(4)
        m = m*4
        j = j + l*3
    end do
    do k = 1, ip(2)
        l = l/3
        call stage(3)
        m = m*3
        j = j + l*2
    end do
    if (ip(1) == 1) call stage(2)
    return

contains

    subroutine stage(r)
        integer, intent(in) :: r

        if (nleft == 1) then                ! last stage: write a_out
            if (key == 0) then
                call kernel(r, a, a_out)
            else
                call kernel(r, b, a_out)    ! key == 1
            end if
        else if (mod(nleft, 2) == 0) then   ! even number left: write b
            if (key == 0) then
                call kernel(r, a, b)
            else
                call kernel(r, a_out, b)    ! key == 2
            end if
            key = 1
        else                                ! odd number left: write a_out
            if (key == 0) then
                call kernel(r, a, a_out)
            else
                call kernel(r, b, a_out)    ! key == 1
            end if
            key = 2
        end if
        nleft = nleft - 1
    end subroutine stage

    subroutine kernel(r, x, y)
        integer, intent(in) :: r
        complex(real64), intent(inout) :: x(*), y(*)

        select case (r)
        case (8)
            call fft8(x, y, w(j), m, l)
        case (5)
            call fft5(x, y, w(j), m, l)
        case (4)
            call fft4(x, y, w(j), m, l)
        case (3)
            call fft3(x, y, w(j), m, l)
        case (2)
            call fft2(x, y, m)
        end select
    end subroutine kernel

end subroutine fft235_o

subroutine fft235(a, b, w, n, ip)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: ip(*), n
    integer :: j, k, key, kp4, kp8, l, m

    if (ip(1) /= 1) then
        kp4 = 2 - mod(ip(1) + 2, 3)
        kp8 = (ip(1) - kp4*2)/3
    else
        kp4 = 0
        kp8 = 0
    end if

    key = 1
    j = 1
    l = n
    m = 1
    do k = 1, kp8
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
    do k = 1, ip(3)
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
    do k = 1, kp4
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
    do k = 1, ip(2)
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
    if (ip(1) == 1) then
        if (key >= 0) then
            call fft2(a, m=m)
        else
            call fft2(b, a, m)
        end if
    end if
    return
end subroutine fft235


subroutine fft3(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call fft3a(a, b, w, l)
    else
        call fft3b(a, b, w, m, l)
    end if
    return
end subroutine fft3


subroutine fft4(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call fft4a(a, b, w, l)
    else
        call fft4b(a, b, w, m, l)
    end if
    return
end subroutine fft4


subroutine fft5(a, b, w, m, l)
    implicit none
    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call fft5a(a, b, w, l)
    else
        call fft5b(a, b, w, m, l)
    end if
    return
end subroutine fft5


subroutine fft8(a, b, w, m, l)
    implicit none

    complex(real64), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call fft8a(a, b, w, l)
    else
        call fft8b(a, b, w, m, l)
    end if
    return
end subroutine fft8


subroutine settbl(w, n)
    implicit none

    complex(real64), intent(inout) :: w(*)
    integer, intent(in) :: n
    integer :: ip(3), kp4, kp8, j, k, l

    call factor(n, ip)

    if (ip(1) /= 1) then
        kp4 = 2 - mod(ip(1) + 2, 3)
        kp8 = (ip(1) - kp4*2)/3
    else
        kp4 = 0
        kp8 = 0
    end if

    j = 1
    l = n
    do k = 1, kp8
        l = l/8
        call settbl0(w(j), 8, l)
        j = j + l*7
    end do
    do k = 1, ip(3)
        l = l/5
        call settbl0(w(j), 5, l)
        j = j + l*4
    end do
    do k = 1, kp4
        l = l/4
        call settbl0(w(j), 4, l)
        j = j + l*3
    end do
    do k = 1, ip(2)
        l = l/3
        call settbl0(w(j), 3, l)
        j = j + l*2
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
    complex(real32), intent(out) :: a_out(*)
    integer, intent(in) :: ip(*), n
    integer :: j, k, key, kp4, kp8, l, m, nleft

    if (ip(1) /= 1) then
        kp4 = 2 - mod(ip(1) + 2, 3)
        kp8 = (ip(1) - kp4*2)/3
    else
        kp4 = 0
        kp8 = 0
    end if

    ! The input a is only read, by the first stage. The other stages alternate
    ! between b and a_out, arranged so that the last stage reads b and writes a_out.
    ! key: where the data is now (0 = a, 1 = b, 2 = a_out).
    ! nleft: stages still to run, including the current one.
    nleft = kp8 + ip(3) + kp4 + ip(2)
    if (ip(1) == 1) nleft = nleft + 1
    key = 0
    j = 1
    l = n
    m = 1
    do k = 1, kp8
        l = l/8
        call stage(8)
        m = m*8
        j = j + l*7
    end do
    do k = 1, ip(3)
        l = l/5
        call stage(5)
        m = m*5
        j = j + l*4
    end do
    do k = 1, kp4
        l = l/4
        call stage(4)
        m = m*4
        j = j + l*3
    end do
    do k = 1, ip(2)
        l = l/3
        call stage(3)
        m = m*3
        j = j + l*2
    end do
    if (ip(1) == 1) call stage(2)
    return

contains

    subroutine stage(r)
        integer, intent(in) :: r

        if (nleft == 1) then                ! last stage: write a_out
            if (key == 0) then
                call kernel(r, a, a_out)
            else
                call kernel(r, b, a_out)    ! key == 1
            end if
        else if (mod(nleft, 2) == 0) then   ! even number left: write b
            if (key == 0) then
                call kernel(r, a, b)
            else
                call kernel(r, a_out, b)    ! key == 2
            end if
            key = 1
        else                                ! odd number left: write a_out
            if (key == 0) then
                call kernel(r, a, a_out)
            else
                call kernel(r, b, a_out)    ! key == 1
            end if
            key = 2
        end if
        nleft = nleft - 1
    end subroutine stage

    subroutine kernel(r, x, y)
        integer, intent(in) :: r
        complex(real32), intent(inout) :: x(*), y(*)

        select case (r)
        case (8)
            call fft8_r32(x, y, w(j), m, l)
        case (5)
            call fft5_r32(x, y, w(j), m, l)
        case (4)
            call fft4_r32(x, y, w(j), m, l)
        case (3)
            call fft3_r32(x, y, w(j), m, l)
        case (2)
            call fft2_r32(x, y, m)
        end select
    end subroutine kernel

end subroutine fft235_o_r32

subroutine fft235_r32(a, b, w, n, ip)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: ip(*), n
    integer :: j, k, key, kp4, kp8, l, m

    if (ip(1) /= 1) then
        kp4 = 2 - mod(ip(1) + 2, 3)
        kp8 = (ip(1) - kp4*2)/3
    else
        kp4 = 0
        kp8 = 0
    end if

    key = 1
    j = 1
    l = n
    m = 1
    do k = 1, kp8
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
    do k = 1, ip(3)
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
    do k = 1, kp4
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
    do k = 1, ip(2)
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
    if (ip(1) == 1) then
        if (key >= 0) then
            call fft2_r32(a, m=m)
        else
            call fft2_r32(b, a, m)
        end if
    end if
    return
end subroutine fft235_r32


subroutine fft3_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call fft3a_r32(a, b, w, l)
    else
        call fft3b_r32(a, b, w, m, l)
    end if
    return
end subroutine fft3_r32


subroutine fft4_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call fft4a_r32(a, b, w, l)
    else
        call fft4b_r32(a, b, w, m, l)
    end if
    return
end subroutine fft4_r32


subroutine fft5_r32(a, b, w, m, l)
    implicit none
    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call fft5a_r32(a, b, w, l)
    else
        call fft5b_r32(a, b, w, m, l)
    end if
    return
end subroutine fft5_r32


subroutine fft8_r32(a, b, w, m, l)
    implicit none

    complex(real32), intent(inout) :: a(*), b(*), w(*)
    integer, intent(in) :: m, l

    if (m == 1) then
        call fft8a_r32(a, b, w, l)
    else
        call fft8b_r32(a, b, w, m, l)
    end if
    return
end subroutine fft8_r32


subroutine settbl_r32(w, n)
    implicit none

    complex(real32), intent(inout) :: w(*)
    integer, intent(in) :: n
    integer :: ip(3), kp4, kp8, j, k, l

    call factor(n, ip)

    if (ip(1) /= 1) then
        kp4 = 2 - mod(ip(1) + 2, 3)
        kp8 = (ip(1) - kp4*2)/3
    else
        kp4 = 0
        kp8 = 0
    end if

    j = 1
    l = n
    do k = 1, kp8
        l = l/8
        call settbl0_r32(w(j), 8, l)
        j = j + l*7
    end do
    do k = 1, ip(3)
        l = l/5
        call settbl0_r32(w(j), 5, l)
        j = j + l*4
    end do
    do k = 1, kp4
        l = l/4
        call settbl0_r32(w(j), 4, l)
        j = j + l*3
    end do
    do k = 1, ip(2)
        l = l/3
        call settbl0_r32(w(j), 3, l)
        j = j + l*2
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


end module fft235_m