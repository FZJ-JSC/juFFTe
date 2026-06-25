! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module zfft1d_m

use, intrinsic :: iso_fortran_env
use param
use factor_m
#ifdef SPRL
use fft235s_m
#else
use fft235_m
#endif

implicit none
complex(real64),  allocatable :: b (:)
complex(real32),  allocatable :: b_r32 (:)
private
public :: zfft1d, zfft1d_64, zfft1d_32

interface zfft1d
  module procedure zfft1d_64, zfft1d_32
end interface

contains

subroutine zfft1d_64(a, n, iopt, out)
    use param
    implicit none

    complex(real64), intent(inout)        :: a(*)
    complex(real64), optional,intent(out) :: out(*)
    integer, intent(in)              :: n, iopt
    complex(real64)                       :: c((NDA2 + NP)*NBLK), d(NDA2)
#ifdef SPRL
    integer,save                     :: ip(16), lnx(16), lny(16)
#else
    integer                          :: ip(3), lnx(3), lny(3)
#endif
    complex(real64), save                 :: wx(NDA2), wy(NDA2)
    real(real64)                          :: dn
    integer                          :: i, nx, ny

    if (iopt == juffte_init) then
        allocate(b(n*2))
    end if

    if (iopt == juffte_bw) then
        if (present(out)) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, n
                out(i) = dconjg(a(i))
            end do
        else
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, n
                a(i) = dconjg(a(i))
            end do
        end if
    end if

    if (n <= l2size/16/3) then
        if (iopt == juffte_init) then
#ifdef SPRL
            call factor2(n, ip)
#endif
            call settbl(b(n + 1), n)
            return
        end if
#ifndef SPRL
            call factor(n, ip)
#endif
        if (present(out)) then

            if (iopt == juffte_bw) then
                call fft235_o( out, b, b(n + 1), n, ip, out)
            else
                call fft235_o( a, b, b(n + 1), n, ip, out)
            end if
        else
            call fft235(a, b, b(n + 1), n, ip)
        end if
    else
                    call getnxny(n, nx, ny)

                    if (iopt == juffte_init) then
#ifdef SPRL
                    call factor2(nx,lnx)
                    call factor2(ny,lny)
#endif
                        call settbl(wx, nx)
                        call settbl(wy, ny)
                        call settbl2(b(n + 1), nx, ny)
                        return
                    end if
#ifndef SPRL
                    call factor(nx, lnx)
                    call factor(ny, lny)
#endif

                    if (present(out)) then
!$OMP PARALLEL PRIVATE(C,D)
                        call zfft1d0_64(a, out, b, c, c, d, wx, wy, b(n + 1), nx, ny, lnx, lny)
!$OMP END PARALLEL
                    else
!$OMP PARALLEL PRIVATE(C,D)
                        call zfft1d0_64(a, a, b, c, c, d, wx, wy, b(n + 1), nx, ny, lnx, lny)
!$OMP END PARALLEL
                    end if
    end if

    if (present(out)) then
        if (iopt == juffte_bw) then
            dn = 1.0d0/dble(n)
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, n
                out(i) = dconjg(out(i))*dn
            end do
        end if
    else
        if (iopt == juffte_bw) then
            dn = 1.0d0/dble(n)
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, n
                a(i) = dconjg(a(i))*dn
            end do
        end if
    end if

return

end subroutine zfft1d_64

subroutine zfft1d0_64(a, ayx, b, cx, cy, d, wx, wy, w, nx, ny, lnx, lny)
    use param
    implicit none

    complex(real64), intent(inout) :: a(nx,*), ayx(ny,*), b(nx,*)
    complex(real64), intent(inout) :: cx(nx + np,*), cy(ny + np,*), d(*)
    complex(real64), intent(inout) :: wx(*), wy(*), w(nx,*)
    integer, intent(in) :: lnx(*), lny(*)
    integer, intent(in) :: nx, ny
    integer :: i, ii, j, jj
!$OMP DO PRIVATE(I,J,JJ)
    do ii = 1, nx, NBLK
        do jj = 1, ny, NBLK
            do i = ii, min(ii + NBLK - 1, nx)
!DIR$ VECTOR ALIGNED
                do j = jj, min(jj + NBLK - 1, ny)
                    cy(j, i - ii + 1) = a(i, j)
                end do
            end do
        end do
        do i = ii, min(ii + NBLK - 1, nx)
            call fft235(cy(1, i - ii + 1), d, wy, ny, lny)
        end do
        do j = 1, ny
!DIR$ VECTOR ALIGNED
            do i = ii, min(ii + NBLK - 1, nx)
                b(i, j) = cy(j, i - ii + 1)
            end do
        end do
    end do
!$OMP DO PRIVATE(I,J)
    do jj = 1, ny, NBLK
        do j = jj, min(jj + NBLK - 1, ny)
!DIR$ VECTOR ALIGNED
            do i = 1, nx
                cx(i, j - jj + 1) = b(i, j)*w(i, j)
            end do
            call fft235(cx(1, j - jj + 1), d, wx, nx, lnx)
        end do
        do i = 1, nx
