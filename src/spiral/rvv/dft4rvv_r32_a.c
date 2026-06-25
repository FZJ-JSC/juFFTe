// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft4a_r32_(float *Y, float *X, float *TW1, int64_t *lp1) {
    int64_t l1;
    float *a241;
    vfloat32m1x2_t r29, r30, r31, r32;
    vfloat32m1_t  a242, a243, a244, a245, a246, a247, s100, s101, 
            s102, s103, s104, s83, s84, s85, s86, s87, 
            s88, s89, s90, s91, s92, s93, s94, s95, 
            s96, s97, s98, s99, t154, t155, t156, t157, 
            t158, t159, t160, t161;
    size_t vl1;
    l1 = *(lp1);
    for (size_t j1 = 0; j1 < l1; j1 += vl1) {
        vl1 = __riscv_vsetvl_e32m1(l1 - j1);
        r29 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*(j1))), vl1);
        s83 = __riscv_vget_f32m1(r29, 0);
        s84 = __riscv_vget_f32m1(r29, 1);
        r30 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + l1)))), vl1);
        s85 = __riscv_vget_f32m1(r30, 0);
        s86 = __riscv_vget_f32m1(r30, 1);
        r31 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((2)*(l1)))))), vl1);
        s87 = __riscv_vget_f32m1(r31, 0);
        s88 = __riscv_vget_f32m1(r31, 1);
        r32 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((3)*(l1)))))), vl1);
        s89 = __riscv_vget_f32m1(r32, 0);
        s90 = __riscv_vget_f32m1(r32, 1);
        t154 = __riscv_vfadd(s83, s87, vl1);
        t155 = __riscv_vfadd(s84, s88, vl1);
        t156 = __riscv_vfsub(s83, s87, vl1);
        t157 = __riscv_vfsub(s84, s88, vl1);
        t158 = __riscv_vfadd(s85, s89, vl1);
        t159 = __riscv_vfadd(s86, s90, vl1);
        t160 = __riscv_vfsub(s85, s89, vl1);
        t161 = __riscv_vfsub(s86, s90, vl1);
        s91 = __riscv_vfadd(t154, t158, vl1);
        s92 = __riscv_vfadd(t155, t159, vl1);
        s93 = __riscv_vfsub(t154, t158, vl1);
        s94 = __riscv_vfsub(t155, t159, vl1);
        s95 = __riscv_vfadd(t156, t161, vl1);
        s96 = __riscv_vfsub(t157, t160, vl1);
        s97 = __riscv_vfsub(t156, t161, vl1);
        s98 = __riscv_vfadd(t157, t160, vl1);
        a241 = (TW1 + ((6)*(j1)));
        a242 = __riscv_vlse32_v_f32m1(a241, sizeof(double) * 6, vl1);
        a243 = __riscv_vlse32_v_f32m1((a241 + 1), sizeof(double) * 6, vl1);
        s99 = __riscv_vfmsac(__riscv_vfmul(a243, s96, vl1), a242, s95, vl1);
        s100 = __riscv_vfmacc(__riscv_vfmul(a242, s96, vl1), a243, s95, vl1);
        a244 = __riscv_vlse32_v_f32m1((a241 + 2), sizeof(double) * 6, vl1);
        a245 = __riscv_vlse32_v_f32m1((a241 + 3), sizeof(double) * 6, vl1);
        s101 = __riscv_vfmsac(__riscv_vfmul(a245, s94, vl1), a244, s93, vl1);
        s102 = __riscv_vfmacc(__riscv_vfmul(a244, s94, vl1), a245, s93, vl1);
        a246 = __riscv_vlse32_v_f32m1((a241 + 4), sizeof(double) * 6, vl1);
        a247 = __riscv_vlse32_v_f32m1((a241 + 5), sizeof(double) * 6, vl1);
        s103 = __riscv_vfmsac(__riscv_vfmul(a247, s98, vl1), a246, s97, vl1);
        s104 = __riscv_vfmacc(__riscv_vfmul(a246, s98, vl1), a247, s97, vl1);
        __riscv_vsse32((Y + ((8)*(j1))), sizeof(double) * 8, s91, vl1);
        __riscv_vsse32((1 + Y + ((8)*(j1))), sizeof(double) * 8, s92, vl1);
        __riscv_vsse32((2 + Y + ((8)*(j1))), sizeof(double) * 8, s99, vl1);
        __riscv_vsse32((3 + Y + ((8)*(j1))), sizeof(double) * 8, s100, vl1);
        __riscv_vsse32((4 + Y + ((8)*(j1))), sizeof(double) * 8, s101, vl1);
        __riscv_vsse32((5 + Y + ((8)*(j1))), sizeof(double) * 8, s102, vl1);
        __riscv_vsse32((6 + Y + ((8)*(j1))), sizeof(double) * 8, s103, vl1);
        __riscv_vsse32((7 + Y + ((8)*(j1))), sizeof(double) * 8, s104, vl1);
    }
}
