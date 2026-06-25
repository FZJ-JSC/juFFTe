// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft9a_r32_(float *Y, float *X, float *TW1, int64_t *lp1) {
    int64_t l1;
    float *a804;
    vfloat32m1x2_t r64, r65, r66, r67, r68, r69, r70, r71, 
            r72;
    vfloat32m1_t  a805, a806, a807, a808, a809, a810, a811, a812, 
            a813, a814, a815, a816, a817, a818, a819, a820, 
            s414, s415, s416, s417, s418, s419, s420, s421, 
            s422, s423, s424, s425, s426, s427, s428, s429, 
            s430, s431, s432, s433, s434, s435, s436, s437, 
            s438, s439, s440, s441, s442, s443, s444, s445, 
            s446, s447, s448, s449, s450, s451, s452, s453, 
            s454, s455, s456, s457, s458, s459, s460, s461, 
            s462, s463, s464, s465, s466, s467, s468, s469, 
            s470, s471, s472, s473, s474, s475, s476, s477, 
            s478, s479, s480, s481, s482, s483, s484, s485, 
            s486, s487, s488, s489, s490, s491, s492, s493, 
            t681, t682, t683, t684, t685, t686, t687, t688, 
            t689, t690, t691, t692, t693, t694, t695, t696, 
            t697, t698, t699, t700, t701, t702, t703, t704, 
            t705, t706, t707, t708, t709, t710, t711, t712, 
            t713, t714, t715, t716, t717, t718, t719, t720, 
            t721, t722;
    size_t vl1;
    l1 = *(lp1);
    for (size_t j1 = 0; j1 < l1; j1 += vl1) {
        vl1 = __riscv_vsetvl_e32m1(l1 - j1);
        r64 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*(j1))), vl1);
        s414 = __riscv_vget_f32m1(r64, 0);
        s415 = __riscv_vget_f32m1(r64, 1);
        r65 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + l1)))), vl1);
        s416 = __riscv_vget_f32m1(r65, 0);
        s417 = __riscv_vget_f32m1(r65, 1);
        r66 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((2)*(l1)))))), vl1);
        s418 = __riscv_vget_f32m1(r66, 0);
        s419 = __riscv_vget_f32m1(r66, 1);
        r67 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((3)*(l1)))))), vl1);
        s420 = __riscv_vget_f32m1(r67, 0);
        s421 = __riscv_vget_f32m1(r67, 1);
        r68 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((4)*(l1)))))), vl1);
        s422 = __riscv_vget_f32m1(r68, 0);
        s423 = __riscv_vget_f32m1(r68, 1);
        r69 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((5)*(l1)))))), vl1);
        s424 = __riscv_vget_f32m1(r69, 0);
        s425 = __riscv_vget_f32m1(r69, 1);
        r70 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((6)*(l1)))))), vl1);
        s426 = __riscv_vget_f32m1(r70, 0);
        s427 = __riscv_vget_f32m1(r70, 1);
        r71 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((7)*(l1)))))), vl1);
        s428 = __riscv_vget_f32m1(r71, 0);
        s429 = __riscv_vget_f32m1(r71, 1);
        r72 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((8)*(l1)))))), vl1);
        s430 = __riscv_vget_f32m1(r72, 0);
        s431 = __riscv_vget_f32m1(r72, 1);
        t681 = __riscv_vfadd(s420, s426, vl1);
        t682 = __riscv_vfadd(s421, s427, vl1);
        t683 = __riscv_vfadd(s414, t681, vl1);
        t684 = __riscv_vfadd(s415, t682, vl1);
        t685 = __riscv_vfnmsac(s414, 0.5, t681, vl1);
        t686 = __riscv_vfnmsac(s415, 0.5, t682, vl1);
        s432 = __riscv_vfmul(__riscv_vfsub(s421, s427, vl1), 0.8660254037844386, vl1);
        s433 = __riscv_vfmul(__riscv_vfsub(s420, s426, vl1), 0.8660254037844386, vl1);
        t687 = __riscv_vfadd(t685, s432, vl1);
        t688 = __riscv_vfsub(t686, s433, vl1);
        t689 = __riscv_vfsub(t685, s432, vl1);
        t690 = __riscv_vfadd(t686, s433, vl1);
        t691 = __riscv_vfadd(s422, s428, vl1);
        t692 = __riscv_vfadd(s423, s429, vl1);
        t693 = __riscv_vfadd(s416, t691, vl1);
        t694 = __riscv_vfadd(s417, t692, vl1);
        t695 = __riscv_vfnmsac(s416, 0.5, t691, vl1);
        t696 = __riscv_vfnmsac(s417, 0.5, t692, vl1);
        s434 = __riscv_vfmul(__riscv_vfsub(s423, s429, vl1), 0.8660254037844386, vl1);
        s435 = __riscv_vfmul(__riscv_vfsub(s422, s428, vl1), 0.8660254037844386, vl1);
        t697 = __riscv_vfadd(t695, s434, vl1);
        t698 = __riscv_vfsub(t696, s435, vl1);
        t699 = __riscv_vfsub(t695, s434, vl1);
        t700 = __riscv_vfadd(t696, s435, vl1);
        s486 = __riscv_vfmacc(t697, 0.83909963117727981, t698, vl1);
        s436 = __riscv_vfmul(s486, 0.76604444311897812, vl1);
        s487 = __riscv_vfnmsac(t698, 0.83909963117727981, t697, vl1);
        s437 = __riscv_vfmul(s487, 0.76604444311897812, vl1);
        s488 = __riscv_vfmacc(t699, 5.6712818196177102, t700, vl1);
        s438 = __riscv_vfmul(s488, 0.17364817766693033, vl1);
        s489 = __riscv_vfnmsac(t700, 5.6712818196177102, t699, vl1);
        s439 = __riscv_vfmul(s489, 0.17364817766693033, vl1);
        t701 = __riscv_vfadd(s424, s430, vl1);
        t702 = __riscv_vfadd(s425, s431, vl1);
        t703 = __riscv_vfadd(s418, t701, vl1);
        t704 = __riscv_vfadd(s419, t702, vl1);
        t705 = __riscv_vfnmsac(s418, 0.5, t701, vl1);
        t706 = __riscv_vfnmsac(s419, 0.5, t702, vl1);
        s440 = __riscv_vfmul(__riscv_vfsub(s425, s431, vl1), 0.8660254037844386, vl1);
        s441 = __riscv_vfmul(__riscv_vfsub(s424, s430, vl1), 0.8660254037844386, vl1);
        t707 = __riscv_vfadd(t705, s440, vl1);
        t708 = __riscv_vfsub(t706, s441, vl1);
        t709 = __riscv_vfsub(t705, s440, vl1);
        t710 = __riscv_vfadd(t706, s441, vl1);
        s490 = __riscv_vfmacc(t707, 5.6712818196177102, t708, vl1);
        s442 = __riscv_vfmul(s490, 0.17364817766693033, vl1);
        s491 = __riscv_vfnmsac(t708, 5.6712818196177102, t707, vl1);
        s443 = __riscv_vfmul(s491, 0.17364817766693033, vl1);
        s492 = __riscv_vfnmsac(t710, 2.7474774194546225, t709, vl1);
        s444 = __riscv_vfmul(s492, 0.34202014332566871, vl1);
        s493 = __riscv_vfmacc(t709, 2.7474774194546225, t710, vl1);
        s445 = __riscv_vfmul(s493, 0.34202014332566871, vl1);
        t711 = __riscv_vfadd(t693, t703, vl1);
        t712 = __riscv_vfadd(t694, t704, vl1);
        t713 = __riscv_vfnmsac(t683, 0.5, t711, vl1);
        t714 = __riscv_vfnmsac(t684, 0.5, t712, vl1);
        s446 = __riscv_vfmul(__riscv_vfsub(t694, t704, vl1), 0.8660254037844386, vl1);
        s447 = __riscv_vfmul(__riscv_vfsub(t693, t703, vl1), 0.8660254037844386, vl1);
        s448 = __riscv_vfadd(t683, t711, vl1);
        s449 = __riscv_vfadd(t684, t712, vl1);
        s450 = __riscv_vfadd(t713, s446, vl1);
        s451 = __riscv_vfsub(t714, s447, vl1);
        s452 = __riscv_vfsub(t713, s446, vl1);
        s453 = __riscv_vfadd(t714, s447, vl1);
        t715 = __riscv_vfadd(s436, s442, vl1);
        t716 = __riscv_vfadd(s437, s443, vl1);
        t717 = __riscv_vfnmsac(t687, 0.5, t715, vl1);
        t718 = __riscv_vfnmsac(t688, 0.5, t716, vl1);
        s454 = __riscv_vfmul(__riscv_vfsub(s437, s443, vl1), 0.8660254037844386, vl1);
        s455 = __riscv_vfmul(__riscv_vfsub(s436, s442, vl1), 0.8660254037844386, vl1);
        s456 = __riscv_vfadd(t687, t715, vl1);
        s457 = __riscv_vfadd(t688, t716, vl1);
        s458 = __riscv_vfadd(t717, s454, vl1);
        s459 = __riscv_vfsub(t718, s455, vl1);
        s460 = __riscv_vfsub(t717, s454, vl1);
        s461 = __riscv_vfadd(t718, s455, vl1);
        t719 = __riscv_vfadd(s438, s444, vl1);
        t720 = __riscv_vfsub(s439, s445, vl1);
        t721 = __riscv_vfnmsac(t689, 0.5, t719, vl1);
        t722 = __riscv_vfnmsac(t690, 0.5, t720, vl1);
        s462 = __riscv_vfmul(__riscv_vfadd(s439, s445, vl1), 0.8660254037844386, vl1);
        s463 = __riscv_vfmul(__riscv_vfsub(s438, s444, vl1), 0.8660254037844386, vl1);
        s464 = __riscv_vfadd(t689, t719, vl1);
        s465 = __riscv_vfadd(t690, t720, vl1);
        s466 = __riscv_vfadd(t721, s462, vl1);
        s467 = __riscv_vfsub(t722, s463, vl1);
        s468 = __riscv_vfsub(t721, s462, vl1);
        s469 = __riscv_vfadd(t722, s463, vl1);
        a804 = (TW1 + ((16)*(j1)));
        a805 = __riscv_vlse32_v_f32m1(a804, sizeof(double) * 16, vl1);
        a806 = __riscv_vlse32_v_f32m1((a804 + 1), sizeof(double) * 16, vl1);
        s470 = __riscv_vfmsac(__riscv_vfmul(a806, s457, vl1), a805, s456, vl1);
        s471 = __riscv_vfmacc(__riscv_vfmul(a805, s457, vl1), a806, s456, vl1);
        a807 = __riscv_vlse32_v_f32m1((a804 + 2), sizeof(double) * 16, vl1);
        a808 = __riscv_vlse32_v_f32m1((a804 + 3), sizeof(double) * 16, vl1);
        s472 = __riscv_vfmsac(__riscv_vfmul(a808, s465, vl1), a807, s464, vl1);
        s473 = __riscv_vfmacc(__riscv_vfmul(a807, s465, vl1), a808, s464, vl1);
        a809 = __riscv_vlse32_v_f32m1((a804 + 4), sizeof(double) * 16, vl1);
        a810 = __riscv_vlse32_v_f32m1((a804 + 5), sizeof(double) * 16, vl1);
        s474 = __riscv_vfmsac(__riscv_vfmul(a810, s451, vl1), a809, s450, vl1);
        s475 = __riscv_vfmacc(__riscv_vfmul(a809, s451, vl1), a810, s450, vl1);
        a811 = __riscv_vlse32_v_f32m1((a804 + 6), sizeof(double) * 16, vl1);
        a812 = __riscv_vlse32_v_f32m1((a804 + 7), sizeof(double) * 16, vl1);
        s476 = __riscv_vfmsac(__riscv_vfmul(a812, s459, vl1), a811, s458, vl1);
        s477 = __riscv_vfmacc(__riscv_vfmul(a811, s459, vl1), a812, s458, vl1);
        a813 = __riscv_vlse32_v_f32m1((a804 + 8), sizeof(double) * 16, vl1);
        a814 = __riscv_vlse32_v_f32m1((a804 + 9), sizeof(double) * 16, vl1);
        s478 = __riscv_vfmsac(__riscv_vfmul(a814, s467, vl1), a813, s466, vl1);
        s479 = __riscv_vfmacc(__riscv_vfmul(a813, s467, vl1), a814, s466, vl1);
        a815 = __riscv_vlse32_v_f32m1((a804 + 10), sizeof(double) * 16, vl1);
        a816 = __riscv_vlse32_v_f32m1((a804 + 11), sizeof(double) * 16, vl1);
        s480 = __riscv_vfmsac(__riscv_vfmul(a816, s453, vl1), a815, s452, vl1);
        s481 = __riscv_vfmacc(__riscv_vfmul(a815, s453, vl1), a816, s452, vl1);
        a817 = __riscv_vlse32_v_f32m1((a804 + 12), sizeof(double) * 16, vl1);
        a818 = __riscv_vlse32_v_f32m1((a804 + 13), sizeof(double) * 16, vl1);
        s482 = __riscv_vfmsac(__riscv_vfmul(a818, s461, vl1), a817, s460, vl1);
        s483 = __riscv_vfmacc(__riscv_vfmul(a817, s461, vl1), a818, s460, vl1);
        a819 = __riscv_vlse32_v_f32m1((a804 + 14), sizeof(double) * 16, vl1);
        a820 = __riscv_vlse32_v_f32m1((a804 + 15), sizeof(double) * 16, vl1);
        s484 = __riscv_vfmsac(__riscv_vfmul(a820, s469, vl1), a819, s468, vl1);
        s485 = __riscv_vfmacc(__riscv_vfmul(a819, s469, vl1), a820, s468, vl1);
        __riscv_vsse32((Y + ((18)*(j1))), sizeof(double) * 18, s448, vl1);
        __riscv_vsse32((1 + Y + ((18)*(j1))), sizeof(double) * 18, s449, vl1);
        __riscv_vsse32((2 + Y + ((18)*(j1))), sizeof(double) * 18, s470, vl1);
        __riscv_vsse32((3 + Y + ((18)*(j1))), sizeof(double) * 18, s471, vl1);
        __riscv_vsse32((4 + Y + ((18)*(j1))), sizeof(double) * 18, s472, vl1);
        __riscv_vsse32((5 + Y + ((18)*(j1))), sizeof(double) * 18, s473, vl1);
        __riscv_vsse32((6 + Y + ((18)*(j1))), sizeof(double) * 18, s474, vl1);
        __riscv_vsse32((7 + Y + ((18)*(j1))), sizeof(double) * 18, s475, vl1);
        __riscv_vsse32((8 + Y + ((18)*(j1))), sizeof(double) * 18, s476, vl1);
        __riscv_vsse32((9 + Y + ((18)*(j1))), sizeof(double) * 18, s477, vl1);
        __riscv_vsse32((10 + Y + ((18)*(j1))), sizeof(double) * 18, s478, vl1);
        __riscv_vsse32((11 + Y + ((18)*(j1))), sizeof(double) * 18, s479, vl1);
        __riscv_vsse32((12 + Y + ((18)*(j1))), sizeof(double) * 18, s480, vl1);
        __riscv_vsse32((13 + Y + ((18)*(j1))), sizeof(double) * 18, s481, vl1);
        __riscv_vsse32((14 + Y + ((18)*(j1))), sizeof(double) * 18, s482, vl1);
        __riscv_vsse32((15 + Y + ((18)*(j1))), sizeof(double) * 18, s483, vl1);
        __riscv_vsse32((16 + Y + ((18)*(j1))), sizeof(double) * 18, s484, vl1);
        __riscv_vsse32((17 + Y + ((18)*(j1))), sizeof(double) * 18, s485, vl1);
    }
}
