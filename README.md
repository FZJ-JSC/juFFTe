<!--
- SPDX-License-Identifier: Apache-2.0
- SPDX-FileCopyrightText: juFFTe developers
-->

# juFFTe

A modern Fast Fourier Transform library inspired by [FFTE](https://www.ffte.jp/) subroutines, written in modern Fortran.

## Build

Requirement: Fortran 2003 compiler. Also, C99 compiler, if Spiral kernels are used. Also, OpenMP.
Tested with GCC (Gfortran), NVIDIA HPC SDK (nvfortran), Flang, and Intel compilers.

To build:

```
cd src
make
make install PREFIX=/your/installation/folder
```

Edit the Makefile if necessary for your system setup.

To build with Spiral:

```
make WITHSPRL=1
```

To use compilers other than gfortran, for example Intel's Fortran compiler:

```
make FC=ifx
```

CMake build is also available:

```
cd src
mkdir build
cmake ../
make install
```

### Example Build for RISC-V RVV ready CPUs

```
make WITHSPRL=1 WITHRVV=1
```

## Usage

### API Overview

| **function**                            | **Description / Functionality** |
| ----------------------------------      | --------------------------------|
| `zfft1d(a, n, juffte_x)`                | 1-D complex-to-complex FFT      |
| `zfft1d_out(a, n, juffte_x, a_out)`     | 1-D complex-to-complex FFT      |
| `zfft2d(a, nx, ny, juffte_x)`           | 2-D complex-to-complex FFT      |
| `zfft3d(a, nx, ny, nz, juffte_x)`       | 3-D complex-to-complex FFT      |
| `dzfft1d(a, a_c, n, juffte_x)`          | 1-D real-to-complex FFT         |
| `zdfft1d(a_c, a, n, juffte_x)`          | 1-D complex-to-real FFT         |
| `dzfft2d(a, a_c, nx, ny, juffte_x)`     | 2-D real-to-complex FFT         |
| `zdfft2d(a_c, a, nx, ny, juffte_x)`     | 2-D complex-to-real FFT         |
| `dzfft3d(a, a_c, nx, ny, nz, juffte_x)` | 3-D real-to-complex FFT         |
| `zdfft3d(a_c, a, nx, ny, nz, juffte_x)` | 3-D complex-to-real FFT         |

- `juffte_x` can be `juffte_init` for initialization, `juffte_fw` for forward FFT, or `juffte_bw` for backward.
- `_out` denotes the out-of-place transformation (output goes last).
- Real-to-complex FFTs produce output in half-complex format with size `(n/2 + 1)` in the first dimension.
- The API supports both single-precision (FP32) and double-precision (FP64) floating-point types for Fortran.

### New API

| **function**                     | **Description / Functionality**     |
| -------------------------------- | ----------------------------------- |
| `fft_init(a)`                    | Initialize 1-D complex FFT plan     |
| `fft_execute(a, juffte_x)`       | Execute 1-D complex FFT             |

### FFTW API (drop-in compatibility)

| **function**                                             | **Description**                |
| -------------------------------------------------------- | ------------------------------ |
| `fftw_malloc(size)`                                      | Allocate aligned memory        |
| `fftw_plan_dft_1d(n, in, out, sign, flags)`              | Create 1-D FFT plan            |
| `fftw_execute_dft(plan)`                                 | Execute FFT (C/C++ API)        |
| `fftw_execute_dft(plan, in, out)`                        | Execute FFT (Fortran API)      |
| `fftw_free(ptr)`                                         | Free aligned memory            |

See the example files `fftw-test.c` and `fftw-test.F90` in the test folders.

### OpenMP

The library uses OpenMP for parallelization. Ensure your compiler has OpenMP support enabled:

```
gfortran -fopenmp your_code.f90 -ljuffte
```


## Build Code with juFFTe

To use juFFTe, link the library with `-ljuffte`. For the Spiral version, use `-ljufftesp` instead. When using from C/C++, include Fortran runtime libraries, e.g., for GCC:

```
gcc your_code.c -ljuffte -lm -lgfortran
```

## Contributing

Contributions to juFFTe are welcome. Please see [`CONTRIBUTING.md`](CONTRIBUTING.md) for contribution instructions, maintainer information, and the definition of **juFFTe developers**.

## License

juFFTe is licensed under the Apache License, Version 2.0. See [`LICENSES/Apache-2.0.txt`](LICENSES/Apache-2.0.txt) for the full license text.

The project uses REUSE/SPDX metadata for license and copyright information.