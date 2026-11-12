! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

! Distributed 2-D and 3-D complex transforms over MPI, built with USE_MPI only: the slab
! decomposition of FFTE's pzfft2d and pzfft3d (D. Takahashi, Fast Fourier Transform
! Algorithms for Parallel Computers, Springer 2019, Sects. 8.1.3 and 8.1.4).
!
! a(nx, ny, nz) is distributed along z over the np ranks of a communicator: rank r holds the
! nz/np planes from r*nz/np on, as a(nx, ny, nz/np), both for the input and the output. The
! FFTs along x and y of a rank's planes are local. An all-to-all then hands every rank its
! nx/np values of x in all planes, (nx/np, ny, nz), for the FFTs along z, and a second one
! brings the result back into planes. np must divide nx and nz. pzfft2d is the same with
! ny = 1: a(nx, ny) distributed along y, as a(nx, ny/np), np dividing nx and ny.
!
! The plans are always the caller's own (plan=) and belong to the communicator, which must
! stay valid while the plan lives. Every call is collective: all ranks of the communicator
! make, run and destroy a plan together, in the same order, and only one transform at a time
! may run on a communicator, never two from different threads (unlike the serial plans).
! MPI is called from the calling thread only, outside parallel regions, so
! MPI_THREAD_FUNNELED suffices if that is the main thread. The whole transform may have more
! than 2^31 - 1 elements; a rank's work, two arrays of its share, may not.
module pzfft3d_m

use, intrinsic :: iso_fortran_env
use mpi_f08
use param
use factor_m
use plan_m
#ifdef SPRL
use fft235s_m
#else
use fft235_m
#endif

implicit none

! Never holds a plan: distributed plans are the caller's own.
type(plan_t), pointer :: plans => null()

private
public :: pzfft2d, pzfft2d_64, pzfft2d_32, pzfft3d, pzfft3d_64, pzfft3d_32

interface pzfft2d
  module procedure pzfft2d_64, pzfft2d_32
end interface

interface pzfft3d
  module procedure pzfft3d_64, pzfft3d_32
end interface

contains

! The work of a plan of routine, of shape dims, as nx x ny x nz on comm: two arrays of a
! rank's share. Stops, on every rank alike, unless the number of ranks divides nx and nz, or
! if that work has more elements than a default integer counts.
integer function work_size(routine, dims, nx, ny, nz, comm)
    character(len=*), intent(in) :: routine
    integer, intent(in) :: dims(:), nx, ny, nz
    type(MPI_Comm), intent(in) :: comm
    character(len=2), parameter :: zname(2:3) = ['ny', 'nz']
    integer :: np
    integer(int64) :: n

    call MPI_Comm_size(comm, np)
    if (mod(nx, np) /= 0 .or. mod(nz, np) /= 0) then
        write(error_unit, '(a,": nx = ",i0," and ",a," = ",i0," on ",i0, &
                          &" ranks; the number of ranks must divide both")') &
            routine, nx, zname(size(dims)), nz, np
        error stop 1
    end if
    n = 2*int(nx, int64)*ny*(nz/np)
    if (n > huge(0)) then
        write(error_unit, '(a,": a rank needs ",i0," elements of work, more than ",i0, &
                          &"; take more ranks")') routine, n, huge(0)
        error stop 1
    end if
    work_size = int(n)
end function work_size

! A thread's work array: a line along x, or NBLK lines along y or z, and the FFT's work.
integer(int64) function thread_size(nx, ny, nz)
    integer, intent(in) :: nx, ny, nz

    thread_size = max(int(nx, int64) + NP, (int(max(ny, nz), int64) + NP)*NBLK) + max(nx, ny, nz)
end function thread_size

! The shape of plan p as nx x ny x nz, a 2-D one's as nx x 1 x ny.
function shape3(p) result(n)
    type(plan_t), intent(in) :: p
    integer :: n(3)

    if (p%rank == 2) then
        n = [p%n(1), 1, p%n(2)]
    else
        n = p%n
    end if
end function shape3

! The 3-D transform of a(nx, ny, nz/np), this rank's planes, in place or into out, of the
! same shape: iopt juffte_init, juffte_fw, juffte_bw or juffte_destroy, on all ranks of comm.
subroutine pzfft3d_64(a, nx, ny, nz, comm, iopt, plan, out)
    complex(real64), intent(inout)         :: a(*)
    integer, intent(in)                    :: nx, ny, nz, iopt
    type(MPI_Comm), intent(in)             :: comm
    type(juffte_plan), intent(inout)       :: plan
    complex(real64), optional, intent(out) :: out(*)

    call slabs_64('pzfft3d', [nx, ny, nz], a, nx, ny, nz, comm, iopt, plan, out)
