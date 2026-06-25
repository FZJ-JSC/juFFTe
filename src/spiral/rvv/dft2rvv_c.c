// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft2c_(double *Y, double *X, int *lp1, int *mp1) {
    int l1, m1;
    vfloat64m1x2_t r33, r34, r35, r36, rvvx2_3, rvvx2_4;
    vfloat64m1_t  s29, s30, s31, s32;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
#pragma GCC unroll 4
    for (size_t k1 = 0; k1 < m1; k1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(m1 - k1);
        r33 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(k1))), vl1);
        s29 = __riscv_vget_f64m1(r33, 0);
        s30 = __riscv_vget_f64m1(r33, 1);
        r34 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((l1)*(m1)))))), vl1);
        s31 = __riscv_vget_f64m1(r34, 0);
        s32 = __riscv_vget_f64m1(r34, 1);
        r35 = __riscv_vset(__riscv_vset(rvvx2_3, 0, __riscv_vfadd(s29, s31, vl1)), 1, __riscv_vfadd(s30, s32, vl1));
        __riscv_vsseg2e64((Y + ((2)*(k1))), r35, vl1);
        r36 = __riscv_vset(__riscv_vset(rvvx2_4, 0, __riscv_vfsub(s29, s31, vl1)), 1, __riscv_vfsub(s30, s32, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + m1)))), r36, vl1);
    }
}
