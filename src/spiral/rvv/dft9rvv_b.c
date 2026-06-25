// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft9b_(double *Y, double *X, double *TW1, int *lp1, int *mp1) {
    double a888, a889, a890, a891, a892, a893, a894, a895, 
            a896, a897, a898, a899, a900, a901, a902, a903;
    int a886, a887, j1, l1, m1;
    vfloat64m1x2_t r145, r146, r147, r148, r149, r150, r151, r152, 
            r153, r154, r155, r156, r157, r158, r159, r160, 
            r161, r162, rvvx2_10, rvvx2_11, rvvx2_12, rvvx2_13, rvvx2_14, rvvx2_15, 
            rvvx2_16, rvvx2_17, rvvx2_18;
    vfloat64m1_t  s396, s397, s398, s399, s400, s401, s402, s403, 
            s404, s405, s406, s407, s408, s409, s410, s411, 
            s412, s413, s414, s415, s416, s417, s418, s419, 
            s420, s421, s422, s423, s424, s425, s426, s427, 
            s428, s429, s430, s431, s432, s433, s434, s435, 
            s436, s437, s438, s439, s440, s441, s442, s443, 
            s444, s445, s446, s447, s448, s449, s450, s451, 
            s452, s453, s454, s455, s456, s457, t681, t682, 
            t683, t684, t685, t686, t687, t688, t689, t690, 
            t691, t692, t693, t694, t695, t696, t697, t698, 
            t699, t700, t701, t702, t703, t704, t705, t706, 
            t707, t708, t709, t710, t711, t712, t713, t714, 
            t715, t716, t717, t718, t719, t720, t721, t722;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for(int j1 = 1; j1 < l1; j1++) {
        for (size_t k1 = 0; k1 < m1; k1 += vl1) {
            vl1 = __riscv_vsetvl_e64m1(m1 - k1);
            a886 = (k1 + ((j1)*(m1)));
            r145 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(a886))), vl1);
            s396 = __riscv_vget_f64m1(r145, 0);
            s397 = __riscv_vget_f64m1(r145, 1);
            r146 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a886 + ((l1)*(m1)))))), vl1);
            s398 = __riscv_vget_f64m1(r146, 0);
            s399 = __riscv_vget_f64m1(r146, 1);
            r147 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a886 + ((((2)*(l1)))*(m1)))))), vl1);
            s400 = __riscv_vget_f64m1(r147, 0);
            s401 = __riscv_vget_f64m1(r147, 1);
            r148 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a886 + ((((3)*(l1)))*(m1)))))), vl1);
            s402 = __riscv_vget_f64m1(r148, 0);
            s403 = __riscv_vget_f64m1(r148, 1);
            r149 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a886 + ((((4)*(l1)))*(m1)))))), vl1);
            s404 = __riscv_vget_f64m1(r149, 0);
            s405 = __riscv_vget_f64m1(r149, 1);
            r150 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a886 + ((((5)*(l1)))*(m1)))))), vl1);
            s406 = __riscv_vget_f64m1(r150, 0);
            s407 = __riscv_vget_f64m1(r150, 1);
            r151 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a886 + ((((6)*(l1)))*(m1)))))), vl1);
            s408 = __riscv_vget_f64m1(r151, 0);
            s409 = __riscv_vget_f64m1(r151, 1);
            r152 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a886 + ((((7)*(l1)))*(m1)))))), vl1);
            s410 = __riscv_vget_f64m1(r152, 0);
            s411 = __riscv_vget_f64m1(r152, 1);
            r153 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a886 + ((((8)*(l1)))*(m1)))))), vl1);
            s412 = __riscv_vget_f64m1(r153, 0);
            s413 = __riscv_vget_f64m1(r153, 1);
            t681 = __riscv_vfadd(s402, s408, vl1);
            t682 = __riscv_vfadd(s403, s409, vl1);
            t683 = __riscv_vfadd(s396, t681, vl1);
            t684 = __riscv_vfadd(s397, t682, vl1);
            t685 = __riscv_vfnmsac(s396, 0.5, t681, vl1);
            t686 = __riscv_vfnmsac(s397, 0.5, t682, vl1);
            s414 = __riscv_vfmul(__riscv_vfsub(s403, s409, vl1), 0.8660254037844386, vl1);
            s415 = __riscv_vfmul(__riscv_vfsub(s402, s408, vl1), 0.8660254037844386, vl1);
            t687 = __riscv_vfadd(t685, s414, vl1);
            t688 = __riscv_vfsub(t686, s415, vl1);
            t689 = __riscv_vfsub(t685, s414, vl1);
            t690 = __riscv_vfadd(t686, s415, vl1);
            t691 = __riscv_vfadd(s404, s410, vl1);
            t692 = __riscv_vfadd(s405, s411, vl1);
            t693 = __riscv_vfadd(s398, t691, vl1);
            t694 = __riscv_vfadd(s399, t692, vl1);
            t695 = __riscv_vfnmsac(s398, 0.5, t691, vl1);
            t696 = __riscv_vfnmsac(s399, 0.5, t692, vl1);
            s416 = __riscv_vfmul(__riscv_vfsub(s405, s411, vl1), 0.8660254037844386, vl1);
            s417 = __riscv_vfmul(__riscv_vfsub(s404, s410, vl1), 0.8660254037844386, vl1);
            t697 = __riscv_vfadd(t695, s416, vl1);
            t698 = __riscv_vfsub(t696, s417, vl1);
            t699 = __riscv_vfsub(t695, s416, vl1);
            t700 = __riscv_vfadd(t696, s417, vl1);
            s450 = __riscv_vfmacc(t697, 0.83909963117727981, t698, vl1);
            s418 = __riscv_vfmul(s450, 0.76604444311897812, vl1);
            s451 = __riscv_vfnmsac(t698, 0.83909963117727981, t697, vl1);
            s419 = __riscv_vfmul(s451, 0.76604444311897812, vl1);
            s452 = __riscv_vfmacc(t699, 5.6712818196177102, t700, vl1);
            s420 = __riscv_vfmul(s452, 0.17364817766693033, vl1);
            s453 = __riscv_vfnmsac(t700, 5.6712818196177102, t699, vl1);
            s421 = __riscv_vfmul(s453, 0.17364817766693033, vl1);
            t701 = __riscv_vfadd(s406, s412, vl1);
            t702 = __riscv_vfadd(s407, s413, vl1);
            t703 = __riscv_vfadd(s400, t701, vl1);
            t704 = __riscv_vfadd(s401, t702, vl1);
            t705 = __riscv_vfnmsac(s400, 0.5, t701, vl1);
            t706 = __riscv_vfnmsac(s401, 0.5, t702, vl1);
            s422 = __riscv_vfmul(__riscv_vfsub(s407, s413, vl1), 0.8660254037844386, vl1);
            s423 = __riscv_vfmul(__riscv_vfsub(s406, s412, vl1), 0.8660254037844386, vl1);
            t707 = __riscv_vfadd(t705, s422, vl1);
            t708 = __riscv_vfsub(t706, s423, vl1);
            t709 = __riscv_vfsub(t705, s422, vl1);
            t710 = __riscv_vfadd(t706, s423, vl1);
            s454 = __riscv_vfmacc(t707, 5.6712818196177102, t708, vl1);
            s424 = __riscv_vfmul(s454, 0.17364817766693033, vl1);
            s455 = __riscv_vfnmsac(t708, 5.6712818196177102, t707, vl1);
            s425 = __riscv_vfmul(s455, 0.17364817766693033, vl1);
            s456 = __riscv_vfnmsac(t710, 2.7474774194546225, t709, vl1);
            s426 = __riscv_vfmul(s456, 0.34202014332566871, vl1);
            s457 = __riscv_vfmacc(t709, 2.7474774194546225, t710, vl1);
            s427 = __riscv_vfmul(s457, 0.34202014332566871, vl1);
            t711 = __riscv_vfadd(t693, t703, vl1);
            t712 = __riscv_vfadd(t694, t704, vl1);
            t713 = __riscv_vfnmsac(t683, 0.5, t711, vl1);
            t714 = __riscv_vfnmsac(t684, 0.5, t712, vl1);
            s428 = __riscv_vfmul(__riscv_vfsub(t694, t704, vl1), 0.8660254037844386, vl1);
            s429 = __riscv_vfmul(__riscv_vfsub(t693, t703, vl1), 0.8660254037844386, vl1);
            s430 = __riscv_vfadd(t713, s428, vl1);
            s431 = __riscv_vfsub(t714, s429, vl1);
            s432 = __riscv_vfsub(t713, s428, vl1);
            s433 = __riscv_vfadd(t714, s429, vl1);
            t715 = __riscv_vfadd(s418, s424, vl1);
            t716 = __riscv_vfadd(s419, s425, vl1);
            t717 = __riscv_vfnmsac(t687, 0.5, t715, vl1);
            t718 = __riscv_vfnmsac(t688, 0.5, t716, vl1);
            s434 = __riscv_vfmul(__riscv_vfsub(s419, s425, vl1), 0.8660254037844386, vl1);
            s435 = __riscv_vfmul(__riscv_vfsub(s418, s424, vl1), 0.8660254037844386, vl1);
            s436 = __riscv_vfadd(t687, t715, vl1);
            s437 = __riscv_vfadd(t688, t716, vl1);
            s438 = __riscv_vfadd(t717, s434, vl1);
            s439 = __riscv_vfsub(t718, s435, vl1);
            s440 = __riscv_vfsub(t717, s434, vl1);
            s441 = __riscv_vfadd(t718, s435, vl1);
            t719 = __riscv_vfadd(s420, s426, vl1);
            t720 = __riscv_vfsub(s421, s427, vl1);
            t721 = __riscv_vfnmsac(t689, 0.5, t719, vl1);
            t722 = __riscv_vfnmsac(t690, 0.5, t720, vl1);
            s442 = __riscv_vfmul(__riscv_vfadd(s421, s427, vl1), 0.8660254037844386, vl1);
            s443 = __riscv_vfmul(__riscv_vfsub(s420, s426, vl1), 0.8660254037844386, vl1);
            s444 = __riscv_vfadd(t689, t719, vl1);
            s445 = __riscv_vfadd(t690, t720, vl1);
            s446 = __riscv_vfadd(t721, s442, vl1);
            s447 = __riscv_vfsub(t722, s443, vl1);
            s448 = __riscv_vfsub(t721, s442, vl1);
            s449 = __riscv_vfadd(t722, s443, vl1);
            a887 = ((16)*(j1));
            a888 = TW1[a887];
            a889 = TW1[(a887 + 1)];
            a890 = TW1[(a887 + 2)];
            a891 = TW1[(a887 + 3)];
            a892 = TW1[(a887 + 4)];
            a893 = TW1[(a887 + 5)];
            a894 = TW1[(a887 + 6)];
            a895 = TW1[(a887 + 7)];
            a896 = TW1[(a887 + 8)];
            a897 = TW1[(a887 + 9)];
            a898 = TW1[(a887 + 10)];
            a899 = TW1[(a887 + 11)];
            a900 = TW1[(a887 + 12)];
            a901 = TW1[(a887 + 13)];
            a902 = TW1[(a887 + 14)];
            a903 = TW1[(a887 + 15)];
            r154 = __riscv_vset(__riscv_vset(rvvx2_10, 0, __riscv_vfadd(t683, t711, vl1)), 1, __riscv_vfadd(t684, t712, vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((9)*(j1)))*(m1)))))), r154, vl1);
            r155 = __riscv_vset(__riscv_vset(rvvx2_11, 0, __riscv_vfsub(__riscv_vfmul(s436, a888, vl1), __riscv_vfmul(s437, a889, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s436, a889, vl1), __riscv_vfmul(s437, a888, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((9)*(j1)))*(m1)) + m1)))), r155, vl1);
            r156 = __riscv_vset(__riscv_vset(rvvx2_12, 0, __riscv_vfsub(__riscv_vfmul(s444, a890, vl1), __riscv_vfmul(s445, a891, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s444, a891, vl1), __riscv_vfmul(s445, a890, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((9)*(j1)))*(m1)) + ((2)*(m1)))))), r156, vl1);
            r157 = __riscv_vset(__riscv_vset(rvvx2_13, 0, __riscv_vfsub(__riscv_vfmul(s430, a892, vl1), __riscv_vfmul(s431, a893, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s430, a893, vl1), __riscv_vfmul(s431, a892, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((9)*(j1)))*(m1)) + ((3)*(m1)))))), r157, vl1);
            r158 = __riscv_vset(__riscv_vset(rvvx2_14, 0, __riscv_vfsub(__riscv_vfmul(s438, a894, vl1), __riscv_vfmul(s439, a895, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s438, a895, vl1), __riscv_vfmul(s439, a894, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((9)*(j1)))*(m1)) + ((4)*(m1)))))), r158, vl1);
            r159 = __riscv_vset(__riscv_vset(rvvx2_15, 0, __riscv_vfsub(__riscv_vfmul(s446, a896, vl1), __riscv_vfmul(s447, a897, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s446, a897, vl1), __riscv_vfmul(s447, a896, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((9)*(j1)))*(m1)) + ((5)*(m1)))))), r159, vl1);
            r160 = __riscv_vset(__riscv_vset(rvvx2_16, 0, __riscv_vfsub(__riscv_vfmul(s432, a898, vl1), __riscv_vfmul(s433, a899, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s432, a899, vl1), __riscv_vfmul(s433, a898, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((9)*(j1)))*(m1)) + ((6)*(m1)))))), r160, vl1);
            r161 = __riscv_vset(__riscv_vset(rvvx2_17, 0, __riscv_vfsub(__riscv_vfmul(s440, a900, vl1), __riscv_vfmul(s441, a901, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s440, a901, vl1), __riscv_vfmul(s441, a900, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((9)*(j1)))*(m1)) + ((7)*(m1)))))), r161, vl1);
            r162 = __riscv_vset(__riscv_vset(rvvx2_18, 0, __riscv_vfsub(__riscv_vfmul(s448, a902, vl1), __riscv_vfmul(s449, a903, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s448, a903, vl1), __riscv_vfmul(s449, a902, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((9)*(j1)))*(m1)) + ((8)*(m1)))))), r162, vl1);
        }
    }
}
