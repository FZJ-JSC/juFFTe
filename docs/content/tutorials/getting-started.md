# Getting Started with juFFTe

## Prerequisites

- Fortran 2003 compiler (gfortran, ifx, nvfortran)
- C99 Compiler if you want to use the library in C or if you like to use the Spiral backend.  
- OpenMP support

## Installation

### Using Make

```bash
cd src
make
make install PREFIX=$HOME/local
```

### Using CMake

```bash
cd src && mkdir build && cd build
cmake ..
make install
```

## Your First FFT

```fortran
program simple_1d_fft
    use iso_fortran_env
    use juffte
    implicit none

    integer, parameter :: n = 1024
    complex(real64), allocatable :: data(:)
    integer :: i

    ! Allocate array
    allocate(data(n))

    ! Initialize with a simple sine wave
    do i = 1, n
        data(i) = cmplx(sin(2.0_real64 * 3.14159265358979_real64 * i / n), &
                       0.0_real64)
    end do

    ! Initialize FFT tables
    call zfft1d(data, n, juffte_init)

    ! Forward transform
    call zfft1d(data, n, juffte_fw)

    ! Print first 10 frequency components
    print *, 'First 10 frequency components:'
    do i = 1, 10
        print '(A,I4,A,F12.6,A,F12.6,A)', '  [', i, ']: ', &
              real(data(i), real64), ' + ', &
              aimag(data(i), real64), 'i'
    end do

    ! Backward transform (should return to original)
    call zfft1d(data, n, juffte_bw)

    deallocate(data)
end program simple_1d_fft
```

Compile:
```bash
gfortran -fopenmp example.f90 -ljuffte -L/path/to/juffte/lib -I/path/to/juffte/include
```
