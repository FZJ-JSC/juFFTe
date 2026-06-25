// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft2b_r32_(float *Y, float *X, float *TW1, int64_t *lp1, int64_t *mp1) {
    float a114, a115;
    int64_t a112, a113, j1, l1, m1;
    vfloat32m1x2_t r33, r34, r35, r36, rvvx2_3, rvvx2_4;
    vfloat32m1_t  s35, s36, s37, s38, s39, s40;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for(int j2 = 0; j2 < (l1 - 1); j2++) {
        j1 = (j2 + 1);
        for(int j2 = 0; j2 < l1; j2++) {
            for (size_t k1 = 0; k1 < m1; k1 += vl1) {
                vl1 = __riscv_vsetvl_e32m1(m1 - k1);
                a112 = (k1 + ((j1)*(m1)));
                r33 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*(a112))), vl1);
                s35 = __riscv_vget_f32m1(r33, 0);
                s36 = __riscv_vget_f32m1(r33, 1);
                r34 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a112 + ((l1)*(m1)))))), vl1);
                s37 = __riscv_vget_f32m1(r34, 0);
                s38 = __riscv_vget_f32m1(r34, 1);
                s39 = __riscv_vfsub(s35, s37, vl1);
                s40 = __riscv_vfsub(s36, s38, vl1);
                a113 = ((2)*(j1));
                a114 = TW1[a113];
                a115 = TW1[(a113 + 1)];
                r35 = __riscv_vset(__riscv_vset(rvvx2_3, 0, __riscv_vfadd(s35, s37, vl1)), 1, __riscv_vfadd(s36, s38, vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((2)*(j1)))*(m1)))))), r35, vl1);
                r36 = __riscv_vset(__riscv_vset(rvvx2_4, 0, __riscv_vfsub(__riscv_vfmul(s39, a114, vl1), __riscv_vfmul(s40, a115, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s39, a115, vl1), __riscv_vfmul(s40, a114, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((2)*(j1)))*(m1)) + m1)))), r36, vl1);
            }
        }
    }
}
