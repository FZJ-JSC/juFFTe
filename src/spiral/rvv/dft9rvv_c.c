// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft9c_(double *Y, double *X, int *lp1, int *mp1) {
    int l1, m1;
    vfloat64m1x2_t r145, r146, r147, r148, r149, r150, r151, r152, 
            r153, r154, r155, r156, r157, r158, r159, r160, 
            r161, r162, rvvx2_10, rvvx2_11, rvvx2_12, rvvx2_13, rvvx2_14, rvvx2_15, 
            rvvx2_16, rvvx2_17, rvvx2_18;
    vfloat64m1_t  s347, s348, s349, s350, s351, s352, s353, s354, 
            s355, s356, s357, s358, s359, s360, s361, s362, 
            s363, s364, s365, s366, s367, s368, s369, s370, 
            s371, s372, s373, s374, s375, s376, s377, s378, 
            s379, s380, s381, s382, s383, s384, s385, s387, 
            s388, s389, s390, s391, s392, s393, t680, t681, 
            t682, t683, t684, t685, t686, t687, t688, t689, 
            t690, t691, t692, t693, t694, t695, t696, t697, 
            t698, t699, t700, t701, t702, t703, t704, t705, 
            t706, t707, t708, t709, t710, t711, t712, t713, 
            t714, t715, t716, t717, t718, t719, t720, t721;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for (size_t k1 = 0; k1 < m1; k1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(m1 - k1);
        r145 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(k1))), vl1);
        s347 = __riscv_vget_f64m1(r145, 0);
        s348 = __riscv_vget_f64m1(r145, 1);
        r146 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((l1)*(m1)))))), vl1);
        s349 = __riscv_vget_f64m1(r146, 0);
        s350 = __riscv_vget_f64m1(r146, 1);
        r147 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((2)*(l1)))*(m1)))))), vl1);
        s351 = __riscv_vget_f64m1(r147, 0);
        s352 = __riscv_vget_f64m1(r147, 1);
        r148 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((3)*(l1)))*(m1)))))), vl1);
        s353 = __riscv_vget_f64m1(r148, 0);
        s354 = __riscv_vget_f64m1(r148, 1);
        r149 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((4)*(l1)))*(m1)))))), vl1);
        s355 = __riscv_vget_f64m1(r149, 0);
        s356 = __riscv_vget_f64m1(r149, 1);
        r150 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((5)*(l1)))*(m1)))))), vl1);
        s357 = __riscv_vget_f64m1(r150, 0);
        s358 = __riscv_vget_f64m1(r150, 1);
        r151 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((6)*(l1)))*(m1)))))), vl1);
        s359 = __riscv_vget_f64m1(r151, 0);
        s360 = __riscv_vget_f64m1(r151, 1);
        r152 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((7)*(l1)))*(m1)))))), vl1);
        s361 = __riscv_vget_f64m1(r152, 0);
        s362 = __riscv_vget_f64m1(r152, 1);
        r153 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((8)*(l1)))*(m1)))))), vl1);
        s363 = __riscv_vget_f64m1(r153, 0);
        s364 = __riscv_vget_f64m1(r153, 1);
        t680 = __riscv_vfadd(s353, s359, vl1);
        t681 = __riscv_vfadd(s354, s360, vl1);
        t682 = __riscv_vfadd(s347, t680, vl1);
        t683 = __riscv_vfadd(s348, t681, vl1);
        t684 = __riscv_vfnmsac(s347, 0.5, t680, vl1);
        t685 = __riscv_vfnmsac(s348, 0.5, t681, vl1);
        s365 = __riscv_vfmul(__riscv_vfsub(s354, s360, vl1), 0.8660254037844386, vl1);
        s366 = __riscv_vfmul(__riscv_vfsub(s353, s359, vl1), 0.8660254037844386, vl1);
        t686 = __riscv_vfadd(t684, s365, vl1);
        t687 = __riscv_vfsub(t685, s366, vl1);
        t688 = __riscv_vfsub(t684, s365, vl1);
        t689 = __riscv_vfadd(t685, s366, vl1);
        t690 = __riscv_vfadd(s355, s361, vl1);
        t691 = __riscv_vfadd(s356, s362, vl1);
        t692 = __riscv_vfadd(s349, t690, vl1);
        t693 = __riscv_vfadd(s350, t691, vl1);
        t694 = __riscv_vfnmsac(s349, 0.5, t690, vl1);
        t695 = __riscv_vfnmsac(s350, 0.5, t691, vl1);
        s367 = __riscv_vfmul(__riscv_vfsub(s356, s362, vl1), 0.8660254037844386, vl1);
        s368 = __riscv_vfmul(__riscv_vfsub(s355, s361, vl1), 0.8660254037844386, vl1);
        t696 = __riscv_vfadd(t694, s367, vl1);
        t697 = __riscv_vfsub(t695, s368, vl1);
        t698 = __riscv_vfsub(t694, s367, vl1);
        t699 = __riscv_vfadd(t695, s368, vl1);
        s385 = __riscv_vfmacc(t696, 0.83909963117727981, t697, vl1);
        s369 = __riscv_vfmul(s385, 0.76604444311897812, vl1);
        s387 = __riscv_vfnmsac(t697, 0.83909963117727981, t696, vl1);
        s370 = __riscv_vfmul(s387, 0.76604444311897812, vl1);
        s388 = __riscv_vfmacc(t698, 5.6712818196177102, t699, vl1);
        s371 = __riscv_vfmul(s388, 0.17364817766693033, vl1);
        s389 = __riscv_vfnmsac(t699, 5.6712818196177102, t698, vl1);
        s372 = __riscv_vfmul(s389, 0.17364817766693033, vl1);
        t700 = __riscv_vfadd(s357, s363, vl1);
        t701 = __riscv_vfadd(s358, s364, vl1);
        t702 = __riscv_vfadd(s351, t700, vl1);
        t703 = __riscv_vfadd(s352, t701, vl1);
        t704 = __riscv_vfnmsac(s351, 0.5, t700, vl1);
        t705 = __riscv_vfnmsac(s352, 0.5, t701, vl1);
        s373 = __riscv_vfmul(__riscv_vfsub(s358, s364, vl1), 0.8660254037844386, vl1);
        s374 = __riscv_vfmul(__riscv_vfsub(s357, s363, vl1), 0.8660254037844386, vl1);
        t706 = __riscv_vfadd(t704, s373, vl1);
        t707 = __riscv_vfsub(t705, s374, vl1);
        t708 = __riscv_vfsub(t704, s373, vl1);
        t709 = __riscv_vfadd(t705, s374, vl1);
        s390 = __riscv_vfmacc(t706, 5.6712818196177102, t707, vl1);
        s375 = __riscv_vfmul(s390, 0.17364817766693033, vl1);
        s391 = __riscv_vfnmsac(t707, 5.6712818196177102, t706, vl1);
        s376 = __riscv_vfmul(s391, 0.17364817766693033, vl1);
        s392 = __riscv_vfnmsac(t709, 2.7474774194546225, t708, vl1);
        s377 = __riscv_vfmul(s392, 0.34202014332566871, vl1);
        s393 = __riscv_vfmacc(t708, 2.7474774194546225, t709, vl1);
        s378 = __riscv_vfmul(s393, 0.34202014332566871, vl1);
        t710 = __riscv_vfadd(t692, t702, vl1);
        t711 = __riscv_vfadd(t693, t703, vl1);
        t712 = __riscv_vfnmsac(t682, 0.5, t710, vl1);
        t713 = __riscv_vfnmsac(t683, 0.5, t711, vl1);
        s379 = __riscv_vfmul(__riscv_vfsub(t693, t703, vl1), 0.8660254037844386, vl1);
        s380 = __riscv_vfmul(__riscv_vfsub(t692, t702, vl1), 0.8660254037844386, vl1);
        t714 = __riscv_vfadd(s369, s375, vl1);
        t715 = __riscv_vfadd(s370, s376, vl1);
        t716 = __riscv_vfnmsac(t686, 0.5, t714, vl1);
        t717 = __riscv_vfnmsac(t687, 0.5, t715, vl1);
        s381 = __riscv_vfmul(__riscv_vfsub(s370, s376, vl1), 0.8660254037844386, vl1);
        s382 = __riscv_vfmul(__riscv_vfsub(s369, s375, vl1), 0.8660254037844386, vl1);
        t718 = __riscv_vfadd(s371, s377, vl1);
        t719 = __riscv_vfsub(s372, s378, vl1);
        t720 = __riscv_vfnmsac(t688, 0.5, t718, vl1);
        t721 = __riscv_vfnmsac(t689, 0.5, t719, vl1);
        s383 = __riscv_vfmul(__riscv_vfadd(s372, s378, vl1), 0.8660254037844386, vl1);
        s384 = __riscv_vfmul(__riscv_vfsub(s371, s377, vl1), 0.8660254037844386, vl1);
        r154 = __riscv_vset(__riscv_vset(rvvx2_10, 0, __riscv_vfadd(t682, t710, vl1)), 1, __riscv_vfadd(t683, t711, vl1));
        __riscv_vsseg2e64((Y + ((2)*(k1))), r154, vl1);
        r155 = __riscv_vset(__riscv_vset(rvvx2_11, 0, __riscv_vfadd(t686, t714, vl1)), 1, __riscv_vfadd(t687, t715, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + m1)))), r155, vl1);
        r156 = __riscv_vset(__riscv_vset(rvvx2_12, 0, __riscv_vfadd(t688, t718, vl1)), 1, __riscv_vfadd(t689, t719, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((2)*(m1)))))), r156, vl1);
        r157 = __riscv_vset(__riscv_vset(rvvx2_13, 0, __riscv_vfadd(t712, s379, vl1)), 1, __riscv_vfsub(t713, s380, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((3)*(m1)))))), r157, vl1);
        r158 = __riscv_vset(__riscv_vset(rvvx2_14, 0, __riscv_vfadd(t716, s381, vl1)), 1, __riscv_vfsub(t717, s382, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((4)*(m1)))))), r158, vl1);
        r159 = __riscv_vset(__riscv_vset(rvvx2_15, 0, __riscv_vfadd(t720, s383, vl1)), 1, __riscv_vfsub(t721, s384, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((5)*(m1)))))), r159, vl1);
        r160 = __riscv_vset(__riscv_vset(rvvx2_16, 0, __riscv_vfsub(t712, s379, vl1)), 1, __riscv_vfadd(t713, s380, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((6)*(m1)))))), r160, vl1);
        r161 = __riscv_vset(__riscv_vset(rvvx2_17, 0, __riscv_vfsub(t716, s381, vl1)), 1, __riscv_vfadd(t717, s382, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((7)*(m1)))))), r161, vl1);
        r162 = __riscv_vset(__riscv_vset(rvvx2_18, 0, __riscv_vfsub(t720, s383, vl1)), 1, __riscv_vfadd(t721, s384, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((8)*(m1)))))), r162, vl1);
    }
}
