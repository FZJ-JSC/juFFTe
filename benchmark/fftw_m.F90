! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module fftw_m
use, intrinsic :: iso_fortran_env
use, intrinsic :: iso_fortran_env
use, intrinsic :: iso_c_binding
use omp_lib
use utils_m
    implicit none
    integer :: nthreads, err
type(C_PTR) :: plan
    include 'fftw3.f03'

private
public  :: fftw_warmup, fftw_bench

contains

subroutine fftw_warmup(n,dim,in,out)

integer, intent (in)      :: n(3), dim
complex(real64), intent(inout) :: in(:), out(:)

nthreads = omp_get_max_threads()

err = fftw_init_threads()
call fftw_plan_with_nthreads(nthreads)

if (dim == 1) then
    call init(in, n(1))
    plan = fftw_plan_dft_1d(n(1), in, out, FFTW_FORWARD, FFTW_ESTIMATE)
else if (dim == 2) then
    call init(in, n(1)*n(2))
    plan = fftw_plan_dft_2d(n(1),n(2), in, out, FFTW_FORWARD, FFTW_ESTIMATE)
else
    call init(in, n(1)*n(2)*n(3))
    plan = fftw_plan_dft_3d(n(1),n(2),n(3), in, out, FFTW_FORWARD, FFTW_ESTIMATE)
endif
call fftw_execute_dft(plan, in, out)
end subroutine fftw_warmup

subroutine fftw_bench(n,dim,in,out,time0)

integer, intent (in)      :: n(3), dim
complex(real64), intent(inout) :: in(:), out(:)
real(real64), intent(out) :: time0
real(real64)              :: time1, time2
integer              :: loop = 1 ,i

do
    time1 = omp_get_wtime()
    do i = 1, loop
        call fftw_execute_dft(plan, in, out)
    end do
    time2 = omp_get_wtime()
    time0 = time2 - time1
    if (time0 >= 1.0d0) then   ! to make sure the benchmarking takes at least 1s
        exit
    end if
    loop = loop*2
end do
time0 = time0/dble(loop)

end subroutine fftw_bench


end module fftw_m
