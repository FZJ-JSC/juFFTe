! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module juffte

use zfft1d_m
use zfft2d_m
use zfft3d_m
use dzfft2d_m
use zdfft2d_m
use dzfft3d_m
use zdfft3d_m
use plan_m, only: juffte_plan
use factor_m
use utils_m
use iso_c_binding
use param

implicit none

! A plan of the FFTW interfaces, Fortran and C: the transform, with the dimensions in the
! native API's order, nx contiguous, iopt juffte_fw or juffte_bw, and its own juFFTe plan,
! as an FFTW plan is its own: no other plan, and no juffte_destroy elsewhere, touches it.
type :: fftw_plan_t
    integer :: rank, n(3), iopt
    type(juffte_plan) :: plan
end type fftw_plan_t
private :: fftw_plan_t, fftw_plan_new, fftw_call, fftw_run

contains

type(C_PTR) function fftw_plan_dft_1d(n,input,output,sign,flags)
    implicit none

    integer(C_INT), value             :: n
    complex(real64), intent(inout)         :: input(:)
    complex(real64), intent(inout)         :: output(:)
    integer(C_INT), value, intent(in) :: sign
    integer(C_INT), value, intent(in) :: flags

    fftw_plan_dft_1d = fftw_plan_new(1, [n, 1, 1], sign)

    end function fftw_plan_dft_1d

    ! As in FFTW, dimensions are given slowest first, the reverse of the native API:
    ! a(nx, ny) is planned as (ny, nx), which is zfft2d(a, nx, ny).
    type(C_PTR) function fftw_plan_dft_2d(n0,n1,input,output,sign,flags)
        implicit none

        integer(C_INT), value             :: n0, n1
        complex(real64), intent(inout)         :: input(:)
        complex(real64), intent(inout)         :: output(:)
        integer(C_INT), value, intent(in) :: sign
        integer(C_INT), value, intent(in) :: flags

        fftw_plan_dft_2d = fftw_plan_new(2, [n1, n0, 1], sign)

        end function fftw_plan_dft_2d

    type(C_PTR) function fftw_plan_dft_3d(n0,n1,n2,input,output,sign,flags)
        implicit none

        integer(C_INT), value             :: n0, n1, n2
        complex(real64), intent(inout)         :: input(:)
        complex(real64), intent(inout)         :: output(:)
        integer(C_INT), value, intent(in) :: sign
        integer(C_INT), value, intent(in) :: flags

        fftw_plan_dft_3d = fftw_plan_new(3, [n2, n1, n0], sign)

        end function fftw_plan_dft_3d

    type(C_PTR) function fftw_plan_new(rank, n, dir)
        implicit none

        integer, intent(in)                    :: rank, n(3), dir
        type(fftw_plan_t), pointer             :: p
        complex(real64)                        :: none(1)

        allocate(p)
        p%rank = rank
        p%n = n
        ! As in FFTW, any sign but FFTW_FORWARD is backward.
        p%iopt = merge(juffte_fw, juffte_bw, dir == FFTW_FORWARD)
        call fftw_call(p, none, juffte_init)
        fftw_plan_new = c_loc(p)

        end function fftw_plan_new

    ! Calls the native transform of plan p with iopt, out of place if output is present.
    subroutine fftw_call(p, input, iopt, output)
        implicit none

        type(fftw_plan_t), intent(inout)       :: p
        complex(real64), intent(inout)         :: input(:)
        integer, intent(in)                    :: iopt
        complex(real64), intent(out), optional :: output(:)

        select case (p%rank)
        case (1); call zfft1d(input, p%n(1), iopt, output, plan=p%plan)
        case (2); call zfft2d(input, p%n(1), p%n(2), iopt, output, plan=p%plan)
        case default; call zfft3d(input, p%n(1), p%n(2), p%n(3), iopt, output, plan=p%plan)
        end select

        end subroutine fftw_call

    subroutine fftw_execute_dft(pln, input, output)

        implicit none

        complex(real64), intent(inout)   :: input(:)
        complex(real64), intent(out)     :: output(:)
        type(C_PTR) , intent(in)    :: pln
        type(fftw_plan_t), pointer  :: p

        if (.not. c_associated(pln)) return
        call c_f_pointer(pln, p)
        if (same(input, output)) then
            call fftw_run(p, input)
        else
            call fftw_run(p, input, output)
        end if
        end subroutine fftw_execute_dft

    ! Runs plan p on input, out of place into output if present: callers pass one array
    ! for an in-place transform, never the same one twice.
    subroutine fftw_run(p, input, output)
        implicit none

        type(fftw_plan_t), intent(inout)       :: p
        complex(real64), intent(inout)         :: input(:)
        complex(real64), intent(out), optional :: output(:)
        integer                                :: n

        call fftw_call(p, input, p%iopt, output)

        ! juFFTe scales the backward transform by 1/n, FFTW does not. Undo it so
        ! that ported FFTW code sees FFTW's convention.
        ! TODO: dirty fix. Settle the normalisation convention in the library instead.
        if (p%iopt == juffte_bw) then
            n = product(p%n)
            if (present(output)) then
                output(1:n) = output(1:n)*dble(n)
            else
                input(1:n) = input(1:n)*dble(n)
            end if
        end if
        end subroutine fftw_run

        subroutine fftw_destroy_plan(pln)

            implicit none

            type(C_PTR), intent(in)         :: pln
            type(fftw_plan_t), pointer      :: p
            complex(real64)                 :: none(1)

            if (.not. c_associated(pln)) return
            call c_f_pointer(pln, p)
            call fftw_call(p, none, juffte_destroy)
            deallocate(p)
        end subroutine fftw_destroy_plan

        ! The C FFTW layer (juffte_fftw.c) runs on the plans of this one. Dimensions in the
        ! native order, as in fftw_plan_t; arrays of the plan's size; output null in place.
        type(C_PTR) function fftw_plan_c(rank, nx, ny, nz, sign) bind(C, name="juffte_fftw_plan_c")
            implicit none
            integer(c_int), value, intent(in) :: rank, nx, ny, nz, sign

            fftw_plan_c = fftw_plan_new(rank, [nx, ny, nz], sign)

        end function fftw_plan_c

        subroutine fftw_execute_c(pln, input, output) bind(C, name="juffte_fftw_execute_c")
            implicit none
            type(C_PTR), value, intent(in)              :: pln, output
            complex(c_double_complex), intent(inout)    :: input(*)
            type(fftw_plan_t), pointer                  :: p
            complex(c_double_complex), pointer          :: out(:)
            integer                                     :: n

            call c_f_pointer(pln, p)
            n = product(p%n)
            if (c_associated(output)) then
                call c_f_pointer(output, out, [n])
                call fftw_run(p, input(1:n), out)
            else
                call fftw_run(p, input(1:n))
            end if

        end subroutine fftw_execute_c

        subroutine fftw_destroy_c(pln) bind(C, name="juffte_fftw_destroy_c")
            implicit none
            type(C_PTR), value, intent(in)  :: pln

            call fftw_destroy_plan(pln)

        end subroutine fftw_destroy_c

        subroutine fft_init(input)

            implicit none

            complex(real64), intent(inout)   :: input(:)
            integer                     :: n

            n = size(input)

            call zfft1d(input, n, 0)

        end subroutine fft_init

        subroutine fft_execute(input,dir)

            implicit none

            complex(real64), target, intent(inout)   :: input(:)
            integer, intent (in)                :: dir 
            integer                             :: n

            n = size(input)

            call zfft1d(input, n, dir)

        end subroutine fft_execute

        ! Drops the reference to the plan that fft_init took.
        subroutine fft_destroy(input)

            implicit none

            complex(real64), intent(inout)   :: input(:)

            call zfft1d(input, size(input), juffte_destroy)

        end subroutine fft_destroy

        subroutine zfft1d_out(input,output, n, dir)

            implicit none

            complex(real64), intent(inout) :: input(:)
            complex(real64), intent(out)   :: output(:)
            integer, intent (in)      :: dir 
            integer, intent (in)      :: n

            call zfft1d(input, n, dir, output)

        end subroutine zfft1d_out

        subroutine zfft1d_c(input, n, iopt) bind(C, name="zfft1d_c")
            implicit none
            integer(c_int), value, intent (in)        :: n, iopt
            complex(c_double_complex), intent (inout) :: input(n)

            call zfft1d(input, n, iopt)

        end subroutine zfft1d_c

        subroutine zfft1d_out_c(input, output, n, iopt) bind(C, name="zfft1d_out_c")
            implicit none
            integer(c_int), value, intent (in)        :: n, iopt
            complex(c_double_complex), intent (inout) :: input(n)
            complex(c_double_complex), intent (out)   :: output(n)

            call zfft1d(input, n, iopt, output)

        end subroutine zfft1d_out_c

        subroutine zfft2d_c(input, nx, ny, iopt) bind(C, name="zfft2d_c")
            implicit none
            integer(c_int), value, intent (in)       :: nx, ny, iopt
            complex(c_double_complex), intent (inout):: input(nx*ny)

            call zfft2d(input, nx, ny, iopt)

        end subroutine zfft2d_c

        subroutine zfft2d_out_c(input, output, nx, ny, iopt) bind(C, name="zfft2d_out_c")
            implicit none
            integer(c_int), value, intent (in)       :: nx, ny, iopt
            complex(c_double_complex), intent (inout):: input(nx*ny)
            complex(c_double_complex), intent (out)  :: output(nx*ny)

            call zfft2d(input, nx, ny, iopt, output)

        end subroutine zfft2d_out_c

        subroutine zfft3d_c(input, nx, ny, nz, iopt) bind(C, name="zfft3d_c")
            implicit none
            integer(c_int), value, intent (in)       :: nx, ny, nz, iopt
            complex(c_double_complex), intent (inout):: input(nx*ny*nz)

            call zfft3d(input, nx, ny, nz, iopt)

        end subroutine zfft3d_c
    
            subroutine zfft3d_out_c(input, output, nx, ny, nz, iopt) bind(C, name="zfft3d_out_c")
            implicit none
            integer(c_int), value, intent (in)       :: nx, ny, nz, iopt
            complex(c_double_complex), intent (inout):: input(nx*ny*nz)
            complex(c_double_complex), intent (out)  :: output(nx*ny*nz)

            call zfft3d(input, nx, ny, nz, iopt, output)

        end subroutine zfft3d_out_c

        subroutine dzfft1d_c(a, a_c, n, iopt) bind(C, name="dzfft1d_c")
            implicit none
            integer(c_int), value, intent (in)      :: n, iopt
            real(c_double), intent (in)             :: a(*)
            complex(c_double_complex), intent (out) :: a_c(*)

            call dzfft1d(a, a_c, n, iopt)

        end subroutine dzfft1d_c

        ! dzfft1d_r64/_r32 and zdfft1d_r64/_r32 were the specific procedures of dzfft1d and
        ! zdfft1d; these keep programs that named them working.
        subroutine dzfft1d_r64(a, a_c, n, iopt)
            implicit none
            integer(c_int), value, intent (in)      :: n, iopt
            real(c_double), intent (in)             :: a(*)
            complex(c_double_complex), intent (out) :: a_c(*)

            call dzfft1d(a, a_c, n, iopt)

        end subroutine dzfft1d_r64

        subroutine dzfft1d_r32(a, a_c, n, iopt)
            implicit none
            integer(c_int), value, intent (in)      :: n, iopt
            real(c_float), intent (in)              :: a(*)
            complex(c_float_complex), intent (out)  :: a_c(*)

            call dzfft1d(a, a_c, n, iopt)

        end subroutine dzfft1d_r32

        subroutine zdfft1d_r64(a, a_r, n, iopt)
            implicit none
            complex(c_double_complex), intent(inout) :: a(*)
            real(c_double), intent(out)              :: a_r(*)
            integer(c_int), value, intent (in)       :: n, iopt

            call zdfft1d(a, a_r, n, iopt)

        end subroutine zdfft1d_r64

        subroutine zdfft1d_r32(a, a_r, n, iopt)
            implicit none
            complex(c_float_complex), intent(inout) :: a(*)
            real(c_float), intent(out)              :: a_r(*)
            integer(c_int), value, intent (in)       :: n, iopt

            call zdfft1d(a, a_r, n, iopt)

        end subroutine zdfft1d_r32

        subroutine dzfft2d_c(a, a_c, nx, ny, iopt) bind(C, name="dzfft2d_c")
            implicit none
            integer(c_int), value, intent (in)      :: nx, ny, iopt
            real(c_double), intent (in)             :: a(*)
            complex(c_double_complex), intent (out) :: a_c(*)

            call dzfft2d(a, a_c, nx, ny, iopt)

        end subroutine dzfft2d_c

        subroutine dzfft3d_c(a, a_c, nx, ny, nz, iopt) bind(C, name="dzfft3d_c")
            implicit none

            integer(c_int), value, intent (in)      :: nx, ny, nz, iopt
            real(c_double), intent (in)             :: a(*)
            complex(c_double_complex), intent (out) :: a_c(*)

            call dzfft3d(a, a_c, nx, ny, nz, iopt)

        end subroutine dzfft3d_c
        subroutine zdfft1d_c(a, a_r, n, iopt) bind(C, name="zdfft1d_c")

            complex(c_double_complex), intent(inout) :: a(*)
            real(c_double), intent(out)              :: a_r(*)
            integer(c_int), value, intent (in)       :: n, iopt

            call zdfft1d(a, a_r, n, iopt)

        end subroutine zdfft1d_c

        subroutine zdfft2d_c(a, a_r, nx, ny, iopt) bind(C, name="zdfft2d_c")
            implicit none

            complex(c_double_complex), intent(inout) :: a(*)
            real(c_double), intent(out)              :: a_r(*)
            integer(c_int), value, intent (in)       :: nx, ny, iopt

            call zdfft2d(a, a_r, nx, ny, iopt)

        end subroutine zdfft2d_c

        subroutine zdfft3d_c(a, a_r, nx, ny, nz, iopt) bind(C, name="zdfft3d_c")
            implicit none

            complex(c_double_complex), intent(inout) :: a(*)
            real(c_double), intent(out)              :: a_r(*)
            integer(c_int), value, intent (in)       :: nx, ny, nz, iopt

            call zdfft3d(a, a_r, nx, ny, nz, iopt)

        end subroutine zdfft3d_c

    end module juffte