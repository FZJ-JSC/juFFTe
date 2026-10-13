<!--
- SPDX-License-Identifier: Apache-2.0
- SPDX-FileCopyrightText: juFFTe developers
-->

# Fortran Tests

`juffte_test.F90` checks one juFFTe transform per run against a reference. The C
counterpart is `tests/c/juffte_test.c`; usage examples are in `examples/`.

```
juffte_test_f [-t complex|real] [-d fw|bw] [-a native|fftw|simple] n1 [n2 [n3]]
```

- Defaults: `-t complex -d fw -a native`. The number of sizes is the dimension; sizes are in
  juFFTe's order, `n1` contiguous.
- `-t real -d fw` is the real-to-complex transform, `-t real -d bw` the complex-to-real one.
- `-a native` checks FP64 and FP32, in place and out of place, and that an out-of-place
  transform leaves its input unchanged. `-a fftw` calls the FFTW-compatible interface as FFTW
  code would, `-a simple` calls `fft_init`/`fft_execute` (1-D complex only). Both are FP64 only.

Forward and backward are tested separately. Every variant runs on the same random input and
its output is compared against the reference in the relative 2-norm, against the bound
`2 log2(N) eps` for the transform plus the reference's own error:

| reference | when | its error bound |
| --- | --- | --- |
| FFTW | built with `-DUSE_REFERENCE_FFTW` | `2 log2(N) eps` |
| direct DFT | otherwise, if `N = n1 n2 n3 < 4000` | `2 (sqrt(n1) + sqrt(n2) + sqrt(n3)) eps` |
| none | otherwise | skipped |

The direct DFT runs along one dimension at a time and never forms the DFT matrix.

Exit status: 0 pass, 1 fail, 2 usage error, 77 skipped (CTest reports it as such).

Only one size can be initialised per process, so every case is a separate run. The sizes are
listed in `tests/sizes.mk`, which CMake and both test Makefiles read. The thorough set adds
about a thousand more cases: every 2-3-5 length up to 128, powers of each radix, the size caps
and lopsided shapes.

## Building and running

With CMake, from the repository root, `ctest` runs every case:

```
cmake -S . -B build [-DWITH_REFERENCE_FFTW=ON] [-DTHOROUGH_TESTS=ON] && cmake --build build
ctest --test-dir build --output-on-failure
ctest --test-dir build -LE thorough        # only the default sizes
```

With the Makefile, against an in-tree `make`-built library:

```
make
make test
make test THOROUGH=1
make test WITH_REFERENCE_FFTW=1 FFTWINC=/usr/include
./juffte_test_f -t real -d bw 96 64
```
