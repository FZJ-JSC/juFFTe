<!--
- SPDX-License-Identifier: Apache-2.0
- SPDX-FileCopyrightText: juFFTe developers
-->

# C Examples

Small programs that use juFFTe from C. Each takes the transform size(s) on the command line,
transforms forward and back, and checks that the input comes back (`test_utils.h`). The
test suite is in `tests/c`.

| **Program**   | **Shows**                                                       |
| ------------- | --------------------------------------------------------------- |
| `test1d`      | 1-D complex-to-complex FFT, native API                          |
| `test2d`      | 2-D complex-to-complex FFT, native API                          |
| `test3d`      | 3-D complex-to-complex FFT, native API                          |
| `rtest1d`     | 1-D real-to-complex and complex-to-real FFT                     |
| `rtest2d`     | 2-D real-to-complex and complex-to-real FFT                     |
| `rtest3d`     | 3-D real-to-complex and complex-to-real FFT                     |
| `fftw-test`   | FFTW interface, 1-D: unchanged FFTW code running on juFFTe      |
| `fftw-test2d` | FFTW interface, 2-D                                             |
| `fftw-test3d` | FFTW interface, 3-D                                             |

## Building and running

Against an in-tree `make`-built library (`make` in `src/` first):

```
make
make run                                  # every example once
./test2d 96 64
make WITH_REFERENCE_FFTW=1 FFTWINC=/usr/include FFTWLIB=/usr/lib64   # fftw-test* on real FFTW
```

CMake builds them too (`-DBUILD_EXAMPLES=OFF` to skip).

## From FFTW to juFFTe

To use juFFTe instead of FFTW, as `fftw-test*.c` do:

1. Replace `#include <fftw3.h>` with `#include <juffte.h>`.
2. Link `-ljuffte -lm -lgfortran` instead of `-lfftw3`.
3. Recompile.
