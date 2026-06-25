// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft3c_r32_(float *Y, float *X, int64_t *lp1, int64_t *mp1) {
    int64_t l1, m1;
    vfloat32m1x2_t r49, r50, r51, r52, r53, r54, rvvx2_4, rvvx2_5, 
            rvvx2_6;
    vfloat32m1_t  s65, s66, s67, s68, s69, s70, s71, s72, 
            t125, t126, t127, t128;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for (size_t k1 = 0; k1 < m1; k1 += vl1) {
        vl1 = __riscv_vsetvl_e32m1(m1 - k1);
        r49 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*(k1))), vl1);
        s65 = __riscv_vget_f32m1(r49, 0);
        s66 = __riscv_vget_f32m1(r49, 1);
        r50 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((k1 + ((l1)*(m1)))))), vl1);
        s67 = __riscv_vget_f32m1(r50, 0);
        s68 = __riscv_vget_f32m1(r50, 1);
        r51 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((k1 + ((((2)*(l1)))*(m1)))))), vl1);
        s69 = __riscv_vget_f32m1(r51, 0);
        s70 = __riscv_vget_f32m1(r51, 1);
        t125 = __riscv_vfadd(s67, s69, vl1);
        t126 = __riscv_vfadd(s68, s70, vl1);
        t127 = __riscv_vfnmsac(s65, 0.5, t125, vl1);
        t128 = __riscv_vfnmsac(s66, 0.5, t126, vl1);
        s71 = __riscv_vfmul(__riscv_vfsub(s68, s70, vl1), 0.8660254037844386, vl1);
        s72 = __riscv_vfmul(__riscv_vfsub(s67, s69, vl1), 0.8660254037844386, vl1);
        r52 = __riscv_vset(__riscv_vset(rvvx2_4, 0, __riscv_vfadd(s65, t125, vl1)), 1, __riscv_vfadd(s66, t126, vl1));
        __riscv_vsseg2e32((Y + ((2)*(k1))), r52, vl1);
        r53 = __riscv_vset(__riscv_vset(rvvx2_5, 0, __riscv_vfadd(t127, s71, vl1)), 1, __riscv_vfsub(t128, s72, vl1));
        __riscv_vsseg2e32((Y + ((2)*((k1 + m1)))), r53, vl1);
        r54 = __riscv_vset(__riscv_vset(rvvx2_6, 0, __riscv_vfsub(t127, s71, vl1)), 1, __riscv_vfadd(t128, s72, vl1));
        __riscv_vsseg2e32((Y + ((2)*((k1 + ((2)*(m1)))))), r54, vl1);
    }
}
