! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module zfft3d_m

use, intrinsic :: iso_fortran_env
use param
use factor_m
#ifdef SPRL
use fft235s_m
#else
use fft235_m
#endif

implicit none

private
public :: zfft3d

interface zfft3d
  module procedure zfft3d_64, zfft3d_32
end interface

contains

subroutine zfft3d_64(a, nx, ny, nz, iopt)

    implicit none

    complex(real64), intent(inout) :: a(*)
    integer, intent(in) :: nx, ny, nz, iopt
    complex(real64) :: b((NDA3 + NP)*NBLK), c(NDA3)
    complex(real64) :: wx(NDA3)=0, wy(NDA3)=0, wz(NDA3)=0
#ifdef SPRL
    integer, save :: lnx(16), lny(16), lnz(16)
#else
    integer, save :: lnx(3), lny(3), lnz(3)
#endif
    real(real64) :: dn
    integer :: i

    if (iopt == juffte_init) then
#ifdef SPRL
    call factor2(nx,lnx)
    call factor2(ny,lny)
    call factor2(nz,lnz)
#endif   
        call settbl(wx, nx)
        call settbl(wy, ny)
        call settbl(wz, nz)
        return
    end if

    if (iopt == 1) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
        do i = 1, nx*ny*nz
            a(i) = dconjg(a(i))
        end do
    end if
#ifndef SPRL
    call factor(nx, lnx)
    call factor(ny, lny)
    call factor(nz, lnz)
#endif

!$OMP PARALLEL PRIVATE(B,C)
    call zfft3d0_64(a, b, b, c, wx, wy, wz, nx, ny, nz, lnx, lny, lnz)
!$OMP END PARALLEL

    if (iopt == 1) then
        dn = 1.0d0/(dble(nx)*dble(ny)*dble(nz))
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
        do i = 1, nx*ny*nz
            a(i) = dconjg(a(i))*dn
        end do
    end if
    return
end subroutine zfft3d_64


subroutine zfft3d0_64(a, by, bz, c, wx, wy, wz, nx, ny, nz, lnx, lny, lnz)
    implicit none

    complex(real64), intent(inout) :: a(nx,ny,*)
    complex(real64), intent(inout) :: by(ny + np,*), bz(nz + np,*), c(*)
    complex(real64), intent(inout) :: wx(*), wy(*), wz(*)
    integer, intent(in) :: lnx(*), lny(*), lnz(*)
    integer, intent(in) :: nx, ny, nz
    integer :: i, ii, j, jj, k, kk

!$OMP DO PRIVATE(I,II,K,KK)
    do j = 1, ny
        do ii = 1, nx, NBLK
            do kk = 1, nz, NBLK
                do i = ii, min(ii + NBLK - 1, nx)
!DIR$ VECTOR ALIGNED
                    do k = kk, min(kk + NBLK - 1, nz)
                        bz(k, i - ii + 1) = a(i, j, k)
                    end do
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx)
                call fft235(bz(1, i - ii + 1), c, wz, nz, lnz)
            end do
            do k = 1, nz
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx)
                    a(i, j, k) = bz(k, i - ii + 1)
                end do
            end do
        end do
    end do
!$OMP DO PRIVATE(I,II,J,JJ)
    do k = 1, nz
        do ii = 1, nx, NBLK
            do jj = 1, ny, NBLK
                do i = ii, min(ii + NBLK - 1, nx)
!DIR$ VECTOR ALIGNED
                    do j = jj, min(jj + NBLK - 1, ny)
                        by(j, i - ii + 1) = a(i, j, k)
                    end do
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx)
                call fft235(by(1, i - ii + 1), c, wy, ny, lny)
            end do
            do j = 1, ny
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx)
                    a(i, j, k) = by(j, i - ii + 1)
                end do
            end do
        end do
        do j = 1, ny
            call fft235(a(1, j, k), c, wx, nx, lnx)
        end do
    end do
    return
end subroutine zfft3d0_64


subroutine zfft3d_32(a, nx, ny, nz, iopt)

    implicit none

    complex(real32), intent(inout) :: a(*)
    integer, intent(in) :: nx, ny, nz, iopt
    complex(real32) :: b((NDA3 + NP)*NBLK), c(NDA3)
    complex(real32) :: wx(NDA3)=0, wy(NDA3)=0, wz(NDA3)=0
#ifdef SPRL
    integer, save :: lnx(16), lny(16), lnz(16)
#else
    integer, save :: lnx(3), lny(3), lnz(3)
#endif
    real(real32) :: dn
    integer :: i

    if (iopt == juffte_init) then
#ifdef SPRL
    call factor2(nx,lnx)
    call factor2(ny,lny)
    call factor2(nz,lnz)
#endif
        call settbl_r32(wx, nx)
        call settbl_r32(wy, ny)
        call settbl_r32(wz, nz)
        return
    end if

    if (iopt == 1) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
        do i = 1, nx*ny*nz
            a(i) = conjg(a(i))
        end do
    end if
#ifndef SPRL
    call factor(nx, lnx)
    call factor(ny, lny)
    call factor(nz, lnz)
#endif

!$OMP PARALLEL PRIVATE(B,C)
    call zfft3d0_32(a, b, b, c, wx, wy, wz, nx, ny, nz, lnx, lny, lnz)
!$OMP END PARALLEL

    if (iopt == 1) then
        dn = 1.0_real32/(real(nx)*real(ny)*real(nz))
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
        do i = 1, nx*ny*nz
            a(i) = conjg(a(i))*dn
        end do
    end if
    return
end subroutine zfft3d_32


subroutine zfft3d0_32(a, by, bz, c, wx, wy, wz, nx, ny, nz, lnx, lny, lnz)
    implicit none

    complex(real32), intent(inout) :: a(nx,ny,*)
    complex(real32), intent(inout) :: by(ny + np,*), bz(nz + np,*), c(*)
    complex(real32), intent(inout) :: wx(*), wy(*), wz(*)
    integer, intent(in) :: lnx(*), lny(*), lnz(*)
    integer, intent(in) :: nx, ny, nz
    integer :: i, ii, j, jj, k, kk

!$OMP DO PRIVATE(I,II,K,KK)
    do j = 1, ny
        do ii = 1, nx, NBLK
            do kk = 1, nz, NBLK
                do i = ii, min(ii + NBLK - 1, nx)
!DIR$ VECTOR ALIGNED
                    do k = kk, min(kk + NBLK - 1, nz)
                        bz(k, i - ii + 1) = a(i, j, k)
                    end do
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx)
                call fft235_r32(bz(1, i - ii + 1), c, wz, nz, lnz)
            end do
            do k = 1, nz
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx)
                    a(i, j, k) = bz(k, i - ii + 1)
                end do
            end do
        end do
    end do
!$OMP DO PRIVATE(I,II,J,JJ)
    do k = 1, nz
        do ii = 1, nx, NBLK
            do jj = 1, ny, NBLK
                do i = ii, min(ii + NBLK - 1, nx)
!DIR$ VECTOR ALIGNED
                    do j = jj, min(jj + NBLK - 1, ny)
                        by(j, i - ii + 1) = a(i, j, k)
                    end do
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx)
                call fft235_r32(by(1, i - ii + 1), c, wy, ny, lny)
            end do
            do j = 1, ny
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx)
                    a(i, j, k) = by(j, i - ii + 1)
                end do
            end do
        end do
        do j = 1, ny
            call fft235_r32(a(1, j, k), c, wx, nx, lnx)
        end do
    end do
    return
end subroutine zfft3d0_32
end module zfft3d_m