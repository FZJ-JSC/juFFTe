! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module zfft1d_m

use, intrinsic :: iso_fortran_env
use param
use factor_m
use plan_m
#ifdef SPRL
use fft235s_m
#else
use fft235_m
#endif

implicit none
type(plan_t), pointer :: plans => null()
private
public :: zfft1d, zfft1d_64, zfft1d_32

interface zfft1d
  module procedure zfft1d_64, zfft1d_32
end interface

contains

subroutine zfft1d_64(a, n, iopt, out, plan)
    use param
    implicit none

    complex(real64), intent(inout)        :: a(*)
    complex(real64), optional,intent(out) :: out(*)
    type(juffte_plan), intent(inout), optional :: plan
    integer, intent(in)              :: n, iopt
    complex(real64), pointer, contiguous  :: w(:), c(:), d(:)
    complex(real64), pointer, contiguous  :: b(:)
    type(plan_t), pointer            :: p
    real(real64)                          :: dn
    integer                          :: i, nx, ny, nc, slot

    call plan_begin(plans, 'zfft1d', [n], iopt, p, b, n, build_64, plan=plan)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return

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

    if (.not. allocated(p%wx)) then  ! fft235 alone, see build_64
        if (present(out)) then

            if (iopt == juffte_bw) then
                call fft235( out, b, p%w, n, p%lp(:, 1))
            else
                call fft235_o( a, b, p%w, n, p%lp(:, 1), out)
            end if
        else
            call fft235(a, b, p%w, n, p%lp(:, 1))
        end if
    else
                    nx = size(p%wx)
                    ny = size(p%wy)

                    ! The thread's work arrays, in its slot of the plan. Out of place backward, out
                    ! already holds conj(a).
                    nc = (max(nx, ny) + NP)*NBLK
!$OMP PARALLEL PRIVATE(W,SLOT,C,D)
                    call plan_thread(p, w, slot)
                    c => w(1:nc)
                    d => w(nc + 1:)
                    if (.not. present(out)) then
                        call zfft1d0_64(a, a, b, c, c, d, p%wx, p%wy, p%w, nx, ny, &
                                        p%lp(:, 1), p%lp(:, 2))
                    else if (iopt == juffte_bw) then
                        call zfft1d0_64(out, out, b, c, c, d, p%wx, p%wy, p%w, nx, ny, &
                                        p%lp(:, 1), p%lp(:, 2))
                    else
                        call zfft1d0_64(a, out, b, c, c, d, p%wx, p%wy, p%w, nx, ny, &
                                        p%lp(:, 1), p%lp(:, 2))
                    end if
                    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
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
    call plan_end(p, b)

end subroutine zfft1d_64

! The tables of a length-n plan: those of fft235, or for the six-step algorithm (n = nx ny)
! those of both factors and the twiddles between the steps.
subroutine build_64(p)
    type(plan_t), intent(inout) :: p
    integer :: n, nx, ny

    n = p%n(1)
    if (n <= l2size/16/3) then
        call radices(n, p%lp(:, 1))
        allocate(p%w(n))
        call settbl(p%w, n)
    else
        call getnxny(n, nx, ny)
        call radices(nx, p%lp(:, 1))
        call radices(ny, p%lp(:, 2))
        allocate(p%wx(nx), p%wy(ny), p%w(n))
        p%nthread = (max(nx, ny) + NP)*NBLK + max(nx, ny)
        call settbl(p%wx, nx)
        call settbl(p%wy, ny)
        call settbl2(p%w, nx, ny)
    end if
end subroutine build_64

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

subroutine zfft1d_32(a, n, iopt, out, plan)
    use param
    implicit none

    complex(real32), intent(inout)        :: a(*)
    complex(real32), optional,intent(out) :: out(*)
    type(juffte_plan), intent(inout), optional :: plan
    integer, intent(in)              :: n, iopt
    complex(real32), pointer, contiguous  :: w(:), c(:), d(:)
    complex(real32), pointer, contiguous  :: b(:)
    type(plan_t), pointer            :: p
    real(real32)                          :: dn
    integer                          :: i, nx, ny, nc, slot

    call plan_begin(plans, 'zfft1d', [n], iopt, p, b, n, build_32, plan=plan)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return

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

    if (.not. allocated(p%wx_r32)) then  ! fft235 alone, see build_32
        if (present(out)) then

            if (iopt == juffte_bw) then
                call fft235_r32( out, b, p%w_r32, n, p%lp(:, 1))
            else
                call fft235_o_r32( a, b, p%w_r32, n, p%lp(:, 1), out)
            end if
        else
            call fft235_r32(a, b, p%w_r32, n, p%lp(:, 1))
        end if
    else
                    nx = size(p%wx_r32)
                    ny = size(p%wy_r32)

                    ! The thread's work arrays, in its slot of the plan. Out of place backward, out
                    ! already holds conj(a).
                    nc = (max(nx, ny) + NP)*NBLK
!$OMP PARALLEL PRIVATE(W,SLOT,C,D)
                    call plan_thread(p, w, slot)
                    c => w(1:nc)
                    d => w(nc + 1:)
                    if (.not. present(out)) then
                        call zfft1d0_32(a, a, b, c, c, d, p%wx_r32, p%wy_r32, p%w_r32, nx, ny, &
                                        p%lp(:, 1), p%lp(:, 2))
                    else if (iopt == juffte_bw) then
                        call zfft1d0_32(out, out, b, c, c, d, p%wx_r32, p%wy_r32, p%w_r32, nx, ny, &
                                        p%lp(:, 1), p%lp(:, 2))
                    else
                        call zfft1d0_32(a, out, b, c, c, d, p%wx_r32, p%wy_r32, p%w_r32, nx, ny, &
                                        p%lp(:, 1), p%lp(:, 2))
                    end if
                    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
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
    call plan_end(p, b)

end subroutine zfft1d_32

! The tables of a length-n plan: those of fft235, or for the six-step algorithm (n = nx ny)
! those of both factors and the twiddles between the steps.
subroutine build_32(p)
    type(plan_t), intent(inout) :: p
    integer :: n, nx, ny

    n = p%n(1)
    if (n <= l2size/16/3) then
        call radices(n, p%lp(:, 1))
        allocate(p%w_r32(n))
        call settbl_r32(p%w_r32, n)
    else
        call getnxny(n, nx, ny)
        call radices(nx, p%lp(:, 1))
        call radices(ny, p%lp(:, 2))
        allocate(p%wx_r32(nx), p%wy_r32(ny), p%w_r32(n))
        p%nthread = (max(nx, ny) + NP)*NBLK + max(nx, ny)
        call settbl_r32(p%wx_r32, nx)
        call settbl_r32(p%wy_r32, ny)
        call settbl2_r32(p%w_r32, nx, ny)
    end if
end subroutine build_32

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