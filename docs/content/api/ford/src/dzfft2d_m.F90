! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module dzfft2d_m

use, intrinsic :: iso_fortran_env
use param
use factor_m
#ifdef SPRL
use fft235s_m
#else
use fft235_m
#endif

implicit none

complex(real64), allocatable :: b (:) ! WORK/COEFFICIENT VECTOR
complex(real32), allocatable :: b_r32 (:)
private
public :: dzfft2d, dzfft2d_64, dzfft2d_32

interface dzfft2d
  module procedure dzfft2d_64, dzfft2d_32
end interface

contains

subroutine dzfft2d_64(a, a_c, nx, ny, iopt)

    implicit none

    real(real64), intent(in) :: a(*)
    complex(real64), intent(inout) :: a_c(*)
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
    call dzfft2d0_64(a, a_c, b, c, c, d, wx, wy, nx, ny, lnx, lny)
!$OMP END PARALLEL
    return
end subroutine dzfft2d_64

subroutine dzfft2d0_64(da, a, b, cx, cy, d, wx, wy, nx, ny, lnx, lny)

    implicit none
    complex(real64), intent(inout) :: a(nx/2 + 1,*), b(nx/2 + 1,*)
    complex(real64), intent(inout) :: cx(*), cy(ny + np,*), d(*)
    complex(real64), intent(inout) :: wx(*), wy(*)
    real(real64), intent(in) :: da(nx,*)
    integer, intent(in) :: nx, ny, lnx(*), lny(*)
    integer :: i, j, ii

    if (mod(ny, 2) == 0) then
!$OMP DO PRIVATE(I)
        do j = 1, ny, 2
            do i = 1, nx
                cx(i) = dcmplx(da(i, j), da(i, j + 1))
            end do
            call fft235(cx, d, wx, nx, lnx)
            b(1, j) = dble(cx(1))
            b(1, j + 1) = dimag(cx(1))
!DIR$ VECTOR ALIGNED
            do i = 2, nx/2 + 1
                b(i, j) = 0.5d0*(cx(i) + dconjg(cx(nx - i + 2)))
                b(i, j + 1) = (0.0d0, -0.5d0)*(cx(i) - dconjg(cx(nx - i + 2)))
            end do
        end do
    else
!$OMP DO PRIVATE(I)
        do j = 1, ny - 1, 2
            do i = 1, nx
                cx(i) = dcmplx(da(i, j), da(i, j + 1))
            end do
            call fft235(cx, d, wx, nx, lnx)
            b(1, j) = dble(cx(1))
            b(1, j + 1) = dimag(cx(1))
!DIR$ VECTOR ALIGNED
            do i = 2, nx/2 + 1
                b(i, j) = 0.5d0*(cx(i) + dconjg(cx(nx - i + 2)))
                b(i, j + 1) = (0.0d0, -0.5d0)*(cx(i) - dconjg(cx(nx - i + 2)))
            end do
        end do
        do i = 1, nx
            cx(i) = dcmplx(da(i, ny), 0.0d0)
        end do
        call fft235(cx, d, wx, nx, lnx)
!DIR$ VECTOR ALIGNED
        do i = 1, nx/2 + 1
            b(i, ny) = cx(i)
        end do
    end if
!$OMP DO PRIVATE(I,J)
    do ii = 1, nx/2 + 1, NBLK
        do i = ii, min(ii + NBLK - 1, nx/2 + 1)
!DIR$ VECTOR ALIGNED
            do j = 1, ny
                cy(j, i - ii + 1) = b(i, j)
            end do
        end do
        do i = ii, min(ii + NBLK - 1, nx/2 + 1)
            call fft235(cy(1, i - ii + 1), d, wy, ny, lny)
        end do
        do j = 1, ny
!DIR$ VECTOR ALIGNED
            do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                a(i, j) = cy(j, i - ii + 1)
            end do
        end do
    end do
    return
end subroutine dzfft2d0_64

subroutine dzfft2d_32(a, a_c, nx, ny, iopt)

    implicit none

    real(real32), intent(in) :: a(*)
    complex(real32), intent(inout) :: a_c(*)
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
    call dzfft2d0_32(a, a_c, b_r32, c, c, d, wx, wy, nx, ny, lnx, lny)
!$OMP END PARALLEL
    return
end subroutine dzfft2d_32

subroutine dzfft2d0_32(da, a, b, cx, cy, d, wx, wy, nx, ny, lnx, lny)

    implicit none
    complex(real32), intent(inout) :: a(nx/2 + 1,*), b(nx/2 + 1,*)
    complex(real32), intent(inout) :: cx(*), cy(ny + np,*), d(*)
    complex(real32), intent(inout) :: wx(*), wy(*)
    real(real32), intent(in) :: da(nx,*)
    integer, intent(in) :: nx, ny, lnx(*), lny(*)
    integer :: i, j, ii

    if (mod(ny, 2) == 0) then
!$OMP DO PRIVATE(I)
        do j = 1, ny, 2
            do i = 1, nx
                cx(i) = cmplx(da(i, j), da(i, j + 1))
            end do
            call fft235_r32(cx, d, wx, nx, lnx)
            b(1, j) = real(cx(1))
            b(1, j + 1) = imag(cx(1))
!DIR$ VECTOR ALIGNED
            do i = 2, nx/2 + 1
                b(i, j) = 0.5_real32*(cx(i) + conjg(cx(nx - i + 2)))
                b(i, j + 1) = (0.0_real32, -0.5_real32)*(cx(i) - conjg(cx(nx - i + 2)))
            end do
        end do
    else
!$OMP DO PRIVATE(I)
        do j = 1, ny - 1, 2
            do i = 1, nx
                cx(i) = cmplx(da(i, j), da(i, j + 1))
            end do
            call fft235_r32(cx, d, wx, nx, lnx)
            b(1, j) = real(cx(1))
            b(1, j + 1) = imag(cx(1))
!DIR$ VECTOR ALIGNED
            do i = 2, nx/2 + 1
                b(i, j) = 0.5_real32*(cx(i) + conjg(cx(nx - i + 2)))
                b(i, j + 1) = (0.0_real32, -0.5_real32)*(cx(i) - conjg(cx(nx - i + 2)))
            end do
        end do
        do i = 1, nx
            cx(i) = cmplx(da(i, ny), 0.0_real32)
        end do
        call fft235_r32(cx, d, wx, nx, lnx)
!DIR$ VECTOR ALIGNED
        do i = 1, nx/2 + 1
            b(i, ny) = cx(i)
        end do
    end if
!$OMP DO PRIVATE(I,J)
    do ii = 1, nx/2 + 1, NBLK
        do i = ii, min(ii + NBLK - 1, nx/2 + 1)
!DIR$ VECTOR ALIGNED
            do j = 1, ny
                cy(j, i - ii + 1) = b(i, j)
            end do
        end do
        do i = ii, min(ii + NBLK - 1, nx/2 + 1)
            call fft235_r32(cy(1, i - ii + 1), d, wy, ny, lny)
        end do
        do j = 1, ny
!DIR$ VECTOR ALIGNED
            do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                a(i, j) = cy(j, i - ii + 1)
            end do
        end do
    end do
    return
end subroutine dzfft2d0_32

end module dzfft2d_m

