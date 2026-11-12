! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module dzfft3d_m

use, intrinsic :: iso_fortran_env
use param
use plan_m
#ifdef SPRL
use fft235s_m
#else
use fft235_m
#endif

implicit none

type(plan_t), pointer :: plans => null()
private
public :: dzfft3d, dzfft3d_64, dzfft3d_32

interface dzfft3d
  module procedure dzfft3d_64, dzfft3d_32
end interface

contains

subroutine dzfft3d_64(a, a_c, nx, ny, nz, iopt, plan)
    use param
    implicit none

    real(real64), intent(in) :: a(*)
    complex(real64), intent(inout) :: a_c(*)
    integer, intent(in) :: nx, ny, nz, iopt
    type(juffte_plan), intent(inout), optional :: plan
    complex(real64), pointer, contiguous :: w(:), c(:), d(:)
    integer(int64) :: nc
    integer :: slot
    complex(real64), pointer, contiguous :: b(:)
    type(plan_t), pointer :: p

    nc = max(int(nx, int64), (int(max(ny, nz), int64) + NP)*NBLK)
    call plan_begin(plans, 'dzfft3d', [nx, ny, nz], iopt, p, b, (nx/2 + 1)*ny*nz, nthread=nc + max(nx, ny, nz), plan=plan)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return
    ! The thread's work arrays, in its slot of the plan.
!$OMP PARALLEL PRIVATE(W,SLOT,C,D)
    call plan_thread(p, w, slot)
    c => w(1:nc)
    d => w(nc + 1:)
    call dzfft3d0_64(a, a_c, b, c, c, c, d, p%wx, p%wy, p%wz, nx, ny, nz, &
                     p%lp(:, 1), p%lp(:, 2), p%lp(:, 3))
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
    call plan_end(p, b)
end subroutine dzfft3d_64

subroutine dzfft3d0_64(da, a, b, cx, cy, cz, d, wx, wy, wz, nx, ny, nz, lnx, lny, lnz)
    use param
    implicit none

    complex(real64), intent(inout) :: a(nx/2 + 1,ny,*), b(nx/2 + 1,ny,*)
    complex(real64), intent(inout) :: cx(*), cy(ny + np,*), cz(nz + np,*), d(*)
    complex(real64), intent(inout) :: wx(*), wy(*), wz(*)
    real(real64), intent(in) :: da(nx,ny,*)
    integer, intent(in) :: nx, ny, nz, lnx(*), lny(*), lnz(*)
    integer :: i, j, ii, k

    if (mod(ny, 2) == 0) then
!$OMP DO PRIVATE(I,II,J)
        do k = 1, nz
            do j = 1, ny, 2
                do i = 1, nx
                    cx(i) = dcmplx(da(i, j, k), da(i, j + 1, k))
                end do
                call fft235(cx, d, wx, nx, lnx)
                b(1, j, k) = dble(cx(1))
                b(1, j + 1, k) = dimag(cx(1))
!DIR$ VECTOR ALIGNED
                do i = 2, nx/2 + 1
                    b(i, j, k) = 0.5d0*(cx(i) + dconjg(cx(nx - i + 2)))
                    b(i, j + 1, k) = (0.0d0, -0.5d0)*(cx(i) - dconjg(cx(nx - i + 2)))
                end do
            end do
            do ii = 1, nx/2 + 1, NBLK
                do i = ii, min(ii + NBLK - 1, nx/2 + 1)
!DIR$ VECTOR ALIGNED
                    do j = 1, ny
                        cy(j, i - ii + 1) = b(i, j, k)
                    end do
                end do
                do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                    call fft235(cy(1, i - ii + 1), d, wy, ny, lny)
                end do
                do j = 1, ny
!DIR$ VECTOR ALIGNED
                    do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                        b(i, j, k) = cy(j, i - ii + 1)
                    end do
                end do
            end do
        end do
    else
