! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module zdfft2d_m

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
public :: zdfft2d, zdfft2d_64, zdfft2d_32, zdfft1d, zdfft1d_64, zdfft1d_32

interface zdfft2d
  module procedure zdfft2d_64, zdfft2d_32
end interface

interface zdfft1d
  module procedure zdfft1d_64, zdfft1d_32
end interface


contains

subroutine zdfft2d_64(a, a_r, nx, ny, iopt, plan)

    implicit none

    complex(real64), intent(inout) :: a(*)
    real(real64), intent(out) :: a_r(*)
    integer, intent(in) :: nx, ny, iopt
    type(juffte_plan), intent(inout), optional :: plan

    call zdfft_64(a, a_r, nx, ny, iopt, 'zdfft2d', [nx, ny], plan)
end subroutine zdfft2d_64

! The 1-D c2r transform of length n: the 2-D one with one row, planned as 1-D.
subroutine zdfft1d_64(a, a_r, n, iopt, plan)

    implicit none

    complex(real64), intent(inout) :: a(*)
    real(real64), intent(out) :: a_r(*)
    integer, intent(in) :: n, iopt
    type(juffte_plan), intent(inout), optional :: plan

    call zdfft_64(a, a_r, n, 1, iopt, 'zdfft1d', [n], plan)
end subroutine zdfft1d_64

! zdfft2d of nx x ny, or zdfft1d of length nx with ny = 1; routine and shape are those of the
! call, for the plan and the messages.
subroutine zdfft_64(a, a_r, nx, ny, iopt, routine, shape, plan)

    implicit none

    complex(real64), intent(inout) :: a(*)
    real(real64), intent(out) :: a_r(*)
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
    call zdfft2d0_64(a, a_r, b, c, c, d, p%wx, p%wy, nx, ny, p%lp(:, 1), p%lp(:, 2))
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
    call plan_end(p, b)
end subroutine zdfft_64

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
        ! The last row of an odd ny, on one thread; the others wait for it.
!$OMP SINGLE
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
!$OMP END SINGLE
    end if
    return
end subroutine zdfft2d0_64

subroutine zdfft2d_32(a, a_r, nx, ny, iopt, plan)

    implicit none

    complex(real32), intent(inout) :: a(*)
    real(real32), intent(out) :: a_r(*)
    integer, intent(in) :: nx, ny, iopt
    type(juffte_plan), intent(inout), optional :: plan

    call zdfft_32(a, a_r, nx, ny, iopt, 'zdfft2d', [nx, ny], plan)
end subroutine zdfft2d_32

! The 1-D c2r transform of length n: the 2-D one with one row, planned as 1-D.
subroutine zdfft1d_32(a, a_r, n, iopt, plan)

    implicit none

    complex(real32), intent(inout) :: a(*)
    real(real32), intent(out) :: a_r(*)
    integer, intent(in) :: n, iopt
    type(juffte_plan), intent(inout), optional :: plan

    call zdfft_32(a, a_r, n, 1, iopt, 'zdfft1d', [n], plan)
end subroutine zdfft1d_32

! zdfft2d of nx x ny, or zdfft1d of length nx with ny = 1; routine and shape are those of the
! call, for the plan and the messages.
subroutine zdfft_32(a, a_r, nx, ny, iopt, routine, shape, plan)

    implicit none

    complex(real32), intent(inout) :: a(*)
    real(real32), intent(out) :: a_r(*)
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
    call zdfft2d0_32(a, a_r, b, c, c, d, p%wx_r32, p%wy_r32, nx, ny, p%lp(:, 1), p%lp(:, 2))
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
    call plan_end(p, b)
end subroutine zdfft_32

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
        ! The last row of an odd ny, on one thread; the others wait for it.
!$OMP SINGLE
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
!$OMP END SINGLE
    end if
    return
end subroutine zdfft2d0_32

end module zdfft2d_m