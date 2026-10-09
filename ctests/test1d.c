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


void init(double _Complex* a, int n);
void dump(const double _Complex* a, int n);

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

    // Keep the input for the round-trip check.

    double _Complex* a_in = malloc(n * sizeof *a_in);

    if (!a_in) {

        perror("malloc");

        return 1;

    }

    memcpy(a_in, a, n * sizeof *a_in);

    zfft1d_c(a, n, juffte_init);   
    zfft1d_c(a, n, juffte_fw);     
    dump(a, n);

    zfft1d_c(a, n, juffte_bw);    
    dump(a, n);

    const char* exe = argv[0];
    if (roundtrip_check_c(a_in, a, n)) {
        printf("%s PASS\n", exe);
    } else {
        printf("%s FAIL\n", exe);
        return 1;
    }

    free(a);

    free(a_in);

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
