! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module zfft2d_m

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
public :: zfft2d, zfft2d_64, zfft2d_32

interface zfft2d
  module procedure zfft2d_64, zfft2d_32
end interface

contains

subroutine zfft2d_64(a, nx, ny, iopt, out, plan)

    implicit none

    complex(real64), intent(inout)         :: a(*)
    complex(real64), optional, intent(out) :: out(*)
    type(juffte_plan), intent(inout), optional :: plan
    integer, intent(in)                    :: nx, ny, iopt
    complex(real64), pointer, contiguous   :: w(:), b(:), c(:)
    type(plan_t), pointer                  :: p
    complex(real64), pointer, contiguous   :: work(:)  ! no work array
    real(real64)                           :: dn
    integer                                :: i, slot
    integer(int64)                         :: nb


    nb = (int(ny, int64) + NP)*NBLK
    call plan_begin(plans, 'zfft2d', [nx, ny], iopt, p, work, nthread=nb + max(nx, ny), plan=plan)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return

    ! Out of place, conjugate into out and transform that in place, so a is not modified.
    if (iopt == juffte_bw) then
        if (present(out)) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny
                out(i) = dconjg(a(i))
            end do
        else
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny
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
        call zfft2d0_64(a, b, c, p%wx, p%wy, nx, ny, p%lp(:, 1), p%lp(:, 2), out)
    else if (present(out)) then
        call zfft2d0_64(out, b, c, p%wx, p%wy, nx, ny, p%lp(:, 1), p%lp(:, 2))
    else
        call zfft2d0_64(a, b, c, p%wx, p%wy, nx, ny, p%lp(:, 1), p%lp(:, 2))
    end if
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
    if (iopt == juffte_bw) then
        dn = 1.0d0/(dble(nx)*dble(ny))
        if (present(out)) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny
                out(i) = dconjg(out(i))*dn
            end do          
        else
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny
                a(i) = dconjg(a(i))*dn
            end do
        end if
    end if
    call plan_end(p, work)
end subroutine zfft2d_64

subroutine zfft2d0_64(a, b, c, wx, wy, nx, ny, lnx, lny, out)

    implicit none

    complex(real64), intent(inout)           :: a(nx,*)
    complex(real64), optional, intent(out)   :: out(nx,*)
    complex(real64), intent(inout)           :: b(ny + np,*), c(*)
    complex(real64), intent(inout)           :: wx(*), wy(*)
    integer, intent(in)                      :: lnx(*), lny(*)
    integer, intent(in)                      :: nx, ny
    integer                                  :: i, ii, j, jj

    if (present(out)) then
!$OMP DO PRIVATE(I,J,JJ)
        do ii = 1, nx, NBLK
            do jj = 1, ny, NBLK
                do i = ii, min(ii + NBLK - 1, nx)
!DIR$ VECTOR ALIGNED
                    do j = jj, min(jj + NBLK - 1, ny)
                        b(j, i - ii + 1) = a(i, j)
                    end do
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx)
                call fft235(b(1, i - ii + 1), c, wy, ny, lny)
            end do
            do j = 1, ny
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx)
                    out(i, j) = b(j, i - ii + 1)
                end do
            end do
        end do
!$OMP DO
        do j = 1, ny
            call fft235(out(1, j), c, wx, nx, lnx)
        end do
    else
!$OMP DO PRIVATE(I,J,JJ)
        do ii = 1, nx, NBLK
            do jj = 1, ny, NBLK
                do i = ii, min(ii + NBLK - 1, nx)
!DIR$ VECTOR ALIGNED
                    do j = jj, min(jj + NBLK - 1, ny)
                        b(j, i - ii + 1) = a(i, j)
                    end do
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx)
                call fft235(b(1, i - ii + 1), c, wy, ny, lny)
            end do
            do j = 1, ny
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx)
                    a(i, j) = b(j, i - ii + 1)
                end do
            end do
        end do
!$OMP DO
        do j = 1, ny
            call fft235(a(1, j), c, wx, nx, lnx)
        end do
    end if
    return
