<!--
- SPDX-License-Identifier: Apache-2.0
- SPDX-FileCopyrightText: juFFTe developers
-->

# Benchmark

This directory contains the `fftbench` program for benchmarking juFFTe FFT performance.

## Building

```
make
```

To build with FFTW comparison support:

```
make WITHFFTW=1 FFTWDIR=/path/to/fftw
```

To build with Spiral kernel library:

```
make WITHSPRL=1
```

## Usage

```
./fftbench [options]
```

### Options

| Option | Description | Default |
| ------ | ----------- | ------- |
| `-dim N` | Number of dimensions (1, 2, or 3) | 1 |
| `-size s1 [s2 [s3]]` | Size per dimension | 256 |
| `-type TYPE` | FFT type: `c2c`, `r2c`, `c2r` | c2c |
| `-h, --help` | Print help message | |

### Examples

```
# 1D complex FFT, size 1024
./fftbench -dim 1 -size 1024

# 2D complex FFT, 512x512
./fftbench -dim 2 -size 512 512

# 3D real-to-complex FFT, 128x128x128
./fftbench -dim 3 -size 128 128 128 -type r2c
```

### Size Auto-fill

If fewer sizes than dimensions are provided, the last value is repeated:

```
./fftbench -dim 3 -size 64      # equivalent to -size 64 64 64
./fftbench -dim 3 -size 64 128  # equivalent to -size 64 128 128
```

## Output

The benchmark outputs:

- **TIME**: Average execution time per FFT operation (seconds)
- **MFLOPS**: Estimated megaflops

When built with FFTW (`WITHFFTW=1`), it also outputs FFTW timing for comparison.

## Utilities

| File | Description |
| ---- | ----------- |
| `bench_utils_m.F90` | Benchmark utilities (argument parsing, array init) |
| `fftw_m.F90` | FFTW interface for comparison (when `WITHFFTW=1`) |
| `utils_m.F90` | General utilities |
| `sc.sh` | Shell script for running scalability tests |

## Cleaning

```
make clean
```
## Known issues

-  Segmentation faults may occur during execution in some environments. If this happens, it is recommended to increase both the system stack size and the OpenMP (OMP) stack size.