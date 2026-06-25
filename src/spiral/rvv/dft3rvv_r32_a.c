// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft3a_r32_(float *Y, float *X, float *TW1, int64_t *lp1) {
    int64_t l1;
    float *a183;
    vfloat32m1x2_t r22, r23, r24;
    vfloat32m1_t  a184, a185, a186, a187, s100, s83, s84, s85, 
            s86, s87, s88, s89, s90, s91, s92, s93, 
            s94, s95, s96, s97, s98, s99, t126, t127, 
            t128, t129;
    size_t vl1;
    l1 = *(lp1);
    for (size_t j1 = 0; j1 < l1; j1 += vl1) {
        vl1 = __riscv_vsetvl_e32m1(l1 - j1);
        r22 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*(j1))), vl1);
        s83 = __riscv_vget_f32m1(r22, 0);
        s84 = __riscv_vget_f32m1(r22, 1);
        r23 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + l1)))), vl1);
        s85 = __riscv_vget_f32m1(r23, 0);
        s86 = __riscv_vget_f32m1(r23, 1);
        r24 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((2)*(l1)))))), vl1);
        s87 = __riscv_vget_f32m1(r24, 0);
        s88 = __riscv_vget_f32m1(r24, 1);
        t126 = __riscv_vfadd(s85, s87, vl1);
        t127 = __riscv_vfadd(s86, s88, vl1);
        t128 = __riscv_vfnmsac(s83, 0.5, t126, vl1);
        t129 = __riscv_vfnmsac(s84, 0.5, t127, vl1);
        s89 = __riscv_vfmul(__riscv_vfsub(s86, s88, vl1), 0.8660254037844386, vl1);
        s90 = __riscv_vfmul(__riscv_vfsub(s85, s87, vl1), 0.8660254037844386, vl1);
        s91 = __riscv_vfadd(s83, t126, vl1);
        s92 = __riscv_vfadd(s84, t127, vl1);
        s93 = __riscv_vfadd(t128, s89, vl1);
        s94 = __riscv_vfsub(t129, s90, vl1);
        s95 = __riscv_vfsub(t128, s89, vl1);
        s96 = __riscv_vfadd(t129, s90, vl1);
        a183 = (TW1 + ((4)*(j1)));
        a184 = __riscv_vlse32_v_f32m1(a183, sizeof(double) * 4, vl1);
        a185 = __riscv_vlse32_v_f32m1((a183 + 1), sizeof(double) * 4, vl1);
        s97 = __riscv_vfmsac(__riscv_vfmul(a185, s94, vl1), a184, s93, vl1);
        s98 = __riscv_vfmacc(__riscv_vfmul(a184, s94, vl1), a185, s93, vl1);
        a186 = __riscv_vlse32_v_f32m1((a183 + 2), sizeof(double) * 4, vl1);
        a187 = __riscv_vlse32_v_f32m1((a183 + 3), sizeof(double) * 4, vl1);
        s99 = __riscv_vfmsac(__riscv_vfmul(a187, s96, vl1), a186, s95, vl1);
        s100 = __riscv_vfmacc(__riscv_vfmul(a186, s96, vl1), a187, s95, vl1);
        __riscv_vsse32((Y + ((6)*(j1))), sizeof(double) * 6, s91, vl1);
        __riscv_vsse32((1 + Y + ((6)*(j1))), sizeof(double) * 6, s92, vl1);
        __riscv_vsse32((2 + Y + ((6)*(j1))), sizeof(double) * 6, s97, vl1);
        __riscv_vsse32((3 + Y + ((6)*(j1))), sizeof(double) * 6, s98, vl1);
        __riscv_vsse32((4 + Y + ((6)*(j1))), sizeof(double) * 6, s99, vl1);
        __riscv_vsse32((5 + Y + ((6)*(j1))), sizeof(double) * 6, s100, vl1);
    }
}
