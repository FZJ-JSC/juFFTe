// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------
//
// Checks one juFFTe transform, called from C, against a reference:
//
//   juffte_test_c [-t complex|real] [-d fw|bw] [-a native|fftw] n1 [n2 [n3]]
//
// Defaults: complex, fw, native. The number of sizes is the dimension, n1 is
// contiguous. "-t real -d fw" is r2c, "-t real -d bw" c2r. "-a fftw" drives the
// FFTW compatibility layer the way FFTW code would.
//
// Every variant of the transform (in place, out of place, ...) runs on the same
// random input and is compared with the reference: FFTW when built with
// USE_REFERENCE_FFTW, otherwise a direct DFT for N = n1 n2 n3 < 4000.
// Exit status: 0 pass, 1 fail, 2 usage, 77 no reference at this size.

#define _XOPEN_SOURCE 700    // getopt, srand48
#define JUFFTE_NO_FFTW_NAMES // fftw_* below is the reference FFTW, not the shim
#include <complex.h>         // before fftw3.h, so that fftw_complex is double complex
#ifdef USE_REFERENCE_FFTW
#include <fftw3.h>
#endif
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "juffte.h"

// The direct DFT is only used below this total size.
#define DENSE_LIMIT 4000

#define COUNT(a) (sizeof(a) / sizeof *(a))

static int rank, is_complex = 1, dir = juffte_fw, fftw_api;
static int n[3] = {1, 1, 1};
static size_t N;               // n1 * n2 * n3
static size_t NH;              // (n1/2 + 1) * n2 * n3, the half spectrum of a real transform
static size_t in_len, out_len; // of the transform under test, in doubles
static int failures;

// Complex data is held as pairs of doubles. All buffers come from the library's
// aligned allocator, juffte_fftw_malloc.
static double complex *cx(double *a)
{
    return (double complex *) a;
}

// ---------------------------------------------------------------------------- checks

// ||a - ref||_2 / ||ref||_2 over len doubles; for complex data the same as over the
// complex values.
static double relerr(const double *a, const double *ref, size_t len)
{
    double diff = 0.0, norm = 0.0;
    for (size_t i = 0; i < len; i++) {
        diff += (a[i] - ref[i]) * (a[i] - ref[i]);
        norm += ref[i] * ref[i];
    }
    return sqrt(diff / norm);
}

// Rounding error of an FFT of length N: 2 log2(N) eps.
static double fft_bound(void)
{
    return 2.0 * log2((double) (N > 2 ? N : 2)) * DBL_EPSILON;
}

static void check(const char *what, double err, double bound)
{
    int ok = err <= bound; // false for NaN
    printf("  %-24s rel. error %9.2e   bound %9.2e   %s\n", what, err, bound, ok ? "ok" : "FAIL");
    failures += !ok;
}

static void check_unchanged(const char *what, const double *a, const double *b, size_t len)
{
    int ok = memcmp(a, b, len * sizeof *a) == 0;
    printf("  %-24s %s\n", what, ok ? "unchanged   ok" : "modified   FAIL");
    failures += !ok;
}

// ---------------------------------------------------------------------------- reference

#ifdef USE_REFERENCE_FFTW

static const char *reference_name(void) { return "FFTW"; }
static int have_reference(void) { return 1; }
static double reference_bound(void) { return fft_bound(); }

// FFTW takes its dimensions slowest first.
static void fftw_dims(int *nr)
{
    for (int d = 0; d < rank; d++)
        nr[d] = n[rank - 1 - d];
}