end subroutine pzfft3d_64

! The 2-D transform of a(nx, ny/np), distributed along y: that of nx x 1 x ny.
subroutine pzfft2d_64(a, nx, ny, comm, iopt, plan, out)
    complex(real64), intent(inout)         :: a(*)
    integer, intent(in)                    :: nx, ny, iopt
    type(MPI_Comm), intent(in)             :: comm
    type(juffte_plan), intent(inout)       :: plan
    complex(real64), optional, intent(out) :: out(*)

    call slabs_64('pzfft2d', [nx, ny], a, nx, 1, ny, comm, iopt, plan, out)
end subroutine pzfft2d_64

! The transform of routine, planned as dims, on a(nx, ny, nz/np); a 2-D one is nx x 1 x ny.
! The plan's work b holds two arrays of a rank's share: the FFTs along x and y read a, the
! last step writes out or a.
subroutine slabs_64(routine, dims, a, nx, ny, nz, comm, iopt, plan, out)
    character(len=*), intent(in)           :: routine
    integer, intent(in)                    :: dims(:), nx, ny, nz, iopt
    complex(real64), intent(inout)         :: a(*)
    type(MPI_Comm), intent(in)             :: comm
    type(juffte_plan), intent(inout)       :: plan
    complex(real64), optional, intent(out) :: out(*)
    complex(real64), pointer, contiguous   :: b(:)
    type(plan_t), pointer                  :: p
    integer                                :: nwork, nl

    nwork = 0
    if (iopt == juffte_init) nwork = work_size(routine, dims, nx, ny, nz, comm)
    call plan_begin(plans, routine, dims, iopt, p, b, nwork=nwork, build=build3_64, &
                    nthread=thread_size(nx, ny, nz), plan=plan, comm=comm%MPI_VAL)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return
    nl = size(b)/2
    call xy_out_64(p, a, b, nx, ny, nz/p%np, iopt == juffte_bw)
    if (present(out)) then
        call steps_64(p, out, b(1:nl), b(nl + 1:), nx, ny, nz, iopt == juffte_bw)
    else
        call steps_64(p, a, b(1:nl), b(nl + 1:), nx, ny, nz, iopt == juffte_bw)
    end if
    call plan_end(p, b)
end subroutine slabs_64

! The tables of a plan of nx x ny x nz, or of a 2-D one: radices and twiddles of the FFTs
! along each dimension.
subroutine build3_64(p)
    type(plan_t), intent(inout) :: p
    type(MPI_Comm) :: comm
    integer :: n(3), d

    comm%MPI_VAL = p%comm
    call MPI_Comm_size(comm, p%np)
    call MPI_Comm_rank(comm, p%me)
    n = shape3(p)
    do d = 1, 3
        call radices(n(d), p%lp(:, d))
    end do
    allocate(p%wx(n(1)), p%wy(n(2)), p%wz(n(3)))
    call settbl(p%wx, n(1))
    call settbl(p%wy, n(2))
    call settbl(p%wz, n(3))
end subroutine build3_64

! The FFTs along x and y of a(nx, ny, nnz), this rank's planes, conjugated first for a
! backward transform, into c(nnx, ny, nnz, np): the np blocks of nnx = nx/np values of x,
! one for each rank, block after block.
subroutine xy_out_64(p, a, c, nx, ny, nnz, backward)
    type(plan_t), pointer, intent(in) :: p
    integer, intent(in) :: nx, ny, nnz
    complex(real64), intent(in) :: a(nx, ny*nnz)
    complex(real64), intent(inout) :: c(*)
    logical, intent(in) :: backward
    complex(real64), pointer, contiguous :: w(:)
    integer :: slot

!$OMP PARALLEL PRIVATE(W,SLOT)
    call plan_thread(p, w, slot)
    call xlines_64(p, a, c, nx, ny*nnz, p%np, backward, w)
    ! The blocks follow each other: their lines along y are those of c(nnx, ny, nnz*np).
    if (ny > 1) call ylines_64(p, c, nx/p%np, ny, nnz*p%np, w)
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
end subroutine xy_out_64

