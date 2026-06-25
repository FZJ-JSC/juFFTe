# juFFTe

[![License: Apache-2.0](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Documentation](https://img.shields.io/badge/docs-latest-green.svg)](https://juffte.gitlab.io)

**juFFTe** is a modern Fast Fourier Transform library written in Fortran 2003, inspired by the [FFTE](https://www.ffte.jp/) library.

## Features

- **1D, 2D, and 3D FFTs** - Complex-to-complex, real-to-complex, and complex-to-real transforms
- **FFTW compatibility** - Drop-in replacement for FFTW with familiar API
- **OpenMP parallelization** - Multi-core performance out of the box
- **Multiple backends** - Standard, Spiral (optimized kernels), SVE, and RVV support
- **Modern Fortran** - Clean, maintainable codebase using Fortran 2003+

## Quick Start

### Installation

```bash
# Using Make
cd src
make
make install PREFIX=/your/installation/folder

# Using CMake
cd src && mkdir build && cd build
cmake ..
make install
```

### First FFT


```fortran
program example
    use juffte
    use iso_fortran_env
    implicit none

    complex(real64), allocatable :: data(:)
    integer :: n

    n = 1024
    allocate(data(n))

    ! Initialize FFT tables
    call zfft1d(data, n, juffte_init)

    ! Forward transform
    call zfft1d(data, n, juffte_fw)

    ! Backward transform
    call zfft1d(data, n, juffte_bw)

    deallocate(data)
end program example
```


<!-- ## Documentation

Full documentation is available at [juffte.gitlab.io](https://juffte.gitlab.io) including:

- **Tutorials** - Step-by-step guides for getting started
- **API Reference** - Complete documentation of all functions and modules
- **Examples** - Working code examples for common use cases
- **Benchmarks** - Performance comparisons and optimization tips -->

## Build with juFFTe

Link against the library:

```bash
gfortran -fopenmp your_code.f90 -ljuffte -L/path/to/juffte/lib -I/path/to/juffte/include
```

For C/C++ programs:

```bash
gcc your_code.c -ljuffte -lgfortran -lm -L/path/to/juffte/lib -I/path/to/juffte/include
```

## License

juFFTe is licensed under the **Apache License 2.0**. See the [LICENSE](LICENSES/Apache-2.0.txt) file for details.

## Contributing

Contributions are welcome! Please see [CONTRIBUTING](CONTRIBUTING.md) for guidelines.

## Credits

juFFTe is developed at **Jülich Supercomputing Centre (JSC)** and other juFFTe developers.
