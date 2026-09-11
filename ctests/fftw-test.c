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
    printf("FFTW interface test\n");
    int n;
    if (argc < 2)
    {
        printf("n = ");
        if (scanf("%d", &n) != 1 || n <= 0)
        {
            fprintf(stderr, "Invalid input for n.\n");
            return 1;
        }
    }
    else
    {
        n = atoi(argv[1]);
    }

    int i;
    fftw_complex *in, *out;
    fftw_plan plan;

    /* Allocate input/output arrays */
    in  = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * n);

    /* Initialize input data (a simple ramp) */
    for (i = 0; i < n; i++) {
        in[i][0] = (double)(i + 1);  /* real part */
        in[i][1] = n - (double)(i );  /* imag part */
    }

    printf("Input data:\n");
    for (i = 0; i < n; i++)
        printf("%3d: %12.6f  %12.6f\n", i+1, in[i][0], in[i][1]);

    /* Create FFT plan: complex-to-complex forward transform */
    plan = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    /* Execute FFT */
// fft_plan_print(plan);

fftw_execute(plan);

    printf("\nFFT output:\n");
    for (i = 0; i < n; i++)
        printf("%3d: %12.6f  %12.6f\n", i+1, out[i][0], out[i][1]);

    /* Clean up */
    // fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
    return 0;
}