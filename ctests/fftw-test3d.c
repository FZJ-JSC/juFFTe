// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#ifdef WITHFFTW
#include <fftw3.h>
#endif
#ifndef WITHFFTW
#include <juffte.h>
#endif

int main(int argc, char **argv)
{
    printf("FFTW 3D interface test\n");
    int nx, ny, nz;
    if (argc < 4)
    {
        printf("nx = ");
        if (scanf("%d", &nx) != 1 || nx <= 0)
        {
            fprintf(stderr, "Invalid input for nx.\n");
            return 1;
        }
        printf("ny = ");
        if (scanf("%d", &ny) != 1 || ny <= 0)
        {
            fprintf(stderr, "Invalid input for ny.\n");
            return 1;
        }
        printf("nz = ");
        if (scanf("%d", &nz) != 1 || nz <= 0)
        {
            fprintf(stderr, "Invalid input for nz.\n");
            return 1;
        }
    }
    else
    {
        nx = atoi(argv[1]);
        ny = atoi(argv[2]);
        nz = atoi(argv[3]);
    }

    int i, j, k, idx, n = nx * ny * nz;
    fftw_complex *in, *out;
    fftw_plan plan;

    /* Allocate input/output arrays (row-major, nx * ny * nz) */
    in  = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);

    /* Initialize input data (a simple ramp) */
    for (i = 0; i < nx; i++) {
        for (j = 0; j < ny; j++) {
            for (k = 0; k < nz; k++) {
                idx = (i * ny + j) * nz + k;
                in[idx][0] = (double)(idx + 1);  /* real part */
                in[idx][1] = n - (double)(idx);  /* imag part */
            }
        }
    }

    printf("Input data:\n");
    for (i = 0; i < nx; i++)
        for (j = 0; j < ny; j++)
            for (k = 0; k < nz; k++) {
                idx = (i * ny + j) * nz + k;
                printf("%3d %3d %3d: %12.6f  %12.6f\n", i+1, j+1, k+1, in[idx][0], in[idx][1]);
            }

    /* Create FFT plan: complex-to-complex forward transform */
    plan = fftw_plan_dft_3d(nx, ny, nz, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    /* Execute FFT */
// fft_plan_print(plan);

fftw_execute(plan);

    printf("\nFFT output:\n");
    for (i = 0; i < nx; i++)
        for (j = 0; j < ny; j++)
            for (k = 0; k < nz; k++) {
                idx = (i * ny + j) * nz + k;
                printf("%3d %3d %3d: %12.6f  %12.6f\n", i+1, j+1, k+1, out[idx][0], out[idx][1]);
            }

    /* Clean up */
    // fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
    return 0;
}
