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
| `-DTHOROUGH_TESTS=ON`     | Test about a thousand more sizes            |
| `-DBUILD_EXAMPLES=OFF`    | Skip the programs in `examples/`            |
| `-DBUILD_SHARED_LIBS=ON`  | Shared instead of static library            |
| `-DWITH_EPI=OFF`          | Don't use `-mepi` with EPI's LLVM (see below) |
| `-DWITH_MPI=ON`           | Distributed 2-D and 3-D transforms over MPI (see below) |

Only the RVV kernels are currently generated: `-DWITHSVE=ON`, and `-DWITHSPRL=ON` on its
own, stop at configure time until those kernel sets exist.

With EPI's LLVM (BSC), which vectorises for RVV with `-mepi`, the library is built with
`-mepi -ffast-math` and needs EPI's vector math library `libprovector-vecclonevp`. CMake
detects the compiler by trying `-mepi`, the Makefile does so when `FC` is `flang` or
`flang-new`; both look for the library next to the compiler. Point CMake to the library
file with `-DEPI_VECMATH_LIBRARY=/path/to/libprovector-vecclonevp.so`, the Makefile to its
directory with `EPI_LIBDIR=/path/to/dir`.

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

A plain Makefile build also exists, and is what `tests/c`, `tests/fortran`, `examples/c`,
`examples/fortran` and `benchmark` link against by default:

```
cd src
make
make install PREFIX=/your/installation/folder
```

It takes `FC=ifx`, `WITHSPRL=1` and `WITHRVV=1` in the same spirit as the CMake options, and
`WITHMPI=1 FC=mpif90` for the distributed transforms.
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

- `juffte_x` can be `juffte_init` for initialization, `juffte_fw` for forward FFT, `juffte_bw` for
  backward, or `juffte_destroy` to undo one `juffte_init`.
- Each transform keeps a plan per shape and precision. `juffte_init` makes it, or takes another
  reference to it if it exists; `juffte_destroy` drops one, and the plan is freed with the
  last. Plans of different shapes can be live at once, and in a build with OpenMP (the
  default) transforms may be called from several threads at once. A transform of a shape
  without a plan stops with a message.
- From Fortran, every transform also takes a plan of your own as a last argument,
  `type(juffte_plan) :: plan`, e.g. `call zfft1d(a, n, juffte_init, plan=plan)`, then
  `juffte_fw`/`juffte_bw` with the same `plan=`, and `juffte_destroy` to free it. Such a plan
  is not shared: its calls skip the lookup and its lock, and no `juffte_destroy` elsewhere in
  the program can free it. Like an FFTW plan, it may run from several threads at once, but
  not while it is made or destroyed, and making a new one in the same variable does not free
  the old one. With many threads running small transforms, give each thread its own: the
  shared plans' lock then serialises them (16 points on 8 threads: 4.5 µs per call with the
  shared plans, 80 ns with a plan per thread).
- Lengths must be products of 2, 3 and 5, and a transform may have up to 2^31 - 1 elements;
  there is no other size limit.