! The FFTs along x of the m lines a(:, j), conjugated first if backward, cut into the np
! blocks of x, c(nx/np, m, np). Inside a parallel region, w a thread's work.
subroutine xlines_64(p, a, c, nx, m, np, backward, w)
    type(plan_t), pointer, intent(in) :: p
    integer, intent(in) :: nx, m, np
    complex(real64), intent(in) :: a(nx, m)
    complex(real64), intent(inout) :: c(nx/np, m, np)
    logical, intent(in) :: backward
    complex(real64), pointer, contiguous, intent(in) :: w(:)
    complex(real64), pointer, contiguous :: cx(:), d(:)
    integer :: j, q, nnx

    nnx = nx/np
    cx => w(1:nx + NP)
    d => w(nx + NP + 1:)
!$OMP DO
    do j = 1, m
        if (backward) then
            cx(1:nx) = conjg(a(:, j))
        else
            cx(1:nx) = a(:, j)
        end if
        call fft235(cx, d, p%wx, nx, p%lp(:, 1))
        do q = 1, np
            c(:, j, q) = cx((q - 1)*nnx + 1:q*nnx)
        end do
    end do
!$OMP END DO
end subroutine xlines_64

! The FFTs along y, in place, of c(nnx, ny, m), in blocks of NBLK columns. Inside a parallel
! region, w a thread's work.
subroutine ylines_64(p, c, nnx, ny, m, w)
    type(plan_t), pointer, intent(in) :: p
    integer, intent(in) :: nnx, ny, m
    complex(real64), intent(inout) :: c(nnx, ny, m)
    complex(real64), pointer, contiguous, intent(in) :: w(:)
    complex(real64), pointer, contiguous :: cy(:, :), d(:)
    integer :: i, ii, j, k

    cy(1:ny + NP, 1:NBLK) => w
    d => w((ny + NP)*NBLK + 1:)
!$OMP DO COLLAPSE(2)
    do k = 1, m
        do ii = 1, nnx, NBLK
            do j = 1, ny
                do i = ii, min(ii + NBLK - 1, nnx)
                    cy(j, i - ii + 1) = c(i, j, k)
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nnx)
                call fft235(cy(:, i - ii + 1), d, p%wy, ny, p%lp(:, 2))
            end do
            do j = 1, ny
                do i = ii, min(ii + NBLK - 1, nnx)
                    c(i, j, k) = cy(j, i - ii + 1)
                end do
            end do
        end do
    end do
!$OMP END DO
end subroutine ylines_64

! The steps after the FFTs along x and y, whose output is in b1: the all-to-all into b2,
! where it is this rank's block of x of every plane, (nnx, ny, nz); the FFTs along z into b1;
! the all-to-all back into b2, the blocks of x of this rank's planes; and those into
! y(nx, ny, nnz), conjugated and divided by n for a backward transform.
subroutine steps_64(p, y, b1, b2, nx, ny, nz, backward)
    type(plan_t), pointer, intent(in) :: p
    complex(real64), intent(out) :: y(*)
    complex(real64), intent(inout) :: b1(*), b2(*)
    integer, intent(in) :: nx, ny, nz
    logical, intent(in) :: backward
    type(MPI_Comm) :: comm
    integer :: nnx, nnz, count

    comm%MPI_VAL = p%comm
    nnx = nx/p%np
    nnz = nz/p%np
    count = nnx*ny*nnz
    call MPI_Alltoall(b1, count, MPI_DOUBLE_COMPLEX, b2, count, MPI_DOUBLE_COMPLEX, comm)
    call zlines_64(p, b2, b1, nnx, ny, nz)
    call MPI_Alltoall(b1, count, MPI_DOUBLE_COMPLEX, b2, count, MPI_DOUBLE_COMPLEX, comm)
    call rearrange_out_64(b2, y, nx, ny*nnz, p%np, backward, nx*real(ny, real64)*nz)
end subroutine steps_64

! The FFTs along z of s(nnx, ny, nz) into t(nnx, ny, nz), in blocks of NBLK columns.
subroutine zlines_64(p, s, t, nnx, ny, nz)
    type(plan_t), pointer, intent(in) :: p
    integer, intent(in) :: nnx, ny, nz
    complex(real64), intent(in) :: s(nnx, ny, nz)
    complex(real64), intent(out) :: t(nnx, ny, nz)
    complex(real64), pointer, contiguous :: w(:), cz(:, :), d(:)
    integer :: i, ii, j, k, slot

