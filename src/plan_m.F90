! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

! A plan holds what a transform of one shape in one precision keeps between calls: the
! factorisations, the twiddle tables and a work array. Every call of a transform begins
! with plan_begin and ends with plan_end.
!
! Shared plans: each transform module keeps a list of them. Calling the transform with
! juffte_init takes a reference to the plan of its shape, making the plan if there is none;
! juffte_destroy drops a reference and frees the plan with the last one. Every other call
! looks the plan up and stops if there is none. The lists, the counts and the claims on
! work arrays change only inside the critical section juffte_plans, so transforms can be
! initialised, run and destroyed from several threads at once. A running call counts as a
! user of the plan, so that a destroy meanwhile frees it only when the call is done.
!
! Plans of the caller's own, a juffte_plan passed as plan=: juffte_init makes one, any other
! call runs on it, juffte_destroy frees it. It stays out of the lists, so its calls take no
! lock and nobody else can destroy it. As an FFTW plan, it may run from several threads at
! once, but not while it is being made or destroyed, and making a new one in the same
! juffte_plan does not free the old.
!
! Either way, a plan's work array serves one call at a time; a concurrent call allocates its
! own. A plan also keeps work arrays for threads, as many slots as OpenMP had threads when it
! was made, which plan_thread hands out inside the parallel regions of the calls; a thread
! that finds them all taken allocates its own.
module plan_m

use, intrinsic :: iso_fortran_env
use param
use factor_m
#ifdef SPRL
use fft235s_m
#else
use fft235_m
#endif
!$ use omp_lib, only: omp_get_max_threads, omp_get_thread_num
implicit none

private
public :: plan_t, juffte_plan, plan_begin, plan_end, plan_thread, plan_thread_end

! A thread's work array, made by that thread on first use.
type :: slot_t
    integer :: busy = 0
    complex(real64), allocatable :: w(:)
    complex(real32), allocatable :: w_r32(:)
end type slot_t

type :: plan_t
    character(len=8) :: routine = ''  ! the transform it is for
    integer :: rank = 0, n(3) = 1, prec = 0
    logical :: listed = .false.      ! shared, in a module's list
    integer :: refs = 0              ! juffte_init calls not yet matched by juffte_destroy
    integer :: calls = 0             ! calls running on the plan
    integer :: busy = 0              ! 1 while a call has b or b_r32
    integer :: lp(16, 3) = 0         ! the radices fft235 takes, per dimension
    complex(real64), allocatable :: wx(:), wy(:), wz(:), w(:), b(:)
    complex(real32), allocatable :: wx_r32(:), wy_r32(:), wz_r32(:), w_r32(:), b_r32(:)
    integer :: nthread = 0           ! elements of a thread's work array
    type(slot_t), allocatable :: slots(:)
    type(plan_t), pointer :: next => null()
end type plan_t

! A plan of the caller's own, for the plan= argument of the transforms.
type :: juffte_plan
    private
    type(plan_t), pointer :: p => null()
end type juffte_plan

abstract interface
    ! Fills in the tables of a new plan, whose rank, n and prec are set.
    subroutine build_i(p)
        import :: plan_t
        type(plan_t), intent(inout) :: p
    end subroutine build_i
end interface

! call plan_begin(head, routine, n, iopt, p, b [, nwork] [, build] [, nthread] [, plan])
!
! The start of every call of a transform, of shape n, in the list head, or with the plan
! of the caller's own if plan is present; routine names the transform. juffte_init checks
! the sizes and makes or takes a plan, building it with build, or with the tables of
! fft235 along each dimension, with a work array of nwork elements and per-thread ones of
! nthread (build may set p%nthread itself). juffte_destroy drops or frees it. Both leave p
! unassociated, and the transform returns. Any other iopt: p is the plan and b the call's
! work array, the plan's or one of the same size while another call has that, until
! plan_end(p, b). The kind of b selects the precision; b stays unassociated if the plan has
! no work array.
interface plan_begin
    module procedure plan_begin_64, plan_begin_32
end interface

interface plan_end
    module procedure plan_end_64, plan_end_32
end interface

! call plan_thread(p, w, k) ... call plan_thread_end(p, w, k)
!
! Inside the parallel region of a call: w is the calling thread's work array of p%nthread
! elements, that of slot k or, with k = 0, one of its own.
interface plan_thread
    module procedure plan_thread_64, plan_thread_32
