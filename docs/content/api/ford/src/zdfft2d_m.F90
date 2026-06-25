! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module zdfft2d_m

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
public :: zdfft2d, zdfft2d_64, zdfft2d_32

interface zdfft2d
  module procedure zdfft2d_64, zdfft2d_32
end interface


contains

subroutine zdfft2d_64(a, a_r, nx, ny, iopt)

    implicit none

    complex(real64), intent(inout) :: a(*)
    real(real64), intent(out) :: a_r(*)
    integer, intent(in) :: nx, ny, iopt
    complex(real64) :: c((NDA2 + NP)*NBLK), d(NDA2)
    complex(real64), save :: wx(NDA2), wy(NDA2)
#ifdef SPRL
    integer :: lnx(16), lny(16)
#else
    integer :: lnx(3), lny(3)
#endif


    if (iopt == juffte_init) then
        allocate (b(nx*ny*2))
#ifdef SPRL
        call factor2(nx,lnx)
        call factor2(ny,lny)
#endif
        call settbl(wx, nx)
        call settbl(wy, ny)
        return
    end if
#ifndef SPRL
    call factor(nx, lnx)
    call factor(ny, lny)
#endif

!$OMP PARALLEL PRIVATE(C,D)
    call zdfft2d0_64(a, a_r, b, c, c, d, wx, wy, nx, ny, lnx, lny)
!$OMP END PARALLEL
    return
end subroutine zdfft2d_64

subroutine zdfft2d0_64(a, da, b, cx, cy, d, wx, wy, nx, ny, lnx, lny)
    use param
    implicit none
    complex(real64), intent(inout) :: a(nx/2 + 1,*), b(nx/2 + 1,*)
    real(real64), intent(inout) :: da(nx,*)
    complex(real64), intent(inout) :: cx(*), cy(ny + np,*), d(*)
    complex(real64), intent(inout) :: wx(*), wy(*)
    integer, intent(in) :: nx, ny, lnx(*), lny(*)
    complex(real64) :: temp
    real(real64) :: dn
    integer :: i, ii, j


    dn = 1.0d0/(dble(nx)*dble(ny))

!$OMP DO PRIVATE(I,J)
    do ii = 1, nx/2 + 1, NBLK
        do i = ii, min(ii + NBLK - 1, nx/2 + 1)
!DIR$ VECTOR ALIGNED
            do j = 1, ny
                cy(j, i - ii + 1) = dconjg(a(i, j))
            end do
        end do
        do i = ii, min(ii + NBLK - 1, nx/2 + 1)
            call fft235(cy(1, i - ii + 1), d, wy, ny, lny)
        end do
        do j = 1, ny
!DIR$ VECTOR ALIGNED
            do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                b(i, j) = cy(j, i - ii + 1)
            end do
        end do
    end do
    if (mod(ny, 2) == 0) then
!$OMP DO PRIVATE(I,TEMP)
        do j = 1, ny, 2
            cx(1) = dcmplx(dble(b(1, j)), dble(b(1, j + 1)))
!DIR$ VECTOR ALIGNED
            do i = 2, nx/2 + 1
                temp = (0.0d0, 1.0d0)*b(i, j + 1)
                cx(i) = b(i, j) + temp
                cx(nx - i + 2) = dconjg(b(i, j) - temp)
            end do
            call fft235(cx, d, wx, nx, lnx)
            do i = 1, nx
                da(i, j) = dble(cx(i))*dn
                da(i, j + 1) = dimag(cx(i))*dn
            end do
        end do
    else
!$OMP DO PRIVATE(I,TEMP)
        do j = 1, ny - 1, 2
            cx(1) = dcmplx(dble(b(1, j)), dble(b(1, j + 1)))
!DIR$ VECTOR ALIGNED
            do i = 2, nx/2 + 1
                temp = (0.0d0, 1.0d0)*b(i, j + 1)
                cx(i) = b(i, j) + temp
                cx(nx - i + 2) = dconjg(b(i, j) - temp)
            end do
            call fft235(cx, d, wx, nx, lnx)
            do i = 1, nx
                da(i, j) = dble(cx(i))*dn
                da(i, j + 1) = dimag(cx(i))*dn
            end do
        end do
        cx(1) = dcmplx(dble(b(1, ny)), 0.0d0)
!DIR$ VECTOR ALIGNED
        do i = 2, nx/2 + 1
            cx(i) = b(i, ny)
            cx(nx - i + 2) = dconjg(b(i, ny))
        end do
        call fft235(cx, d, wx, nx, lnx)
        do i = 1, nx
            da(i, ny) = dble(cx(i))*dn
        end do
    end if
    return