!$OMP PARALLEL PRIVATE(W,CZ,D,SLOT,I,K)
    call plan_thread(p, w, slot)
    cz(1:nz + NP, 1:NBLK) => w
    d => w((nz + NP)*NBLK + 1:)
!$OMP DO COLLAPSE(2)
    do j = 1, ny
        do ii = 1, nnx, NBLK
            do k = 1, nz
                do i = ii, min(ii + NBLK - 1, nnx)
                    cz(k, i - ii + 1) = s(i, j, k)
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nnx)
                call fft235(cz(:, i - ii + 1), d, p%wz, nz, p%lp(:, 3))
            end do
            do k = 1, nz
                do i = ii, min(ii + NBLK - 1, nnx)
                    t(i, j, k) = cz(k, i - ii + 1)
                end do
            end do
        end do
    end do
!$OMP END DO
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
end subroutine zlines_64

! The np blocks of x of this rank's m lines, c(nx/np, m, np), into natural order, y(nx, m);
! conjugated and divided by n for a backward transform.
subroutine rearrange_out_64(c, y, nx, m, np, backward, n)
    integer, intent(in) :: nx, m, np
    complex(real64), intent(in) :: c(nx/np, m, np)
    complex(real64), intent(out) :: y(nx, m)
    logical, intent(in) :: backward
    real(real64), intent(in) :: n
    real(real64) :: dn
    integer :: j, q, nnx

    nnx = nx/np
    dn = 1/n
!$OMP PARALLEL DO PRIVATE(Q)
    do j = 1, m
        do q = 1, np
            if (backward) then
                y((q - 1)*nnx + 1:q*nnx, j) = conjg(c(:, j, q))*dn
            else
                y((q - 1)*nnx + 1:q*nnx, j) = c(:, j, q)
            end if
        end do
    end do
end subroutine rearrange_out_64

! The 3-D transform of a(nx, ny, nz/np), this rank's planes, in place or into out, of the
! same shape: iopt juffte_init, juffte_fw, juffte_bw or juffte_destroy, on all ranks of comm.
subroutine pzfft3d_32(a, nx, ny, nz, comm, iopt, plan, out)
    complex(real32), intent(inout)         :: a(*)
    integer, intent(in)                    :: nx, ny, nz, iopt
    type(MPI_Comm), intent(in)             :: comm
    type(juffte_plan), intent(inout)       :: plan
    complex(real32), optional, intent(out) :: out(*)

    call slabs_32('pzfft3d', [nx, ny, nz], a, nx, ny, nz, comm, iopt, plan, out)
end subroutine pzfft3d_32

! The 2-D transform of a(nx, ny/np), distributed along y: that of nx x 1 x ny.
subroutine pzfft2d_32(a, nx, ny, comm, iopt, plan, out)
    complex(real32), intent(inout)         :: a(*)
    integer, intent(in)                    :: nx, ny, iopt
    type(MPI_Comm), intent(in)             :: comm
    type(juffte_plan), intent(inout)       :: plan
    complex(real32), optional, intent(out) :: out(*)

    call slabs_32('pzfft2d', [nx, ny], a, nx, 1, ny, comm, iopt, plan, out)
end subroutine pzfft2d_32

! The transform of routine, planned as dims, on a(nx, ny, nz/np); a 2-D one is nx x 1 x ny.
! The plan's work b holds two arrays of a rank's share: the FFTs along x and y read a, the
! last step writes out or a.
subroutine slabs_32(routine, dims, a, nx, ny, nz, comm, iopt, plan, out)
    character(len=*), intent(in)           :: routine
    integer, intent(in)                    :: dims(:), nx, ny, nz, iopt
    complex(real32), intent(inout)         :: a(*)
    type(MPI_Comm), intent(in)             :: comm
    type(juffte_plan), intent(inout)       :: plan
    complex(real32), optional, intent(out) :: out(*)
    complex(real32), pointer, contiguous   :: b(:)
    type(plan_t), pointer                  :: p
    integer                                :: nwork, nl

    nwork = 0
    if (iopt == juffte_init) nwork = work_size(routine, dims, nx, ny, nz, comm)
    call plan_begin(plans, routine, dims, iopt, p, b, nwork=nwork, build=build3_32, &
                    nthread=thread_size(nx, ny, nz), plan=plan, comm=comm%MPI_VAL)
    if (iopt == juffte_init .or. iopt == juffte_destroy) return
    nl = size(b)/2
    call xy_out_32(p, a, b, nx, ny, nz/p%np, iopt == juffte_bw)
    if (present(out)) then
        call steps_32(p, out, b(1:nl), b(nl + 1:), nx, ny, nz, iopt == juffte_bw)
    else
        call steps_32(p, a, b(1:nl), b(nl + 1:), nx, ny, nz, iopt == juffte_bw)
    end if
    call plan_end(p, b)
