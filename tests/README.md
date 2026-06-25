<!--
- SPDX-License-Identifier: Apache-2.0
- SPDX-FileCopyrightText: juFFTe developers
-->

# Tests

This directory contains test programs for juFFTe.

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
| `test1d-out`   | 1D out-of-place complex-to-complex FFT test          |
| `test1dni`     | 1D in-place complex-to-complex FFT test              |
| `test1d-fftwint` | 1D FFTW interface test                              |
| `test2d`       | 2D complex-to-complex FFT test                       |
| `test3d`       | 3D complex-to-complex FFT test                       |
| `rtest1d`      | 1D real-to-complex FFT test                          |
| `rtest2d`      | 2D real-to-complex FFT test                          |
| `rtest3d`      | 3D real-to-complex FFT test                          |

## Test Utilities

- `test_utils_m.F90`: Shared utility module for test programs

## Cleaning

To clean build artifacts:
```
make clean
```
