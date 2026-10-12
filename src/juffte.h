// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

#ifndef JUFFTE_H
#define JUFFTE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FFTW_ALIGNMENT 32

enum { juffte_init = 0, juffte_fw = -1, juffte_bw = 1 };

// Native C API. The complex type is layout-compatible with fftw_complex below.
#define CLXTYP double _Complex

void zfft1d_c(CLXTYP *input, int n, int iopt);
void zfft1d_out_c(CLXTYP *input, CLXTYP *output, int n, int iopt);
void zfft2d_c(CLXTYP *input, int nx, int ny, int iopt);
void zfft2d_out_c(CLXTYP *input, CLXTYP *output, int nx, int ny, int iopt);
void zfft3d_c(CLXTYP *input, int nx, int ny, int nz, int iopt);
void zfft3d_out_c(CLXTYP *input, CLXTYP *output, int nx, int ny, int nz, int iopt);
void dzfft1d_c(double *a, CLXTYP *a_c, int n, int iopt);
void dzfft2d_c(double *a, CLXTYP *a_c, int nx, int ny, int iopt);
void dzfft3d_c(double *a, CLXTYP *a_c, int nx, int ny, int nz, int iopt);
void zdfft1d_c(CLXTYP *a, double *a_r, int n, int iopt);
void zdfft2d_c(CLXTYP *a, double *a_r, int nx, int ny, int iopt);
void zdfft3d_c(CLXTYP *a, double *a_r, int nx, int ny, int nz, int iopt);

// ----------------------------------------------------------------------------
// FFTW compatibility layer. Always available; the definitions live in the
// library, so this header may be included from any number of translation units.
// It is part of libjuffte -- there is no separate library to link.
// ----------------------------------------------------------------------------

// Matches FFTW's fallback typedef, so in[i][0] / in[i][1] behave as expected.
typedef double juffte_fftw_complex[2];

// Values taken from fftw3.h so that flags compare and combine identically. The
// definitions are token for token those of fftw3.h, so both headers can be included.
#define FFTW_FORWARD (-1)
#define FFTW_BACKWARD (+1)
#define FFTW_MEASURE (0U)
#define FFTW_EXHAUSTIVE (1U << 3)
#define FFTW_PATIENT (1U << 5)
#define FFTW_ESTIMATE (1U << 6)

// Opaque, and a pointer as in FFTW, so that `fftw_plan p = NULL;` compiles.
typedef struct juffte_plan_s *juffte_fftw_plan;

// The entry points carry juffte_ names so that the library exports nothing that
// clashes with real FFTW; a program can therefore link juFFTe and libfftw3 side
// by side (the benchmark does). The macros below give source compatibility: code
// written against FFTW keeps calling fftw_*, and including this header instead of
// fftw3.h redirects those calls into juFFTe.
void *juffte_fftw_malloc(size_t n);
void juffte_fftw_free(void *p);

juffte_fftw_plan juffte_fftw_plan_dft_1d(int n, juffte_fftw_complex *in,
                                         juffte_fftw_complex *out, int dir, int flag);
juffte_fftw_plan juffte_fftw_plan_dft_2d(int n0, int n1, juffte_fftw_complex *in,
                                         juffte_fftw_complex *out, int dir, int flag);
juffte_fftw_plan juffte_fftw_plan_dft_3d(int n0, int n1, int n2, juffte_fftw_complex *in,
                                         juffte_fftw_complex *out, int dir, int flag);

void juffte_fftw_execute(const juffte_fftw_plan p);
void juffte_fftw_execute_dft(const juffte_fftw_plan p, juffte_fftw_complex *in,
                             juffte_fftw_complex *out);
void juffte_fftw_destroy_plan(juffte_fftw_plan p);

void juffte_fft_plan_print(const juffte_fftw_plan p); // debug helper, not part of the FFTW API

// Define JUFFTE_NO_FFTW_NAMES to leave FFTW's names alone, e.g. to include fftw3.h
// as well and call both libraries from one file (the test suite does).
#ifndef JUFFTE_NO_FFTW_NAMES
typedef juffte_fftw_complex fftw_complex;
typedef juffte_fftw_plan    fftw_plan;

#define fftw_malloc        juffte_fftw_malloc
#define fftw_free          juffte_fftw_free
#define fftw_plan_dft_1d   juffte_fftw_plan_dft_1d
#define fftw_plan_dft_2d   juffte_fftw_plan_dft_2d
#define fftw_plan_dft_3d   juffte_fftw_plan_dft_3d
#define fftw_execute       juffte_fftw_execute
#define fftw_execute_dft   juffte_fftw_execute_dft
#define fftw_destroy_plan  juffte_fftw_destroy_plan
#define fft_plan_print     juffte_fft_plan_print
#endif // JUFFTE_NO_FFTW_NAMES

#ifdef __cplusplus
}
#endif

#endif // JUFFTE_H
