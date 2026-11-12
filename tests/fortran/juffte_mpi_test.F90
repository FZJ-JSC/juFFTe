! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------
!
! Checks the distributed transforms on the ranks it is started on, one per run:
!
!   mpiexec -n np juffte_mpi_test_f [-d fw|bw] [-c] nx ny [nz]
!
! Two sizes check pzfft2d, three pzfft3d, in juFFTe's order, nx contiguous; forward unless
! -d bw. The transform is checked in FP64 and FP32, in place and out of place, which must
! leave its input unchanged. Every rank makes the same random input, transforms all of it
! with the serial transform, zfft2d or zfft3d in FP64 (checked against FFTW and the DFT by
! juffte_test_f), and compares its slab of the distributed result with that; the errors are
! summed over the ranks. -c runs a plan on a duplicate of the communicator it was made on,
! which must stop. Exit status on every rank: 0 pass, 1 fail, 2 usage.
program juffte_mpi_test

use, intrinsic :: iso_fortran_env
use mpi_f08
use juffte
implicit none

type(MPI_Comm) :: comm
integer :: n(3), rank, np, me, iopt, provided, failures, nt, nloc, off
logical :: other_comm
character(len=40) :: dims
complex(real64), allocatable :: x(:), ref(:)

call MPI_Init_thread(MPI_THREAD_FUNNELED, provided)
comm = MPI_COMM_WORLD
call MPI_Comm_size(comm, np)
call MPI_Comm_rank(comm, me)
if (provided < MPI_THREAD_FUNNELED) then
    if (me == 0) print '(a)', 'FAIL: MPI does not provide MPI_THREAD_FUNNELED'
    call MPI_Finalize()
    stop 1
end if
call parse_args()
failures = 0

! A rank's slab: its planes, or in 2-D its rows, follow each other in the whole array.
nt = product(n(1:rank))
nloc = nt/np
off = me*nloc
if (rank == 2) write(dims, '(i0," x ",i0)') n(1:2)
if (rank == 3) write(dims, '(i0," x ",i0," x ",i0)') n
if (me == 0) print '("pzfft",i0,"d ",a," of ",a," on ",i0," ranks")', rank, &
    trim(merge('forward ', 'backward', iopt == juffte_fw)), trim(dims), np

if (other_comm) call run_on_other_comm()
allocate(x(nt), ref(nt))
call seed()
x = cmplx(random_real(nt), random_real(nt), real64)
call reference(x, ref)
call check_64(x, ref)
! FP32 against the FP64 transform of the input rounded to FP32.
x = cmplx(real(real(x), real32), real(aimag(x), real32), real64)
call reference(x, ref)
call check_32(x, ref)

call MPI_Finalize()
if (failures > 0) stop 1