!DIR$ VECTOR ALIGNED
            do j = jj, min(jj + NBLK - 1, ny)
                ayx(j, i) = cx(i, j - jj + 1)
            end do
        end do
    end do
    return
end subroutine zfft1d0_64

subroutine zfft1d_32(a, n, iopt, out)
    use param
    implicit none

    complex(real32), intent(inout)        :: a(*)
    complex(real32), optional,intent(out) :: out(*)
    integer, intent(in)              :: n, iopt
    complex(real32)                       :: c((NDA2 + NP)*NBLK), d(NDA2)
#ifdef SPRL
    integer,save                     :: ip(16), lnx(16), lny(16)
#else
    integer                          :: ip(3), lnx(3), lny(3)
#endif
    complex(real32), save                 :: wx(NDA2), wy(NDA2)
    real(real32)                          :: dn
    integer                          :: i, nx, ny

    if (iopt == juffte_init) then
        allocate(b_r32(n*2))
    end if

    if (iopt == juffte_bw) then
        if (present(out)) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, n
                out(i) = conjg(a(i))
            end do
        else
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, n
                a(i) = conjg(a(i))
            end do
        end if
    end if

    if (n <= l2size/16/3) then
        if (iopt == juffte_init) then
#ifdef SPRL
            call factor2(n, ip)
#endif
            call settbl_r32(b_r32(n + 1), n)
            return
        end if
#ifndef SPRL
            call factor(n, ip)
#endif
        if (present(out)) then

            if (iopt == juffte_bw) then
                call fft235_o_r32( out, b_r32, b_r32(n + 1), n, ip, out)
            else
                call fft235_o_r32( a, b_r32, b_r32(n + 1), n, ip, out)
            end if
        else
            call fft235_r32(a, b_r32, b_r32(n + 1), n, ip)
        end if
    else
                    call getnxny(n, nx, ny)

                    if (iopt == juffte_init) then
#ifdef SPRL
                    call factor2(nx,lnx)
                    call factor2(ny,lny)
#endif
                        call settbl_r32(wx, nx)
                        call settbl_r32(wy, ny)
                        call settbl2_r32(b_r32(n + 1), nx, ny)
                        return
                    end if
#ifndef SPRL
                    call factor(nx, lnx)
                    call factor(ny, lny)
#endif

                    if (present(out)) then
!$OMP PARALLEL PRIVATE(C,D)
                        call zfft1d0_32(a, out, b_r32, c, c, d, wx, wy, b_r32(n + 1), nx, ny, lnx, lny)
!$OMP END PARALLEL
                    else
!$OMP PARALLEL PRIVATE(C,D)
                        call zfft1d0_32(a, a, b_r32, c, c, d, wx, wy, b_r32(n + 1), nx, ny, lnx, lny)
!$OMP END PARALLEL
                    end if
    end if

    if (present(out)) then
        if (iopt == juffte_bw) then
            dn = 1.0_real32/real(n)
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, n
                out(i) = conjg(out(i))*dn
            end do
        end if
    else
        if (iopt == juffte_bw) then
            dn = 1.0_real32/real(n)
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, n
                a(i) = conjg(a(i))*dn
            end do
        end if
    end if

return

end subroutine zfft1d_32

subroutine zfft1d0_32(a, ayx, b, cx, cy, d, wx, wy, w, nx, ny, lnx, lny)
    use param
    implicit none

    complex(real32), intent(inout) :: a(nx,*), ayx(ny,*), b(nx,*)
    complex(real32), intent(inout) :: cx(nx + np,*), cy(ny + np,*), d(*)
    complex(real32), intent(inout) :: wx(*), wy(*), w(nx,*)
    integer, intent(in) :: lnx(*), lny(*)
    integer, intent(in) :: nx, ny
    integer :: i, ii, j, jj
!$OMP DO PRIVATE(I,J,JJ)
    do ii = 1, nx, NBLK
        do jj = 1, ny, NBLK
            do i = ii, min(ii + NBLK - 1, nx)
!DIR$ VECTOR ALIGNED
                do j = jj, min(jj + NBLK - 1, ny)
                    cy(j, i - ii + 1) = a(i, j)
                end do
            end do
        end do
        do i = ii, min(ii + NBLK - 1, nx)
            call fft235_r32(cy(1, i - ii + 1), d, wy, ny, lny)
        end do
        do j = 1, ny
!DIR$ VECTOR ALIGNED
            do i = ii, min(ii + NBLK - 1, nx)
                b(i, j) = cy(j, i - ii + 1)
            end do
        end do
    end do
!$OMP DO PRIVATE(I,J)
    do jj = 1, ny, NBLK
        do j = jj, min(jj + NBLK - 1, ny)
!DIR$ VECTOR ALIGNED
            do i = 1, nx
                cx(i, j - jj + 1) = b(i, j)*w(i, j)
            end do
            call fft235_r32(cx(1, j - jj + 1), d, wx, nx, lnx)
        end do
        do i = 1, nx
!DIR$ VECTOR ALIGNED
            do j = jj, min(jj + NBLK - 1, ny)
                ayx(j, i) = cx(i, j - jj + 1)
            end do
        end do
    end do
    return
end subroutine zfft1d0_32

end module zfft1d_m