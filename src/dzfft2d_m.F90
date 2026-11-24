! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module dzfft2d_m

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
public :: dzfft2d, dzfft2d_64, dzfft2d_32, dzfft1d, dzfft1d_64, dzfft1d_32

interface dzfft2d
  module procedure dzfft2d_64, dzfft2d_32
end interface

interface dzfft1d
  module procedure dzfft1d_64, dzfft1d_32
end interface

contains

subroutine dzfft2d_64(a, a_c, nx, ny, iopt, plan)

    implicit none

    real(real64), intent(in) :: a(*)
    complex(real64), intent(inout) :: a_c(*)
    integer, intent(in) :: nx, ny, iopt
    type(juffte_plan), intent(inout), optional :: plan

    call dzfft_64(a, a_c, nx, ny, iopt, 'dzfft2d', [nx, ny], plan)
end subroutine dzfft2d_64

! The 1-D r2c transform of length n: the 2-D one with one row, planned as 1-D.
subroutine dzfft1d_64(a, a_c, n, iopt, plan)

    implicit none

    real(real64), intent(in) :: a(*)
    complex(real64), intent(inout) :: a_c(*)
    integer, intent(in) :: n, iopt
    type(juffte_plan), intent(inout), optional :: plan

    call dzfft_64(a, a_c, n, 1, iopt, 'dzfft1d', [n], plan)
end subroutine dzfft1d_64

! dzfft2d of nx x ny, or dzfft1d of length nx with ny = 1; routine and shape are those of the
! call, for the plan and the messages.
subroutine dzfft_64(a, a_c, nx, ny, iopt, routine, shape, plan)

    implicit none

    real(real64), intent(in) :: a(*)
    complex(real64), intent(inout) :: a_c(*)
    integer, intent(in) :: nx, ny, iopt
    character(len=*), intent(in) :: routine
    integer, intent(in) :: shape(:)
    type(juffte_plan), intent(inout), optional :: plan
    complex(real64), pointer, contiguous :: w(:), c(:), d(:)
    integer(int64) :: nc
    integer :: slot
    complex(real64), pointer, contiguous :: b(:)
    type(plan_t), pointer :: p

    nc = max(int(nx, int64), (int(ny, int64) + NP)*NBLK)
    call plan_begin(plans, routine, shape, iopt, p, b, (nx/2 + 1)*ny, nthread=nc + max(nx, ny), plan=plan)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return
    ! The thread's work arrays, in its slot of the plan.
    ! With one row (the 1-D transforms), every thread would transform the same row.
!$OMP PARALLEL PRIVATE(W,SLOT,C,D) IF(ny > 1)
    call plan_thread(p, w, slot)
    c => w(1:nc)
    d => w(nc + 1:)
    call dzfft2d0_64(a, a_c, b, c, c, d, p%wx, p%wy, nx, ny, p%lp(:, 1), p%lp(:, 2))
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
    call plan_end(p, b)
end subroutine dzfft_64

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
        ! The last row of an odd ny, on one thread; the others wait for it.
!$OMP SINGLE
        do i = 1, nx
            cx(i) = dcmplx(da(i, ny), 0.0d0)
        end do
        call fft235(cx, d, wx, nx, lnx)
!DIR$ VECTOR ALIGNED
        do i = 1, nx/2 + 1
            b(i, ny) = cx(i)
        end do
!$OMP END SINGLE
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

subroutine dzfft2d_32(a, a_c, nx, ny, iopt, plan)

    implicit none

    real(real32), intent(in) :: a(*)
    complex(real32), intent(inout) :: a_c(*)
    integer, intent(in) :: nx, ny, iopt
    type(juffte_plan), intent(inout), optional :: plan

    call dzfft_32(a, a_c, nx, ny, iopt, 'dzfft2d', [nx, ny], plan)
end subroutine dzfft2d_32

! The 1-D r2c transform of length n: the 2-D one with one row, planned as 1-D.
subroutine dzfft1d_32(a, a_c, n, iopt, plan)

    implicit none

    real(real32), intent(in) :: a(*)
    complex(real32), intent(inout) :: a_c(*)
    integer, intent(in) :: n, iopt
    type(juffte_plan), intent(inout), optional :: plan

    call dzfft_32(a, a_c, n, 1, iopt, 'dzfft1d', [n], plan)
end subroutine dzfft1d_32

! dzfft2d of nx x ny, or dzfft1d of length nx with ny = 1; routine and shape are those of the
! call, for the plan and the messages.
subroutine dzfft_32(a, a_c, nx, ny, iopt, routine, shape, plan)

    implicit none

    real(real32), intent(in) :: a(*)
    complex(real32), intent(inout) :: a_c(*)
    integer, intent(in) :: nx, ny, iopt
    character(len=*), intent(in) :: routine
    integer, intent(in) :: shape(:)
    type(juffte_plan), intent(inout), optional :: plan
    complex(real32), pointer, contiguous :: w(:), c(:), d(:)
    integer(int64) :: nc
    integer :: slot
    complex(real32), pointer, contiguous :: b(:)
    type(plan_t), pointer :: p

    nc = max(int(nx, int64), (int(ny, int64) + NP)*NBLK)
    call plan_begin(plans, routine, shape, iopt, p, b, (nx/2 + 1)*ny, nthread=nc + max(nx, ny), plan=plan)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return
    ! The thread's work arrays, in its slot of the plan.
    ! With one row (the 1-D transforms), every thread would transform the same row.
!$OMP PARALLEL PRIVATE(W,SLOT,C,D) IF(ny > 1)
    call plan_thread(p, w, slot)
    c => w(1:nc)
    d => w(nc + 1:)
    call dzfft2d0_32(a, a_c, b, c, c, d, p%wx_r32, p%wy_r32, nx, ny, p%lp(:, 1), p%lp(:, 2))
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
    call plan_end(p, b)
end subroutine dzfft_32

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
        ! The last row of an odd ny, on one thread; the others wait for it.
!$OMP SINGLE
        do i = 1, nx
            cx(i) = cmplx(da(i, ny), 0.0_real32)
        end do
        call fft235_r32(cx, d, wx, nx, lnx)
!DIR$ VECTOR ALIGNED
        do i = 1, nx/2 + 1
            b(i, ny) = cx(i)
        end do
!$OMP END SINGLE
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

