// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include <float.h>
#include "../src/juffte.h"
#include "test_utils.h"

#define NDA 16777216

void init(double *a, int n);
void dump(const double _Complex *a, int n);
void rdump(const double *a, int n);

int main(int argc, char **argv) {
    static double a[NDA], b[NDA];
    static double _Complex a_c[NDA], b_c[NDA];

    int nx, ny;
    static double a_in[NDA];
    char exe[20];

    if (argc < 3) {
        printf(" NX = ");
        scanf("%d", &nx);
        printf(" NY = ");
        scanf("%d", &ny);
    } else {
        nx = atoi(argv[1]);
        ny = atoi(argv[2]);
    }

    init(a, nx * ny);
    memcpy(a_in, a, (nx * ny) * sizeof a[0]);  // keep the input for the round-trip check


    dzfft2d_c(a, a_c, nx, ny, juffte_init);
    dzfft2d_c(a, a_c, nx, ny, juffte_fw);
    dump(a_c, (nx / 2 + 1) * ny);

    zdfft2d_c(a_c, a, nx, ny, juffte_init);

    zdfft2d_c(a_c, a, nx, ny, juffte_bw);
    rdump(a, nx * ny);

    strncpy(exe, argv[0], sizeof(exe) - 1);
    exe[sizeof(exe) - 1] = '\0';

    if (roundtrip_check_r(a_in, a, nx * ny)) {
        printf("%s PASS\n", exe);
    } else {
        printf("%s FAIL\n", exe);
        return 1;
    }

    return 0;
}

void init(double *a, int n) {
    for (int i = 0; i < n; ++i) {
        a[i] = (double)(i + 1);  // Fortran is 1-based
    }
}

void dump(const double _Complex *a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d (%f, %f)\n", i + 1, creal(a[i]), cimag(a[i]));
    }
}

void rdump(const double *a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d %f\n", i + 1, a[i]);
    }
}
