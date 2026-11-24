---
title: "juFFTe API Reference"
---

# API Reference

This page lists all public API functions in juFFTe.

## Complex-to-Complex Transforms

### `zfft1d`
1D complex FFT
```fortran
call zfft1d(a, n, jufft_x)
```

### `zfft2d`
2D complex FFT
```fortran
call zfft2d(a, nx, ny, jufft_x)
```

### `zfft3d`
3D complex FFT
```fortran
call zfft3d(a, nx, ny, nz, jufft_x)
```

## Real-to-Complex Transforms

### `dzfft1d`
1D real-to-complex FFT
```fortran
call dzfft1d(a, a_c, n, jufft_x)
```

### `dzfft2d`
2D real-to-complex FFT
```fortran
call dzfft2d(a, a_c, nx, ny, jufft_x)
```

### `dzfft3d`
3D real-to-complex FFT
```fortran
call dzfft3d(a, a_c, nx, ny, nz, jufft_x)
```

## Complex-to-Real Transforms

### `zdfft1d`
1D complex-to-real FFT
```fortran
call zdfft1d(a_c, a, n, jufft_x)
```

### `zdfft2d`
2D complex-to-real FFT
```fortran
call zdfft2d(a_c, a, nx, ny, jufft_x)
```

### `zdfft3d`
3D complex-to-real FFT
```fortran
call zdfft3d(a_c, a, nx, ny, nz, jufft_x)
```

## Parameters

- `a`: Real input/output array
- `a_c`: Complex input/output array  
- `n`, `nx`, `ny`, `nz`: Transform sizes
- `jufft_x`: Operation type (`juffte_init`, `juffte_fw`, `juffte_bw`, `juffte_destroy`)

`juffte_init` makes the plan of a shape, or takes another reference to it, and
`juffte_destroy` drops one; the plan is freed with the last. Plans of different shapes can be
live at once, and in a build with OpenMP transforms may be called from several threads at
once.

Every transform also takes a plan of the caller's own as an optional last argument,
`plan=`, a `type(juffte_plan)`: `juffte_init` makes it, `juffte_fw`/`juffte_bw` run on it and
`juffte_destroy` frees it. It is not shared, so its calls take no lock and nothing else can
free it; it may run from several threads at once, but not while it is made or destroyed.

```fortran
type(juffte_plan) :: plan
call zfft2d(a, nx, ny, juffte_init, plan=plan)
call zfft2d(a, nx, ny, juffte_fw, plan=plan)
call zfft2d(a, nx, ny, juffte_destroy, plan=plan)
```

Lengths must be products of 2, 3 and 5, and a transform may have up to 2^31 - 1 elements.
