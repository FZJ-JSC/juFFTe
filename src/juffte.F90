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
use factor_m
use utils_m
use iso_c_binding
use param

implicit none


logical                  :: juffte_initialized = .false. 

! FFTW interface
integer                  :: fftw_plan       = 0
integer                  :: fftw_dir = 0
integer                  :: fftw_size       = 0   

interface dzfft1d
    module procedure :: dzfft1d_r64
    module procedure :: dzfft1d_r32
end interface

interface zdfft1d
    module procedure :: zdfft1d_r64
    module procedure :: zdfft1d_r32
end interface

contains

type(C_PTR) function fftw_plan_dft_1d(n,input,output,sign,flags)
    implicit none

    integer(C_INT), value             :: n
    complex(real64), intent(inout)         :: input(:)
    complex(real64), intent(inout)         :: output(:)
    integer(C_INT), value, intent(in) :: sign
    integer(C_INT), value, intent(in) :: flags

fftw_plan = flags
fftw_dir  = sign
fftw_size = n

if (juffte_initialized .eqv. .false. ) then
    if (same(input,output)) then
        call zfft1d(input, fftw_size, juffte_init)
    else    
        call zfft1d(input, fftw_size, juffte_init, output)
        endif
        juffte_initialized = .true.
        endif

    end function fftw_plan_dft_1d

    subroutine fftw_execute_dft(pln, input, output)

        implicit none

        complex(real64), intent(inout)   :: input(:)
        complex(real64), intent(out)     :: output(:)
        type(C_PTR) , intent(in)    :: pln

        ! fftw_plan=pln
        fftw_size = size(input)
        if (same (input,output)) then
            call zfft1d(input, fftw_size, fftw_dir)
        else
            call zfft1d(input, fftw_size, fftw_dir, output)
            endif
        end subroutine fftw_execute_dft

        subroutine fftw_destroy_plan(pln)

            implicit none

            type(C_PTR), intent(in)         :: pln

            fftw_plan = 0
            fftw_size = 0 
        end subroutine fftw_destroy_plan


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

        subroutine zfft3d_c(input, nx, ny, nz, iopt) bind(C, name="zfft3d_c")
            implicit none
            integer(c_int), value, intent (in)       :: nx, ny, nz, iopt
            complex(c_double_complex), intent (inout):: input(nx*ny*nz)

            call zfft3d(input, nx, ny, nz, iopt)

        end subroutine zfft3d_c

        subroutine dzfft1d_c(a, a_c, n, iopt) bind(C, name="dzfft1d_c")
            implicit none
            integer(c_int), value, intent (in)      :: n, iopt
            real(c_double), intent (in)             :: a(*)
            complex(c_double_complex), intent (out) :: a_c(*)

            call dzfft2d(a, a_c, n,1, iopt)

        end subroutine dzfft1d_c

        subroutine dzfft1d_r32(a, a_c, n, iopt)
            implicit none
            integer(c_int), value, intent (in)      :: n, iopt
            real(c_float), intent (in)             :: a(*)
            complex(c_float_complex), intent (out) :: a_c(*)

            call dzfft2d(a, a_c, n,1, iopt)

        end subroutine dzfft1d_r32

        subroutine dzfft1d_r64(a, a_c, n, iopt)
            implicit none
            integer(c_int), value, intent (in)      :: n, iopt
            real(c_double), intent (in)             :: a(*)
            complex(c_double_complex), intent (out) :: a_c(*)

            call dzfft2d(a, a_c, n,1, iopt)

        end subroutine dzfft1d_r64


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

            call zdfft2d(a, a_r, n, 1, iopt)

        end subroutine zdfft1d_c

        subroutine zdfft1d_r32(a, a_r, n, iopt)
            implicit none

            complex(c_float_complex), intent(inout) :: a(*)
            real(c_float), intent(out)              :: a_r(*)
            integer(c_int), value, intent (in)       :: n, iopt

            call zdfft2d(a, a_r, n, 1, iopt)

        end subroutine zdfft1d_r32

        subroutine zdfft1d_r64(a, a_r, n, iopt)
            implicit none

            complex(c_double_complex), intent(inout) :: a(*)
            real(c_double), intent(out)              :: a_r(*)
            integer(c_int), value, intent (in)       :: n, iopt

            call zdfft2d(a, a_r, n, 1, iopt)

        end subroutine zdfft1d_r64

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