! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module utils_m

use, intrinsic :: iso_fortran_env
use iso_c_binding
implicit none
private
public :: same, aligned_allocate, aligned_deallocate

interface same
    module procedure same_real
    module procedure same_complex
end interface

interface
    function posix_memalign(ptr, alignment, size) bind(C)
        import
        type(c_ptr) :: ptr
        integer(c_size_t), value :: alignment
        integer(c_size_t), value :: size
        integer(c_int) :: posix_memalign
    end function

    subroutine free(ptr) bind(C)
        import
        type(c_ptr), value :: ptr
    end subroutine
end interface

interface aligned_allocate
    module procedure aligned_allocate_real
    module procedure aligned_allocate_complex
end interface

interface aligned_deallocate
    module procedure aligned_deallocate_real
    module procedure aligned_deallocate_complex
end interface

contains

logical function same_real (a,b)
real(real64), target, intent(in) :: a(:)
real(real64), target, intent(in) :: b(:)
same_real = c_associated(c_loc(a), c_loc(b))
end function same_real

logical function same_complex (a,b)
complex(real64), target, intent(in) :: a(:)
complex(real64), target, intent(in) :: b(:)
same_complex = c_associated(c_loc(a), c_loc(b))
end function same_complex

subroutine aligned_allocate_real(arr,n,alignment)
    implicit none
    real(c_double), pointer :: arr(:)
    integer, intent(in) :: n
    integer, intent(in) :: alignment

    type(c_ptr) :: raw
    integer(c_int) :: ierr

    ierr = posix_memalign(raw, int(alignment,c_size_t), int(n,c_size_t)*c_sizeof(0.0d0))
    if (ierr /= 0) error stop "allocation failed"

    call c_f_pointer(raw, arr, [n])
end subroutine


subroutine aligned_allocate_complex(arr,n,alignment)
    implicit none
    complex(c_double_complex), pointer :: arr(:)
    integer, intent(in) :: n
    integer, intent(in) :: alignment

    type(c_ptr) :: raw
    integer(c_int) :: ierr

    ierr = posix_memalign(raw, int(alignment,c_size_t), int(n,c_size_t)*c_sizeof((0.0d0,0.0d0)))
    if (ierr /= 0) error stop "allocation failed"

    call c_f_pointer(raw, arr, [n])
end subroutine


subroutine aligned_deallocate_real(a)
    implicit none
    real(c_double), pointer :: a(:)
    type(c_ptr) :: p

    p = c_loc(a(1))
    call free(p)

    nullify(a)
end subroutine

subroutine aligned_deallocate_complex(a)
    implicit none
    complex(c_double_complex), pointer :: a(:)
    type(c_ptr) :: p

    p = c_loc(a(1))
    call free(p)

    nullify(a)
end subroutine


end module utils_m