end subroutine slabs_32

! The tables of a plan of nx x ny x nz, or of a 2-D one: radices and twiddles of the FFTs
! along each dimension.
subroutine build3_32(p)
    type(plan_t), intent(inout) :: p
    type(MPI_Comm) :: comm
    integer :: n(3), d

    comm%MPI_VAL = p%comm
    call MPI_Comm_size(comm, p%np)
    call MPI_Comm_rank(comm, p%me)
    n = shape3(p)
    do d = 1, 3
        call radices(n(d), p%lp(:, d))
    end do
    allocate(p%wx_r32(n(1)), p%wy_r32(n(2)), p%wz_r32(n(3)))
    call settbl_r32(p%wx_r32, n(1))
    call settbl_r32(p%wy_r32, n(2))
    call settbl_r32(p%wz_r32, n(3))
end subroutine build3_32

! The FFTs along x and y of a(nx, ny, nnz), this rank's planes, conjugated first for a
! backward transform, into c(nnx, ny, nnz, np): the np blocks of nnx = nx/np values of x,
! one for each rank, block after block.
subroutine xy_out_32(p, a, c, nx, ny, nnz, backward)
    type(plan_t), pointer, intent(in) :: p
    integer, intent(in) :: nx, ny, nnz
    complex(real32), intent(in) :: a(nx, ny*nnz)
    complex(real32), intent(inout) :: c(*)
    logical, intent(in) :: backward
    complex(real32), pointer, contiguous :: w(:)
    integer :: slot

!$OMP PARALLEL PRIVATE(W,SLOT)
    call plan_thread(p, w, slot)
    call xlines_32(p, a, c, nx, ny*nnz, p%np, backward, w)
    ! The blocks follow each other: their lines along y are those of c(nnx, ny, nnz*np).
    if (ny > 1) call ylines_32(p, c, nx/p%np, ny, nnz*p%np, w)
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
end subroutine xy_out_32

! The FFTs along x of the m lines a(:, j), conjugated first if backward, cut into the np
! blocks of x, c(nx/np, m, np). Inside a parallel region, w a thread's work.
subroutine xlines_32(p, a, c, nx, m, np, backward, w)
    type(plan_t), pointer, intent(in) :: p
    integer, intent(in) :: nx, m, np
    complex(real32), intent(in) :: a(nx, m)
    complex(real32), intent(inout) :: c(nx/np, m, np)
    logical, intent(in) :: backward
    complex(real32), pointer, contiguous, intent(in) :: w(:)
    complex(real32), pointer, contiguous :: cx(:), d(:)
    integer :: j, q, nnx

    nnx = nx/np
    cx => w(1:nx + NP)
    d => w(nx + NP + 1:)
!$OMP DO
    do j = 1, m
        if (backward) then
            cx(1:nx) = conjg(a(:, j))
        else
            cx(1:nx) = a(:, j)
        end if
        call fft235_r32(cx, d, p%wx_r32, nx, p%lp(:, 1))
        do q = 1, np
            c(:, j, q) = cx((q - 1)*nnx + 1:q*nnx)
        end do
    end do
!$OMP END DO
end subroutine xlines_32

! The FFTs along y, in place, of c(nnx, ny, m), in blocks of NBLK columns. Inside a parallel
! region, w a thread's work.
subroutine ylines_32(p, c, nnx, ny, m, w)
    type(plan_t), pointer, intent(in) :: p
    integer, intent(in) :: nnx, ny, m
    complex(real32), intent(inout) :: c(nnx, ny, m)
    complex(real32), pointer, contiguous, intent(in) :: w(:)
    complex(real32), pointer, contiguous :: cy(:, :), d(:)
    integer :: i, ii, j, k

    cy(1:ny + NP, 1:NBLK) => w
    d => w((ny + NP)*NBLK + 1:)
