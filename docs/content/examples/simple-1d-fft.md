# Example: Simple 1D FFT

This example demonstrates a basic 1D FFT using juFFTe.

## Fortran

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

Compile and run:

```bash
gfortran -fopenmp -o simple_1d_fft simple_1d_fft.f90 -ljuffte -L/path/to/juffte/lib -I/path/to/juffte/include
./simple_1d_fft
```
## C

```c
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>
#include <math.h>
#include <juffte.h>

void init(double _Complex* a, int n) {
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1.0 + _Complex_I * (n - i);
    }
}

int main(int argc, char** argv) {
    int n=1024;
    double _Complex* a = calloc(n, sizeof(double _Complex));

    init(a, n);

    zfft1d_c(a, n, juffte_init);   // init
    zfft1d_c(a, n, juffte_fw);  // Forward
    zfft1d_c(a, n, juffte_bw);   // backwardz
    free(a);

    return 0;
}

```

Compile and run:

```bash
gcc -fopenmp -o simple_1d_fft simple_1d_fft.f90 -L/path/to/juffte/lib -I/path/to/juffte/include
./simple_1d_fft
```

