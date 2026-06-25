// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft8c_(double *Y, double *X, int *lp1, int *mp1) {
    int l1, m1;
    vfloat64m1x2_t r129, r130, r131, r132, r133, r134, r135, r136, 
            r137, r138, r139, r140, r141, r142, r143, r144, 
            rvvx2_10, rvvx2_11, rvvx2_12, rvvx2_13, rvvx2_14, rvvx2_15, rvvx2_16, rvvx2_9;
    vfloat64m1_t  a353, a354, a355, a356, s173, s174, s175, s176, 
            s177, s178, s179, s180, s181, s182, s183, s184, 
            s185, s186, s187, s188, s189, s190, s191, s192, 
            t614, t615, t616, t617, t618, t619, t620, t621, 
            t622, t623, t624, t625, t626, t627, t628, t629, 
            t630, t631, t632, t633, t634, t635, t636, t637, 
            t638, t639, t640, t641;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for (size_t k1 = 0; k1 < m1; k1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(m1 - k1);
        r129 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(k1))), vl1);
        s173 = __riscv_vget_f64m1(r129, 0);
        s174 = __riscv_vget_f64m1(r129, 1);
        r130 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((l1)*(m1)))))), vl1);
        s175 = __riscv_vget_f64m1(r130, 0);
        s176 = __riscv_vget_f64m1(r130, 1);
        r131 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((2)*(l1)))*(m1)))))), vl1);
        s177 = __riscv_vget_f64m1(r131, 0);
        s178 = __riscv_vget_f64m1(r131, 1);
        r132 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((3)*(l1)))*(m1)))))), vl1);
        s179 = __riscv_vget_f64m1(r132, 0);
        s180 = __riscv_vget_f64m1(r132, 1);
        r133 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((4)*(l1)))*(m1)))))), vl1);
        s181 = __riscv_vget_f64m1(r133, 0);
        s182 = __riscv_vget_f64m1(r133, 1);
        r134 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((5)*(l1)))*(m1)))))), vl1);
        s183 = __riscv_vget_f64m1(r134, 0);
        s184 = __riscv_vget_f64m1(r134, 1);
        r135 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((6)*(l1)))*(m1)))))), vl1);
        s185 = __riscv_vget_f64m1(r135, 0);
        s186 = __riscv_vget_f64m1(r135, 1);
        r136 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((7)*(l1)))*(m1)))))), vl1);
        s187 = __riscv_vget_f64m1(r136, 0);
        s188 = __riscv_vget_f64m1(r136, 1);
        t614 = __riscv_vfadd(s173, s181, vl1);
        t615 = __riscv_vfadd(s174, s182, vl1);
        t616 = __riscv_vfsub(s173, s181, vl1);
        t617 = __riscv_vfsub(s174, s182, vl1);
        t618 = __riscv_vfadd(s177, s185, vl1);
        t619 = __riscv_vfadd(s178, s186, vl1);
        t620 = __riscv_vfsub(s177, s185, vl1);
        t621 = __riscv_vfsub(s178, s186, vl1);
        t622 = __riscv_vfadd(t614, t618, vl1);
        t623 = __riscv_vfadd(t615, t619, vl1);
        t624 = __riscv_vfsub(t614, t618, vl1);
        t625 = __riscv_vfsub(t615, t619, vl1);
        t626 = __riscv_vfadd(t616, t621, vl1);
        t627 = __riscv_vfsub(t617, t620, vl1);
        t628 = __riscv_vfsub(t616, t621, vl1);
        t629 = __riscv_vfadd(t617, t620, vl1);
        t630 = __riscv_vfadd(s175, s183, vl1);
        t631 = __riscv_vfadd(s176, s184, vl1);
        t632 = __riscv_vfsub(s175, s183, vl1);
        t633 = __riscv_vfsub(s176, s184, vl1);
        t634 = __riscv_vfadd(s179, s187, vl1);
        t635 = __riscv_vfadd(s180, s188, vl1);
        t636 = __riscv_vfsub(s179, s187, vl1);
        t637 = __riscv_vfsub(s180, s188, vl1);
        t638 = __riscv_vfadd(t630, t634, vl1);
        t639 = __riscv_vfadd(t631, t635, vl1);
        t640 = __riscv_vfsub(t630, t634, vl1);
        t641 = __riscv_vfsub(t631, t635, vl1);
        a353 = __riscv_vfmul(__riscv_vfadd(t632, t637, vl1), 0.70710678118654757, vl1);
        a354 = __riscv_vfmul(__riscv_vfsub(t633, t636, vl1), 0.70710678118654757, vl1);
        s189 = __riscv_vfadd(a353, a354, vl1);
        s190 = __riscv_vfsub(a354, a353, vl1);
        a355 = __riscv_vfmul(__riscv_vfadd(t633, t636, vl1), 0.70710678118654757, vl1);
        a356 = __riscv_vfmul(__riscv_vfsub(t632, t637, vl1), 0.70710678118654757, vl1);
        s191 = __riscv_vfsub(a355, a356, vl1);
        s192 = __riscv_vfadd(a356, a355, vl1);
        r137 = __riscv_vset(__riscv_vset(rvvx2_9, 0, __riscv_vfadd(t622, t638, vl1)), 1, __riscv_vfadd(t623, t639, vl1));
        __riscv_vsseg2e64((Y + ((2)*(k1))), r137, vl1);
        r138 = __riscv_vset(__riscv_vset(rvvx2_10, 0, __riscv_vfadd(t626, s189, vl1)), 1, __riscv_vfadd(t627, s190, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + m1)))), r138, vl1);
        r139 = __riscv_vset(__riscv_vset(rvvx2_11, 0, __riscv_vfadd(t624, t641, vl1)), 1, __riscv_vfsub(t625, t640, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((2)*(m1)))))), r139, vl1);
        r140 = __riscv_vset(__riscv_vset(rvvx2_12, 0, __riscv_vfadd(t628, s191, vl1)), 1, __riscv_vfsub(t629, s192, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((3)*(m1)))))), r140, vl1);
        r141 = __riscv_vset(__riscv_vset(rvvx2_13, 0, __riscv_vfsub(t622, t638, vl1)), 1, __riscv_vfsub(t623, t639, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((4)*(m1)))))), r141, vl1);
        r142 = __riscv_vset(__riscv_vset(rvvx2_14, 0, __riscv_vfsub(t626, s189, vl1)), 1, __riscv_vfsub(t627, s190, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((5)*(m1)))))), r142, vl1);
        r143 = __riscv_vset(__riscv_vset(rvvx2_15, 0, __riscv_vfsub(t624, t641, vl1)), 1, __riscv_vfadd(t625, t640, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((6)*(m1)))))), r143, vl1);
        r144 = __riscv_vset(__riscv_vset(rvvx2_16, 0, __riscv_vfsub(t628, s191, vl1)), 1, __riscv_vfadd(t629, s192, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((7)*(m1)))))), r144, vl1);
    }
}
