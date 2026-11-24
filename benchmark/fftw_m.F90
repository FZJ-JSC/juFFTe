! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module fftw_m
use, intrinsic :: iso_c_binding
use omp_lib
    implicit none
    include 'fftw3.f03'

private
public :: fftw_bench_plan, fftw_bench_run, fftw_bench_destroy

type(c_ptr) :: plan = c_null_ptr
! The planned arrays, for the execute calls (fftw3.f03 has no plain fftw_execute).
character(len=3) :: plan_type
complex(c_double_complex), pointer, contiguous :: c_in(:), c_out(:)
real(c_double), pointer, contiguous :: r(:)

contains

! Plans FFTW's counterpart of the juFFTe transform on the same arrays: c2c on a, in place or
! into b; r2c from a_r into a; c2r from a into a_r. FFTW is row-major, so the dimensions go
! in reversed. Planning other than with estimate overwrites the arrays.
subroutine fftw_bench_plan(fft_type, direction, placement, n, planner, wisdom, a, b, a_r)

character(len=*), intent(in)   :: fft_type, direction, placement, planner, wisdom
integer, intent(in)            :: n(:)
complex(c_double_complex), contiguous, target, intent(inout) :: a(:), b(:)
real(c_double), contiguous, target, intent(inout)            :: a_r(:)
integer(c_int) :: rank, dims(3), sign, flags, ok

if (fftw_init_threads() == 0) error stop "fftw_init_threads failed"
call fftw_plan_with_nthreads(omp_get_max_threads())

select case (planner)
case ("estimate"); flags = FFTW_ESTIMATE
case ("patient");  flags = FFTW_PATIENT
case default;      flags = FFTW_MEASURE
end select
if (len_trim(wisdom) > 0) ok = fftw_import_wisdom_from_filename(trim(wisdom) // c_null_char)

rank = size(n)
dims(1:rank) = int(n(rank:1:-1), c_int)
plan_type = fft_type
select case (fft_type)
case ("r2c")
    r => a_r
    c_out => a
    plan = fftw_plan_dft_r2c(rank, dims, r, c_out, flags)
case ("c2r")
    c_in => a
    r => a_r
    plan = fftw_plan_dft_c2r(rank, dims, c_in, r, flags)
case default
    sign = FFTW_FORWARD
    if (direction == "bw") sign = FFTW_BACKWARD
    c_in => a
    c_out => a
    if (placement == "out") c_out => b
    plan = fftw_plan_dft(rank, dims, c_in, c_out, sign, flags)
end select
if (.not. c_associated(plan)) error stop "FFTW could not plan the transform"

if (len_trim(wisdom) > 0) ok = fftw_export_wisdom_to_filename(trim(wisdom) // c_null_char)
end subroutine fftw_bench_plan

subroutine fftw_bench_run()
select case (plan_type)
case ("r2c"); call fftw_execute_dft_r2c(plan, r, c_out)
case ("c2r"); call fftw_execute_dft_c2r(plan, c_in, r)
case default; call fftw_execute_dft(plan, c_in, c_out)
end select
end subroutine fftw_bench_run

subroutine fftw_bench_destroy()
call fftw_destroy_plan(plan)
call fftw_cleanup_threads()
end subroutine fftw_bench_destroy

end module fftw_m