end interface

interface plan_thread_end
    module procedure plan_thread_end_64, plan_thread_end_32
end interface

contains

subroutine plan_begin_64(head, routine, n, iopt, p, b, nwork, build, nthread, plan)
    type(plan_t), pointer, intent(inout) :: head
    character(len=*), intent(in) :: routine
    integer, intent(in) :: n(:), iopt
    type(plan_t), pointer, intent(out) :: p
    complex(real64), pointer, contiguous, intent(out) :: b(:)
    integer, intent(in), optional :: nwork
    integer(int64), intent(in), optional :: nthread
    procedure(build_i), optional :: build
    type(juffte_plan), intent(inout), optional :: plan
    logical :: own

    call check_iopt(routine, iopt)
    b => null()
    if (present(plan) .or. iopt == juffte_init .or. iopt == juffte_destroy) then
        call begin(head, routine, n, 64, iopt, p, own, nwork, build, nthread, plan)
    else
        call plan_acquire(head, routine, n, 64, p, own)
    end if
    if (.not. associated(p)) return
    if (own) then
        b => p%b
    else if (allocated(p%b)) then
        allocate(b(size(p%b)))
    end if
end subroutine plan_begin_64

subroutine plan_begin_32(head, routine, n, iopt, p, b, nwork, build, nthread, plan)
    type(plan_t), pointer, intent(inout) :: head
    character(len=*), intent(in) :: routine
    integer, intent(in) :: n(:), iopt
    type(plan_t), pointer, intent(out) :: p
    complex(real32), pointer, contiguous, intent(out) :: b(:)
    integer, intent(in), optional :: nwork
    integer(int64), intent(in), optional :: nthread
    procedure(build_i), optional :: build
    type(juffte_plan), intent(inout), optional :: plan
    logical :: own

    call check_iopt(routine, iopt)
    b => null()
    if (present(plan) .or. iopt == juffte_init .or. iopt == juffte_destroy) then
        call begin(head, routine, n, 32, iopt, p, own, nwork, build, nthread, plan)
    else
        call plan_acquire(head, routine, n, 32, p, own)
    end if
    if (.not. associated(p)) return
    if (own) then
        b => p%b_r32
    else if (allocated(p%b_r32)) then
        allocate(b(size(p%b_r32)))
    end if
end subroutine plan_begin_32

! The end of a call that plan_begin started: gives the work array back, or frees the
! call's own.
subroutine plan_end_64(p, b)
    type(plan_t), pointer, intent(inout) :: p
    complex(real64), pointer, contiguous, intent(inout) :: b(:)
    logical :: own

    own = .false.
    if (allocated(p%b)) own = associated(b, p%b)
    if (associated(b) .and. .not. own) deallocate(b)
    call plan_release(p, own)
end subroutine plan_end_64

subroutine plan_end_32(p, b)
    type(plan_t), pointer, intent(inout) :: p
    complex(real32), pointer, contiguous, intent(inout) :: b(:)
    logical :: own

    own = .false.
    if (allocated(p%b_r32)) own = associated(b, p%b_r32)
    if (associated(b) .and. .not. own) deallocate(b)
    call plan_release(p, own)
end subroutine plan_end_32

