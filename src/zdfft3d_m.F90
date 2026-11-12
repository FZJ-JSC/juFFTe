! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module zdfft3d_m

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
public :: zdfft3d, zdfft3d_64, zdfft3d_32

interface zdfft3d
  module procedure zdfft3d_64, zdfft3d_32
end interface


contains

subroutine zdfft3d_64(a, a_r, nx, ny, nz, iopt, plan)
    use param
    implicit none
    complex(real64), intent(inout) :: a(*)
    real(real64), intent(out) :: a_r(*)
    integer, intent(in) :: nx, ny, nz, iopt
    type(juffte_plan), intent(inout), optional :: plan
    complex(real64), pointer, contiguous :: w(:), c(:), d(:)
    integer(int64) :: nc
    integer :: slot
    complex(real64), pointer, contiguous :: b(:)
    type(plan_t), pointer :: p

    nc = max(int(nx, int64), (int(max(ny, nz), int64) + NP)*NBLK)
    call plan_begin(plans, 'zdfft3d', [nx, ny, nz], iopt, p, b, (nx/2 + 1)*ny*nz, nthread=nc + max(nx, ny, nz), plan=plan)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return
    ! The thread's work arrays, in its slot of the plan.
!$OMP PARALLEL PRIVATE(W,SLOT,C,D)
    call plan_thread(p, w, slot)
    c => w(1:nc)
    d => w(nc + 1:)
    call zdfft3d0_64(a, a_r, b, c, c, c, d, p%wx, p%wy, p%wz, nx, ny, nz, &
                     p%lp(:, 1), p%lp(:, 2), p%lp(:, 3))
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
    call plan_end(p, b)
end subroutine zdfft3d_64

subroutine zdfft3d0_64(a, da, b, cx, cy, cz, d, wx, wy, wz, nx, ny, nz, lnx, lny, lnz)
    use param
    implicit none

    complex(real64), intent(inout) :: a(nx/2 + 1,ny,*), b(nx/2 + 1,ny,*)
    real(real64), intent(inout) :: da(nx,ny,*)
    complex(real64), intent(inout) :: cx(*), cy(ny + np,*), cz(nz + np,*), d(*)
    complex(real64), intent(inout) :: wx(*), wy(*), wz(*)
    integer, intent(in) :: nx, ny, nz, lnx(*), lny(*), lnz(*)
    complex(real64) :: temp
    real(real64) :: dn
    integer :: i, ii, j, k

    dn = 1.0d0/(dble(nx)*dble(ny)*dble(nz))

!$OMP DO PRIVATE(I,II,K)
    do j = 1, ny
        do ii = 1, nx/2 + 1, NBLK
            do i = ii, min(ii + NBLK - 1, nx/2 + 1)
!DIR$ VECTOR ALIGNED
                do k = 1, nz
                    cz(k, i - ii + 1) = dconjg(a(i, j, k))
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                call fft235(cz(1, i - ii + 1), d, wz, nz, lnz)
            end do
            do k = 1, nz
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                    b(i, j, k) = cz(k, i - ii + 1)
                end do
            end do
        end do
    end do
    if (mod(ny, 2) == 0) then
!$OMP DO PRIVATE(I,II,J,TEMP)
        do k = 1, nz
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
            do j = 1, ny, 2
                cx(1) = dcmplx(dble(b(1, j, k)), dble(b(1, j + 1, k)))
!DIR$ VECTOR ALIGNED
                do i = 2, nx/2 + 1
                    temp = (0.0d0, 1.0d0)*b(i, j + 1, k)
                    cx(i) = b(i, j, k) + temp
                    cx(nx - i + 2) = dconjg(b(i, j, k) - temp)
                end do
                call fft235(cx, d, wx, nx, lnx)
                do i = 1, nx
                    da(i, j, k) = dble(cx(i))*dn
                    da(i, j + 1, k) = dimag(cx(i))*dn
                end do
            end do
        end do
    else
!$OMP DO PRIVATE(I,II,TEMP)
        do k = 1, nz
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
            do j = 1, ny - 1, 2
                cx(1) = dcmplx(dble(b(1, j, k)), dble(b(1, j + 1, k)))
!DIR$ VECTOR ALIGNED
                do i = 2, nx/2 + 1
                    temp = (0.0d0, 1.0d0)*b(i, j + 1, k)
                    cx(i) = b(i, j, k) + temp
                    cx(nx - i + 2) = dconjg(b(i, j, k) - temp)
                end do
                call fft235(cx, d, wx, nx, lnx)
                do i = 1, nx
                    da(i, j, k) = dble(cx(i))*dn
                    da(i, j + 1, k) = dimag(cx(i))*dn
                end do
            end do
            cx(1) = dcmplx(dble(b(1, ny, k)), 0.0d0)
!DIR$ VECTOR ALIGNED
            do i = 2, nx/2 + 1
                cx(i) = b(i, ny, k)
                cx(nx - i + 2) = dconjg(b(i, ny, k))
            end do
            call fft235(cx, d, wx, nx, lnx)
            do i = 1, nx
                da(i, ny, k) = dble(cx(i))*dn
            end do
        end do
    end if
    return
