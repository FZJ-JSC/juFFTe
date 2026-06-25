// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft5a_(double *Y, double *X, double *TW1, int *lp1) {
    int l1;
    double *a379;
    vfloat64m1x2_t r36, r37, r38, r39, r40;
    vfloat64m1_t  a380, a381, a382, a383, a384, a385, a387, a388, 
            s171, s172, s173, s174, s175, s176, s177, s178, 
            s179, s180, s181, s182, s183, s184, s185, s186, 
            s187, s188, s189, s190, s191, s192, s193, s194, 
            s195, s196, s197, s198, s199, s200, s201, s202, 
            s203, s204, s205, s206, s207, s208, t395, t396, 
            t397, t398, t399, t400, t401, t402, t403, t404, 
            t405, t406, t407, t408, t409, t410, t411, t412, 
            t413, t414, t415, t416, t417, t418;
    size_t vl1;
    l1 = *(lp1);
    for (size_t j1 = 0; j1 < l1; j1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(l1 - j1);
        r36 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(j1))), vl1);
        s171 = __riscv_vget_f64m1(r36, 0);
        s172 = __riscv_vget_f64m1(r36, 1);
        r37 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + l1)))), vl1);
        s173 = __riscv_vget_f64m1(r37, 0);
        s174 = __riscv_vget_f64m1(r37, 1);
        r38 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((2)*(l1)))))), vl1);
        s175 = __riscv_vget_f64m1(r38, 0);
        s176 = __riscv_vget_f64m1(r38, 1);
        r39 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((3)*(l1)))))), vl1);
        s177 = __riscv_vget_f64m1(r39, 0);
        s178 = __riscv_vget_f64m1(r39, 1);
        r40 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((4)*(l1)))))), vl1);
        s179 = __riscv_vget_f64m1(r40, 0);
        s180 = __riscv_vget_f64m1(r40, 1);
        t395 = __riscv_vfadd(s173, s179, vl1);
        t396 = __riscv_vfadd(s174, s180, vl1);
        t397 = __riscv_vfsub(s173, s179, vl1);
        t398 = __riscv_vfsub(s174, s180, vl1);
        t399 = __riscv_vfadd(s175, s177, vl1);
        t400 = __riscv_vfadd(s176, s178, vl1);
        t401 = __riscv_vfsub(s175, s177, vl1);
        t402 = __riscv_vfsub(s176, s178, vl1);
        t403 = __riscv_vfadd(t395, t399, vl1);
        t404 = __riscv_vfadd(t396, t400, vl1);
        t405 = __riscv_vfadd(t397, t402, vl1);
        t406 = __riscv_vfsub(t398, t401, vl1);
        t407 = __riscv_vfsub(t397, t402, vl1);
        t408 = __riscv_vfadd(t398, t401, vl1);
        t409 = __riscv_vfnmsac(s171, 0.25, t403, vl1);
        t410 = __riscv_vfnmsac(s172, 0.25, t404, vl1);
        s205 = __riscv_vfmacc(t405, 1.6180339887498947, t406, vl1);
        s181 = __riscv_vfmul(s205, 0.29389262614623657, vl1);
        s206 = __riscv_vfnmsac(t406, 1.6180339887498947, t405, vl1);
        s182 = __riscv_vfmul(s206, 0.29389262614623657, vl1);
        s183 = __riscv_vfmul(__riscv_vfsub(t395, t399, vl1), 0.55901699437494745, vl1);
        s184 = __riscv_vfmul(__riscv_vfsub(t396, t400, vl1), 0.55901699437494745, vl1);
        s207 = __riscv_vfnmsac(t408, 0.6180339887498949, t407, vl1);
        s185 = __riscv_vfmul(s207, 0.47552825814757677, vl1);
        s208 = __riscv_vfmacc(t407, 0.6180339887498949, t408, vl1);
        s186 = __riscv_vfmul(s208, 0.47552825814757677, vl1);
        s187 = __riscv_vfadd(s171, t403, vl1);
        s188 = __riscv_vfadd(s172, t404, vl1);
        t411 = __riscv_vfadd(t409, s183, vl1);
        t412 = __riscv_vfadd(t410, s184, vl1);
        t413 = __riscv_vfsub(t409, s183, vl1);
        t414 = __riscv_vfsub(t410, s184, vl1);
        t415 = __riscv_vfadd(s181, s185, vl1);
        t416 = __riscv_vfsub(s182, s186, vl1);
        t417 = __riscv_vfsub(s181, s185, vl1);
        t418 = __riscv_vfadd(s182, s186, vl1);
        s189 = __riscv_vfadd(t411, t415, vl1);
        s190 = __riscv_vfadd(t412, t416, vl1);
        s191 = __riscv_vfsub(t411, t415, vl1);
        s192 = __riscv_vfsub(t412, t416, vl1);
        s193 = __riscv_vfadd(t413, t418, vl1);
        s194 = __riscv_vfsub(t414, t417, vl1);
        s195 = __riscv_vfsub(t413, t418, vl1);
        s196 = __riscv_vfadd(t414, t417, vl1);
        a379 = (TW1 + ((8)*(j1)));
        a380 = __riscv_vlse64_v_f64m1(a379, sizeof(double) * 8, vl1);
        a381 = __riscv_vlse64_v_f64m1((a379 + 1), sizeof(double) * 8, vl1);
        s197 = __riscv_vfmsac(__riscv_vfmul(a381, s190, vl1), a380, s189, vl1);
        s198 = __riscv_vfmacc(__riscv_vfmul(a380, s190, vl1), a381, s189, vl1);
        a382 = __riscv_vlse64_v_f64m1((a379 + 2), sizeof(double) * 8, vl1);
        a383 = __riscv_vlse64_v_f64m1((a379 + 3), sizeof(double) * 8, vl1);
        s199 = __riscv_vfmsac(__riscv_vfmul(a383, s194, vl1), a382, s193, vl1);
        s200 = __riscv_vfmacc(__riscv_vfmul(a382, s194, vl1), a383, s193, vl1);
        a384 = __riscv_vlse64_v_f64m1((a379 + 4), sizeof(double) * 8, vl1);
        a385 = __riscv_vlse64_v_f64m1((a379 + 5), sizeof(double) * 8, vl1);
        s201 = __riscv_vfmsac(__riscv_vfmul(a385, s196, vl1), a384, s195, vl1);
        s202 = __riscv_vfmacc(__riscv_vfmul(a384, s196, vl1), a385, s195, vl1);
        a387 = __riscv_vlse64_v_f64m1((a379 + 6), sizeof(double) * 8, vl1);
        a388 = __riscv_vlse64_v_f64m1((a379 + 7), sizeof(double) * 8, vl1);
        s203 = __riscv_vfmsac(__riscv_vfmul(a388, s192, vl1), a387, s191, vl1);
        s204 = __riscv_vfmacc(__riscv_vfmul(a387, s192, vl1), a388, s191, vl1);
        __riscv_vsse64((Y + ((10)*(j1))), sizeof(double) * 10, s187, vl1);
        __riscv_vsse64((1 + Y + ((10)*(j1))), sizeof(double) * 10, s188, vl1);
        __riscv_vsse64((2 + Y + ((10)*(j1))), sizeof(double) * 10, s197, vl1);
        __riscv_vsse64((3 + Y + ((10)*(j1))), sizeof(double) * 10, s198, vl1);
        __riscv_vsse64((4 + Y + ((10)*(j1))), sizeof(double) * 10, s199, vl1);
        __riscv_vsse64((5 + Y + ((10)*(j1))), sizeof(double) * 10, s200, vl1);
        __riscv_vsse64((6 + Y + ((10)*(j1))), sizeof(double) * 10, s201, vl1);
        __riscv_vsse64((7 + Y + ((10)*(j1))), sizeof(double) * 10, s202, vl1);
        __riscv_vsse64((8 + Y + ((10)*(j1))), sizeof(double) * 10, s203, vl1);
        __riscv_vsse64((9 + Y + ((10)*(j1))), sizeof(double) * 10, s204, vl1);
    }
}
