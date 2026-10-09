// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "../src/juffte.h"

#define NDA 16777216
#define TOLLCONST 10

void init(double _Complex* a, int n);
void dump(const double _Complex* a, int n);
double geterrtol(int n);

int main(int argc, char** argv) {
    int nx, ny;
    if (argc < 3) {
        printf(" nx = ");
        if (scanf("%d", &nx) != 1 || nx <= 0) {
            fprintf(stderr, "Invalid input for nx\n");
            return 1;
        }
        printf(" ny = ");
        if (scanf("%d", &ny) != 1 || ny <= 0) {
            fprintf(stderr, "Invalid input for ny\n");
            return 1;
        }
    } else {
        nx = atoi(argv[1]);
        ny = atoi(argv[2]);
    }

    int n = nx * ny;
    if (n > NDA) {
        fprintf(stderr, "Requested size exceeds maximum (%d > %d)\n", n, NDA);
        return 1;
    }

    double _Complex* a = calloc(NDA, sizeof(double _Complex));
    if (!a) {
        perror("calloc");
        return 1;
    }

    init(a, n);

    // Init FFT
    zfft2d_c(a, nx, ny, juffte_init);

    // Save last value
    double _Complex a_in = a[n - 1];
    double errtol = geterrtol(n);
    // printf("errtol = %e\n", errtol);

    // Forward FFT
    zfft2d_c(a, nx, ny, juffte_fw);
    dump(a, n);

    // Inverse FFT again
    zfft2d_c(a, nx, ny, juffte_bw);
    dump(a, n);

    double err = cabs(a[n - 1] - a_in) / cabs(a_in);
    const char* exe = argv[0];

    if (err < errtol) {
        printf("%s PASS\n", exe);
    } else {
        printf("%s FAIL (error = %.2e)\n", exe, err);
        free(a);
        return 1;
    }

    free(a);
    return 0;
}

void init(double _Complex* a, int n) {
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1.0 + _Complex_I * (n - i);
    }
}

void dump(const double _Complex* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%4d: %.6f + %.6fi\n", i + 1, creal(a[i]), cimag(a[i]));
    }
}

double geterrtol(int n) {
    return TOLLCONST * DBL_EPSILON * log2((double)n);
}