end subroutine zdfft3d0_64

subroutine zdfft3d_32(a, a_r, nx, ny, nz, iopt, plan)
    use param
    implicit none
    complex(real32), intent(inout) :: a(*)
    real(real32), intent(out) :: a_r(*)
    integer, intent(in) :: nx, ny, nz, iopt
    type(juffte_plan), intent(inout), optional :: plan
    complex(real32), pointer, contiguous :: w(:), c(:), d(:)
    integer(int64) :: nc
    integer :: slot
    complex(real32), pointer, contiguous :: b(:)
    type(plan_t), pointer :: p

    nc = max(int(nx, int64), (int(max(ny, nz), int64) + NP)*NBLK)
    call plan_begin(plans, 'zdfft3d', [nx, ny, nz], iopt, p, b, (nx/2 + 1)*ny*nz, nthread=nc + max(nx, ny, nz), plan=plan)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return
    ! The thread's work arrays, in its slot of the plan.
!$OMP PARALLEL PRIVATE(W,SLOT,C,D)
    call plan_thread(p, w, slot)
    c => w(1:nc)
    d => w(nc + 1:)
    call zdfft3d0_32(a, a_r, b, c, c, c, d, p%wx_r32, p%wy_r32, p%wz_r32, nx, ny, nz, &
                     p%lp(:, 1), p%lp(:, 2), p%lp(:, 3))
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
    call plan_end(p, b)
end subroutine zdfft3d_32

subroutine zdfft3d0_32(a, da, b, cx, cy, cz, d, wx, wy, wz, nx, ny, nz, lnx, lny, lnz)
    use param
    implicit none

    complex(real32), intent(inout) :: a(nx/2 + 1,ny,*), b(nx/2 + 1,ny,*)
    real(real32), intent(inout) :: da(nx,ny,*)
    complex(real32), intent(inout) :: cx(*), cy(ny + np,*), cz(nz + np,*), d(*)
    complex(real32), intent(inout) :: wx(*), wy(*), wz(*)
    integer, intent(in) :: nx, ny, nz, lnx(*), lny(*), lnz(*)
    complex(real32) :: temp
    real(real32) :: dn
    integer :: i, ii, j, k

    dn = 1.0_real32/(real(nx)*real(ny)*real(nz))

!$OMP DO PRIVATE(I,II,K)
    do j = 1, ny
        do ii = 1, nx/2 + 1, NBLK
            do i = ii, min(ii + NBLK - 1, nx/2 + 1)
!DIR$ VECTOR ALIGNED
                do k = 1, nz
                    cz(k, i - ii + 1) = conjg(a(i, j, k))
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                call fft235_r32(cz(1, i - ii + 1), d, wz, nz, lnz)
            end do
            do k = 1, nz
!DIR$ VECTOR ALIGNED
                do i = ii, min(ii + NBLK - 1, nx/2 + 1)
                    b(i, j, k) = cz(k, i - ii + 1)
                end do
            end do
        end do
    end do
    if (mod(ny, 2) == 0) then
!$OMP DO PRIVATE(I,II,J,TEMP)
        do k = 1, nz
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
            do j = 1, ny, 2
                cx(1) = cmplx(real(b(1, j, k)), real(b(1, j + 1, k)))
!DIR$ VECTOR ALIGNED
                do i = 2, nx/2 + 1
                    temp = (0.0_real32, 1.0_real32)*b(i, j + 1, k)
                    cx(i) = b(i, j, k) + temp
                    cx(nx - i + 2) = conjg(b(i, j, k) - temp)
                end do
                call fft235_r32(cx, d, wx, nx, lnx)
                do i = 1, nx
                    da(i, j, k) = real(cx(i))*dn
                    da(i, j + 1, k) = imag(cx(i))*dn
                end do
            end do
        end do
    else
!$OMP DO PRIVATE(I,II,TEMP)
        do k = 1, nz
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
            do j = 1, ny - 1, 2
                cx(1) = cmplx(real(b(1, j, k)), real(b(1, j + 1, k)))
!DIR$ VECTOR ALIGNED
                do i = 2, nx/2 + 1
                    temp = (0.0_real32, 1.0_real32)*b(i, j + 1, k)
                    cx(i) = b(i, j, k) + temp
                    cx(nx - i + 2) = conjg(b(i, j, k) - temp)
                end do
                call fft235_r32(cx, d, wx, nx, lnx)
                do i = 1, nx
                    da(i, j, k) = real(cx(i))*dn
                    da(i, j + 1, k) = imag(cx(i))*dn
                end do
            end do
            cx(1) = cmplx(real(b(1, ny, k)), 0.0_real32)
!DIR$ VECTOR ALIGNED
            do i = 2, nx/2 + 1
                cx(i) = b(i, ny, k)
                cx(nx - i + 2) = conjg(b(i, ny, k))
            end do
            call fft235_r32(cx, d, wx, nx, lnx)
            do i = 1, nx
                da(i, ny, k) = real(cx(i))*dn
            end do
        end do
    end if
    return
end subroutine zdfft3d0_32

end module zdfft3d_m
