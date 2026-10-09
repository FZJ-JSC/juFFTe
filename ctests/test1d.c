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

#define TOLLCONST 10

void init(double _Complex* a, int n);
void dump(const double _Complex* a, int n);
double geterrtol(int n);

int main(int argc, char** argv) {
    int n;
    if (argc < 2) {
        printf("n = ");
        if (scanf("%d", &n) != 1 || n <= 0) {
            fprintf(stderr, "Invalid input for n.\n");
            return 1;
        }
    } else {
        n = atoi(argv[1]);
    }

    double _Complex* a = calloc(n, sizeof(double _Complex));
 
    if (!a) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    init(a, n);
    dump(a, n);

    double _Complex a_in = a[n - 1];  // Save original last value
    double errtol = geterrtol(n);
    // printf("errtol = %e\n", errtol);

    zfft1d_c(a, n, juffte_init);   
    zfft1d_c(a, n, juffte_fw);     
    dump(a, n);

    zfft1d_c(a, n, juffte_bw);    
    dump(a, n);

    double err = cabs(a[n - 1] - a_in) / cabs(a_in);

    const char* exe = argv[0];
    if (err < errtol) {
        printf("%s PASS\n", exe);
    } else {
        printf("%s FAIL (error = %e)\n", exe, err);
        return 1;
    }

    free(a);

    return 0;
}

void init(double _Complex* a, int n) {
#pragma omp parallel for simd
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1.0 + _Complex_I * (n - i);
    }
}

void dump(const double _Complex* a, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%4d: %.4f + %.4fi\n", i + 1, creal(a[i]), cimag(a[i]));
    }
}

double geterrtol(int n) {
    return TOLLCONST * DBL_EPSILON * log2((double)n);
}
