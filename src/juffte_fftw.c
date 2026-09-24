// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------
//
// FFTW compatibility layer. Declarations are in juffte.h.

#include <stdio.h>
#include <stdlib.h>

#include "juffte.h"

struct juffte_plan_s {
    int n;              // total length (nx*ny*nz)
    int rank;           // 1, 2 or 3
    int nx, ny, nz;     // per-dimension sizes
    int dir;
    int flag;
    fftw_complex *c_in;
    fftw_complex *c_out;
};

void *fftw_malloc(size_t n)
{
    void *p = NULL;
    if (posix_memalign(&p, FFTW_ALIGNMENT, n) != 0)
        p = NULL;
    return p;
}

void fftw_free(void *p)
{
    free(p);
}

static struct juffte_plan_s *plan_alloc(int rank, int nx, int ny, int nz,
                                        fftw_complex *in, fftw_complex *out,
                                        int dir, int flag)
{
    struct juffte_plan_s *p = (struct juffte_plan_s *) malloc(sizeof(*p));
    if (!p)
        return NULL;
    p->rank = rank;
    p->nx = nx;
    p->ny = ny;
    p->nz = nz;
    p->n = nx * ny * nz;
    p->c_in = in;
    p->c_out = out;
    p->dir = dir;
    p->flag = flag;
    return p;
}

// The transform routines take the native complex type; fftw_complex is
// layout-compatible (two doubles), so the cast is safe.
static CLXTYP *cx(fftw_complex *a)
{
    return (CLXTYP *) a;
}

// juFFTe scales the backward transform by 1/n, FFTW does not. Undo the scaling
// so that ported FFTW code sees FFTW's convention.
// TODO: dirty fix. Settle the normalisation convention in the library instead.
static void unscale_backward(const fftw_plan p, fftw_complex *out)
{
    if (p->dir != FFTW_BACKWARD)
        return;

    const double s = (double) p->n;
    for (int i = 0; i < p->n; i++) {
        out[i][0] *= s;
        out[i][1] *= s;
    }
}

static void plan_run(const fftw_plan p, fftw_complex *in, fftw_complex *out)
{
    if (p->rank == 3) {
        if (in == out)
            zfft3d_c(cx(in), p->nx, p->ny, p->nz, p->dir);
        else
            zfft3d_out_c(cx(in), cx(out), p->nx, p->ny, p->nz, p->dir);
    } else if (p->rank == 2) {
        if (in == out)
            zfft2d_c(cx(in), p->nx, p->ny, p->dir);
        else
            zfft2d_out_c(cx(in), cx(out), p->nx, p->ny, p->dir);
    } else {
        if (in == out)
            zfft1d_c(cx(in), p->n, p->dir);
        else
            zfft1d_out_c(cx(in), cx(out), p->n, p->dir);
    }

    unscale_backward(p, out);
}

fftw_plan fftw_plan_dft_1d(int n, fftw_complex *in, fftw_complex *out, int dir, int flag)
{
    fftw_plan p = plan_alloc(1, n, 1, 1, in, out, dir, flag);
    if (!p)
        return NULL;

    if (in == out)
        zfft1d_c(cx(in), n, juffte_init);
    else
        zfft1d_out_c(cx(in), cx(out), n, juffte_init);

    return p;
}

fftw_plan fftw_plan_dft_2d(int nx, int ny, fftw_complex *in, fftw_complex *out, int dir, int flag)
{
    fftw_plan p = plan_alloc(2, nx, ny, 1, in, out, dir, flag);
    if (!p)
        return NULL;

    if (in == out)
        zfft2d_c(cx(in), nx, ny, juffte_init);
    else
        zfft2d_out_c(cx(in), cx(out), nx, ny, juffte_init);

    return p;
}

fftw_plan fftw_plan_dft_3d(int nx, int ny, int nz, fftw_complex *in, fftw_complex *out,
                           int dir, int flag)
{
    fftw_plan p = plan_alloc(3, nx, ny, nz, in, out, dir, flag);
    if (!p)
        return NULL;

    if (in == out)
        zfft3d_c(cx(in), nx, ny, nz, juffte_init);
    else
        zfft3d_out_c(cx(in), cx(out), nx, ny, nz, juffte_init);

    return p;
}

void fftw_execute(const fftw_plan p)
{
    if (!p)
        return;
    plan_run(p, p->c_in, p->c_out);
}

void fftw_execute_dft(const fftw_plan p, fftw_complex *in, fftw_complex *out)
{
    if (!p)
        return;
    plan_run(p, in, out);
}

void fftw_destroy_plan(fftw_plan p)
{
    free(p);
}

void fft_plan_print(const fftw_plan p)
{
    if (!p)
        return;

    if (p->c_in == p->c_out)
        printf("In place FFT\n");

    printf("Input array:\n");
    for (int i = 0; i < p->n; i++)
        printf("  [%d] = %f + %fi\n", i, p->c_in[i][0], p->c_in[i][1]);

    printf("Output array:\n");
    for (int i = 0; i < p->n; i++)
        printf("  [%d] = %f + %fi\n", i, p->c_out[i][0], p->c_out[i][1]);
}
