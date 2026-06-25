// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft2a_r32_(float *Y, float *X, float *TW1, int64_t *lp1) {
    int64_t a93, l1;
    float *a94;
    vfloat32m1x2_t r15, r16;
    vfloat32m1_t  a95, a96, s39, s40, s41, s42, s43, s44, 
            s45, s46, s47, s48;
    size_t vl1;
    l1 = *(lp1);
    for (size_t j1 = 0; j1 < l1; j1 += vl1) {
        vl1 = __riscv_vsetvl_e32m1(l1 - j1);
        a93 = ((2)*(j1));
        r15 = __riscv_vlseg2e32_v_f32m1x2((X + a93), vl1);
        s39 = __riscv_vget_f32m1(r15, 0);
        s40 = __riscv_vget_f32m1(r15, 1);
        r16 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + l1)))), vl1);
        s41 = __riscv_vget_f32m1(r16, 0);
        s42 = __riscv_vget_f32m1(r16, 1);
        s43 = __riscv_vfadd(s39, s41, vl1);
        s44 = __riscv_vfadd(s40, s42, vl1);
        s45 = __riscv_vfsub(s39, s41, vl1);
        s46 = __riscv_vfsub(s40, s42, vl1);
        a94 = (TW1 + a93);
        a95 = __riscv_vlse32_v_f32m1(a94, sizeof(double) * 2, vl1);
        a96 = __riscv_vlse32_v_f32m1((a94 + 1), sizeof(double) * 2, vl1);
        s47 = __riscv_vfmsac(__riscv_vfmul(a96, s46, vl1), a95, s45, vl1);
        s48 = __riscv_vfmacc(__riscv_vfmul(a95, s46, vl1), a96, s45, vl1);
        __riscv_vsse32((Y + ((4)*(j1))), sizeof(double) * 4, s43, vl1);
        __riscv_vsse32((1 + Y + ((4)*(j1))), sizeof(double) * 4, s44, vl1);
        __riscv_vsse32((2 + Y + ((4)*(j1))), sizeof(double) * 4, s47, vl1);
        __riscv_vsse32((3 + Y + ((4)*(j1))), sizeof(double) * 4, s48, vl1);
    }
}