end subroutine zfft2d0_64

subroutine zfft2d_32(a, nx, ny, iopt, out, plan)

    implicit none

    complex(real32), intent(inout)         :: a(*)
    complex(real32), optional, intent(out) :: out(*)
    type(juffte_plan), intent(inout), optional :: plan
    integer, intent(in)                    :: nx, ny, iopt
    complex(real32), pointer, contiguous   :: w(:), b(:), c(:)
    type(plan_t), pointer                  :: p
    complex(real32), pointer, contiguous   :: work(:)  ! no work array
    real(real32)                           :: dn
    integer                                :: i, slot
    integer(int64)                         :: nb


    nb = (int(ny, int64) + NP)*NBLK
    call plan_begin(plans, 'zfft2d', [nx, ny], iopt, p, work, nthread=nb + max(nx, ny), plan=plan)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return

    ! Out of place, conjugate into out and transform that in place, so a is not modified.
    if (iopt == juffte_bw) then
        if (present(out)) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny
                out(i) = conjg(a(i))
            end do
        else
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny
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
        call zfft2d0_32(a, b, c, p%wx_r32, p%wy_r32, nx, ny, p%lp(:, 1), p%lp(:, 2), out)
    else if (present(out)) then
        call zfft2d0_32(out, b, c, p%wx_r32, p%wy_r32, nx, ny, p%lp(:, 1), p%lp(:, 2))
    else
        call zfft2d0_32(a, b, c, p%wx_r32, p%wy_r32, nx, ny, p%lp(:, 1), p%lp(:, 2))
    end if
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
    if (iopt == juffte_bw) then
        dn = 1.0_real32/(real(nx)*real(ny))
        if (present (out)) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny
                out(i) = conjg(out(i))*dn
            end do
        else
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny
                a(i) = conjg(a(i))*dn
            end do
        end if
    end if
    call plan_end(p, work)
end subroutine zfft2d_32

subroutine zfft2d0_32(a, b, c, wx, wy, nx, ny, lnx, lny, out)

    implicit none

    complex(real32), intent(inout)         :: a(nx,*)
    complex(real32), optional, intent(out) :: out(nx,*)
    complex(real32), intent(inout)         :: b(ny + np,*), c(*)
    complex(real32), intent(inout)         :: wx(*), wy(*)
    integer, intent(in)                    :: lnx(*), lny(*)
    integer, intent(in)                    :: nx, ny
    integer                                :: i, ii, j, jj

    if (present(out)) then
!$OMP DO PRIVATE(I,J,JJ)
        do ii = 1, nx, NBLK
            do jj = 1, ny, NBLK
                do i = ii, min(ii + NBLK - 1, nx)
!DIR$ VECTOR ALIGNED
                    do j = jj, min(jj + NBLK - 1, ny)
                        b(j, i - ii + 1) = a(i, j)
                    end do
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx)
                call fft235_r32(b(1, i - ii + 1), c, wy, ny, lny)
            end do
            do j = 1, ny
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx)
                    out(i, j) = b(j, i - ii + 1)
                end do
            end do
        end do
!$OMP DO
        do j = 1, ny
            call fft235_r32(out(1, j), c, wx, nx, lnx)
        end do
    else
!$OMP DO PRIVATE(I,J,JJ)
        do ii = 1, nx, NBLK
            do jj = 1, ny, NBLK
                do i = ii, min(ii + NBLK - 1, nx)
!DIR$ VECTOR ALIGNED
                    do j = jj, min(jj + NBLK - 1, ny)
                        b(j, i - ii + 1) = a(i, j)
                    end do
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx)
                call fft235_r32(b(1, i - ii + 1), c, wy, ny, lny)
            end do
            do j = 1, ny
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx)
                    a(i, j) = b(j, i - ii + 1)
                end do
            end do
        end do
!$OMP DO
        do j = 1, ny
            call fft235_r32(a(1, j), c, wx, nx, lnx)
        end do
    end if
    return
end subroutine zfft2d0_32


end module zfft2d_m