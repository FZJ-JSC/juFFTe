// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft5b_r32_(float *Y, float *X, float *TW1, int64_t *lp1, int64_t *mp1) {
    float a428, a429, a430, a431, a432, a433, a434, a435;
    int64_t a426, a427, j1, l1, m1;
    vfloat32m1x2_t r81, r82, r83, r84, r85, r86, r87, r88, 
            r89, r90, rvvx2_10, rvvx2_6, rvvx2_7, rvvx2_8, rvvx2_9;
    vfloat32m1_t  s161, s162, s163, s164, s165, s166, s167, s168, 
            s169, s170, s171, s172, s173, s174, s175, s176, 
            s177, s178, s179, s180, s181, s182, s183, s184, 
            s185, s186, s187, s188, t395, t396, t397, t398, 
            t399, t400, t401, t402, t403, t404, t405, t406, 
            t407, t408, t409, t410, t411, t412, t413, t414, 
            t415, t416, t417, t418;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for(int j2 = 0; j2 < (l1 - 1); j2++) {
        j1 = (j2 + 1);
        for(int j2 = 0; j2 < l1; j2++) {
            for (size_t k1 = 0; k1 < m1; k1 += vl1) {
                vl1 = __riscv_vsetvl_e32m1(m1 - k1);
                a426 = (k1 + ((j1)*(m1)));
                r81 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*(a426))), vl1);
                s161 = __riscv_vget_f32m1(r81, 0);
                s162 = __riscv_vget_f32m1(r81, 1);
                r82 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a426 + ((l1)*(m1)))))), vl1);
                s163 = __riscv_vget_f32m1(r82, 0);
                s164 = __riscv_vget_f32m1(r82, 1);
                r83 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a426 + ((((2)*(l1)))*(m1)))))), vl1);
                s165 = __riscv_vget_f32m1(r83, 0);
                s166 = __riscv_vget_f32m1(r83, 1);
                r84 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a426 + ((((3)*(l1)))*(m1)))))), vl1);
                s167 = __riscv_vget_f32m1(r84, 0);
                s168 = __riscv_vget_f32m1(r84, 1);
                r85 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a426 + ((((4)*(l1)))*(m1)))))), vl1);
                s169 = __riscv_vget_f32m1(r85, 0);
                s170 = __riscv_vget_f32m1(r85, 1);
                t395 = __riscv_vfadd(s163, s169, vl1);
                t396 = __riscv_vfadd(s164, s170, vl1);
                t397 = __riscv_vfsub(s163, s169, vl1);
                t398 = __riscv_vfsub(s164, s170, vl1);
                t399 = __riscv_vfadd(s165, s167, vl1);
                t400 = __riscv_vfadd(s166, s168, vl1);
                t401 = __riscv_vfsub(s165, s167, vl1);
                t402 = __riscv_vfsub(s166, s168, vl1);
                t403 = __riscv_vfadd(t395, t399, vl1);
                t404 = __riscv_vfadd(t396, t400, vl1);
                t405 = __riscv_vfadd(t397, t402, vl1);
                t406 = __riscv_vfsub(t398, t401, vl1);
                t407 = __riscv_vfsub(t397, t402, vl1);
                t408 = __riscv_vfadd(t398, t401, vl1);
                t409 = __riscv_vfnmsac(s161, 0.25, t403, vl1);
                t410 = __riscv_vfnmsac(s162, 0.25, t404, vl1);
                s185 = __riscv_vfmacc(t405, 1.6180339887498947, t406, vl1);
                s171 = __riscv_vfmul(s185, 0.29389262614623657, vl1);
                s186 = __riscv_vfnmsac(t406, 1.6180339887498947, t405, vl1);
                s172 = __riscv_vfmul(s186, 0.29389262614623657, vl1);
                s173 = __riscv_vfmul(__riscv_vfsub(t395, t399, vl1), 0.55901699437494745, vl1);
                s174 = __riscv_vfmul(__riscv_vfsub(t396, t400, vl1), 0.55901699437494745, vl1);
                s187 = __riscv_vfnmsac(t408, 0.6180339887498949, t407, vl1);
                s175 = __riscv_vfmul(s187, 0.47552825814757677, vl1);
                s188 = __riscv_vfmacc(t407, 0.6180339887498949, t408, vl1);
                s176 = __riscv_vfmul(s188, 0.47552825814757677, vl1);
                t411 = __riscv_vfadd(t409, s173, vl1);
                t412 = __riscv_vfadd(t410, s174, vl1);
                t413 = __riscv_vfsub(t409, s173, vl1);
                t414 = __riscv_vfsub(t410, s174, vl1);
                t415 = __riscv_vfadd(s171, s175, vl1);
                t416 = __riscv_vfsub(s172, s176, vl1);
                t417 = __riscv_vfsub(s171, s175, vl1);
                t418 = __riscv_vfadd(s172, s176, vl1);
                s177 = __riscv_vfadd(t411, t415, vl1);
                s178 = __riscv_vfadd(t412, t416, vl1);
                s179 = __riscv_vfsub(t411, t415, vl1);
                s180 = __riscv_vfsub(t412, t416, vl1);
                s181 = __riscv_vfadd(t413, t418, vl1);
                s182 = __riscv_vfsub(t414, t417, vl1);
                s183 = __riscv_vfsub(t413, t418, vl1);
                s184 = __riscv_vfadd(t414, t417, vl1);
                a427 = ((8)*(j1));
                a428 = TW1[a427];
                a429 = TW1[(a427 + 1)];
                a430 = TW1[(a427 + 2)];
                a431 = TW1[(a427 + 3)];
                a432 = TW1[(a427 + 4)];
                a433 = TW1[(a427 + 5)];
                a434 = TW1[(a427 + 6)];
                a435 = TW1[(a427 + 7)];
                r86 = __riscv_vset(__riscv_vset(rvvx2_6, 0, __riscv_vfadd(s161, t403, vl1)), 1, __riscv_vfadd(s162, t404, vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((5)*(j1)))*(m1)))))), r86, vl1);
                r87 = __riscv_vset(__riscv_vset(rvvx2_7, 0, __riscv_vfsub(__riscv_vfmul(s177, a428, vl1), __riscv_vfmul(s178, a429, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s177, a429, vl1), __riscv_vfmul(s178, a428, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((5)*(j1)))*(m1)) + m1)))), r87, vl1);
                r88 = __riscv_vset(__riscv_vset(rvvx2_8, 0, __riscv_vfsub(__riscv_vfmul(s181, a430, vl1), __riscv_vfmul(s182, a431, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s181, a431, vl1), __riscv_vfmul(s182, a430, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((5)*(j1)))*(m1)) + ((2)*(m1)))))), r88, vl1);
                r89 = __riscv_vset(__riscv_vset(rvvx2_9, 0, __riscv_vfsub(__riscv_vfmul(s183, a432, vl1), __riscv_vfmul(s184, a433, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s183, a433, vl1), __riscv_vfmul(s184, a432, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((5)*(j1)))*(m1)) + ((3)*(m1)))))), r89, vl1);
                r90 = __riscv_vset(__riscv_vset(rvvx2_10, 0, __riscv_vfsub(__riscv_vfmul(s179, a434, vl1), __riscv_vfmul(s180, a435, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s179, a435, vl1), __riscv_vfmul(s180, a434, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((5)*(j1)))*(m1)) + ((4)*(m1)))))), r90, vl1);
            }
        }
    }
}
