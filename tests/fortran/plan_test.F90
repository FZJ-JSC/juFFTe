! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------
!
! Checks the plans (src/plan_m.F90) where the transform tests cannot reach them in a
! deterministic way, and the messages with which they stop a program:
!
!   plan_test           a destroy while a call runs, and a plan someone else made meanwhile
!   plan_test CASE      must stop with the message of CASE: unmade, other-shape,
!                       other-transform, too-large, work-too-large or bad-iopt
!
! Run it with MALLOC_PERTURB_ set, so that memory freed too early does not keep its
! contents. Exit status: 0 pass, 1 fail, 2 usage; the stops exit with 1 as well.

module plan_test_m

    use, intrinsic :: iso_fortran_env, only: real64
    use param, only: juffte_init, juffte_fw, juffte_destroy
    use plan_m
    implicit none

    type(plan_t), pointer :: plans => null()

contains

    ! Builds nothing, but makes the same plan meanwhile, as another thread could.
    subroutine build_meanwhile(p)
        type(plan_t), intent(inout) :: p
        type(plan_t), pointer :: q
        complex(real64), pointer, contiguous :: b(:)

        call plan_begin(plans, 'test', p%n(1:p%rank), juffte_init, q, b)
    end subroutine build_meanwhile

end module plan_test_m


program plan_test

    use plan_test_m
    use juffte, only: zfft1d, zfft2d, zfft3d, dzfft2d, juffte_plan
    implicit none

    character(len=16) :: what
    integer :: failures = 0

    call get_command_argument(1, what)
    select case (what)
    case ('')
        call destroy_while_running()
        call made_meanwhile()
    case ('unmade', 'other-shape', 'other-transform', 'too-large', 'work-too-large', 'bad-iopt')
        call stop_on(what)
        print '(a)', 'FAIL: did not stop'
        stop 1
    case default
        print '(a)', 'usage: plan_test [unmade|other-shape|other-transform|too-large|' // &
                     'work-too-large|bad-iopt]'
        stop 2
    end select
    if (failures > 0) then
        print '(a)', 'FAIL'
        stop 1
    end if
    print '(a)', 'PASS'

contains

    subroutine check(what, ok)
        character(len=*), intent(in) :: what
        logical, intent(in) :: ok
        character(len=48) :: w

        w = what
        print '(2x,a,1x,a)', w, trim(merge('ok  ', 'FAIL', ok))
        if (.not. ok) failures = failures + 1
    end subroutine check

    ! The last reference goes while a call runs on the plan: the plan leaves the list at
    ! once, and keeps its tables and work array until the call ends.
    subroutine destroy_while_running()
        type(plan_t), pointer :: p, q
        complex(real64), pointer, contiguous :: b(:), none(:)
        complex(real64), allocatable :: wx(:)

        call plan_begin(plans, 'test', [16, 8], juffte_init, p, b, nwork=32)
        call plan_begin(plans, 'test', [16, 8], juffte_fw, p, b)
        wx = p%wx
        b = 1
        call plan_begin(plans, 'test', [16, 8], juffte_destroy, q, none)
        call check('destroyed plan leaves the list', .not. associated(plans))
        call check('the running call keeps it', p%refs == 0 .and. p%calls == 1)
        call check('with its tables', all(p%wx == wx))
        call check('and its work array', associated(b, p%b) .and. all(b == 1))
        call plan_end(p, b)
    end subroutine destroy_while_running

    ! While a plan is built, someone else makes the same one: the list keeps theirs, with
    ! both references, and drops the one built second.
    subroutine made_meanwhile()
        type(plan_t), pointer :: p
        complex(real64), pointer, contiguous :: b(:)

        call plan_begin(plans, 'test', [12, 10], juffte_init, p, b, build=build_meanwhile)
        call plan_begin(plans, 'test', [12, 10], juffte_fw, p, b)
        call check('one plan of the shape', associated(plans, p) .and. .not. associated(p%next))
        call check('the one made first', allocated(p%wx))
        call check('with both references', p%refs == 2)
        call plan_end(p, b)
        call plan_begin(plans, 'test', [12, 10], juffte_destroy, p, b)
        call check('kept after one destroy', associated(plans))
        call plan_begin(plans, 'test', [12, 10], juffte_destroy, p, b)
        call check('gone after the second', .not. associated(plans))
    end subroutine made_meanwhile

    subroutine stop_on(what)
        character(len=*), intent(in) :: what
        type(juffte_plan) :: plan
        complex(real64) :: a(64)
        real(real64) :: r(64)

        a = 0
        r = 0
        select case (what)
        case ('unmade')
            call zfft1d(a, 16, juffte_fw, plan=plan)
        case ('other-shape')
            call zfft1d(a, 16, juffte_init, plan=plan)
            call zfft1d(a, 32, juffte_fw, plan=plan)
        case ('other-transform')
            call zfft2d(a, 4, 4, juffte_init, plan=plan)
            call dzfft2d(r, a, 4, 4, juffte_fw, plan=plan)
        case ('too-large')
            call zfft3d(a, 2048, 2048, 1024, juffte_init)
        case ('work-too-large')
            ! 2^28 elements, but a thread's work arrays would hold more than 2^31.
            call zfft2d(a, 2, 134217728, juffte_init)
        case ('bad-iopt')
            ! FFTE's transposed forward transform, which juFFTe does not have.
            call zfft1d(a, 16, -2)
        end select
    end subroutine stop_on

end program plan_test
