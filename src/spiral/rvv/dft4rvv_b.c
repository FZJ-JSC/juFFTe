// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft4b_(double *Y, double *X, double *TW1, int *lp1, int *mp1) {
    double a280, a281, a282, a283, a284, a285;
    int a278, a279, j1, l1, m1;
    vfloat64m1x2_t r65, r66, r67, r68, r69, r70, r71, r72, 
            rvvx2_5, rvvx2_6, rvvx2_7, rvvx2_8;
    vfloat64m1_t  s75, s76, s77, s78, s79, s80, s81, s82, 
            s83, s84, s85, s86, s87, s88, t154, t155, 
            t156, t157, t158, t159, t160, t161;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for(int j1 = 1; j1 < l1; j1++) {
#pragma GCC unroll 2
        for (size_t k1 = 0; k1 < m1; k1 += vl1) {
            vl1 = __riscv_vsetvl_e64m1(m1 - k1);
            a278 = (k1 + ((j1)*(m1)));
            r65 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(a278))), vl1);
            s75 = __riscv_vget_f64m1(r65, 0);
            s76 = __riscv_vget_f64m1(r65, 1);
            r66 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a278 + ((l1)*(m1)))))), vl1);
            s77 = __riscv_vget_f64m1(r66, 0);
            s78 = __riscv_vget_f64m1(r66, 1);
            r67 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a278 + ((((2)*(l1)))*(m1)))))), vl1);
            s79 = __riscv_vget_f64m1(r67, 0);
            s80 = __riscv_vget_f64m1(r67, 1);
            r68 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a278 + ((((3)*(l1)))*(m1)))))), vl1);
            s81 = __riscv_vget_f64m1(r68, 0);
            s82 = __riscv_vget_f64m1(r68, 1);
            t154 = __riscv_vfadd(s75, s79, vl1);
            t155 = __riscv_vfadd(s76, s80, vl1);
            t156 = __riscv_vfsub(s75, s79, vl1);
            t157 = __riscv_vfsub(s76, s80, vl1);
            t158 = __riscv_vfadd(s77, s81, vl1);
            t159 = __riscv_vfadd(s78, s82, vl1);
            t160 = __riscv_vfsub(s77, s81, vl1);
            t161 = __riscv_vfsub(s78, s82, vl1);
            s83 = __riscv_vfsub(t154, t158, vl1);
            s84 = __riscv_vfsub(t155, t159, vl1);
            s85 = __riscv_vfadd(t156, t161, vl1);
            s86 = __riscv_vfsub(t157, t160, vl1);
            s87 = __riscv_vfsub(t156, t161, vl1);
            s88 = __riscv_vfadd(t157, t160, vl1);
            a279 = ((6)*(j1));
            a280 = TW1[a279];
            a281 = TW1[(a279 + 1)];
            a282 = TW1[(a279 + 2)];
            a283 = TW1[(a279 + 3)];
            a284 = TW1[(a279 + 4)];
            a285 = TW1[(a279 + 5)];
            r69 = __riscv_vset(__riscv_vset(rvvx2_5, 0, __riscv_vfadd(t154, t158, vl1)), 1, __riscv_vfadd(t155, t159, vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((4)*(j1)))*(m1)))))), r69, vl1);
            r70 = __riscv_vset(__riscv_vset(rvvx2_6, 0, __riscv_vfsub(__riscv_vfmul(s85, a280, vl1), __riscv_vfmul(s86, a281, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s85, a281, vl1), __riscv_vfmul(s86, a280, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((4)*(j1)))*(m1)) + m1)))), r70, vl1);
            r71 = __riscv_vset(__riscv_vset(rvvx2_7, 0, __riscv_vfsub(__riscv_vfmul(s83, a282, vl1), __riscv_vfmul(s84, a283, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s83, a283, vl1), __riscv_vfmul(s84, a282, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((4)*(j1)))*(m1)) + ((2)*(m1)))))), r71, vl1);
            r72 = __riscv_vset(__riscv_vset(rvvx2_8, 0, __riscv_vfsub(__riscv_vfmul(s87, a284, vl1), __riscv_vfmul(s88, a285, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s87, a285, vl1), __riscv_vfmul(s88, a284, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((4)*(j1)))*(m1)) + ((3)*(m1)))))), r72, vl1);
        }
    }
}