!$OMP DO PRIVATE(I,II,J)
        do k = 1, nz
            do j = 1, ny - 1, 2
                do i = 1, nx
                    cx(i) = dcmplx(da(i, j, k), da(i, j + 1, k))
                end do
                call fft235(cx, d, wx, nx, lnx)
                b(1, j, k) = dble(cx(1))
                b(1, j + 1, k) = dimag(cx(1))
!DIR$ VECTOR ALIGNED
                do i = 2, nx/2 + 1
                    b(i, j, k) = 0.5d0*(cx(i) + dconjg(cx(nx - i + 2)))
                    b(i, j + 1, k) = (0.0d0, -0.5d0)*(cx(i) - dconjg(cx(nx - i + 2)))
                end do
            end do
            do i = 1, nx
                cx(i) = dcmplx(da(i, ny, k), 0.0d0)
            end do
            call fft235(cx, d, wx, nx, lnx)
!DIR$ VECTOR ALIGNED
            do i = 1, nx/2 + 1
                b(i, ny, k) = cx(i)
            end do
            do ii = 1, nx/2 + 1, NBLK
                do i = ii, min(ii + NBLK - 1, nx/2 + 1)
!DIR$ VECTOR ALIGNED
                    do j = 1, ny
                        cy(j, i - ii + 1) = b(i, j, k)
                    end do
                end do
                do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                    call fft235(cy(1, i - ii + 1), d, wy, ny, lny)
                end do
                do j = 1, ny
!DIR$ VECTOR ALIGNED
                    do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                        b(i, j, k) = cy(j, i - ii + 1)
                    end do
                end do
            end do
        end do
    end if
!$OMP DO PRIVATE(I,II,K)
    do j = 1, ny
        do ii = 1, nx/2 + 1, NBLK
            do i = ii, min(ii + NBLK - 1, nx/2 + 1)
!DIR$ VECTOR ALIGNED
                do k = 1, nz
                    cz(k, i - ii + 1) = b(i, j, k)
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                call fft235(cz(1, i - ii + 1), d, wz, nz, lnz)
            end do
            do k = 1, nz
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                    a(i, j, k) = cz(k, i - ii + 1)
                end do
            end do
        end do
    end do
    return
end subroutine dzfft3d0_64

subroutine dzfft3d_32(a, a_c, nx, ny, nz, iopt, plan)
    use param
    implicit none

    real(real32), intent(in) :: a(*)
    complex(real32), intent(inout) :: a_c(*)
    integer, intent(in) :: nx, ny, nz, iopt
    type(juffte_plan), intent(inout), optional :: plan
    complex(real32), pointer, contiguous :: w(:), c(:), d(:)
    integer(int64) :: nc
    integer :: slot
    complex(real32), pointer, contiguous :: b(:)
    type(plan_t), pointer :: p

    nc = max(int(nx, int64), (int(max(ny, nz), int64) + NP)*NBLK)
    call plan_begin(plans, 'dzfft3d', [nx, ny, nz], iopt, p, b, (nx/2 + 1)*ny*nz, nthread=nc + max(nx, ny, nz), plan=plan)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return
    ! The thread's work arrays, in its slot of the plan.
!$OMP PARALLEL PRIVATE(W,SLOT,C,D)
    call plan_thread(p, w, slot)
    c => w(1:nc)
    d => w(nc + 1:)
    call dzfft3d0_32(a, a_c, b, c, c, c, d, p%wx_r32, p%wy_r32, p%wz_r32, nx, ny, nz, &
                     p%lp(:, 1), p%lp(:, 2), p%lp(:, 3))
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
    call plan_end(p, b)
end subroutine dzfft3d_32

subroutine dzfft3d0_32(da, a, b, cx, cy, cz, d, wx, wy, wz, nx, ny, nz, lnx, lny, lnz)
    use param
    implicit none

    complex(real32), intent(inout) :: a(nx/2 + 1,ny,*), b(nx/2 + 1,ny,*)
    complex(real32), intent(inout) :: cx(*), cy(ny + np,*), cz(nz + np,*), d(*)
    complex(real32), intent(inout) :: wx(*), wy(*), wz(*)
    real(real32), intent(in) :: da(nx,ny,*)
    integer, intent(in) :: nx, ny, nz, lnx(*), lny(*), lnz(*)
    integer :: i, j, ii, k

    if (mod(ny, 2) == 0) then
