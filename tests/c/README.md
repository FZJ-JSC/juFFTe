<!--
- SPDX-License-Identifier: Apache-2.0
- SPDX-FileCopyrightText: juFFTe developers
-->

# C Tests

`juffte_test.c` checks one juFFTe transform per run, through the C API, against a reference.
It works like the Fortran test; see `tests/fortran/README.md` for the options, references and
error bounds. Options are parsed with `getopt`, the input comes from `drand48`.

```
juffte_test_c [-t complex|real] [-d fw|bw] [-a native|fftw] n1 [n2 [n3]]
```

The C API is FP64 only. `-a fftw` calls the FFTW compatibility layer as FFTW code would:
dimensions slowest first, unnormalised backward transform. With `-DUSE_REFERENCE_FFTW` the test
includes both `fftw3.h` and `juffte.h`, which is what `JUFFTE_NO_FFTW_NAMES` is for.

## Building and running

```
make
make test
make test THOROUGH=1
make test WITH_REFERENCE_FFTW=1 FFTWINC=/usr/include FFTWLIB=/usr/lib64
./juffte_test_c -t real -d bw 12 18 20
```
