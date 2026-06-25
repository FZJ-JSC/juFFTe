! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

program fftbench
    use omp_lib
    use bench_utils_m
    use juffte

#ifdef FFTW
use fftw_m
#endif

    implicit none

    complex(c_double_complex), pointer         :: a(:), b(:)
    real(c_double), pointer                    :: a_r(:)  
    integer :: lnx(3), lny(3), lnz(3), nx, ny, nz, i, l, loop, total
    character(len=100) :: args
    real(real64) :: flops, time0, time1, time2
    integer(c_intptr_t) :: addr

    call parse_args()

    print *, "Parsed arguments:"
    print *, "  dim        =", dim
    print *, "  type       =         ", trim(fft_type)
    print *, "  size       =", size
  
    print *, "Total points =", product(size)
    total = product(size)
    call aligned_allocate(a,total,ALN)
    call aligned_allocate(b,product(size),ALN)
    call aligned_allocate(a_r,product(size),ALN)

    addr = transfer(c_loc(A(1)), addr)

if (mod(addr,ALN) == 0) then
    print *, "Arrays are,", ALN,"byte aligned"
else
    print *, "Array are NOT,", ALN, " aligned"
endif
    print *, ""
    call init_arrays()
    call warmup()
   
    loop = 1
    
    call bench()

    write(6, *) "Results:"
    write(6, *) "  TIME       =", time0
    write(6, *) "  MFLOPS     =", flops
    write(6, *) ""
#ifdef FFTW
call fftw_warmup(size,dim,a,b)

call fftw_bench(size,dim,a,b,time0)
    write(6, *) "FFTW Results:"
    write(6, *) "  FFTW TIME  =", time0
     write(6, *) ""

#endif

    call aligned_deallocate(a)
    call aligned_deallocate(b)
    call aligned_deallocate(a_r)

