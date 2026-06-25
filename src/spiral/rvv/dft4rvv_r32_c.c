// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft4c_r32_(float *Y, float *X, int64_t *lp1, int64_t *mp1) {
    int64_t l1, m1;
    vfloat32m1x2_t r65, r66, r67, r68, r69, r70, r71, r72, 
            rvvx2_5, rvvx2_6, rvvx2_7, rvvx2_8;
    vfloat32m1_t  s57, s58, s59, s60, s61, s62, s63, s64, 
            t153, t154, t155, t156, t157, t158, t159, t160;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for (size_t k1 = 0; k1 < m1; k1 += vl1) {
        vl1 = __riscv_vsetvl_e32m1(m1 - k1);
        r65 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*(k1))), vl1);
        s57 = __riscv_vget_f32m1(r65, 0);
        s58 = __riscv_vget_f32m1(r65, 1);
        r66 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((k1 + ((l1)*(m1)))))), vl1);
        s59 = __riscv_vget_f32m1(r66, 0);
        s60 = __riscv_vget_f32m1(r66, 1);
        r67 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((k1 + ((((2)*(l1)))*(m1)))))), vl1);
        s61 = __riscv_vget_f32m1(r67, 0);
        s62 = __riscv_vget_f32m1(r67, 1);
        r68 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((k1 + ((((3)*(l1)))*(m1)))))), vl1);
        s63 = __riscv_vget_f32m1(r68, 0);
        s64 = __riscv_vget_f32m1(r68, 1);
        t153 = __riscv_vfadd(s57, s61, vl1);
        t154 = __riscv_vfadd(s58, s62, vl1);
        t155 = __riscv_vfsub(s57, s61, vl1);
        t156 = __riscv_vfsub(s58, s62, vl1);
        t157 = __riscv_vfadd(s59, s63, vl1);
        t158 = __riscv_vfadd(s60, s64, vl1);
        t159 = __riscv_vfsub(s59, s63, vl1);
        t160 = __riscv_vfsub(s60, s64, vl1);
        r69 = __riscv_vset(__riscv_vset(rvvx2_5, 0, __riscv_vfadd(t153, t157, vl1)), 1, __riscv_vfadd(t154, t158, vl1));
        __riscv_vsseg2e32((Y + ((2)*(k1))), r69, vl1);
        r70 = __riscv_vset(__riscv_vset(rvvx2_6, 0, __riscv_vfadd(t155, t160, vl1)), 1, __riscv_vfsub(t156, t159, vl1));
        __riscv_vsseg2e32((Y + ((2)*((k1 + m1)))), r70, vl1);
        r71 = __riscv_vset(__riscv_vset(rvvx2_7, 0, __riscv_vfsub(t153, t157, vl1)), 1, __riscv_vfsub(t154, t158, vl1));
        __riscv_vsseg2e32((Y + ((2)*((k1 + ((2)*(m1)))))), r71, vl1);
        r72 = __riscv_vset(__riscv_vset(rvvx2_8, 0, __riscv_vfsub(t155, t160, vl1)), 1, __riscv_vfadd(t156, t159, vl1));
        __riscv_vsseg2e32((Y + ((2)*((k1 + ((3)*(m1)))))), r72, vl1);
    }
}
