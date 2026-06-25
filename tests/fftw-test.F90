! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

program fftw_modern_example
    use, intrinsic :: iso_c_binding
    use juffte
    implicit none
    
    ! include 'fftw3.f03'

    integer(C_INT) :: n, i
    type(C_PTR) :: plan
    complex(C_DOUBLE_COMPLEX), allocatable :: in(:), out(:)

    ! Problem size
    n = 2

    ! Allocate arrays
    allocate(in(n), out(n))

    ! Initialize input data (a simple ramp)
    do i = 1, n
        in(i) = cmplx(real(i, C_DOUBLE), 0.0_C_DOUBLE, kind=C_DOUBLE_COMPLEX)
    end do

    print *, "Input data:"
    do i = 1, n
        print '(I3, 2F12.6)', i, real(in(i)), aimag(in(i))
    end do

    ! Create FFTW plan (complex-to-complex forward)
    plan = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE)

    ! Execute the FFT
    call fftw_execute_dft(plan, in, out)

    print *, ""
    print *, "FFT output:"
    do i = 1, n
        print '(I3, 2F12.6)', i, real(out(i)), aimag(out(i))
    end do

    ! Clean up
    call fftw_destroy_plan(plan)

end program fftw_modern_example