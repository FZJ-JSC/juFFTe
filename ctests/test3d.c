// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>
#include <float.h>
#include "../src/juffte.h"
#include "test_utils.h"

#define NDA 16777216

void init(double _Complex* a, int n);
void dump(const double _Complex* a, int n);

int main(int argc, char** argv) {
    int nx, ny, nz;

    if (argc < 4) {
        printf(" NX = "); if (scanf("%d", &nx) != 1) return 1;
        printf(" NY = "); if (scanf("%d", &ny) != 1) return 1;
        printf(" NZ = "); if (scanf("%d", &nz) != 1) return 1;
    } else {
        nx = atoi(argv[1]);
        ny = atoi(argv[2]);
        nz = atoi(argv[3]);
    }

    int n = nx * ny * nz;
    if (n > NDA) {
        fprintf(stderr, "Size %d exceeds buffer limit %d\n", n, NDA);
        return 1;
    }

    double _Complex* a = calloc(NDA, sizeof(double _Complex));
    if (!a) {
        perror("calloc");
        return 1;
    }

    init(a, n);

    // init FFT
    zfft3d_c(a, nx, ny, nz, juffte_init);

    // Keep the input for the round-trip check.

    double _Complex* a_in = malloc(n * sizeof *a_in);

    if (!a_in) {

        perror("malloc");

        return 1;

    }

    memcpy(a_in, a, n * sizeof *a_in);

    // Inverse FFT
    zfft3d_c(a, nx, ny, nz, juffte_fw);
    dump(a, n);

    // Forward FFT again
    zfft3d_c(a, nx, ny, nz, juffte_bw);
    dump(a, n);

    if (roundtrip_check_c(a_in, a, n)) {
        printf("%s PASS\n", argv[0]);
    } else {
        printf("%s FAIL\n", argv[0]);
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
        a[i] = (double)(i + 1) + _Complex_I * (double)(n - i);
    }
}

void dump(const double _Complex* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%4d: %.6f + %.6fi\n", i + 1, creal(a[i]), cimag(a[i]));
    }
}
