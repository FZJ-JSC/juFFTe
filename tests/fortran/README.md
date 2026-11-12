<!--
- SPDX-License-Identifier: Apache-2.0
- SPDX-FileCopyrightText: juFFTe developers
-->

# Fortran Tests

`juffte_test.F90` checks one juFFTe transform per run against a reference. The C
counterpart is `tests/c/juffte_test.c`; usage examples are in `examples/`.

```
juffte_test_f [-t complex|real] [-d fw|bw] [-a native|plan|fftw|simple] [-o m1[xm2[xm3]]]
              [-p] n1 [n2 [n3]]
```

- Defaults: `-t complex -d fw -a native`. The number of sizes is the dimension; sizes are in
  juFFTe's order, `n1` contiguous.
- `-t real -d fw` is the real-to-complex transform, `-t real -d bw` the complex-to-real one.
- `-a native` checks FP64 and FP32, in place and out of place, and that an out-of-place
  transform leaves its input unchanged; `-a plan` does the same with a plan of the caller's
  own (`plan=`). `-a fftw` calls the FFTW-compatible interface as FFTW code would, `-a simple`
  calls `fft_init`/`fft_execute` (1-D complex only). Both are FP64 only.
- `-o m1xm2` makes a plan of the shape `m1 x m2` before the plan under test and another one
  after it, the same way, runs the second and destroys both. Neither may disturb the plan under
  test.
- `-p` runs each variant from four threads at once, each with two threads of its own for the
  transform, thread `k` on the input times `2^k`. With the native and simple API every thread
  makes, runs and destroys its own references to the shared plans; with `-a plan` and
  `-a fftw` they all run one plan, made before.

`plan_test.F90` checks the plans themselves where the transform tests cannot reach them in a
deterministic way: a destroy while a call runs on the plan, and a plan that someone else made
while it was being built. `plan_test unmade|other-shape|other-transform|too-large` must stop
with the message for a wrong `plan=` or a transform of more than 2^31 - 1 elements. Run it with
`MALLOC_PERTURB_` set, as CTest and `make test` do.

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

Every case is a separate run. The sizes are listed in `tests/sizes.mk`, which CMake and both
test Makefiles read. The thorough set adds about a thousand more cases: every 2-3-5 length up
to 128, powers of each radix, lengths past the former size caps and lopsided shapes. The
cases with `-o` and `-p`, and `plan_test`'s, carry the CTest label `plans`.

`juffte_mpi_test_f` checks the distributed transforms, `pzfft2d` and `pzfft3d`, on the ranks
it runs on: FP64 and FP32, in place and out of place, against the serial transform of the
whole array; `-c` runs a plan on another communicator, which must stop. It is built with
`-DWITH_MPI=ON`; each size of `MPI_2D` and `MPI_3D` runs on 1 to 4 ranks (`MPI_RANKS`), label
`mpi`:

```
mpiexec -n np juffte_mpi_test_f [-d fw|bw] [-c] nx ny [nz]
```

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
make mpitest FC=mpif90    # library built with make WITHMPI=1 FC=mpif90
```
