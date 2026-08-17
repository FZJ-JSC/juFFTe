! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module zfft2d_m

use, intrinsic :: iso_fortran_env
use param
use factor_m
#ifdef SPRL
use fft235s_m
#else
use fft235_m
#endif

implicit none

complex(real64), allocatable :: b(:)
!$OMP THREADPRIVATE(b)
complex(real32), allocatable :: b_r32(:)
!$OMP THREADPRIVATE(b_r32)

private
public :: zfft2d, zfft2d_64, zfft2d_32

interface zfft2d
  module procedure zfft2d_64, zfft2d_32
end interface

contains

subroutine zfft2d_64(a, nx, ny, iopt, out)

    implicit none

    complex(real64), intent(inout) :: a(*)
    complex(real64), optional, intent(out)   :: out(*)
    integer, intent(in) :: nx, ny, iopt
    complex(real64), save :: wx(NDA2), wy(NDA2), c(NDA2)
#ifdef SPRL
    integer, save :: lnx(16), lny(16)
#else 
    integer, save :: lnx(3), lny(3)
#endif
    real(real64) :: dn
    integer :: i


    if (iopt == juffte_init) then
    allocate (b((NDA2 + NP)*NBLK))
#ifdef SPRL
    call factor2(nx,lnx)
    call factor2(ny,lny)
#endif
        call settbl(wx, nx)
        call settbl(wy, ny)
        return
    end if

    if (iopt == juffte_bw) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny
                a(i) = dconjg(a(i))
            end do
    end if
#ifndef SPRL
    call factor(nx, lnx)
    call factor(ny, lny)
#endif
if (present(out)) then
!$OMP PARALLEL PRIVATE(C)
    call zfft2d0_64(a, b, c, wx, wy, nx, ny, lnx, lny, out)
!$OMP END PARALLEL
else
!$OMP PARALLEL PRIVATE(C)
    call zfft2d0_64(a, b, c, wx, wy, nx, ny, lnx, lny)
!$OMP END PARALLEL
endif
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
    return
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

subroutine zfft2d_32(a, nx, ny, iopt, out)

    implicit none

    complex(real32), intent(inout)         :: a(*)
    complex(real32), optional, intent(out) :: out(*)
    integer, intent(in) :: nx, ny, iopt
    complex(real32) :: wx(NDA2), wy(NDA2),  c(NDA2)
#ifdef SPRL
    integer, save :: lnx(16), lny(16)
#else 
    integer, save :: lnx(3), lny(3)
#endif
    real(real32) :: dn
    integer :: i


    if (iopt == juffte_init) then
       allocate (b_r32((NDA2 + NP)*NBLK))
#ifdef SPRL
    call factor2(nx,lnx)
    call factor2(ny,lny)
#endif
        call settbl_r32(wx, nx)
        call settbl_r32(wy, ny)
        return
    end if

    if (iopt == juffte_bw) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny
                a(i) = conjg(a(i))
            end do
    end if
#ifndef SPRL
    call factor(nx, lnx)
    call factor(ny, lny)
#endif
if (present(out)) then
!$OMP PARALLEL PRIVATE(C)
    call zfft2d0_32(a, b_r32, c, wx, wy, nx, ny, lnx, lny, out)
!$OMP END PARALLEL
else
!$OMP PARALLEL PRIVATE(C)
    call zfft2d0_32(a, b_r32, c, wx, wy, nx, ny, lnx, lny)
!$OMP END PARALLEL
endif
    if (iopt == juffte_bw) then
        dn = 1.0_real32/(real(nx)*real(ny))
        if (present (out)) then
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny
                out(i) = conjg(a(i))*dn
            end do
        else
!$OMP PARALLEL DO
!DIR$ VECTOR ALIGNED
            do i = 1, nx*ny
                a(i) = conjg(a(i))*dn
            end do
        end if
    end if
    return
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