static void reference_c2c(double complex *x, int sign)
{
    int nr[3];
    fftw_dims(nr);
    fftw_plan p = fftw_plan_dft(rank, nr, x, x, sign, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
}

static void reference_r2c(const double *x, double complex *y)
{
    int nr[3];
    fftw_dims(nr);
    double *in = juffte_fftw_malloc(N * sizeof *in);
    memcpy(in, x, N * sizeof *in);
    fftw_plan p = fftw_plan_dft_r2c(rank, nr, in, y, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
    juffte_fftw_free(in);
}

static void reference_c2r(const double complex *x, double *y)
{
    int nr[3];
    fftw_dims(nr);
    double complex *in = juffte_fftw_malloc(NH * sizeof *in); // c2r overwrites its input
    memcpy(in, x, NH * sizeof *in);
    fftw_plan p = fftw_plan_dft_c2r(rank, nr, in, y, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
    juffte_fftw_free(in);
}

#else

static const char *reference_name(void) { return "direct DFT"; }

static int have_reference(void)
{
    return N < DENSE_LIMIT;
}

// The direct DFT's rounding error grows like sqrt(n) per dimension.
static double reference_bound(void)
{
    double s = 0.0;
    for (int d = 0; d < rank; d++)
        s += sqrt((double) n[d]);
    return 2.0 * s * DBL_EPSILON;
}

// Unnormalised DFT along each dimension in turn, in place. The DFT matrix is never
// formed: one row of twiddle factors per dimension, indexed by p*q mod n.
static void reference_c2c(double complex *x, int sign)
{
    for (int axis = 0; axis < rank; axis++) {
        const int len = n[axis];
        size_t stride = 1, outer = 1;
        for (int d = 0; d < axis; d++)
            stride *= n[d];
        for (int d = axis + 1; d < 3; d++)
            outer *= n[d];

        double complex *w = juffte_fftw_malloc(len * sizeof *w);
        double complex *line = juffte_fftw_malloc(len * sizeof *line);
        for (int k = 0; k < len; k++) {
            double t = 2.0 * 3.14159265358979323846 * k / len;
            w[k] = CMPLX(cos(t), sign * sin(t));
        }
        for (size_t o = 0; o < outer; o++)
            for (size_t i = 0; i < stride; i++) {
                double complex *base = x + i + o * stride * len;
                for (int p = 0; p < len; p++)
                    line[p] = base[p * stride];
                for (int q = 0; q < len; q++) {
                    double complex acc = 0.0;
                    for (int p = 0, k = 0; p < len; p++) { // k = p*q mod len
                        acc += line[p] * w[k];
                        k += q;
                        if (k >= len)
                            k -= len;
                    }
                    base[q * stride] = acc;
                }
            }
        juffte_fftw_free(w);
        juffte_fftw_free(line);
    }
}

static void reference_r2c(const double *x, double complex *y)
{
    const size_t h = n[0] / 2 + 1, rows = N / n[0];
    double complex *full = juffte_fftw_malloc(N * sizeof *full);
    for (size_t i = 0; i < N; i++)
        full[i] = x[i];
    reference_c2c(full, FFTW_FORWARD);
    for (size_t r = 0; r < rows; r++)
        memcpy(y + r * h, full + r * n[0], h * sizeof *y);
    juffte_fftw_free(full);
}

// Rebuilds the full spectrum from the half one by Hermitian symmetry.
static void reference_c2r(const double complex *x, double *y)
{
    const size_t h = n[0] / 2 + 1;
    double complex *full = juffte_fftw_malloc(N * sizeof *full);
    for (int k = 0; k < n[2]; k++)
        for (int j = 0; j < n[1]; j++)
            for (int i = 0; i < n[0]; i++) {
                size_t at = i + (size_t) n[0] * (j + (size_t) n[1] * k);
                if ((size_t) i < h)
                    full[at] = x[i + h * (j + (size_t) n[1] * k)];
                else
                    full[at] = conj(x[(n[0] - i) + h * ((n[1] - j) % n[1] +
                                                        (size_t) n[1] * ((n[2] - k) % n[2]))]);
            }
    reference_c2c(full, FFTW_BACKWARD);
    for (size_t i = 0; i < N; i++)
        y[i] = creal(full[i]);
    juffte_fftw_free(full);
}

#endif

// The expected output for input x, in juFFTe's convention: the native backward
// transform is normalised, the FFTW layer's is not.
static void reference(const double *x, double *y)
{
    if (is_complex) {
        memcpy(y, x, out_len * sizeof *y);
        reference_c2c(cx(y), dir);
    } else if (dir == juffte_fw) {
        reference_r2c(x, cx(y));
    } else {
        reference_c2r((const double complex *) x, y);
    }
    if (dir == juffte_bw && !fftw_api)
        for (size_t i = 0; i < out_len; i++)
            y[i] /= N;
}

// Random input in [-1, 1). A c2r input must be the half spectrum of a real array,
// so it is the reference r2c of random data.
static double *make_input(void)
{
    double *x = juffte_fftw_malloc(in_len * sizeof *x);
    double *r = (!is_complex && dir == juffte_bw) ? juffte_fftw_malloc(N * sizeof *r) : x;
    size_t len = (r == x) ? in_len : N;

    for (size_t i = 0; i < len; i++)
        r[i] = 2.0 * drand48() - 1.0;
    if (r != x) {
        reference_r2c(r, cx(x));
        juffte_fftw_free(r);
    }
    return x;
}

// ---------------------------------------------------------------------------- variants

// One way of calling the transform under test: run(in, out, iopt) leaves the result
// in out, or in in if in_place. init: call it with juffte_init first. keeps_input:
// it must leave in unchanged.
struct variant {
    const char *name;
    void (*run)(double *in, double *out, int iopt);
    int init, in_place, keeps_input;
};

static void c2c_in_place(double *in, double *out, int iopt)
{
    (void) out;
    if (rank == 1)
        zfft1d_c(cx(in), n[0], iopt);
    else if (rank == 2)
        zfft2d_c(cx(in), n[0], n[1], iopt);
    else
        zfft3d_c(cx(in), n[0], n[1], n[2], iopt);
}

static void c2c_out_of_place(double *in, double *out, int iopt)
{
    if (rank == 1)
        zfft1d_out_c(cx(in), cx(out), n[0], iopt);
    else if (rank == 2)
        zfft2d_out_c(cx(in), cx(out), n[0], n[1], iopt);
    else
        zfft3d_out_c(cx(in), cx(out), n[0], n[1], n[2], iopt);
}

static void r2c(double *in, double *out, int iopt)
{
    if (rank == 1)
        dzfft1d_c(in, cx(out), n[0], iopt);
    else if (rank == 2)
        dzfft2d_c(in, cx(out), n[0], n[1], iopt);
    else
        dzfft3d_c(in, cx(out), n[0], n[1], n[2], iopt);
}

static void c2r(double *in, double *out, int iopt)
{
    if (rank == 1)
        zdfft1d_c(cx(in), out, n[0], iopt);
    else if (rank == 2)
        zdfft2d_c(cx(in), out, n[0], n[1], iopt);
    else
        zdfft3d_c(cx(in), out, n[0], n[1], n[2], iopt);
}

// The FFTW layer as FFTW code would call it: dimensions slowest first, one plan.
// fftw_execute works on the arrays the plan was made with, so the data is staged
// through them.
static juffte_fftw_plan plan;
static double *plan_in, *plan_out;

static void api_execute(double *in, double *out, int iopt)
{
    if (iopt == juffte_init) {
        plan_in = juffte_fftw_malloc(in_len * sizeof *plan_in);
        plan_out = juffte_fftw_malloc(out_len * sizeof *plan_out);
        juffte_fftw_complex *i = (juffte_fftw_complex *) plan_in;
        juffte_fftw_complex *o = (juffte_fftw_complex *) plan_out;
        if (rank == 1)
            plan = juffte_fftw_plan_dft_1d(n[0], i, o, dir, FFTW_ESTIMATE);
        else if (rank == 2)
            plan = juffte_fftw_plan_dft_2d(n[1], n[0], i, o, dir, FFTW_ESTIMATE);
        else
            plan = juffte_fftw_plan_dft_3d(n[2], n[1], n[0], i, o, dir, FFTW_ESTIMATE);
        return;
    }
    memcpy(plan_in, in, in_len * sizeof *in);
    juffte_fftw_execute(plan);
    memcpy(in, plan_in, in_len * sizeof *in);
    memcpy(out, plan_out, out_len * sizeof *out);
}

static void api_execute_dft(double *in, double *out, int iopt)
{
    (void) iopt; // the plan's direction
    juffte_fftw_execute_dft(plan, (juffte_fftw_complex *) in, (juffte_fftw_complex *) out);
}

static const struct variant c2c_variants[] = {
    {"in place", c2c_in_place, .init = 1, .in_place = 1},
    {"out of place", c2c_out_of_place, .keeps_input = 1},
};
static const struct variant r2c_variants[] = {{"r2c", r2c, .init = 1, .keeps_input = 1}};
static const struct variant c2r_variants[] = {{"c2r", c2r, .init = 1}};
static const struct variant fftw_api_variants[] = {
    {"fftw_execute", api_execute, .init = 1, .keeps_input = 1},
    {"fftw_execute_dft", api_execute_dft, .keeps_input = 1},
};

// Runs every variant on the same input and compares it with the reference.
static void run_variants(const struct variant *v, size_t count)
{
    double *x = make_input(), *ref = juffte_fftw_malloc(out_len * sizeof *ref);
    double *in = juffte_fftw_malloc(in_len * sizeof *in);
    double *out = juffte_fftw_malloc(out_len * sizeof *out);
    const double bound = fft_bound() + reference_bound();
    char label[64];

    reference(x, ref);
    for (size_t i = 0; i < count; i++) {
        if (v[i].init) {
            memcpy(in, x, in_len * sizeof *in);
            v[i].run(in, out, juffte_init);
        }
        memcpy(in, x, in_len * sizeof *in);
        memset(out, 0, out_len * sizeof *out);
        v[i].run(in, out, dir);
        check(v[i].name, relerr(v[i].in_place ? in : out, ref, out_len), bound);
        if (v[i].keeps_input) {
            snprintf(label, sizeof label, "%s, input", v[i].name);
            check_unchanged(label, in, x, in_len);
        }
    }
    juffte_fftw_free(x), juffte_fftw_free(ref), juffte_fftw_free(in), juffte_fftw_free(out);
}

// ---------------------------------------------------------------------------- main

static int usage(const char *exe)
{
    fprintf(stderr, "usage: %s [-t complex|real] [-d fw|bw] [-a native|fftw] n1 [n2 [n3]]\n", exe);
    return 2;
}

static int parse_size(const char *s)
{
    char *end;
    long v = strtol(s, &end, 10);
    return (*end == '\0' && v >= 1 && v <= 1 << 30) ? (int) v : 0;
}

int main(int argc, char **argv)
{
    int opt;
    while ((opt = getopt(argc, argv, "t:d:a:")) != -1) {
        if (opt == 't' && strcmp(optarg, "complex") == 0)
            is_complex = 1;
        else if (opt == 't' && strcmp(optarg, "real") == 0)
            is_complex = 0;
        else if (opt == 'd' && strcmp(optarg, "fw") == 0)
            dir = juffte_fw;
        else if (opt == 'd' && strcmp(optarg, "bw") == 0)
            dir = juffte_bw;
        else if (opt == 'a' && strcmp(optarg, "native") == 0)
            fftw_api = 0;
        else if (opt == 'a' && strcmp(optarg, "fftw") == 0)
            fftw_api = 1;
        else
            return usage(argv[0]);
    }

    rank = argc - optind;
    if (rank < 1 || rank > 3)
        return usage(argv[0]);
    N = 1;
    for (int d = 0; d < rank; d++) {
        if (!(n[d] = parse_size(argv[optind + d])))
            return usage(argv[0]);
        N *= n[d];
    }
    NH = N / n[0] * (n[0] / 2 + 1);
    if (fftw_api && !is_complex) {
        fprintf(stderr, "The FFTW compatibility layer has no real transforms.\n");
        return 2;
    }
    in_len = is_complex ? 2 * N : dir == juffte_fw ? N : 2 * NH;
    out_len = is_complex ? 2 * N : dir == juffte_fw ? 2 * NH : N;

    printf("%s %s %d", is_complex ? "complex" : "real", dir == juffte_fw ? "fw" : "bw", n[0]);
    for (int d = 1; d < rank; d++)
        printf("x%d", n[d]);
    printf(", %s API, reference: %s\n", fftw_api ? "FFTW" : "native",
           have_reference() ? reference_name() : "none");
    if (!have_reference()) {
        puts("SKIP: no reference at this size");
        return 77;
    }

    srand48(5489);
    if (fftw_api)
        run_variants(fftw_api_variants, COUNT(fftw_api_variants));
    else if (is_complex)
        run_variants(c2c_variants, COUNT(c2c_variants));
    else if (dir == juffte_fw)
        run_variants(r2c_variants, COUNT(r2c_variants));
    else
        run_variants(c2r_variants, COUNT(c2r_variants));

    puts(failures ? "FAIL" : "PASS");
    return failures ? 1 : 0;
}
