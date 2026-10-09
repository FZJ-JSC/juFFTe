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
#include "test_utils.h"

#define NDA 16777216

void init(double _Complex* a, int n);
void dump(const double _Complex* a, int n);

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
    // Keep the input for the round-trip check.
    double _Complex* a_in = malloc(n * sizeof *a_in);
    if (!a_in) {
        perror("malloc");
        return 1;
    }
    memcpy(a_in, a, n * sizeof *a_in);

    // Forward FFT
    zfft2d_c(a, nx, ny, juffte_fw);
    dump(a, n);

    // Inverse FFT again
    zfft2d_c(a, nx, ny, juffte_bw);
    dump(a, n);
    const char* exe = argv[0];

    if (roundtrip_check_c(a_in, a, n)) {
        printf("%s PASS\n", exe);
    } else {
        printf("%s FAIL\n", exe);
        free(a);
        free(a_in);
        return 1;
    }

    free(a);

    free(a_in);
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
