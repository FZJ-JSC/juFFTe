<!--
- SPDX-License-Identifier: Apache-2.0
- SPDX-FileCopyrightText: juFFTe developers
-->

# Fortran Examples

Small programs that use juFFTe from Fortran. Each takes the transform size(s) on the command
line, transforms forward and back, and checks that the input comes back (`test_utils_m.F90`).
The test suite is in `tests/fortran`.

| **Program**      | **Shows**                                                    |
| ---------------- | ------------------------------------------------------------ |
| `test1d`         | 1-D complex-to-complex FFT, in place, FP64 and FP32          |
| `test1d-out`     | 1-D complex-to-complex FFT, out of place                     |
| `test1dni`       | 1-D complex-to-complex FFT with `fft_init`/`fft_execute`     |
| `test1d-fftwint` | FFTW interface, 1-D                                          |
| `test2d`         | 2-D complex-to-complex FFT, in place, FP64 and FP32          |
| `test2d-out`     | 2-D complex-to-complex FFT, out of place                     |
| `test2d-fftwint` | FFTW interface, 2-D                                          |
| `test3d`         | 3-D complex-to-complex FFT, in place, FP64 and FP32          |
| `test3d-out`     | 3-D complex-to-complex FFT, out of place                     |
| `test3d-fftwint` | FFTW interface, 3-D                                          |
| `rtest1d`        | 1-D real-to-complex and complex-to-real FFT, FP64 and FP32   |
| `rtest2d`        | 2-D real-to-complex and complex-to-real FFT, FP64 and FP32   |
| `rtest3d`        | 3-D real-to-complex and complex-to-real FFT, FP64 and FP32   |

## Building and running

Against an in-tree `make`-built library (`make` in `src/` first):

```
make
make run                                  # every example once
./test2d 96 64
make WITH_REFERENCE_FFTW=1 FFTWINC=/usr/include   # *-fftwint on real FFTW
```

CMake builds them too (`-DBUILD_EXAMPLES=OFF` to skip).

## From FFTW to juFFTe

To use juFFTe instead of FFTW, as `*-fftwint.F90` do:

1. Replace `include 'fftw3.f03'` with `use juffte`.
2. Replace `-lfftw3` with `-ljuffte` in your Makefile.
3. Recompile.

The FFTW calls keep FFTW's dimension order, slowest first, which in Fortran is the reverse of
the declared shape: `a(nx, ny)` is planned as `fftw_plan_dft_2d(ny, nx, ...)`. juFFTe's native
API keeps the declared order: `zfft2d(a, nx, ny, ...)`.
