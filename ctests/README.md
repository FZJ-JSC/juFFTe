<!--
- SPDX-License-Identifier: Apache-2.0
- SPDX-FileCopyrightText: juFFTe developers
-->

# C/C++ Tests

This directory contains C test programs for juFFTe.

## Building Tests

To build all tests:
```
make
```

To run all tests:
```
make test
```

## Test Programs

| **Program**    | **Description**                                      |
| -------------- | ---------------------------------------------------- |
| `test1d`       | 1D complex-to-complex FFT test                       |
| `test2d`       | 2D complex-to-complex FFT test                       |
| `test3d`       | 3D complex-to-complex FFT test                       |
| `rtest1d`      | 1D real-to-complex FFT test                          |
| `rtest2d`      | 2D real-to-complex FFT test                          |
| `rtest3d`      | 3D real-to-complex FFT test                          |
| `fftw-test`    | FFTW interface compatibility test (1D)               |
| `fftw-test2d`  | FFTW interface compatibility test (2D)               |

## Cleaning

To clean build artifacts:
```
make clean
```
## From FFTW to juFFTe

to use juFFTe instead of fftw:

1. Replace `#include <fftw3.h>` with `#include <juffte.h>`.
2. Add `-DFFTW` and  `-ljuffte -lm -lgfortran` to your compilation/linking flags.
3. Recompile.