end subroutine zdfft2d0_64

subroutine zdfft2d_32(a, a_r, nx, ny, iopt)

    implicit none

    complex(real32), intent(inout) :: a(*)
    real(real32), intent(out) :: a_r(*)
    integer, intent(in) :: nx, ny, iopt
    complex(real32) :: c((NDA2 + NP)*NBLK), d(NDA2)
    complex(real32), save :: wx(NDA2), wy(NDA2)
#ifdef SPRL
    integer :: lnx(16), lny(16)
#else
    integer :: lnx(3), lny(3)
#endif


    if (iopt == juffte_init) then
        allocate (b_r32(nx*ny*2))
#ifdef SPRL
        call factor2(nx,lnx)
        call factor2(ny,lny)
#endif
        call settbl_r32(wx, nx)
        call settbl_r32(wy, ny)
        return
    end if
#ifndef SPRL
    call factor(nx, lnx)
    call factor(ny, lny)
#endif

!$OMP PARALLEL PRIVATE(C,D)
    call zdfft2d0_32(a, a_r, b_r32, c, c, d, wx, wy, nx, ny, lnx, lny)
!$OMP END PARALLEL
    return
end subroutine zdfft2d_32

subroutine zdfft2d0_32(a, da, b, cx, cy, d, wx, wy, nx, ny, lnx, lny)
    use param
    implicit none
    complex(real32), intent(inout) :: a(nx/2 + 1,*), b(nx/2 + 1,*)
    real(real32), intent(inout) :: da(nx,*)
    complex(real32), intent(inout) :: cx(*), cy(ny + np,*), d(*)
    complex(real32), intent(inout) :: wx(*), wy(*)
    integer, intent(in) :: nx, ny, lnx(*), lny(*)
    complex(real32) :: temp
    real(real32) :: dn
    integer :: i, ii, j


    dn = 1.0_real32/(real(nx)*real(ny))

!$OMP DO PRIVATE(I,J)
    do ii = 1, nx/2 + 1, NBLK
        do i = ii, min(ii + NBLK - 1, nx/2 + 1)
!DIR$ VECTOR ALIGNED
            do j = 1, ny
                cy(j, i - ii + 1) = conjg(a(i, j))
            end do
        end do
        do i = ii, min(ii + NBLK - 1, nx/2 + 1)
            call fft235_r32(cy(1, i - ii + 1), d, wy, ny, lny)
        end do
        do j = 1, ny
!DIR$ VECTOR ALIGNED
            do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                b(i, j) = cy(j, i - ii + 1)
            end do
        end do
    end do
    if (mod(ny, 2) == 0) then
!$OMP DO PRIVATE(I,TEMP)
        do j = 1, ny, 2
            cx(1) = cmplx(real(b(1, j)), real(b(1, j + 1)))
!DIR$ VECTOR ALIGNED
            do i = 2, nx/2 + 1
                temp = (0.0_real32, 1.0_real32)*b(i, j + 1)
                cx(i) = b(i, j) + temp
                cx(nx - i + 2) = conjg(b(i, j) - temp)
            end do
            call fft235_r32(cx, d, wx, nx, lnx)
            do i = 1, nx
                da(i, j) = real(cx(i))*dn
                da(i, j + 1) = imag(cx(i))*dn
            end do
        end do
    else
!$OMP DO PRIVATE(I,TEMP)
        do j = 1, ny - 1, 2
            cx(1) = cmplx(real(b(1, j)), real(b(1, j + 1)))
!DIR$ VECTOR ALIGNED
            do i = 2, nx/2 + 1
                temp = (0.0_real32, 1.0_real32)*b(i, j + 1)
                cx(i) = b(i, j) + temp
                cx(nx - i + 2) = conjg(b(i, j) - temp)
            end do
            call fft235_r32(cx, d, wx, nx, lnx)
            do i = 1, nx
                da(i, j) = real(cx(i))*dn
                da(i, j + 1) = imag(cx(i))*dn
            end do
        end do
        cx(1) = cmplx(real(b(1, ny)), 0.0_real32)
!DIR$ VECTOR ALIGNED
        do i = 2, nx/2 + 1
            cx(i) = b(i, ny)
            cx(nx - i + 2) = conjg(b(i, ny))
        end do
        call fft235_r32(cx, d, wx, nx, lnx)
        do i = 1, nx
            da(i, ny) = real(cx(i))*dn
        end do
    end if
    return
end subroutine zdfft2d0_32

end module zdfft2d_m