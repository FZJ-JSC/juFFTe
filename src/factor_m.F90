! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module factor_m

use, intrinsic :: iso_fortran_env
implicit none

private
#ifdef SPRL
public  :: factor, factor2, getnxny
#else
public  :: factor, getnxny
#endif

contains

subroutine factor(n, ip)
    implicit none
    integer, intent(in) :: n
    integer, intent(inout) :: ip(*)
    integer :: n2, nx, ny, i

    ip(1) = 0
    ip(2) = 0
    ip(3) = 0
    n2 = n
    if (mod(n, 2) /= 0 .and. mod(n, 3) /= 0 .and. mod(n, 5) /= 0) then
        return
    end if
    do while (n2 > 1)
        if (mod(n2, 2) == 0) then
            ip(1) = ip(1) + 1
            n2 = n2/2
        else
            if (mod(n2, 3) == 0) then
                ip(2) = ip(2) + 1
                n2 = n2/3
            else
                if (mod(n2, 5) == 0) then
                    ip(3) = ip(3) + 1
                    n2 = n2/5
                else
                    exit
                end if
            end if
        end if
    end do
    return
end subroutine factor

#ifdef SPRL

subroutine factor2(n, kp)
    implicit none
    integer, intent(in) :: n
    integer, intent(inout) :: kp(*)
    integer :: n2, nx, ny, i, ip(3)
    integer :: l3, l4, l5, l6, l8, l9, l10, l12, l15, l16
    integer :: j3, j4, j5, j6, j8, j9, j10, j12, j15, j16   
    real    :: h, h2

    call factor(n, ip)

    do i = 1, 16
        kp(i) = 0
    end do
    if (n == 2) then
        kp(2) = 1
        return
    end if
    h = 0.0d0
    l16 = ip(1)/4
    do j16 = 0, l16
        l15 = min(ip(2), ip(3))
        do j15 = 0, l15
            l12 = min((ip(1) - j16*4)/2, ip(2) - j15)
            do j12 = 0, l12
                l10 = min(ip(1) - j12*2 - j16*4, ip(3) - j15)
                do j10 = 0, l10
                    l9 = (ip(2) - j12 - j15)/2
                    do j9 = 0, l9
                        l8 = min((ip(1) - j10 - j12*2 - j16*4)/3, 3)
                        do j8 = 0, l8
                            l6 = min(ip(1) - j8*3 - j10 - j12*2 - j16*4, ip(2) - j9*2 - j12 - j15)
                            do j6 = 0, l6
                                l5 = ip(3) - j10 - j15
                                do j5 = 0, l5
                                    l4 = min((ip(1) - j6 - j8*3 - j10 - j12*2 - j16*4)/2, 1)
                                    do j4 = 0, l4
                                        l3 = min(ip(2) - j6 - j9*2 - j12 - j15, 1)
                                        do j3 = 0, l3
                                            if (ip(1) == j4*2 + j6 + j8*3 + j10 + j12*2 + j16*4 .and. ip(2) &
                                                    == j3 + j6 + j9*2 + j12 + j15 .and. ip(3) == j5 + j10 + j15) then
                                                h2 = harmmean(j3, j4, j5, j6, j8, j9, j10, j12, j15, j16)
                                                if (h2 >= h) then
                                                    kp(3) = j3
                                                    kp(4) = j4
                                                    kp(5) = j5
                                                    kp(6) = j6
                                                    kp(8) = j8
                                                    kp(9) = j9
                                                    kp(10) = j10
                                                    kp(12) = j12
                                                    kp(15) = j15
                                                    kp(16) = j16
                                                    h = h2
                                                end if
                                            end if
                                        end do
                                    end do
                                end do
                            end do
                        end do
                    end do
                end do
            end do
        end do
    end do
    return
end subroutine factor2

function harmmean(j3, j4, j5, j6, j8, j9, j10, j12, j15, j16) result(res)
    implicit none
    integer, intent (in) :: j3, j4, j5, j6, j8, j9, j10, j12, j15, j16
    integer              :: i, icount
    real(real64)              :: res
    integer              :: jp(16)

    do i = 1, 16
        jp(i) = 0
    end do
    jp(3) = j3
    jp(4) = j4
    jp(5) = j5
    jp(6) = j6
    jp(8) = j8
    jp(9) = j9
    jp(10) = j10
    jp(12) = j12
    jp(15) = j15
    jp(16) = j16
    icount = 0
    res = 0.0d0
    do i = 3, 16
        if (jp(i) /= 0) then
            res = res + dble(jp(i))/dble(i)
            icount = icount + jp(i)
        end if
    end do
    res = dble(icount)/res
    return
end function harmmean

#endif


subroutine getnxny(n, nx, ny)
    implicit none
    integer, intent(in) :: n
    integer, intent(inout) :: nx, ny
    integer :: ip(3), lnx(3), lny(3)
    integer :: i, j, k, ires2, isqrtn
    real(real64) :: ires

    isqrtn = idint(dsqrt(dble(n)))
    call factor(n, ip)
    do i = 1, 3
        lnx(i) = 0
    end do
    ires = isqrtn
    do k = 0, (ip(3) + 1)/2
        do j = 0, (ip(2) + 1)/2
            do i = 0, (ip(1) + 1)/2
                nx = 2**i*3**j*5**k
                if (nx <= isqrtn) then
                    ires2 = isqrtn - nx
                    if (ires2 < ires) then
                        lnx(1) = i
                        lnx(2) = j
                        lnx(3) = k
                        ires = ires2
                    end if
                end if
            end do
        end do
    end do
    do i = 1, 3
        lny(i) = ip(i) - lnx(i)
    end do
    nx = 2**lnx(1)*3**lnx(2)*5**lnx(3)
    ny = 2**lny(1)*3**lny(2)*5**lny(3)
    return
end subroutine getnxny

end module factor_m