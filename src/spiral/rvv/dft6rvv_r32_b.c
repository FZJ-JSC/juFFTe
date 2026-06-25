// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft6b_r32_(float *Y, float *X, float *TW1, int64_t *lp1, int64_t *mp1) {
    float a575, a576, a577, a578, a579, a580, a581, a582, 
            a583, a584;
    int64_t a573, a574, j1, l1, m1;
    vfloat32m1x2_t r100, r101, r102, r103, r104, r105, r106, r107, 
            r108, r97, r98, r99, rvvx2_10, rvvx2_11, rvvx2_12, rvvx2_7, 
            rvvx2_8, rvvx2_9;
    vfloat32m1_t  s235, s236, s237, s238, s239, s240, s241, s242, 
            s243, s244, s245, s246, s247, s248, s249, s250, 
            s251, s252, s253, s254, s255, s256, s257, s258, 
            s259, s260, s261, s262, s263, s264, s265, s266, 
            s267, s268, t495, t496, t497, t498, t499, t500, 
            t501, t502, t503, t504, t505, t506, t507, t508, 
            t509, t510, t511, t512, t513, t514;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for(int j2 = 0; j2 < (l1 - 1); j2++) {
        j1 = (j2 + 1);
        for(int j2 = 0; j2 < l1; j2++) {
            for (size_t k1 = 0; k1 < m1; k1 += vl1) {
                vl1 = __riscv_vsetvl_e32m1(m1 - k1);
                a573 = (k1 + ((j1)*(m1)));
                r97 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*(a573))), vl1);
                s235 = __riscv_vget_f32m1(r97, 0);
                s236 = __riscv_vget_f32m1(r97, 1);
                r98 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a573 + ((l1)*(m1)))))), vl1);
                s237 = __riscv_vget_f32m1(r98, 0);
                s238 = __riscv_vget_f32m1(r98, 1);
                r99 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a573 + ((((2)*(l1)))*(m1)))))), vl1);
                s239 = __riscv_vget_f32m1(r99, 0);
                s240 = __riscv_vget_f32m1(r99, 1);
                r100 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a573 + ((((3)*(l1)))*(m1)))))), vl1);
                s241 = __riscv_vget_f32m1(r100, 0);
                s242 = __riscv_vget_f32m1(r100, 1);
                r101 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a573 + ((((4)*(l1)))*(m1)))))), vl1);
                s243 = __riscv_vget_f32m1(r101, 0);
                s244 = __riscv_vget_f32m1(r101, 1);
                r102 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a573 + ((((5)*(l1)))*(m1)))))), vl1);
                s245 = __riscv_vget_f32m1(r102, 0);
                s246 = __riscv_vget_f32m1(r102, 1);
                t495 = __riscv_vfadd(s239, s243, vl1);
                t496 = __riscv_vfadd(s240, s244, vl1);
                t497 = __riscv_vfadd(s235, t495, vl1);
                t498 = __riscv_vfadd(s236, t496, vl1);
                t499 = __riscv_vfnmsac(s235, 0.5, t495, vl1);
                t500 = __riscv_vfnmsac(s236, 0.5, t496, vl1);
                s247 = __riscv_vfmul(__riscv_vfsub(s240, s244, vl1), 0.8660254037844386, vl1);
                s248 = __riscv_vfmul(__riscv_vfsub(s239, s243, vl1), 0.8660254037844386, vl1);
                t501 = __riscv_vfadd(t499, s247, vl1);
                t502 = __riscv_vfsub(t500, s248, vl1);
                t503 = __riscv_vfsub(t499, s247, vl1);
                t504 = __riscv_vfadd(t500, s248, vl1);
                t505 = __riscv_vfadd(s241, s245, vl1);
                t506 = __riscv_vfadd(s242, s246, vl1);
                t507 = __riscv_vfadd(s237, t505, vl1);
                t508 = __riscv_vfadd(s238, t506, vl1);
                t509 = __riscv_vfnmsac(s237, 0.5, t505, vl1);
                t510 = __riscv_vfnmsac(s238, 0.5, t506, vl1);
                s249 = __riscv_vfmul(__riscv_vfsub(s242, s246, vl1), 0.8660254037844386, vl1);
                s250 = __riscv_vfmul(__riscv_vfsub(s241, s245, vl1), 0.8660254037844386, vl1);
                t511 = __riscv_vfadd(t509, s249, vl1);
                t512 = __riscv_vfsub(t510, s250, vl1);
                t513 = __riscv_vfsub(t509, s249, vl1);
                t514 = __riscv_vfadd(t510, s250, vl1);
                s265 = __riscv_vfmacc(t511, 1.7320508075688772, t512, vl1);
                s251 = __riscv_vfmul(s265, 0.5, vl1);
                s266 = __riscv_vfnmsac(t512, 1.7320508075688772, t511, vl1);
                s252 = __riscv_vfmul(s266, 0.5, vl1);
                s267 = __riscv_vfnmsac(t514, 0.57735026918962584, t513, vl1);
                s253 = __riscv_vfmul(s267, 0.8660254037844386, vl1);
                s268 = __riscv_vfmacc(t513, 0.57735026918962584, t514, vl1);
                s254 = __riscv_vfmul(s268, 0.8660254037844386, vl1);
                s255 = __riscv_vfsub(t497, t507, vl1);
                s256 = __riscv_vfsub(t498, t508, vl1);
                s257 = __riscv_vfadd(t501, s251, vl1);
                s258 = __riscv_vfadd(t502, s252, vl1);
                s259 = __riscv_vfsub(t501, s251, vl1);
                s260 = __riscv_vfsub(t502, s252, vl1);
                s261 = __riscv_vfadd(t503, s253, vl1);
                s262 = __riscv_vfsub(t504, s254, vl1);
                s263 = __riscv_vfsub(t503, s253, vl1);
                s264 = __riscv_vfadd(t504, s254, vl1);
                a574 = ((10)*(j1));
                a575 = TW1[a574];
                a576 = TW1[(a574 + 1)];
                a577 = TW1[(a574 + 2)];
                a578 = TW1[(a574 + 3)];
                a579 = TW1[(a574 + 4)];
                a580 = TW1[(a574 + 5)];
                a581 = TW1[(a574 + 6)];
                a582 = TW1[(a574 + 7)];
                a583 = TW1[(a574 + 8)];
                a584 = TW1[(a574 + 9)];
                r103 = __riscv_vset(__riscv_vset(rvvx2_7, 0, __riscv_vfadd(t497, t507, vl1)), 1, __riscv_vfadd(t498, t508, vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((6)*(j1)))*(m1)))))), r103, vl1);
                r104 = __riscv_vset(__riscv_vset(rvvx2_8, 0, __riscv_vfsub(__riscv_vfmul(s257, a575, vl1), __riscv_vfmul(s258, a576, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s257, a576, vl1), __riscv_vfmul(s258, a575, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((6)*(j1)))*(m1)) + m1)))), r104, vl1);
                r105 = __riscv_vset(__riscv_vset(rvvx2_9, 0, __riscv_vfsub(__riscv_vfmul(s261, a577, vl1), __riscv_vfmul(s262, a578, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s261, a578, vl1), __riscv_vfmul(s262, a577, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((6)*(j1)))*(m1)) + ((2)*(m1)))))), r105, vl1);
                r106 = __riscv_vset(__riscv_vset(rvvx2_10, 0, __riscv_vfsub(__riscv_vfmul(s255, a579, vl1), __riscv_vfmul(s256, a580, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s255, a580, vl1), __riscv_vfmul(s256, a579, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((6)*(j1)))*(m1)) + ((3)*(m1)))))), r106, vl1);
                r107 = __riscv_vset(__riscv_vset(rvvx2_11, 0, __riscv_vfsub(__riscv_vfmul(s259, a581, vl1), __riscv_vfmul(s260, a582, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s259, a582, vl1), __riscv_vfmul(s260, a581, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((6)*(j1)))*(m1)) + ((4)*(m1)))))), r107, vl1);
                r108 = __riscv_vset(__riscv_vset(rvvx2_12, 0, __riscv_vfsub(__riscv_vfmul(s263, a583, vl1), __riscv_vfmul(s264, a584, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s263, a584, vl1), __riscv_vfmul(s264, a583, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((6)*(j1)))*(m1)) + ((5)*(m1)))))), r108, vl1);
            }
        }
    }
}
