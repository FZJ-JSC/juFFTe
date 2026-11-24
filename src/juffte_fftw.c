// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------
//
// FFTW compatibility layer. Declarations are in juffte.h, which also maps the
// fftw_* names used below onto the exported juffte_fftw_* symbols.

#include <stdio.h>
#include <stdlib.h>

#include "juffte.h"

// The plans and the transforms are those of the Fortran FFTW layer (juffte.F90), which
// gives every plan its own juFFTe plan and undoes juFFTe's backward scaling. Dimensions
// in the native order, nx contiguous.
void *juffte_fftw_plan_c(int rank, int nx, int ny, int nz, int sign);
void juffte_fftw_execute_c(void *plan, fftw_complex *in, fftw_complex *out); // out NULL: in place
void juffte_fftw_destroy_c(void *plan);

struct juffte_plan_s {
    void *plan;         // the Fortran layer's
    int n;              // total length (nx*ny*nz)
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

static fftw_plan plan_new(int rank, int nx, int ny, int nz, fftw_complex *in,
                          fftw_complex *out, int sign)
{
    fftw_plan p = (fftw_plan) malloc(sizeof(*p));
    if (!p)
        return NULL;
    p->plan = juffte_fftw_plan_c(rank, nx, ny, nz, sign);
    p->n = nx * ny * nz;
    p->c_in = in;
    p->c_out = out;
    return p;
}

fftw_plan fftw_plan_dft_1d(int n, fftw_complex *in, fftw_complex *out, int dir, int flag)
{
    (void) flag; // juFFTe has one plan per transform, however it is asked to plan
    return plan_new(1, n, 1, 1, in, out, dir);
}

// As in FFTW, dimensions are given slowest first, the reverse of the native API, where nx
// is the contiguous one: (n0, n1) here is zfft2d(n1, n0).
fftw_plan fftw_plan_dft_2d(int n0, int n1, fftw_complex *in, fftw_complex *out, int dir, int flag)
{
    (void) flag;
    return plan_new(2, n1, n0, 1, in, out, dir);
}

fftw_plan fftw_plan_dft_3d(int n0, int n1, int n2, fftw_complex *in, fftw_complex *out,
                           int dir, int flag)
{
    (void) flag;
    return plan_new(3, n2, n1, n0, in, out, dir);
}

void fftw_execute(const fftw_plan p)
{
    if (!p)
        return;
    juffte_fftw_execute_c(p->plan, p->c_in, p->c_in == p->c_out ? NULL : p->c_out);
}

void fftw_execute_dft(const fftw_plan p, fftw_complex *in, fftw_complex *out)
{
    if (!p)
        return;
    juffte_fftw_execute_c(p->plan, in, in == out ? NULL : out);
}

void fftw_destroy_plan(fftw_plan p)
{
    if (!p)
        return;
    juffte_fftw_destroy_c(p->plan);
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
