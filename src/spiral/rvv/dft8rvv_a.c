// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft8a_(double *Y, double *X, double *TW1, int *lp1) {
    int l1;
    double *a654;
    vfloat64m1x2_t r57, r58, r59, r60, r61, r62, r63, r64;
    vfloat64m1_t  a650, a651, a652, a653, a655, a656, a657, a658, 
            a659, a660, a661, a662, a663, a664, a665, a666, 
            a667, a668, s231, s232, s233, s234, s235, s236, 
            s237, s238, s239, s240, s241, s242, s243, s244, 
            s245, s246, s247, s248, s249, s250, s251, s252, 
            s253, s254, s255, s256, s257, s258, s259, s260, 
            s261, s262, s263, s264, s265, s266, s267, s268, 
            s269, s270, s271, s272, s273, s274, s275, s276, 
            s277, s278, s279, s280, t615, t616, t617, t618, 
            t619, t620, t621, t622, t623, t624, t625, t626, 
            t627, t628, t629, t630, t631, t632, t633, t634, 
            t635, t636, t637, t638, t639, t640, t641, t642;
    size_t vl1;
    l1 = *(lp1);
    for (size_t j1 = 0; j1 < l1; j1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(l1 - j1);
        r57 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(j1))), vl1);
        s231 = __riscv_vget_f64m1(r57, 0);
        s232 = __riscv_vget_f64m1(r57, 1);
        r58 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + l1)))), vl1);
        s233 = __riscv_vget_f64m1(r58, 0);
        s234 = __riscv_vget_f64m1(r58, 1);
        r59 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((2)*(l1)))))), vl1);
        s235 = __riscv_vget_f64m1(r59, 0);
        s236 = __riscv_vget_f64m1(r59, 1);
        r60 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((3)*(l1)))))), vl1);
        s237 = __riscv_vget_f64m1(r60, 0);
        s238 = __riscv_vget_f64m1(r60, 1);
        r61 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((4)*(l1)))))), vl1);
        s239 = __riscv_vget_f64m1(r61, 0);
        s240 = __riscv_vget_f64m1(r61, 1);
        r62 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((5)*(l1)))))), vl1);
        s241 = __riscv_vget_f64m1(r62, 0);
        s242 = __riscv_vget_f64m1(r62, 1);
        r63 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((6)*(l1)))))), vl1);
        s243 = __riscv_vget_f64m1(r63, 0);
        s244 = __riscv_vget_f64m1(r63, 1);
        r64 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((7)*(l1)))))), vl1);
        s245 = __riscv_vget_f64m1(r64, 0);
        s246 = __riscv_vget_f64m1(r64, 1);
        t615 = __riscv_vfadd(s231, s239, vl1);
        t616 = __riscv_vfadd(s232, s240, vl1);
        t617 = __riscv_vfsub(s231, s239, vl1);
        t618 = __riscv_vfsub(s232, s240, vl1);
        t619 = __riscv_vfadd(s235, s243, vl1);
        t620 = __riscv_vfadd(s236, s244, vl1);
        t621 = __riscv_vfsub(s235, s243, vl1);
        t622 = __riscv_vfsub(s236, s244, vl1);
        t623 = __riscv_vfadd(t615, t619, vl1);
        t624 = __riscv_vfadd(t616, t620, vl1);
        t625 = __riscv_vfsub(t615, t619, vl1);
        t626 = __riscv_vfsub(t616, t620, vl1);
        t627 = __riscv_vfadd(t617, t622, vl1);
        t628 = __riscv_vfsub(t618, t621, vl1);
        t629 = __riscv_vfsub(t617, t622, vl1);
        t630 = __riscv_vfadd(t618, t621, vl1);
        t631 = __riscv_vfadd(s233, s241, vl1);
        t632 = __riscv_vfadd(s234, s242, vl1);
        t633 = __riscv_vfsub(s233, s241, vl1);
        t634 = __riscv_vfsub(s234, s242, vl1);
        t635 = __riscv_vfadd(s237, s245, vl1);
        t636 = __riscv_vfadd(s238, s246, vl1);
        t637 = __riscv_vfsub(s237, s245, vl1);
        t638 = __riscv_vfsub(s238, s246, vl1);
        t639 = __riscv_vfadd(t631, t635, vl1);
        t640 = __riscv_vfadd(t632, t636, vl1);
        t641 = __riscv_vfsub(t631, t635, vl1);
        t642 = __riscv_vfsub(t632, t636, vl1);
        a650 = __riscv_vfmul(__riscv_vfadd(t633, t638, vl1), 0.70710678118654757, vl1);
        a651 = __riscv_vfmul(__riscv_vfsub(t634, t637, vl1), 0.70710678118654757, vl1);
        s247 = __riscv_vfadd(a650, a651, vl1);
        s248 = __riscv_vfsub(a651, a650, vl1);
        a652 = __riscv_vfmul(__riscv_vfadd(t634, t637, vl1), 0.70710678118654757, vl1);
        a653 = __riscv_vfmul(__riscv_vfsub(t633, t638, vl1), 0.70710678118654757, vl1);
        s249 = __riscv_vfsub(a652, a653, vl1);
        s250 = __riscv_vfadd(a653, a652, vl1);
        s251 = __riscv_vfadd(t623, t639, vl1);
        s252 = __riscv_vfadd(t624, t640, vl1);
        s253 = __riscv_vfsub(t623, t639, vl1);
        s254 = __riscv_vfsub(t624, t640, vl1);
        s255 = __riscv_vfadd(t627, s247, vl1);
        s256 = __riscv_vfadd(t628, s248, vl1);
        s257 = __riscv_vfsub(t627, s247, vl1);
        s258 = __riscv_vfsub(t628, s248, vl1);
        s259 = __riscv_vfadd(t625, t642, vl1);
        s260 = __riscv_vfsub(t626, t641, vl1);
        s261 = __riscv_vfsub(t625, t642, vl1);
        s262 = __riscv_vfadd(t626, t641, vl1);
        s263 = __riscv_vfadd(t629, s249, vl1);
        s264 = __riscv_vfsub(t630, s250, vl1);
        s265 = __riscv_vfsub(t629, s249, vl1);
        s266 = __riscv_vfadd(t630, s250, vl1);
        a654 = (TW1 + ((14)*(j1)));
        a655 = __riscv_vlse64_v_f64m1(a654, sizeof(double) * 14, vl1);
        a656 = __riscv_vlse64_v_f64m1((a654 + 1), sizeof(double) * 14, vl1);
        s267 = __riscv_vfmsac(__riscv_vfmul(a656, s256, vl1), a655, s255, vl1);
        s268 = __riscv_vfmacc(__riscv_vfmul(a655, s256, vl1), a656, s255, vl1);
        a657 = __riscv_vlse64_v_f64m1((a654 + 2), sizeof(double) * 14, vl1);
        a658 = __riscv_vlse64_v_f64m1((a654 + 3), sizeof(double) * 14, vl1);
        s269 = __riscv_vfmsac(__riscv_vfmul(a658, s260, vl1), a657, s259, vl1);
        s270 = __riscv_vfmacc(__riscv_vfmul(a657, s260, vl1), a658, s259, vl1);
        a659 = __riscv_vlse64_v_f64m1((a654 + 4), sizeof(double) * 14, vl1);
        a660 = __riscv_vlse64_v_f64m1((a654 + 5), sizeof(double) * 14, vl1);
        s271 = __riscv_vfmsac(__riscv_vfmul(a660, s264, vl1), a659, s263, vl1);
        s272 = __riscv_vfmacc(__riscv_vfmul(a659, s264, vl1), a660, s263, vl1);
        a661 = __riscv_vlse64_v_f64m1((a654 + 6), sizeof(double) * 14, vl1);
        a662 = __riscv_vlse64_v_f64m1((a654 + 7), sizeof(double) * 14, vl1);
        s273 = __riscv_vfmsac(__riscv_vfmul(a662, s254, vl1), a661, s253, vl1);
        s274 = __riscv_vfmacc(__riscv_vfmul(a661, s254, vl1), a662, s253, vl1);
        a663 = __riscv_vlse64_v_f64m1((a654 + 8), sizeof(double) * 14, vl1);
        a664 = __riscv_vlse64_v_f64m1((a654 + 9), sizeof(double) * 14, vl1);
        s275 = __riscv_vfmsac(__riscv_vfmul(a664, s258, vl1), a663, s257, vl1);
        s276 = __riscv_vfmacc(__riscv_vfmul(a663, s258, vl1), a664, s257, vl1);
        a665 = __riscv_vlse64_v_f64m1((a654 + 10), sizeof(double) * 14, vl1);
        a666 = __riscv_vlse64_v_f64m1((a654 + 11), sizeof(double) * 14, vl1);
        s277 = __riscv_vfmsac(__riscv_vfmul(a666, s262, vl1), a665, s261, vl1);
        s278 = __riscv_vfmacc(__riscv_vfmul(a665, s262, vl1), a666, s261, vl1);
        a667 = __riscv_vlse64_v_f64m1((a654 + 12), sizeof(double) * 14, vl1);
        a668 = __riscv_vlse64_v_f64m1((a654 + 13), sizeof(double) * 14, vl1);
        s279 = __riscv_vfmsac(__riscv_vfmul(a668, s266, vl1), a667, s265, vl1);
        s280 = __riscv_vfmacc(__riscv_vfmul(a667, s266, vl1), a668, s265, vl1);
        __riscv_vsse64((Y + ((16)*(j1))), sizeof(double) * 16, s251, vl1);
        __riscv_vsse64((1 + Y + ((16)*(j1))), sizeof(double) * 16, s252, vl1);
        __riscv_vsse64((2 + Y + ((16)*(j1))), sizeof(double) * 16, s267, vl1);
        __riscv_vsse64((3 + Y + ((16)*(j1))), sizeof(double) * 16, s268, vl1);
        __riscv_vsse64((4 + Y + ((16)*(j1))), sizeof(double) * 16, s269, vl1);
        __riscv_vsse64((5 + Y + ((16)*(j1))), sizeof(double) * 16, s270, vl1);
        __riscv_vsse64((6 + Y + ((16)*(j1))), sizeof(double) * 16, s271, vl1);
        __riscv_vsse64((7 + Y + ((16)*(j1))), sizeof(double) * 16, s272, vl1);
        __riscv_vsse64((8 + Y + ((16)*(j1))), sizeof(double) * 16, s273, vl1);
        __riscv_vsse64((9 + Y + ((16)*(j1))), sizeof(double) * 16, s274, vl1);
        __riscv_vsse64((10 + Y + ((16)*(j1))), sizeof(double) * 16, s275, vl1);
        __riscv_vsse64((11 + Y + ((16)*(j1))), sizeof(double) * 16, s276, vl1);
        __riscv_vsse64((12 + Y + ((16)*(j1))), sizeof(double) * 16, s277, vl1);
        __riscv_vsse64((13 + Y + ((16)*(j1))), sizeof(double) * 16, s278, vl1);
        __riscv_vsse64((14 + Y + ((16)*(j1))), sizeof(double) * 16, s279, vl1);
        __riscv_vsse64((15 + Y + ((16)*(j1))), sizeof(double) * 16, s280, vl1);
    }
}