!$OMP DO COLLAPSE(2)
    do k = 1, m
        do ii = 1, nnx, NBLK
            do j = 1, ny
                do i = ii, min(ii + NBLK - 1, nnx)
                    cy(j, i - ii + 1) = c(i, j, k)
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nnx)
                call fft235_r32(cy(:, i - ii + 1), d, p%wy_r32, ny, p%lp(:, 2))
            end do
            do j = 1, ny
                do i = ii, min(ii + NBLK - 1, nnx)
                    c(i, j, k) = cy(j, i - ii + 1)
                end do
            end do
        end do
    end do
!$OMP END DO
end subroutine ylines_32

! The steps after the FFTs along x and y, whose output is in b1: the all-to-all into b2,
! where it is this rank's block of x of every plane, (nnx, ny, nz); the FFTs along z into b1;
! the all-to-all back into b2, the blocks of x of this rank's planes; and those into
! y(nx, ny, nnz), conjugated and divided by n for a backward transform.
subroutine steps_32(p, y, b1, b2, nx, ny, nz, backward)
    type(plan_t), pointer, intent(in) :: p
    complex(real32), intent(out) :: y(*)
    complex(real32), intent(inout) :: b1(*), b2(*)
    integer, intent(in) :: nx, ny, nz
    logical, intent(in) :: backward
    type(MPI_Comm) :: comm
    integer :: nnx, nnz, count

    comm%MPI_VAL = p%comm
    nnx = nx/p%np
    nnz = nz/p%np
    count = nnx*ny*nnz
    call MPI_Alltoall(b1, count, MPI_COMPLEX, b2, count, MPI_COMPLEX, comm)
    call zlines_32(p, b2, b1, nnx, ny, nz)
    call MPI_Alltoall(b1, count, MPI_COMPLEX, b2, count, MPI_COMPLEX, comm)
    call rearrange_out_32(b2, y, nx, ny*nnz, p%np, backward, nx*real(ny, real32)*nz)
end subroutine steps_32

! The FFTs along z of s(nnx, ny, nz) into t(nnx, ny, nz), in blocks of NBLK columns.
subroutine zlines_32(p, s, t, nnx, ny, nz)
    type(plan_t), pointer, intent(in) :: p
    integer, intent(in) :: nnx, ny, nz
    complex(real32), intent(in) :: s(nnx, ny, nz)
    complex(real32), intent(out) :: t(nnx, ny, nz)
    complex(real32), pointer, contiguous :: w(:), cz(:, :), d(:)
    integer :: i, ii, j, k, slot

!$OMP PARALLEL PRIVATE(W,CZ,D,SLOT,I,K)
    call plan_thread(p, w, slot)
    cz(1:nz + NP, 1:NBLK) => w
    d => w((nz + NP)*NBLK + 1:)
!$OMP DO COLLAPSE(2)
    do j = 1, ny
        do ii = 1, nnx, NBLK
            do k = 1, nz
                do i = ii, min(ii + NBLK - 1, nnx)
                    cz(k, i - ii + 1) = s(i, j, k)
                end do
            end do
            do i = ii, min(ii + NBLK - 1, nnx)
                call fft235_r32(cz(:, i - ii + 1), d, p%wz_r32, nz, p%lp(:, 3))
            end do
            do k = 1, nz
                do i = ii, min(ii + NBLK - 1, nnx)
                    t(i, j, k) = cz(k, i - ii + 1)
                end do
            end do
        end do
    end do
!$OMP END DO
    call plan_thread_end(p, w, slot)
!$OMP END PARALLEL
end subroutine zlines_32

! The np blocks of x of this rank's m lines, c(nx/np, m, np), into natural order, y(nx, m);
! conjugated and divided by n for a backward transform.
subroutine rearrange_out_32(c, y, nx, m, np, backward, n)
    integer, intent(in) :: nx, m, np
    complex(real32), intent(in) :: c(nx/np, m, np)
    complex(real32), intent(out) :: y(nx, m)
    logical, intent(in) :: backward
    real(real32), intent(in) :: n
    real(real32) :: dn
    integer :: j, q, nnx

    nnx = nx/np
    dn = 1/n
!$OMP PARALLEL DO PRIVATE(Q)
    do j = 1, m
        do q = 1, np
            if (backward) then
                y((q - 1)*nnx + 1:q*nnx, j) = conjg(c(:, j, q))*dn
            else
                y((q - 1)*nnx + 1:q*nnx, j) = c(:, j, q)
            end if
        end do
    end do
end subroutine rearrange_out_32

end module pzfft3d_m