!$OMP DO PRIVATE(I,II,J)
        do k = 1, nz
            do j = 1, ny, 2
                do i = 1, nx
                    cx(i) = cmplx(da(i, j, k), da(i, j + 1, k))
                end do
                call fft235_r32(cx, d, wx, nx, lnx)
                b(1, j, k) = real(cx(1))
                b(1, j + 1, k) = imag(cx(1))
!DIR$ VECTOR ALIGNED
                do i = 2, nx/2 + 1
                    b(i, j, k) = 0.5_real32*(cx(i) + conjg(cx(nx - i + 2)))
                    b(i, j + 1, k) = (0.0_real32, -0.5_real32)*(cx(i) - conjg(cx(nx - i + 2)))
                end do
            end do
            do ii = 1, nx/2 + 1, NBLK
                do i = ii, min(ii + NBLK - 1, nx/2 + 1)
!DIR$ VECTOR ALIGNED
                    do j = 1, ny
                        cy(j, i - ii + 1) = b(i, j, k)
                    end do
                end do
                do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                    call fft235_r32(cy(1, i - ii + 1), d, wy, ny, lny)
                end do
                do j = 1, ny
!DIR$ VECTOR ALIGNED
                    do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                        b(i, j, k) = cy(j, i - ii + 1)
                    end do
                end do
            end do
        end do
    else
!$OMP DO PRIVATE(I,II,J)
        do k = 1, nz
            do j = 1, ny - 1, 2
                do i = 1, nx
                    cx(i) = cmplx(da(i, j, k), da(i, j + 1, k))
                end do
                call fft235_r32(cx, d, wx, nx, lnx)
                b(1, j, k) = real(cx(1))
                b(1, j + 1, k) = imag(cx(1))
!DIR$ VECTOR ALIGNED
                do i = 2, nx/2 + 1
                    b(i, j, k) = 0.5_real32*(cx(i) + conjg(cx(nx - i + 2)))
                    b(i, j + 1, k) = (0.0_real32, -0.5_real32)*(cx(i) - conjg(cx(nx - i + 2)))
                end do
            end do
            do i = 1, nx
                cx(i) = cmplx(da(i, ny, k), 0.0_real32)
            end do
            call fft235_r32(cx, d, wx, nx, lnx)
!DIR$ VECTOR ALIGNED
            do i = 1, nx/2 + 1
                b(i, ny, k) = cx(i)
            end do
            do ii = 1, nx/2 + 1, NBLK
                do i = ii, min(ii + NBLK - 1, nx/2 + 1)
!DIR$ VECTOR ALIGNED
                    do j = 1, ny
                        cy(j, i - ii + 1) = b(i, j, k)
                    end do
                end do
                do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                    call fft235_r32(cy(1, i - ii + 1), d, wy, ny, lny)
                end do
                do j = 1, ny
!DIR$ VECTOR ALIGNED
                    do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                        b(i, j, k) = cy(j, i - ii + 1)
                    end do
                end do
            end do
        end do
    end if
!$OMP DO PRIVATE(I,II,K)
    do j = 1, ny
        do ii = 1, nx/2 + 1, NBLK
            do i = ii, min(ii + NBLK - 1, nx/2 + 1)
!DIR$ VECTOR ALIGNED
                do k = 1, nz
                    cz(k, i - ii + 1) = b(i, j, k)
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                call fft235_r32(cz(1, i - ii + 1), d, wz, nz, lnz)
            end do
            do k = 1, nz
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                    a(i, j, k) = cz(k, i - ii + 1)
                end do
            end do
        end do
    end do
    return
end subroutine dzfft3d0_32


end module dzfft3d_m