! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module zfft3d_m

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
public :: zfft3d

interface zfft3d
  module procedure zfft3d_64, zfft3d_32
end interface

contains

subroutine zfft3d_64(a, nx, ny, nz, iopt, out, plan)

    implicit none

    complex(real64), intent(inout)         :: a(*)
    complex(real64), optional, intent(out) :: out(*)
    type(juffte_plan), intent(inout), optional :: plan
    integer, intent(in)                    :: nx, ny, nz, iopt
    complex(real64), pointer, contiguous   :: w(:), b(:), c(:)
    type(plan_t), pointer                  :: p
    complex(real64), pointer, contiguous   :: work(:)  ! no work array
    real(real64)                           :: dn
    integer                                :: i, slot
    integer(int64)                         :: nb

    nb = (int(max(ny, nz), int64) + NP)*NBLK
    call plan_begin(plans, 'zfft3d', [nx, ny, nz], iopt, p, work, nthread=nb + max(nx, ny, nz), plan=plan)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return

    ! Out of place, conjugate into out and transform that in place, so a is not modified.
    if (iopt == juffte_bw) then
        if (present(out)) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny*nz
                out(i) = dconjg(a(i))
            end do
        else
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny*nz
                a(i) = dconjg(a(i))
            end do
        end if
    end if

! The thread's work arrays, in its slot of the plan.
!$OMP PARALLEL PRIVATE(W,SLOT,B,C)
    call plan_thread(p, w, slot)
    b => w(1:nb)
    c => w(nb + 1:)
    if (present(out) .and. iopt /= juffte_bw) then
        call zfft3d0_64(a, b, b, c, p%wx, p%wy, p%wz, nx, ny, nz, &
                        p%lp(:, 1), p%lp(:, 2), p%lp(:, 3), out)
    else if (present(out)) then
        call zfft3d0_64(out, b, b, c, p%wx, p%wy, p%wz, nx, ny, nz, &
                        p%lp(:, 1), p%lp(:, 2), p%lp(:, 3))
    else
        call zfft3d0_64(a, b, b, c, p%wx, p%wy, p%wz, nx, ny, nz, &
                        p%lp(:, 1), p%lp(:, 2), p%lp(:, 3))
    end if
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
    if (iopt == juffte_bw) then
        dn = 1.0d0/(dble(nx)*dble(ny)*dble(nz))
        if (present(out)) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny*nz
                out(i) = dconjg(out(i))*dn
            end do
        else
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny*nz
                a(i) = dconjg(a(i))*dn
            end do
        end if
    end if
    call plan_end(p, work)
end subroutine zfft3d_64


subroutine zfft3d0_64(a, by, bz, c, wx, wy, wz, nx, ny, nz, lnx, lny, lnz, out)
    implicit none

    complex(real64), intent(inout)        :: a(nx,ny,*)
    complex(real64), optional,intent(out) :: out(nx,ny,*)
    complex(real64), intent(inout)        :: by(ny + np,*), bz(nz + np,*), c(*)
    complex(real64), intent(inout)        :: wx(*), wy(*), wz(*)
    integer, intent(in)                   :: lnx(*), lny(*), lnz(*)
    integer, intent(in)                   :: nx, ny, nz
    integer                               :: i, ii, j, jj, k, kk

if (present (out)) then ! out of place
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
                    out(i, j, k) = bz(k, i - ii + 1)
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
                        by(j, i - ii + 1) = out(i, j, k)
                    end do
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx)
                call fft235(by(1, i - ii + 1), c, wy, ny, lny)
            end do
            do j = 1, ny
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx)
                    out(i, j, k) = by(j, i - ii + 1)
                end do
            end do
        end do
        do j = 1, ny
            call fft235(out(1, j, k), c, wx, nx, lnx)
        end do
    end do
else ! in place
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
end if 
    return
end subroutine zfft3d0_64


subroutine zfft3d_32(a, nx, ny, nz, iopt, out, plan)

    implicit none

    complex(real32), intent(inout)         :: a(*)
    complex(real32), optional, intent(out) :: out(*)
    type(juffte_plan), intent(inout), optional :: plan
    integer, intent(in)                    :: nx, ny, nz, iopt
    complex(real32), pointer, contiguous   :: w(:), b(:), c(:)
    type(plan_t), pointer                  :: p
    complex(real32), pointer, contiguous   :: work(:)  ! no work array
    real(real32)                           :: dn
    integer                                :: i, slot
    integer(int64)                         :: nb

    nb = (int(max(ny, nz), int64) + NP)*NBLK
    call plan_begin(plans, 'zfft3d', [nx, ny, nz], iopt, p, work, nthread=nb + max(nx, ny, nz), plan=plan)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return

    ! Out of place, conjugate into out and transform that in place, so a is not modified.
    if (iopt == juffte_bw) then
        if (present(out)) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny*nz
                out(i) = conjg(a(i))
            end do
        else
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny*nz
                a(i) = conjg(a(i))
            end do
        end if
    end if
! The thread's work arrays, in its slot of the plan.
!$OMP PARALLEL PRIVATE(W,SLOT,B,C)
    call plan_thread(p, w, slot)
    b => w(1:nb)
    c => w(nb + 1:)
    if (present(out) .and. iopt /= juffte_bw) then
        call zfft3d0_32(a, b, b, c, p%wx_r32, p%wy_r32, p%wz_r32, nx, ny, nz, &
                        p%lp(:, 1), p%lp(:, 2), p%lp(:, 3), out)
    else if (present(out)) then
        call zfft3d0_32(out, b, b, c, p%wx_r32, p%wy_r32, p%wz_r32, nx, ny, nz, &
                        p%lp(:, 1), p%lp(:, 2), p%lp(:, 3))
    else
        call zfft3d0_32(a, b, b, c, p%wx_r32, p%wy_r32, p%wz_r32, nx, ny, nz, &
                        p%lp(:, 1), p%lp(:, 2), p%lp(:, 3))
    end if
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
    if (iopt == juffte_bw) then
        dn = 1.0_real32/(real(nx)*real(ny)*real(nz))
        if (present(out)) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny*nz
                out(i) = conjg(out(i))*dn
            end do
        else
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny*nz
                a(i) = conjg(a(i))*dn
            end do
        end if
    end if
    call plan_end(p, work)
end subroutine zfft3d_32


subroutine zfft3d0_32(a, by, bz, c, wx, wy, wz, nx, ny, nz, lnx, lny, lnz, out)
    implicit none

    complex(real32), intent(inout)         :: a(nx,ny,*)
    complex(real32), optional, intent(out) :: out(nx,ny,*)
    complex(real32), intent(inout)         :: by(ny + np,*), bz(nz + np,*), c(*)
    complex(real32), intent(inout)         :: wx(*), wy(*), wz(*)
    integer, intent(in)                    :: lnx(*), lny(*), lnz(*)
    integer, intent(in)                    :: nx, ny, nz
    integer                                :: i, ii, j, jj, k, kk

if (present(out)) then ! out of place
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
                    out(i, j, k) = bz(k, i - ii + 1)
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
                        by(j, i - ii + 1) = out(i, j, k)
                    end do
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx)
                call fft235_r32(by(1, i - ii + 1), c, wy, ny, lny)
            end do
            do j = 1, ny
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx)
                    out(i, j, k) = by(j, i - ii + 1)
                end do
            end do
        end do
        do j = 1, ny
            call fft235_r32(out(1, j, k), c, wx, nx, lnx)
        end do
    end do
else ! in place
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
end if
    return
end subroutine zfft3d0_32
end module zfft3d_m