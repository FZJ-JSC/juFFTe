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

#define NDA 16777216
#define TOLLCONST 10

void init(double *a, int n);
void dump(const double _Complex *a, int n);
void rdump(const double *a, int n);
double geterrtol(int n);

int main(int argc, char **argv) {
    static double a[NDA], b[NDA];
    static double _Complex a_c[NDA], b_c[NDA];

    int n;
    double a_in;
    char exe[20];

    if (argc < 2) {
        printf(" N = ");
        scanf("%d", &n);
    } else {
        n = atoi(argv[1]);
    }

    init(a, n);
    a_in = a[n - 1];  // C is 0-based
    double errtol = geterrtol(n);
    // printf("errtol = %e\n", errtol);


    dzfft1d_c(a, a_c, n, juffte_init);
    dzfft1d_c(a, a_c, n, juffte_fw);
    dump(a_c, (n / 2 + 1));

    zdfft1d_c(a_c, a, n, juffte_init);

    zdfft1d_c(a_c, a, n, juffte_bw);
    rdump(a, n);

    strncpy(exe, argv[0], sizeof(exe) - 1);
    exe[sizeof(exe) - 1] = '\0';

    if (fabs((a_in - a[n - 1]) / a_in) < errtol) {
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

double geterrtol(int n) {
    return TOLLCONST * DBL_EPSILON * log2((double)n);
}
