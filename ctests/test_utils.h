// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

#ifndef JUFFTE_CTESTS_TEST_UTILS_H
#define JUFFTE_CTESTS_TEST_UTILS_H

#include <complex.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

// Checks a forward + backward round trip x -> xhat over the whole array, against
// the rounding-error bound  ||x - xhat||_2 <= 2 log2(n) eps ||x||_2.
static inline int roundtrip_report(double err, int n)
{
    double bound = 2.0 * log2((double) n) * DBL_EPSILON;
    printf("  relative 2-norm error %10.3e   bound 2 log2(n) eps %10.3e\n", err, bound);
    return err <= bound;
}

static inline int roundtrip_check_c(const double _Complex *x, const double _Complex *xhat, int n)
{
    double diff = 0.0, norm = 0.0;
    for (int i = 0; i < n; i++) {
        double d = cabs(x[i] - xhat[i]);
        double m = cabs(x[i]);
        diff += d * d;
        norm += m * m;
    }
    return roundtrip_report(sqrt(diff / norm), n);
}

static inline int roundtrip_check_r(const double *x, const double *xhat, int n)
{
    double diff = 0.0, norm = 0.0;
    for (int i = 0; i < n; i++) {
        double d = x[i] - xhat[i];
        diff += d * d;
        norm += x[i] * x[i];
    }
    return roundtrip_report(sqrt(diff / norm), n);
}

#endif