- `_out` denotes the out-of-place transformation (output goes last).
- Dimensions are given contiguous first: in `zfft2d(a, nx, ny, ...)`, `nx` is the contiguous
  one (Fortran's array order), from C as well.
- Real-to-complex FFTs produce output in half-complex format with size `(n/2 + 1)` in the first dimension.
- The API supports both single-precision (FP32) and double-precision (FP64) floating-point types for Fortran.

### New API

| **function**                     | **Description / Functionality**     |
| -------------------------------- | ----------------------------------- |
| `fft_init(a)`                    | Initialize 1-D complex FFT plan     |
| `fft_execute(a, juffte_x)`       | Execute 1-D complex FFT             |
| `fft_destroy(a)`                 | Release the plan of `fft_init`      |

### FFTW API (drop-in compatibility)

| **function**                                              | **C** | **Fortran** |
| --------------------------------------------------------- | :---: | :---------: |
| `fftw_malloc(size)`                                       | yes   | –           |
| `fftw_free(ptr)`                                          | yes   | –           |
| `fftw_plan_dft_1d(n, in, out, sign, flags)`               | yes   | yes         |
| `fftw_plan_dft_2d(n0, n1, in, out, sign, flags)`          | yes   | yes         |
| `fftw_plan_dft_3d(n0, n1, n2, in, out, sign, flags)`      | yes   | yes         |
| `fftw_execute(plan)`                                      | yes   | –           |
| `fftw_execute_dft(plan, in, out)`                         | yes   | yes         |
| `fftw_destroy_plan(plan)`                                 | yes   | yes         |

**Dimension order.** FFTW lists the dimensions the other way round from juFFTe's native API:
slowest first, the contiguous one last (C's row-major order). `fftw_plan_dft_2d(n0, n1, ...)`
describes an `n0 x n1` array with `n1` contiguous, the same transform as
`zfft2d(a, n1, n0, ...)`. From Fortran this means reversing the declared shape: `a(nx, ny)` is
planned as `fftw_plan_dft_2d(ny, nx, ...)`, exactly as with FFTW's own Fortran interface. The
layer follows FFTW here, so that ported code runs unchanged.

The layer is always built into `libjuffte` — no build option, macro or extra library. From C,
include `juffte.h` instead of `fftw3.h`; from Fortran, `use juffte` instead of
`include 'fftw3.f03'`. Either way, link `-ljuffte` instead of `-lfftw3`.

The C entry points are exported as `juffte_fftw_*` and `juffte.h` maps the `fftw_*` names onto
them, so juFFTe exports nothing that clashes with real FFTW. A program can therefore link both
libraries at once — which is how the benchmark compares them.

Each `fftw_plan_dft_*` makes a plan of its own, which `fftw_destroy_plan` frees, so any
number of plans can be live at once and run from several threads at once, as in FFTW. As in
FFTW, any sign other than `FFTW_FORWARD` is backward, and the planner flags make no
difference.

See `examples/c/fftw-test*.c` and `examples/fortran/test*-fftwint.F90` for FFTW code running on
juFFTe.

### Distributed transforms (MPI)

Built with `-DWITH_MPI=ON` (or `make WITHMPI=1 FC=mpif90`), libjuffte also has 2-D and 3-D
complex transforms distributed over the ranks of an MPI communicator, as FFTE's `pzfft2d` and
`pzfft3d`: the slab decomposition of D. Takahashi, *Fast Fourier Transform Algorithms for
Parallel Computers* (Springer 2019), Sects. 8.1.3 and 8.1.4.

```fortran
use mpi_f08
use juffte
type(juffte_plan) :: plan
complex(real64), allocatable :: a(:), b(:)
integer :: np

call MPI_Comm_size(MPI_COMM_WORLD, np)
allocate(a(nx*ny*(nz/np)), b(nx*ny*(nz/np)))    ! this rank's planes, a(nx, ny, nz/np)
call pzfft3d(a, nx, ny, nz, MPI_COMM_WORLD, juffte_init, plan)
call pzfft3d(a, nx, ny, nz, MPI_COMM_WORLD, juffte_fw, plan)          ! in place
call pzfft3d(a, nx, ny, nz, MPI_COMM_WORLD, juffte_bw, plan, out=b)   ! out of place
call pzfft3d(a, nx, ny, nz, MPI_COMM_WORLD, juffte_destroy, plan)
```

- Of `np` ranks, rank `r` holds the `nz/np` planes from `r*nz/np` on, as `a(nx, ny, nz/np)`,
  in the input and in the output. `np` must divide `nx` and `nz`. `pzfft2d(a, nx, ny, comm,
  ...)` does the same for `a(nx, ny/np)`, with `np` dividing `nx` and `ny`.
- The FFTs along x and y are local. An all-to-all hands every rank `nx/np` values of x in
  all planes for the FFTs along z, and a second one brings the result back.
- The plan is required and belongs to the communicator (`type(MPI_Comm)`, from `mpi_f08`).
  Every call is collective: all its ranks make, run and destroy the plan together, in the
  same order. Only one transform at a time may run on a communicator: unlike the serial
  plans, never call them from several threads at once.
- MPI is called from the calling thread, outside parallel regions, so `MPI_THREAD_FUNNELED`
  is enough. Each rank runs its FFTs on OpenMP threads: give the ranks cores of their own,
  with Open MPI e.g. `mpiexec --map-by slot:PE=4 --bind-to core` for 4 threads each.
- FP64 and FP32; the backward transform is normalised, as in the serial ones. The whole
  transform may have more than 2^31 - 1 elements, a rank's share up to 2^30.
- Fortran only. CMake's `juffte::juffte` brings MPI's Fortran libraries; with the Makefile,
  link with `mpif90`.

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

A library built with EPI's LLVM also needs `-lprovector-vecclonevp` from the compiler's `lib`
directory. The CMake package adds it by itself; the Makefile build writes the flags as
`JUFFTE_LIBS` into `juffte.mk` next to the library, for a Makefile to include.

## Contributing

Contributions to juFFTe are welcome. Please see [`CONTRIBUTING.md`](CONTRIBUTING.md) for contribution instructions, maintainer information, and the definition of **juFFTe developers**.

## License

juFFTe is licensed under the Apache License, Version 2.0. See [`LICENSES/Apache-2.0.txt`](LICENSES/Apache-2.0.txt) for the full license text.

The project uses REUSE/SPDX metadata for license and copyright information.