! plan_begin for juffte_init, juffte_destroy and plans of the caller's own, without the
! work array. own: the call has the plan's work array to itself.
subroutine begin(head, routine, n, prec, iopt, p, own, nwork, build, nthread, plan)
    type(plan_t), pointer, intent(inout) :: head
    character(len=*), intent(in) :: routine
    integer, intent(in) :: n(:), prec, iopt
    type(plan_t), pointer, intent(out) :: p
    logical, intent(out) :: own
    integer, intent(in), optional :: nwork
    integer(int64), intent(in), optional :: nthread
    procedure(build_i), optional :: build
    type(juffte_plan), intent(inout), optional :: plan

    p => null()
    own = .false.
    if (iopt == juffte_init) call check_shape(routine, n)
    if (.not. present(plan)) then
        if (iopt == juffte_init) then
            call plan_init(head, routine, n, prec, nwork, build, nthread)
        else
            call plan_destroy(head, routine, n, prec)
        end if
        return
    end if

    select case (iopt)
    case (juffte_init)
        ! Never reads what plan held: a private copy in an OpenMP region need not be
        ! default-initialised (gfortran's are not). A plan it held is the caller's to destroy.
        plan%p => make(routine, n, prec, nwork, build, nthread)
    case (juffte_destroy)
        call check_own(routine, n, prec, plan%p)
        deallocate(plan%p)
    case default
        call check_own(routine, n, prec, plan%p)
        p => plan%p
        own = claim(p)
    end select
end subroutine begin

! Stops unless every length of shape n is a product of 2, 3 and 5, and the transform has
! no more elements than a default integer counts.
subroutine check_shape(routine, n)
    character(len=*), intent(in) :: routine
    integer, intent(in) :: n(:)
    integer :: d

    do d = 1, size(n)
        call check_size(routine, n(d))
    end do
    if (product(int(n, int64)) > huge(0)) then
        write(error_unit, '(a,": ",a," has more than ",i0," elements")') &
            routine, trim(shape_text(n)), huge(0)
        error stop 1
    end if
end subroutine check_shape

! A new plan, not yet in any list.
function make(routine, n, prec, nwork, build, nthread) result(p)
    character(len=*), intent(in) :: routine
    integer, intent(in) :: n(:), prec
    integer, intent(in), optional :: nwork
    integer(int64), intent(in), optional :: nthread
    procedure(build_i), optional :: build
    type(plan_t), pointer :: p
    integer :: slots

    allocate(p)
    p%routine = routine
    p%rank = size(n)
    p%n(1:size(n)) = n
    p%prec = prec
    if (present(nthread)) then
        if (nthread > huge(0)) then
            write(error_unit, '(a,": ",a," needs per-thread work arrays of more than ",i0, &
                              &" elements")') routine, trim(shape_text(n)), huge(0)
            error stop 1
        end if
        p%nthread = int(nthread)
    end if
    if (present(build)) then
        call build(p)
    else
        call tables(p)
    end if
    if (present(nwork)) then
        if (prec == 64) then
            allocate(p%b(nwork))
        else
            allocate(p%b_r32(nwork))
        end if
    end if
    if (p%nthread > 0) then
        slots = 1
!$      slots = omp_get_max_threads()
        allocate(p%slots(slots))
    end if
end function make

! The tables of fft235 along each dimension. A 1-D plan gets a second dimension of length
! 1, for the 1-D real transforms, which are the 2-D ones with one row.
subroutine tables(p)
    type(plan_t), intent(inout) :: p
    integer :: d

    do d = 1, max(p%rank, 2)
        call radices(p%n(d), p%lp(:, d))
    end do
    if (p%prec == 64) then
        allocate(p%wx(p%n(1)), p%wy(p%n(2)))
        call settbl(p%wx, p%n(1))
        call settbl(p%wy, p%n(2))
        if (p%rank == 3) then
            allocate(p%wz(p%n(3)))
            call settbl(p%wz, p%n(3))
        end if
    else
        allocate(p%wx_r32(p%n(1)), p%wy_r32(p%n(2)))
        call settbl_r32(p%wx_r32, p%n(1))
        call settbl_r32(p%wy_r32, p%n(2))
        if (p%rank == 3) then
            allocate(p%wz_r32(p%n(3)))
            call settbl_r32(p%wz_r32, p%n(3))
        end if
    end if
end subroutine tables

! Takes a reference to the shared plan of shape n in precision prec (32 or 64), making it
! if there is none. It is built outside the critical section, so that the other
! transforms keep running meanwhile; if another thread has made the same plan by then,
! this one is dropped.
subroutine plan_init(head, routine, n, prec, nwork, build, nthread)
    type(plan_t), pointer, intent(inout) :: head
    character(len=*), intent(in) :: routine
    integer, intent(in) :: n(:), prec
    integer, intent(in), optional :: nwork
    integer(int64), intent(in), optional :: nthread
    procedure(build_i), optional :: build
    type(plan_t), pointer :: p, new

!$OMP CRITICAL (juffte_plans)
    p => find(head, n, prec)
    if (associated(p)) p%refs = p%refs + 1
!$OMP END CRITICAL (juffte_plans)
    if (associated(p)) return

    new => make(routine, n, prec, nwork, build, nthread)
    new%listed = .true.
!$OMP CRITICAL (juffte_plans)
    p => find(head, n, prec)
    if (associated(p)) then
        p%refs = p%refs + 1
    else
        new%refs = 1
        new%next => head
        head => new
    end if
!$OMP END CRITICAL (juffte_plans)
    if (associated(p)) deallocate(new)
end subroutine plan_init

! Drops a reference to the shared plan of shape n. With the last one the plan leaves the
! list, and is freed once no call is running on it.
subroutine plan_destroy(head, routine, n, prec)
    type(plan_t), pointer, intent(inout) :: head
    character(len=*), intent(in) :: routine
    integer, intent(in) :: n(:), prec
    type(plan_t), pointer :: p, prev
    logical :: found, gone

    gone = .false.
!$OMP CRITICAL (juffte_plans)
    p => find(head, n, prec, prev)
    found = associated(p)
    if (found) then
        p%refs = p%refs - 1
        if (p%refs == 0) then
            if (associated(prev)) then
                prev%next => p%next
            else
                head => p%next
            end if
            gone = p%calls == 0
        end if
    end if
!$OMP END CRITICAL (juffte_plans)
    if (.not. found) call missing(routine, n, prec, ' to destroy')
    if (gone) deallocate(p)
end subroutine plan_destroy

! The shared plan of shape n for one call, which hands it back with plan_release. own:
! the call has the plan's work array to itself.
subroutine plan_acquire(head, routine, n, prec, p, own)
    type(plan_t), pointer, intent(in) :: head
    character(len=*), intent(in) :: routine
    integer, intent(in) :: n(:), prec
    type(plan_t), pointer, intent(out) :: p
    logical, intent(out) :: own

    own = .false.
!$OMP CRITICAL (juffte_plans)
    p => find(head, n, prec)
    if (associated(p)) then
        p%calls = p%calls + 1
        own = p%busy == 0 .and. (allocated(p%b) .or. allocated(p%b_r32))
        if (own) p%busy = 1
    end if
!$OMP END CRITICAL (juffte_plans)
    if (.not. associated(p)) call missing(routine, n, prec, '; call it with juffte_init first')
end subroutine plan_acquire

! Claims the work array of a plan of the caller's own for a call.
logical function claim(p)
    type(plan_t), intent(inout) :: p

    claim = .false.
    if (allocated(p%b) .or. allocated(p%b_r32)) claim = take(p%busy)
end function claim

! Sets flag from 0 to 1 without a lock; false if it was 1. The swap here and the release in
! give are sequentially consistent, so whoever takes the flag next sees the writes made
! while it was held. Reading first leaves the flag's cache line alone while it is held.
logical function take(flag)
    integer, intent(inout) :: flag
    integer :: old

!$OMP ATOMIC READ SEQ_CST
    old = flag
    if (old == 0) then
!$OMP ATOMIC CAPTURE SEQ_CST
        old = flag
        flag = 1
!$OMP END ATOMIC
    end if
    take = old == 0
end function take

subroutine give(flag)
    integer, intent(inout) :: flag

!$OMP ATOMIC WRITE SEQ_CST
    flag = 0
end subroutine give

! Takes a free slot for the calling thread, its own thread number's first: callers from an
! outer parallel region all have thread number 0 in their own teams. 0 if all are taken.
integer function slot(p) result(k)
    type(plan_t), pointer, intent(in) :: p
    integer :: first, i

    k = 0
    if (.not. allocated(p%slots)) return
    first = 0
!$  first = omp_get_thread_num()
    do i = 0, size(p%slots) - 1
        k = mod(first + i, size(p%slots)) + 1
        if (take(p%slots(k)%busy)) return
    end do
    k = 0
end function slot

subroutine plan_thread_64(p, w, k)
    type(plan_t), pointer, intent(in) :: p
    complex(real64), pointer, contiguous, intent(out) :: w(:)
    integer, intent(out) :: k

    k = slot(p)
    if (k == 0) then
        allocate(w(p%nthread))
        return
    end if
    if (.not. allocated(p%slots(k)%w)) allocate(p%slots(k)%w(p%nthread))
    w => p%slots(k)%w
end subroutine plan_thread_64

subroutine plan_thread_32(p, w, k)
    type(plan_t), pointer, intent(in) :: p
    complex(real32), pointer, contiguous, intent(out) :: w(:)
    integer, intent(out) :: k

    k = slot(p)
    if (k == 0) then
        allocate(w(p%nthread))
        return
    end if
    if (.not. allocated(p%slots(k)%w_r32)) allocate(p%slots(k)%w_r32(p%nthread))
    w => p%slots(k)%w_r32
end subroutine plan_thread_32

! Gives slot k back, or frees w if the thread had none (k = 0).
subroutine plan_thread_end_64(p, w, k)
    type(plan_t), pointer, intent(in) :: p
    complex(real64), pointer, contiguous, intent(inout) :: w(:)
    integer, intent(in) :: k

    if (k > 0) then
        call give(p%slots(k)%busy)
    else
        deallocate(w)
    end if
end subroutine plan_thread_end_64

subroutine plan_thread_end_32(p, w, k)
    type(plan_t), pointer, intent(in) :: p
    complex(real32), pointer, contiguous, intent(inout) :: w(:)
    integer, intent(in) :: k

    if (k > 0) then
        call give(p%slots(k)%busy)
    else
        deallocate(w)
    end if
end subroutine plan_thread_end_32

! Ends a call on p. A shared plan is freed if it was destroyed meanwhile; inside the
! critical section, so that the next call to claim the work array sees this one's writes.
subroutine plan_release(p, own)
    type(plan_t), pointer, intent(inout) :: p
    logical, intent(in) :: own
    logical :: gone

    if (.not. p%listed) then
        if (own) call give(p%busy)
        return
    end if
!$OMP CRITICAL (juffte_plans)
    if (own) p%busy = 0
    p%calls = p%calls - 1
    gone = p%refs == 0 .and. p%calls == 0
!$OMP END CRITICAL (juffte_plans)
    if (gone) deallocate(p)
end subroutine plan_release

! Stops unless iopt is juffte_init, juffte_fw, juffte_bw or juffte_destroy.
subroutine check_iopt(routine, iopt)
    character(len=*), intent(in) :: routine
    integer, intent(in) :: iopt

    select case (iopt)
    case (juffte_init, juffte_fw, juffte_bw, juffte_destroy)
    case default
        write(error_unit, '(a,": iopt is ",i0,"; use juffte_init (",i0,"), juffte_fw (",i0, &
                          &"), juffte_bw (",i0,") or juffte_destroy (",i0,")")') routine, iopt, &
            juffte_init, juffte_fw, juffte_bw, juffte_destroy
        error stop 1
    end select
end subroutine check_iopt

! Stops unless p, the plan of the caller's own, is one for this transform of shape n in
! precision prec.
subroutine check_own(routine, n, prec, p)
    character(len=*), intent(in) :: routine
    integer, intent(in) :: n(:), prec
    type(plan_t), pointer, intent(in) :: p

    if (.not. associated(p)) then
        write(error_unit, '(a,": plan= holds no plan; make it with juffte_init first")') routine
        error stop 1
    end if
    if (p%routine /= routine .or. .not. matches(p, n, prec)) then
        write(error_unit, '(a,": plan= holds a ",a," plan for ",a," in FP",i0,", not a ",a, &
                          &" plan for ",a," in FP",i0)') routine, trim(p%routine), &
            trim(shape_text(p%n(1:p%rank))), p%prec, routine, trim(shape_text(n)), prec
        error stop 1
    end if
end subroutine check_own

! The plan of shape n in precision prec in the list head, and the one before it in prev.
function find(head, n, prec, prev) result(p)
    type(plan_t), pointer, intent(in) :: head
    integer, intent(in) :: n(:), prec
    type(plan_t), pointer, intent(out), optional :: prev
    type(plan_t), pointer :: p, before

    before => null()
    p => head
    do while (associated(p))
        if (matches(p, n, prec)) exit
        before => p
        p => p%next
    end do
    if (present(prev)) prev => before
end function find

logical function matches(p, n, prec)
    type(plan_t), intent(in) :: p
    integer, intent(in) :: n(:), prec

    matches = p%prec == prec .and. p%rank == size(n)
    if (matches) matches = all(p%n(1:size(n)) == n)
end function matches

! "length 96" or "16 x 32"
function shape_text(n) result(text)
    integer, intent(in) :: n(:)
    character(len=64) :: text

    if (size(n) == 1) then
        write(text, '("length ",i0)') n(1)
    else
        write(text, '(i0,*(:," x ",i0))') n
    end if
end function shape_text

subroutine missing(routine, n, prec, advice)
    character(len=*), intent(in) :: routine, advice
    integer, intent(in) :: n(:), prec

    write(error_unit, '(a,": no FP",i0," plan for ",a,a)') routine, prec, trim(shape_text(n)), &
        advice
    error stop 1
end subroutine missing

end module plan_m