contains
  subroutine init_arrays()
  
    nx = size(1)
    ny = size(2)
    nz = size(3) 
    if (fft_type == "r2c") then
        if (dim == 1) then
            call factor(nx, lnx)
            call init(a_r, nx)
        elseif (dim == 2) then
            call factor(nx, lnx)
            call factor(ny, lny)
            call init(a_r, nx*ny)
        else
            call factor(nx, lnx)
            call factor(ny, lny)
            call factor(nz, lnz)
            call init(a_r, nx*ny*nz)
        endif
    else if (fft_type == "c2r") then
        if (dim == 1) then
            call factor(nx, lnx)
            call init(a, nx)
        elseif (dim == 2) then
            call factor(nx, lnx)
            call factor(ny, lny)
            call init(a, nx*ny)
        else
            call factor(nx, lnx)
            call factor(ny, lny)
            call factor(nz, lnz)
            call init(a, nx*ny*nz)
        endif
    
    else
        if (dim == 1) then
            call factor(nx, lnx) ! needed for flops calculation
            call init(a, nx)
        elseif(dim == 2 ) then
            call factor(nx, lnx)
            call factor(ny, lny)
            call init(a, nx*ny)
        else 
            call factor(nx, lnx)
            call factor(ny, lny)
            call factor(nz, lnz)
            call init(a, nx*ny*nz)       
        endif
    endif
  end subroutine init_arrays

  subroutine warmup()

    if (fft_type == "r2c") then
        if (dim == 1) then
            call dzfft1d(a_r, a, nx, juffte_init)
            call dzfft1d(a_r, a, nx, juffte_fw)
        elseif (dim == 2) then
            call dzfft2d(a_r, a, nx, ny, juffte_init)
            call dzfft2d(a_r, a, nx, ny, juffte_fw)
        else
            call dzfft3d(a_r, a, nx, ny, nz, juffte_init)
            call dzfft3d(a_r, a, nx, ny, nz, juffte_fw)
        endif
    elseif (fft_type == "c2r") then
        if (dim == 1) then
            call zdfft1d(a, a_r, nx, juffte_init)
            call zdfft1d(a, a_r, nx, juffte_fw)
        elseif (dim == 2) then
            call zdfft2d(a, a_r, nx, ny, juffte_init)
            call zdfft2d(a, a_r, nx, ny, juffte_fw)
        else
            call zdfft3d(a, a_r, nx, ny, nz, juffte_init)
            call zdfft3d(a, a_r, nx, ny, nz, juffte_fw)
        endif
    else

        if (dim == 1) then
            call zfft1d(a, nx, juffte_init)
            call zfft1d(a, nx, juffte_fw)
        elseif(dim == 2 ) then
            call zfft2d(a, nx, ny, juffte_init)
            call zfft2d(a, nx, ny, juffte_fw)
        else
            call zfft3d(a, nx, ny, nz, juffte_init)
            call zfft3d(a, nx, ny, nz, juffte_fw)
        endif
    endif
  end subroutine warmup
  subroutine bench()
      if (fft_type == "r2c") then
        if (dim == 1) then
             do
                time1 = omp_get_wtime()
                do i = 1, loop
                    call dzfft1d(a_r, a, nx, juffte_fw)
                end do
                time2 = omp_get_wtime()
                time0 = time2 - time1
                if (time0 >= 1.0d0) then
                    exit
                end if
                loop = loop*2
             end do
            time0 = time0/dble(loop)
            flops = (2.5d0*dble(lnx(1)) + 4.66666666666666d0*dble(lnx(2)) &
                     + 6.8d0*dble(lnx(3) ))*dble(nx)/time0/1.0d6
        elseif (dim == 2) then
             do
                time1 = omp_get_wtime()
                do i = 1, loop
                    call dzfft2d(a_r, a, nx, ny, juffte_fw)
                end do
                time2 = omp_get_wtime()
                time0 = time2 - time1
                if (time0 >= 1.0d0) then
                    exit
                end if
                loop = loop*2
             end do
            time0 = time0/dble(loop)
            flops = (2.5d0*dble(lnx(1) + lny(1)) + 4.66666666666666d0*dble(lnx(2) &
                    + lny(2)) + 6.8d0*dble(lnx(3) + lny(3)))*dble(nx)*dble(ny)/time0/1.0d6
        else
            do
                time1 = omp_get_wtime()
                do i = 1, loop
                    call dzfft3d(a_r, a, nx, ny, nz, juffte_fw)
                end do
            time2 = omp_get_wtime()
            time0 = time2 - time1
            if (time0 >= 1.0d0) then
                exit
            end if
            loop = loop*2
            end do
            time0 = time0/dble(loop)
            flops = (2.5d0*dble(lnx(1) + lny(1) + lnz(1)) + 4.66666666666666d0*dble(lnx(2) + lny(2) &
                   + lnz(2)) + 6.8d0*dble(lnx(3) + lny(3) + lnz(3)))*dble(nx)*dble(ny)*dble(nz)/time0/1.0d6
        endif
    elseif (fft_type == "c2r") then
        if (dim == 1) then
             do
                time1 = omp_get_wtime()
                do i = 1, loop
                    call zdfft1d(a, a_r, nx, juffte_fw)
                end do
                time2 = omp_get_wtime()
                time0 = time2 - time1
                if (time0 >= 1.0d0) then
                    exit
                end if
                loop = loop*2
             end do
            time0 = time0/dble(loop)
            flops = (2.5d0*dble(lnx(1)) + 4.66666666666666d0*dble(lnx(2)) &
                    + 6.8d0*dble(lnx(3)))*dble(nx)/time0/1.0d6
        elseif (dim == 2) then
             do
                time1 = omp_get_wtime()
                do i = 1, loop
                    call zdfft2d(a, a_r, nx, ny, juffte_fw)
                end do
                time2 = omp_get_wtime()
                time0 = time2 - time1
                if (time0 >= 1.0d0) then
                    exit
                end if
                loop = loop*2
             end do
            time0 = time0/dble(loop)
            flops = (2.5d0*dble(lnx(1) + lny(1)) + 4.66666666666666d0*dble(lnx(2) &
                    + lny(2)) + 6.8d0*dble(lnx(3) + lny(3)))*dble(nx)*dble(ny)/time0/1.0d6

        else ! dim == 3
            do
                time1 = omp_get_wtime()
                do i = 1, loop
                    call zdfft3d(a, a_r, nx, ny, nz, juffte_fw)
                end do
            time2 = omp_get_wtime()
            time0 = time2 - time1
            if (time0 >= 1.0d0) then
                exit
            end if
            loop = loop*2
            end do
            time0 = time0/dble(loop)
            flops = (2.5d0*dble(lnx(1) + lny(1) + lnz(1)) + 4.66666666666666d0*dble(lnx(2) + lny(2) &
                   + lnz(2)) + 6.8d0*dble(lnx(3) + lny(3) + lnz(3)))*dble(nx)*dble(ny)*dble(nz)/time0/1.0d6
        endif                     
    else                      ! fft_type == "c2c"
            if (dim == 1) then
                do
                    time1 = omp_get_wtime()
                    do i = 1, loop
                        call zfft1d(a, nx, juffte_fw)
                    end do
                    time2 = omp_get_wtime()
                    time0 = time2 - time1
                    if (time0 >= 1.0d0) then   ! to make sure the benchmarking takes at least 1s
                        exit
                    end if
                    loop = loop*2
                end do
                time0 = time0/dble(loop)
                flops = (2.5d0*dble(lnx(1)) + 4.66666666666666d0*dble(lnx(2)) + 6.8d0*dble(lnx(3)))*2.0d0*dble(nx)/time0/1.0d6
            elseif (dim == 2) then
                    do
                     time1 = omp_get_wtime()
                        do i = 1, loop
                            call zfft2d(a, nx, ny, juffte_fw)
                        end do
                        time2 = omp_get_wtime()
                        time0 = time2 - time1
                        if (time0 >= 1.0d0) then
                           exit
                        end if
                        loop = loop*2
                    end do
                    time0 = time0/dble(loop)
                    flops = (2.5d0*dble(lnx(1) + lny(1)) + 4.66666666666666d0*dble(lnx(2) &
                        + lny(2)) + 6.8d0*dble(lnx(3) + lny(3)))*2.0d0*dble(nx)*dble(ny)/time0/1.0d6
            else 
                    do
                        time1 = omp_get_wtime()
                        do i = 1, loop
                            call zfft3d(a, nx, ny, nz, juffte_fw)
                        end do
                        time2 = omp_get_wtime()
                        time0 = time2 - time1
                        if (time0 >= 1.0d0) then
                            exit
                        end if
                        loop = loop*2
                    end do
                time0 = time0/dble(loop)
                flops = (2.5d0*dble(lnx(1) + lny(1) + lnz(1)) + 4.66666666666666d0*dble(lnx(2) + lny(2) + lnz(2)) & 
                        + 6.8d0*dble(lnx(3) + lny(3) + lnz(3)))*2.0d0*dble(nx)*dble(ny)*dble(nz)/time0/1.0d6
            endif
    endif
end subroutine bench

end program fftbench