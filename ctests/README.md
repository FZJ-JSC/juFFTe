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
| `fftw-test`    | FFTW interface compatibility test                    |

## Cleaning

To clean build artifacts:
```
make clean
```
