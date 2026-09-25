<!--
- SPDX-License-Identifier: Apache-2.0
- SPDX-FileCopyrightText: juFFTe developers
-->

# juFFTe

A modern Fast Fourier Transform library inspired by [FFTE](https://www.ffte.jp/) subroutines, written in modern Fortran.

## Build

Requirement: Fortran 2003 compiler. Also, C99 compiler, if Spiral kernels are used. Also, OpenMP.
Tested with GCC (Gfortran), NVIDIA HPC SDK (nvfortran), Flang, and Intel compilers.

CMake is the recommended build. Configure from the repository root:

```
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure
cmake --install build --prefix /your/installation/folder
```

Options:

| Option | Effect |
| ------------------------- | ------------------------------------------- |
| `-DWITHSPRL=ON`           | Spiral kernel backend                       |
| `-DWITHRVV=ON`            | RISC-V RVV kernels (implies `WITHSPRL`)     |
| `-DWITHSVE=ON`            | Arm SVE kernels (implies `WITHSPRL`)        |
| `-DWITH_REFERENCE_FFTW=ON`| Build the comparisons against a reference FFTW|
| `-DBUILD_SHARED_LIBS=ON`  | Shared instead of static library            |

Only the RVV kernels are currently generated: `-DWITHSVE=ON`, and `-DWITHSPRL=ON` on its
own, stop at configure time until those kernel sets exist.

To use a different compiler, for example Intel's:

```
cmake -S . -B build -DCMAKE_Fortran_COMPILER=ifx -DCMAKE_C_COMPILER=icx
```

Installing writes the library, the public `.mod` files, `src/juffte.h` and a CMake
package config, so a downstream project can use it directly:

```cmake
find_package(juffte REQUIRED)
target_link_libraries(myapp PRIVATE juffte::juffte)
```

### Cross compiling for RISC-V

A toolchain file is provided for a `riscv64-unknown-linux-gnu` cross toolchain:

```
cmake -S . -B build-riscv -DCMAKE_TOOLCHAIN_FILE=cmake/riscv-rvv.cmake \
      -DWITHSPRL=ON -DWITHRVV=ON
cmake --build build-riscv -j
```

Override `RISCV_TOOLCHAIN_PREFIX` (default `/opt/riscv`) and `RISCV_TARGET_TRIPLE`
(default `riscv64-unknown-linux-gnu`) if the toolchain lives elsewhere.

Executables are linked statically, and if `qemu-riscv64-static` is installed it is
registered as the CTest emulator, so the suite can be run under emulation:

```
ctest --test-dir build-riscv --output-on-failure
```

### Makefile build

A plain Makefile build also exists, and is what the `tests`, `ctests` and `benchmark`
directories link against by default:

```
cd src
make
make install PREFIX=/your/installation/folder
```

It takes `FC=ifx`, `WITHSPRL=1` and `WITHRVV=1` in the same spirit as the CMake options.
Edit the Makefile if necessary for your system setup.

## Usage

### API Overview

| **function**                                | **Description / Functionality** |
| --------------------------------------------| --------------------------------|
| `zfft1d(a, n, juffte_x)`                    | 1-D complex-to-complex FFT      |
| `zfft1d_out(a, n, juffte_x, a_out)`         | 1-D complex-to-complex FFT      |
| `zfft2d(a, nx, ny, juffte_x)`               | 2-D complex-to-complex FFT      |
| `zfft2d_out(a, nx, ny, juffte_x, a_out)`    | 2-D complex-to-complex FFT      |
| `zfft3d(a, nx, ny, nz, juffte_x)`           | 3-D complex-to-complex FFT      |
| `zfft3d_out(a, nx, ny, nz, juffte_x, a_out)`| 3-D complex-to-complex FFT      |
| `dzfft1d(a, a_c, n, juffte_x)`              | 1-D real-to-complex FFT         |
| `zdfft1d(a_c, a, n, juffte_x)`              | 1-D complex-to-real FFT         |
| `dzfft2d(a, a_c, nx, ny, juffte_x)`         | 2-D real-to-complex FFT         |
| `zdfft2d(a_c, a, nx, ny, juffte_x)`         | 2-D complex-to-real FFT         |
| `dzfft3d(a, a_c, nx, ny, nz, juffte_x)`     | 3-D real-to-complex FFT         |
| `zdfft3d(a_c, a, nx, ny, nz, juffte_x)`     | 3-D complex-to-real FFT         |

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

| **function**                                              | **C** | **Fortran** |
| --------------------------------------------------------- | :---: | :---------: |
| `fftw_malloc(size)`                                       | yes   | –           |
| `fftw_free(ptr)`                                          | yes   | –           |
| `fftw_plan_dft_1d(n, in, out, sign, flags)`               | yes   | yes         |
| `fftw_plan_dft_2d(nx, ny, in, out, sign, flags)`          | yes   | yes         |
| `fftw_plan_dft_3d(nx, ny, nz, in, out, sign, flags)`      | yes   | yes         |
| `fftw_execute(plan)`                                      | yes   | –           |
| `fftw_execute_dft(plan, in, out)`                         | yes   | yes         |
| `fftw_destroy_plan(plan)`                                 | yes   | yes         |

The layer is always built into `libjuffte` — no build option, macro or extra library. From C,
include `juffte.h` instead of `fftw3.h`; from Fortran, `use juffte` instead of
`include 'fftw3.f03'`. Either way, link `-ljuffte` instead of `-lfftw3`.

The C entry points are exported as `juffte_fftw_*` and `juffte.h` maps the `fftw_*` names onto
them, so juFFTe exports nothing that clashes with real FFTW. A program can therefore link both
libraries at once — which is how the benchmark compares them.

Known limitation: only one plan can be live at a time. Creating a second plan currently
fails. See the open issues.

See the example files `fftw-test.c` and `test1d-fftwint.F90` in the test folders.

### OpenMP

The library uses OpenMP for parallelization. Ensure your compiler has OpenMP support enabled:

```
gfortran -fopenmp your_code.f90 -ljuffte
```


## Build Code with juFFTe

To use juFFTe, link the library with `-ljuffte`. There is one library for every backend and for
both the native and the FFTW-compatible API. When using from C/C++, include Fortran runtime libraries, e.g., for GCC:

```
gcc your_code.c -ljuffte -lm -lgfortran
```

## Contributing

Contributions to juFFTe are welcome. Please see [`CONTRIBUTING.md`](CONTRIBUTING.md) for contribution instructions, maintainer information, and the definition of **juFFTe developers**.

## License

juFFTe is licensed under the Apache License, Version 2.0. See [`LICENSES/Apache-2.0.txt`](LICENSES/Apache-2.0.txt) for the full license text.

The project uses REUSE/SPDX metadata for license and copyright information.