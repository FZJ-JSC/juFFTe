// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include "../src/juffte.h"

#define NDA 16777216

void init(double *a, int n);
void dump_complex(const double complex *a, int n);
void dump_real(const double *a, int n);

int main(int argc, char **argv) {
    static double a[NDA], b[NDA];
    static double complex a_c[NDA], b_c[NDA];

    double a_in;
    int nx, ny, nz;
    char exe[20];

    if (argc < 4) {
        printf(" NX = "); scanf("%d", &nx);
        printf(" NY = "); scanf("%d", &ny);
        printf(" NZ = "); scanf("%d", &nz);
    } else {
        nx = atoi(argv[1]);
        ny = atoi(argv[2]);
        nz = atoi(argv[3]);
    }

    int total = nx * ny * nz;
    int spec_len = (nx / 2 + 1) * ny * nz;

    init(a, total);
    a_in = a[total - 1];

    int iopt;


    dzfft3d_c(a, a_c, nx, ny, nz, juffte_init);

    dzfft3d_c(a, a_c, nx, ny, nz, juffte_fw);
    dump_complex(a_c, spec_len);

    zdfft3d_c(a_c, a, nx, ny, nz, juffte_init);

    zdfft3d_c(a_c, a, nx, ny, nz, juffte_bw);
    dump_real(a, total);

    strncpy(exe, argv[0], sizeof(exe));
    exe[sizeof(exe)-1] = '\0';

    if (fabs(a_in - a[total - 1]) < 1e-6) {
        printf("%s PASS\n", exe);
    } else {
        printf("%s FAIL\n", exe);
        return 1;
    }

    return 0;
}

// Initialization of real input
void init(double *a, int n) {
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        a[i] = (double)(i + 1);
    }
}

// Dump complex array
void dump_complex(const double complex *a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%5d  (%12.5e, %12.5e)\n", i + 1, creal(a[i]), cimag(a[i]));
    }
}

// Dump real array
void dump_real(const double *a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%5d  %12.5e\n", i + 1, a[i]);
    }
}
