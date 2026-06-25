// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

#ifndef JUFFTE_H
#define JUFFTE_H
#define FFTW_ALIGNMENT 32
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <complex.h>

int juffte_init =0;
int juffte_fw = 1;
int juffte_bw = -1;


#ifdef FFTW
typedef double fftw_complex[2];
#define CLXTYP fftw_complex // double[2]
#else
#define CLXTYP double _Complex // native complex
#endif

void zfft1d_c(CLXTYP *input, int n, int iopt);
void zfft1d_out_c(CLXTYP *input, CLXTYP *output, int n, int iopt);
void zfft2d_c(CLXTYP *input, int nx, int ny, int iopt);
void zfft3d_c(CLXTYP *input, int nx, int ny, int nz, int iopt);
void dzfft1d_c(double *a, CLXTYP *a_c, int n, int iopt);
void dzfft2d_c(double *a, CLXTYP *a_c, int nx, int ny, int iopt);
void dzfft3d_c(double *a, CLXTYP *a_c, int nx, int ny, int nz, int iopt);
void zdfft1d_c(CLXTYP *a, double *a_r, int n, int iopt);
void zdfft2d_c(CLXTYP *a, double *a_r, int nx, int ny, int iopt);
void zdfft3d_c(CLXTYP *a, double *a_r, int nx, int ny, int nz, int iopt);

// FFTW stuff

#ifdef FFTW

int FFTW_init = 0;
int FFTW_FORWARD = -1;
int FFTW_BACKWARD = 1;
int FFTW_ESTIMATE = 0;
int FFTW_MEASURE    = 1;
int FFTW_PATIENT    = 2;
int FFTW_EXHAUSTIVE = 3;

// typedef double fftw_complex[2];


typedef struct
{
    int n;           // length of transform
    int dir;
    int flag;
    // Buffers (only some are used depending on type)
    double *r_in;           // R2C input or C2R output
    fftw_complex *c_in;  // C2C or C2R input
    fftw_complex *c_out; // C2C or R2C output
    double *r_out;          // C2R output or R2C input (rare)

    // Derived sizes
    int complex_len; // n/2 + 1 for R2C/C2R
} fftw_plan;

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

fftw_plan fftw_plan_dft_1d(int n, fftw_complex *in, fftw_complex *out, int dir, int flag)
{
    fftw_plan p;
    p.n = n;
    p.c_in = in;
    p.c_out = out;
    p.dir = dir;
    p.flag = flag;

    if (p.c_in == p.c_out)
        {
            zfft1d_c(p.c_in, p.n, 0);
        }
    else
        {
            zfft1d_out_c(p.c_in, p.c_out, p.n, 0);
        }
    
    return p;
}

void fft_plan_print(fftw_plan p) // for debug
{

    if (p.c_in == p.c_out)
    {
        printf("In place FFT\n");
    }

    printf("Input array:\n");
    for (int i = 0; i < p.n; i++)
        printf("  [%d] = %f + %fi\n", i, p.c_in[i][0], p.c_in[i][1]);

    printf("Output array:\n");
    for (int i = 0; i < p.n; i++)
        printf("  [%d] = %f + %fi\n", i, p.c_out[i][0], p.c_out[i][1]);
}

void fftw_execute(fftw_plan p) // for debug
{

    if(p.c_in == p.c_out)    
    {
        zfft1d_c(p.c_in, p.n, p.dir);
    }
    else
    {
        zfft1d_out_c(p.c_in, p.c_out, p.n, p.dir);
    }     
}
#endif



#ifdef __cplusplus
}
}
#endif

#endif // juffte_H