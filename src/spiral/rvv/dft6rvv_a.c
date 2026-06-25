// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft6a_(double *Y, double *X, double *TW1, int *lp1) {
    int l1;
    double *a518;
    vfloat64m1x2_t r43, r44, r45, r46, r47, r48;
    vfloat64m1_t  a519, a520, a521, a522, a523, a524, a525, a526, 
            a527, a528, s247, s248, s249, s250, s251, s252, 
            s253, s254, s255, s256, s257, s258, s259, s260, 
            s261, s262, s263, s264, s265, s266, s267, s268, 
            s269, s270, s271, s272, s273, s274, s275, s276, 
            s277, s278, s279, s280, s281, s282, s283, s284, 
            s285, s286, s287, s288, s289, s290, s291, s292, 
            t495, t496, t497, t498, t499, t500, t501, t502, 
            t503, t504, t505, t506, t507, t508, t509, t510, 
            t511, t512, t513, t514;
    size_t vl1;
    l1 = *(lp1);
    for (size_t j1 = 0; j1 < l1; j1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(l1 - j1);
        r43 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(j1))), vl1);
        s247 = __riscv_vget_f64m1(r43, 0);
        s248 = __riscv_vget_f64m1(r43, 1);
        r44 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + l1)))), vl1);
        s249 = __riscv_vget_f64m1(r44, 0);
        s250 = __riscv_vget_f64m1(r44, 1);
        r45 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((2)*(l1)))))), vl1);
        s251 = __riscv_vget_f64m1(r45, 0);
        s252 = __riscv_vget_f64m1(r45, 1);
        r46 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((3)*(l1)))))), vl1);
        s253 = __riscv_vget_f64m1(r46, 0);
        s254 = __riscv_vget_f64m1(r46, 1);
        r47 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((4)*(l1)))))), vl1);
        s255 = __riscv_vget_f64m1(r47, 0);
        s256 = __riscv_vget_f64m1(r47, 1);
        r48 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((5)*(l1)))))), vl1);
        s257 = __riscv_vget_f64m1(r48, 0);
        s258 = __riscv_vget_f64m1(r48, 1);
        t495 = __riscv_vfadd(s251, s255, vl1);
        t496 = __riscv_vfadd(s252, s256, vl1);
        t497 = __riscv_vfadd(s247, t495, vl1);
        t498 = __riscv_vfadd(s248, t496, vl1);
        t499 = __riscv_vfnmsac(s247, 0.5, t495, vl1);
        t500 = __riscv_vfnmsac(s248, 0.5, t496, vl1);
        s259 = __riscv_vfmul(__riscv_vfsub(s252, s256, vl1), 0.8660254037844386, vl1);
        s260 = __riscv_vfmul(__riscv_vfsub(s251, s255, vl1), 0.8660254037844386, vl1);
        t501 = __riscv_vfadd(t499, s259, vl1);
        t502 = __riscv_vfsub(t500, s260, vl1);
        t503 = __riscv_vfsub(t499, s259, vl1);
        t504 = __riscv_vfadd(t500, s260, vl1);
        t505 = __riscv_vfadd(s253, s257, vl1);
        t506 = __riscv_vfadd(s254, s258, vl1);
        t507 = __riscv_vfadd(s249, t505, vl1);
        t508 = __riscv_vfadd(s250, t506, vl1);
        t509 = __riscv_vfnmsac(s249, 0.5, t505, vl1);
        t510 = __riscv_vfnmsac(s250, 0.5, t506, vl1);
        s261 = __riscv_vfmul(__riscv_vfsub(s254, s258, vl1), 0.8660254037844386, vl1);
        s262 = __riscv_vfmul(__riscv_vfsub(s253, s257, vl1), 0.8660254037844386, vl1);
        t511 = __riscv_vfadd(t509, s261, vl1);
        t512 = __riscv_vfsub(t510, s262, vl1);
        t513 = __riscv_vfsub(t509, s261, vl1);
        t514 = __riscv_vfadd(t510, s262, vl1);
        s289 = __riscv_vfmacc(t511, 1.7320508075688772, t512, vl1);
        s263 = __riscv_vfmul(s289, 0.5, vl1);
        s290 = __riscv_vfnmsac(t512, 1.7320508075688772, t511, vl1);
        s264 = __riscv_vfmul(s290, 0.5, vl1);
        s291 = __riscv_vfnmsac(t514, 0.57735026918962584, t513, vl1);
        s265 = __riscv_vfmul(s291, 0.8660254037844386, vl1);
        s292 = __riscv_vfmacc(t513, 0.57735026918962584, t514, vl1);
        s266 = __riscv_vfmul(s292, 0.8660254037844386, vl1);
        s267 = __riscv_vfadd(t497, t507, vl1);
        s268 = __riscv_vfadd(t498, t508, vl1);
        s269 = __riscv_vfsub(t497, t507, vl1);
        s270 = __riscv_vfsub(t498, t508, vl1);
        s271 = __riscv_vfadd(t501, s263, vl1);
        s272 = __riscv_vfadd(t502, s264, vl1);
        s273 = __riscv_vfsub(t501, s263, vl1);
        s274 = __riscv_vfsub(t502, s264, vl1);
        s275 = __riscv_vfadd(t503, s265, vl1);
        s276 = __riscv_vfsub(t504, s266, vl1);
        s277 = __riscv_vfsub(t503, s265, vl1);
        s278 = __riscv_vfadd(t504, s266, vl1);
        a518 = (TW1 + ((10)*(j1)));
        a519 = __riscv_vlse64_v_f64m1(a518, sizeof(double) * 10, vl1);
        a520 = __riscv_vlse64_v_f64m1((a518 + 1), sizeof(double) * 10, vl1);
        s279 = __riscv_vfmsac(__riscv_vfmul(a520, s272, vl1), a519, s271, vl1);
        s280 = __riscv_vfmacc(__riscv_vfmul(a519, s272, vl1), a520, s271, vl1);
        a521 = __riscv_vlse64_v_f64m1((a518 + 2), sizeof(double) * 10, vl1);
        a522 = __riscv_vlse64_v_f64m1((a518 + 3), sizeof(double) * 10, vl1);
        s281 = __riscv_vfmsac(__riscv_vfmul(a522, s276, vl1), a521, s275, vl1);
        s282 = __riscv_vfmacc(__riscv_vfmul(a521, s276, vl1), a522, s275, vl1);
        a523 = __riscv_vlse64_v_f64m1((a518 + 4), sizeof(double) * 10, vl1);
        a524 = __riscv_vlse64_v_f64m1((a518 + 5), sizeof(double) * 10, vl1);
        s283 = __riscv_vfmsac(__riscv_vfmul(a524, s270, vl1), a523, s269, vl1);
        s284 = __riscv_vfmacc(__riscv_vfmul(a523, s270, vl1), a524, s269, vl1);
        a525 = __riscv_vlse64_v_f64m1((a518 + 6), sizeof(double) * 10, vl1);
        a526 = __riscv_vlse64_v_f64m1((a518 + 7), sizeof(double) * 10, vl1);
        s285 = __riscv_vfmsac(__riscv_vfmul(a526, s274, vl1), a525, s273, vl1);
        s286 = __riscv_vfmacc(__riscv_vfmul(a525, s274, vl1), a526, s273, vl1);
        a527 = __riscv_vlse64_v_f64m1((a518 + 8), sizeof(double) * 10, vl1);
        a528 = __riscv_vlse64_v_f64m1((a518 + 9), sizeof(double) * 10, vl1);
        s287 = __riscv_vfmsac(__riscv_vfmul(a528, s278, vl1), a527, s277, vl1);
        s288 = __riscv_vfmacc(__riscv_vfmul(a527, s278, vl1), a528, s277, vl1);
        __riscv_vsse64((Y + ((12)*(j1))), sizeof(double) * 12, s267, vl1);
        __riscv_vsse64((1 + Y + ((12)*(j1))), sizeof(double) * 12, s268, vl1);
        __riscv_vsse64((2 + Y + ((12)*(j1))), sizeof(double) * 12, s279, vl1);
        __riscv_vsse64((3 + Y + ((12)*(j1))), sizeof(double) * 12, s280, vl1);
        __riscv_vsse64((4 + Y + ((12)*(j1))), sizeof(double) * 12, s281, vl1);
        __riscv_vsse64((5 + Y + ((12)*(j1))), sizeof(double) * 12, s282, vl1);
        __riscv_vsse64((6 + Y + ((12)*(j1))), sizeof(double) * 12, s283, vl1);
        __riscv_vsse64((7 + Y + ((12)*(j1))), sizeof(double) * 12, s284, vl1);
        __riscv_vsse64((8 + Y + ((12)*(j1))), sizeof(double) * 12, s285, vl1);
        __riscv_vsse64((9 + Y + ((12)*(j1))), sizeof(double) * 12, s286, vl1);
        __riscv_vsse64((10 + Y + ((12)*(j1))), sizeof(double) * 12, s287, vl1);
        __riscv_vsse64((11 + Y + ((12)*(j1))), sizeof(double) * 12, s288, vl1);
    }
}
