// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft8b_r32_(float *Y, float *X, float *TW1, int64_t *lp1, int64_t *mp1) {
    float a729, a730, a731, a732, a733, a734, a735, a736, 
            a737, a738, a739, a740, a741, a742;
    int64_t a723, a728, j1, l1, m1;
    vfloat32m1x2_t r129, r130, r131, r132, r133, r134, r135, r136, 
            r137, r138, r139, r140, r141, r142, r143, r144, 
            rvvx2_10, rvvx2_11, rvvx2_12, rvvx2_13, rvvx2_14, rvvx2_15, rvvx2_16, rvvx2_9;
    vfloat32m1_t  a724, a725, a726, a727, s215, s216, s217, s218, 
            s219, s220, s221, s222, s223, s224, s225, s226, 
            s227, s228, s229, s230, s231, s232, s233, s234, 
            s235, s236, s237, s238, s239, s240, s241, s242, 
            s243, s244, s245, s246, s247, s248, t615, t616, 
            t617, t618, t619, t620, t621, t622, t623, t624, 
            t625, t626, t627, t628, t629, t630, t631, t632, 
            t633, t634, t635, t636, t637, t638, t639, t640, 
            t641, t642;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for(int j2 = 0; j2 < (l1 - 1); j2++) {
        j1 = (j2 + 1);
        for(int j2 = 0; j2 < l1; j2++) {
            for (size_t k1 = 0; k1 < m1; k1 += vl1) {
                vl1 = __riscv_vsetvl_e32m1(m1 - k1);
                a723 = (k1 + ((j1)*(m1)));
                r129 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*(a723))), vl1);
                s215 = __riscv_vget_f32m1(r129, 0);
                s216 = __riscv_vget_f32m1(r129, 1);
                r130 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a723 + ((l1)*(m1)))))), vl1);
                s217 = __riscv_vget_f32m1(r130, 0);
                s218 = __riscv_vget_f32m1(r130, 1);
                r131 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a723 + ((((2)*(l1)))*(m1)))))), vl1);
                s219 = __riscv_vget_f32m1(r131, 0);
                s220 = __riscv_vget_f32m1(r131, 1);
                r132 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a723 + ((((3)*(l1)))*(m1)))))), vl1);
                s221 = __riscv_vget_f32m1(r132, 0);
                s222 = __riscv_vget_f32m1(r132, 1);
                r133 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a723 + ((((4)*(l1)))*(m1)))))), vl1);
                s223 = __riscv_vget_f32m1(r133, 0);
                s224 = __riscv_vget_f32m1(r133, 1);
                r134 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a723 + ((((5)*(l1)))*(m1)))))), vl1);
                s225 = __riscv_vget_f32m1(r134, 0);
                s226 = __riscv_vget_f32m1(r134, 1);
                r135 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a723 + ((((6)*(l1)))*(m1)))))), vl1);
                s227 = __riscv_vget_f32m1(r135, 0);
                s228 = __riscv_vget_f32m1(r135, 1);
                r136 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a723 + ((((7)*(l1)))*(m1)))))), vl1);
                s229 = __riscv_vget_f32m1(r136, 0);
                s230 = __riscv_vget_f32m1(r136, 1);
                t615 = __riscv_vfadd(s215, s223, vl1);
                t616 = __riscv_vfadd(s216, s224, vl1);
                t617 = __riscv_vfsub(s215, s223, vl1);
                t618 = __riscv_vfsub(s216, s224, vl1);
                t619 = __riscv_vfadd(s219, s227, vl1);
                t620 = __riscv_vfadd(s220, s228, vl1);
                t621 = __riscv_vfsub(s219, s227, vl1);
                t622 = __riscv_vfsub(s220, s228, vl1);
                t623 = __riscv_vfadd(t615, t619, vl1);
                t624 = __riscv_vfadd(t616, t620, vl1);
                t625 = __riscv_vfsub(t615, t619, vl1);
                t626 = __riscv_vfsub(t616, t620, vl1);
                t627 = __riscv_vfadd(t617, t622, vl1);
                t628 = __riscv_vfsub(t618, t621, vl1);
                t629 = __riscv_vfsub(t617, t622, vl1);
                t630 = __riscv_vfadd(t618, t621, vl1);
                t631 = __riscv_vfadd(s217, s225, vl1);
                t632 = __riscv_vfadd(s218, s226, vl1);
                t633 = __riscv_vfsub(s217, s225, vl1);
                t634 = __riscv_vfsub(s218, s226, vl1);
                t635 = __riscv_vfadd(s221, s229, vl1);
                t636 = __riscv_vfadd(s222, s230, vl1);
                t637 = __riscv_vfsub(s221, s229, vl1);
                t638 = __riscv_vfsub(s222, s230, vl1);
                t639 = __riscv_vfadd(t631, t635, vl1);
                t640 = __riscv_vfadd(t632, t636, vl1);
                t641 = __riscv_vfsub(t631, t635, vl1);
                t642 = __riscv_vfsub(t632, t636, vl1);
                a724 = __riscv_vfmul(__riscv_vfadd(t633, t638, vl1), 0.70710678118654757, vl1);
                a725 = __riscv_vfmul(__riscv_vfsub(t634, t637, vl1), 0.70710678118654757, vl1);
                s231 = __riscv_vfadd(a724, a725, vl1);
                s232 = __riscv_vfsub(a725, a724, vl1);
                a726 = __riscv_vfmul(__riscv_vfadd(t634, t637, vl1), 0.70710678118654757, vl1);
                a727 = __riscv_vfmul(__riscv_vfsub(t633, t638, vl1), 0.70710678118654757, vl1);
                s233 = __riscv_vfsub(a726, a727, vl1);
                s234 = __riscv_vfadd(a727, a726, vl1);
                s235 = __riscv_vfsub(t623, t639, vl1);
                s236 = __riscv_vfsub(t624, t640, vl1);
                s237 = __riscv_vfadd(t627, s231, vl1);
                s238 = __riscv_vfadd(t628, s232, vl1);
                s239 = __riscv_vfsub(t627, s231, vl1);
                s240 = __riscv_vfsub(t628, s232, vl1);
                s241 = __riscv_vfadd(t625, t642, vl1);
                s242 = __riscv_vfsub(t626, t641, vl1);
                s243 = __riscv_vfsub(t625, t642, vl1);
                s244 = __riscv_vfadd(t626, t641, vl1);
                s245 = __riscv_vfadd(t629, s233, vl1);
                s246 = __riscv_vfsub(t630, s234, vl1);
                s247 = __riscv_vfsub(t629, s233, vl1);
                s248 = __riscv_vfadd(t630, s234, vl1);
                a728 = ((14)*(j1));
                a729 = TW1[a728];
                a730 = TW1[(a728 + 1)];
                a731 = TW1[(a728 + 2)];
                a732 = TW1[(a728 + 3)];
                a733 = TW1[(a728 + 4)];
                a734 = TW1[(a728 + 5)];
                a735 = TW1[(a728 + 6)];
                a736 = TW1[(a728 + 7)];
                a737 = TW1[(a728 + 8)];
                a738 = TW1[(a728 + 9)];
                a739 = TW1[(a728 + 10)];
                a740 = TW1[(a728 + 11)];
                a741 = TW1[(a728 + 12)];
                a742 = TW1[(a728 + 13)];
                r137 = __riscv_vset(__riscv_vset(rvvx2_9, 0, __riscv_vfadd(t623, t639, vl1)), 1, __riscv_vfadd(t624, t640, vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((8)*(j1)))*(m1)))))), r137, vl1);
                r138 = __riscv_vset(__riscv_vset(rvvx2_10, 0, __riscv_vfsub(__riscv_vfmul(s237, a729, vl1), __riscv_vfmul(s238, a730, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s237, a730, vl1), __riscv_vfmul(s238, a729, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((8)*(j1)))*(m1)) + m1)))), r138, vl1);
                r139 = __riscv_vset(__riscv_vset(rvvx2_11, 0, __riscv_vfsub(__riscv_vfmul(s241, a731, vl1), __riscv_vfmul(s242, a732, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s241, a732, vl1), __riscv_vfmul(s242, a731, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((8)*(j1)))*(m1)) + ((2)*(m1)))))), r139, vl1);
                r140 = __riscv_vset(__riscv_vset(rvvx2_12, 0, __riscv_vfsub(__riscv_vfmul(s245, a733, vl1), __riscv_vfmul(s246, a734, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s245, a734, vl1), __riscv_vfmul(s246, a733, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((8)*(j1)))*(m1)) + ((3)*(m1)))))), r140, vl1);
                r141 = __riscv_vset(__riscv_vset(rvvx2_13, 0, __riscv_vfsub(__riscv_vfmul(s235, a735, vl1), __riscv_vfmul(s236, a736, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s235, a736, vl1), __riscv_vfmul(s236, a735, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((8)*(j1)))*(m1)) + ((4)*(m1)))))), r141, vl1);
                r142 = __riscv_vset(__riscv_vset(rvvx2_14, 0, __riscv_vfsub(__riscv_vfmul(s239, a737, vl1), __riscv_vfmul(s240, a738, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s239, a738, vl1), __riscv_vfmul(s240, a737, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((8)*(j1)))*(m1)) + ((5)*(m1)))))), r142, vl1);
                r143 = __riscv_vset(__riscv_vset(rvvx2_15, 0, __riscv_vfsub(__riscv_vfmul(s243, a739, vl1), __riscv_vfmul(s244, a740, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s243, a740, vl1), __riscv_vfmul(s244, a739, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((8)*(j1)))*(m1)) + ((6)*(m1)))))), r143, vl1);
                r144 = __riscv_vset(__riscv_vset(rvvx2_16, 0, __riscv_vfsub(__riscv_vfmul(s247, a741, vl1), __riscv_vfmul(s248, a742, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s247, a742, vl1), __riscv_vfmul(s248, a741, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((8)*(j1)))*(m1)) + ((7)*(m1)))))), r144, vl1);
            }
        }
    }
}
