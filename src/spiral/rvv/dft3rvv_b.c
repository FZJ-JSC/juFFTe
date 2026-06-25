// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft3b_(double *Y, double *X, double *TW1, int *lp1, int *mp1) {
    double a213, a214, a215, a216;
    int a211, a212, j1, l1, m1;
    vfloat64m1x2_t r49, r50, r51, r52, r53, r54, rvvx2_4, rvvx2_5, 
            rvvx2_6;
    vfloat64m1_t  s77, s78, s79, s80, s81, s82, s83, s84, 
            s85, s86, s87, s88, t126, t127, t128, t129;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for(int j1 = 1; j1 < l1; j1++) {
#pragma GCC unroll 2
        for (size_t k1 = 0; k1 < m1; k1 += vl1) {
            vl1 = __riscv_vsetvl_e64m1(m1 - k1);
            a211 = (k1 + ((j1)*(m1)));
            r49 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(a211))), vl1);
            s77 = __riscv_vget_f64m1(r49, 0);
            s78 = __riscv_vget_f64m1(r49, 1);
            r50 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a211 + ((l1)*(m1)))))), vl1);
            s79 = __riscv_vget_f64m1(r50, 0);
            s80 = __riscv_vget_f64m1(r50, 1);
            r51 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a211 + ((((2)*(l1)))*(m1)))))), vl1);
            s81 = __riscv_vget_f64m1(r51, 0);
            s82 = __riscv_vget_f64m1(r51, 1);
            t126 = __riscv_vfadd(s79, s81, vl1);
            t127 = __riscv_vfadd(s80, s82, vl1);
            t128 = __riscv_vfnmsac(s77, 0.5, t126, vl1);
            t129 = __riscv_vfnmsac(s78, 0.5, t127, vl1);
            s83 = __riscv_vfmul(__riscv_vfsub(s80, s82, vl1), 0.8660254037844386, vl1);
            s84 = __riscv_vfmul(__riscv_vfsub(s79, s81, vl1), 0.8660254037844386, vl1);
            s85 = __riscv_vfadd(t128, s83, vl1);
            s86 = __riscv_vfsub(t129, s84, vl1);
            s87 = __riscv_vfsub(t128, s83, vl1);
            s88 = __riscv_vfadd(t129, s84, vl1);
            a212 = ((4)*(j1));
            a213 = TW1[a212];
            a214 = TW1[(a212 + 1)];
            a215 = TW1[(a212 + 2)];
            a216 = TW1[(a212 + 3)];
            r52 = __riscv_vset(__riscv_vset(rvvx2_4, 0, __riscv_vfadd(s77, t126, vl1)), 1, __riscv_vfadd(s78, t127, vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((3)*(j1)))*(m1)))))), r52, vl1);
            r53 = __riscv_vset(__riscv_vset(rvvx2_5, 0, __riscv_vfsub(__riscv_vfmul(s85, a213, vl1), __riscv_vfmul(s86, a214, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s85, a214, vl1), __riscv_vfmul(s86, a213, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((3)*(j1)))*(m1)) + m1)))), r53, vl1);
            r54 = __riscv_vset(__riscv_vset(rvvx2_6, 0, __riscv_vfsub(__riscv_vfmul(s87, a215, vl1), __riscv_vfmul(s88, a216, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s87, a216, vl1), __riscv_vfmul(s88, a215, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((3)*(j1)))*(m1)) + ((2)*(m1)))))), r54, vl1);
        }
    }
}