contains

    subroutine usage()
        if (me == 0) print '(a)', 'usage: mpiexec -n np juffte_mpi_test_f [-d fw|bw] [-c] nx ny [nz]'
        call MPI_Finalize()
        stop 2
    end subroutine usage

    subroutine parse_args()
        character(len=32) :: arg
        integer :: i, stat

        iopt = juffte_fw
        other_comm = .false.
        rank = 0
        n = 1
        i = 1
        do while (i <= command_argument_count())
            call get_command_argument(i, arg)
            select case (arg)
            case ('-d')
                i = i + 1
                call get_command_argument(i, arg)
                select case (arg)
                case ('fw')
                    iopt = juffte_fw
                case ('bw')
                    iopt = juffte_bw
                case default
                    call usage()
                end select
            case ('-c')
                other_comm = .true.
            case default
                if (rank == 3) call usage()
                rank = rank + 1
                read(arg, *, iostat=stat) n(rank)
                if (stat /= 0) call usage()
                if (n(rank) < 1) call usage()
            end select
            i = i + 1
        end do
        if (rank < 2) call usage()
    end subroutine parse_args

    subroutine seed()
        integer :: k, j
        integer, allocatable :: s(:)

        call random_seed(size=k)
        allocate(s(k))
        s = [(104729*j + 7, j = 1, k)]
        call random_seed(put=s)
    end subroutine seed

    ! Random values in [-1, 1), the same on every rank.
    function random_real(count) result(v)
        integer, intent(in) :: count
        real(real64) :: v(count)

        call random_number(v)
        v = 2*v - 1
    end function random_real

    ! The serial transform of all of x into y.
    subroutine reference(x, y)
        complex(real64), intent(inout) :: x(:)
        complex(real64), intent(out) :: y(:)
        type(juffte_plan) :: sp

        if (rank == 2) then
            call zfft2d(x, n(1), n(2), juffte_init, plan=sp)
            call zfft2d(x, n(1), n(2), iopt, out=y, plan=sp)
            call zfft2d(x, n(1), n(2), juffte_destroy, plan=sp)
        else
            call zfft3d(x, n(1), n(2), n(3), juffte_init, plan=sp)
            call zfft3d(x, n(1), n(2), n(3), iopt, out=y, plan=sp)
            call zfft3d(x, n(1), n(2), n(3), juffte_destroy, plan=sp)
        end if
    end subroutine reference

    ! The relative 2-norm error of this rank's slab y against want, over all ranks, against
    ! that of an FFT in precision prec plus the reference's.
    subroutine check(what, y, want, prec)
        character(len=*), intent(in) :: what
        complex(real64), intent(in) :: y(:), want(:)
        integer, intent(in) :: prec
        real(real64) :: s(2), err, bound, eps
        character(len=24) :: w

        s = [sum(abs(y - want)**2), sum(abs(want)**2)]
        call MPI_Allreduce(MPI_IN_PLACE, s, 2, MPI_DOUBLE_PRECISION, MPI_SUM, comm)
        err = sqrt(s(1)/s(2))
        eps = merge(real(epsilon(1.0_real32), real64), epsilon(1.0_real64), prec == 32)
        bound = 2*log(real(max(nt, 2), real64))/log(2.0_real64)*(eps + epsilon(1.0_real64))
        w = what
        if (me == 0) print '(2x,a,1x,"rel. error ",es9.2,"   bound ",es9.2,3x,a)', w, err, &
            bound, trim(merge('ok  ', 'FAIL', err <= bound))
        if (.not. err <= bound) failures = failures + 1  ! NaN fails too
    end subroutine check

    ! Fails unless every rank's input is unchanged.
    subroutine check_unchanged(what, same)
        character(len=*), intent(in) :: what
        logical, intent(in) :: same
        logical :: all_same
        character(len=24) :: w

        call MPI_Allreduce(same, all_same, 1, MPI_LOGICAL, MPI_LAND, comm)
        w = what
        if (me == 0) print '(2x,a,1x,"input unchanged",36x,a)', w, &
            trim(merge('ok  ', 'FAIL', all_same))
        if (.not. all_same) failures = failures + 1
    end subroutine check_unchanged

    subroutine check_64(x, ref)
        complex(real64), intent(in) :: x(:), ref(:)
        complex(real64), allocatable :: a(:), b(:)
        type(juffte_plan) :: plan

        allocate(a(nloc), b(nloc))
        a = x(off + 1:off + nloc)
        call run_64(a, juffte_init, plan)
        call run_64(a, iopt, plan)
        call check('FP64 in place', a, ref(off + 1:off + nloc), 64)
        a = x(off + 1:off + nloc)
        call run_64(a, iopt, plan, b)
        call check('FP64 out of place', b, ref(off + 1:off + nloc), 64)
        call check_unchanged('FP64 out of place', all(a == x(off + 1:off + nloc)))
        call run_64(a, juffte_destroy, plan)
    end subroutine check_64

    subroutine check_32(x, ref)
        complex(real64), intent(in) :: x(:), ref(:)
        complex(real32), allocatable :: a(:), b(:)
        type(juffte_plan) :: plan

        allocate(a(nloc), b(nloc))
        a = cmplx(x(off + 1:off + nloc), kind=real32)
        call run_32(a, juffte_init, plan)
        call run_32(a, iopt, plan)
        call check('FP32 in place', cmplx(a, kind=real64), ref(off + 1:off + nloc), 32)
        a = cmplx(x(off + 1:off + nloc), kind=real32)
        call run_32(a, iopt, plan, b)
        call check('FP32 out of place', cmplx(b, kind=real64), ref(off + 1:off + nloc), 32)
        call check_unchanged('FP32 out of place', &
                             all(a == cmplx(x(off + 1:off + nloc), kind=real32)))
        call run_32(a, juffte_destroy, plan)
    end subroutine check_32

    subroutine run_64(a, iop, plan, b)
        complex(real64), intent(inout) :: a(:)
        integer, intent(in) :: iop
        type(juffte_plan), intent(inout) :: plan
        complex(real64), intent(out), optional :: b(:)

        if (rank == 2) then
            call pzfft2d(a, n(1), n(2), comm, iop, plan, b)
        else
            call pzfft3d(a, n(1), n(2), n(3), comm, iop, plan, b)
        end if
    end subroutine run_64

    subroutine run_32(a, iop, plan, b)
        complex(real32), intent(inout) :: a(:)
        integer, intent(in) :: iop
        type(juffte_plan), intent(inout) :: plan
        complex(real32), intent(out), optional :: b(:)

        if (rank == 2) then
            call pzfft2d(a, n(1), n(2), comm, iop, plan, b)
        else
            call pzfft3d(a, n(1), n(2), n(3), comm, iop, plan, b)
        end if
    end subroutine run_32

    ! A plan made on comm and run on a duplicate of it: the library must stop.
    subroutine run_on_other_comm()
        complex(real64), allocatable :: a(:)
        type(juffte_plan) :: plan
        type(MPI_Comm) :: dup

        allocate(a(nloc))
        a = 0
        call MPI_Comm_dup(comm, dup)
        call run_64(a, juffte_init, plan)
        comm = dup
        call run_64(a, iopt, plan)
        if (me == 0) print '(a)', 'FAIL: the plan ran on another communicator'
        call MPI_Finalize()
        stop 1
    end subroutine run_on_other_comm

end program juffte_mpi_test
