// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft14c_(double *Y, double *X, int *lp1, int *mp1) {
    int l1, m1;
    vfloat64m1x2_t r225, r226, r227, r228, r229, r230, r231, r232, 
            r233, r234, r235, r236, r237, r238, r239, r240, 
            r241, r242, r243, r244, r245, r246, r247, r248, 
            r249, r250, r251, r252, rvvx2_15, rvvx2_16, rvvx2_17, rvvx2_18, 
            rvvx2_19, rvvx2_20, rvvx2_21, rvvx2_22, rvvx2_23, rvvx2_24, rvvx2_25, rvvx2_26, 
            rvvx2_27, rvvx2_28;
    vfloat64m1_t  s2694, s2695, s2696, s2697, s2698, s2699, s2700, s2701, 
            s2702, s2703, s2704, s2705, s2706, s2707, s2708, s2709, 
            s2710, s2711, s2712, s2713, s2714, s2715, s2716, s2717, 
            s2718, s2719, s2720, s2721, s2722, s2723, s2724, s2725, 
            s2726, s2727, s2728, s2729, s2730, s2731, s2732, s2733, 
            s2734, s2735, s2736, s2737, s2738, s2739, s2740, s2741, 
            s2742, s2743, s2744, s2745, s2746, s2747, s2748, s2749, 
            s2750, s2751, s2752, s2753, s2754, s2755, s2756, s2757, 
            s2758, s2759, s2760, s2761, s2762, s2763, s2764, s2765, 
            s2766, s2767, s2768, s2769, s2770, s2771, s2772, s2773, 
            s2774, s2775, s2776, s2777, s2778, s2779, s2780, s2781, 
            s2782, s2783, s2784, s2785, s2786, s2787, s2788, s2789, 
            s2790, s2791, s2792, s2793, s2794, s2795, s2796, s2797, 
            s2798, s2799, s2800, s2801, s2802, s2803, s2804, s2805, 
            s2806, s2807, s2808, s2809, s2810, s2811, s2812, s2813, 
            s2814, s2815, s2816, s2817, s2818, s2819, s2820, s2821, 
            s2822, s2823, s2824, s2825, s2826, s2827, s2828, s2829, 
            t6734, t6735, t6736, t6737, t6738, t6739, t6740, t6741, 
            t6742, t6743, t6744, t6745, t6746, t6747, t6748, t6749, 
            t6750, t6751, t6752, t6753, t6754, t6755, t6756, t6757, 
            t6758, t6759, t6760, t6761, t6762, t6763, t6764, t6765, 
            t6766, t6767, t6768, t6769, t6770, t6771, t6772, t6773, 
            t6774, t6775, t6776, t6777, t6778, t6779, t6780, t6781, 
            t6782, t6783, t6784, t6785, t6786, t6787, t6788, t6789, 
            t6790, t6791, t6792, t6793, t6794, t6795, t6796, t6797, 
            t6798, t6799, t6800, t6801, t6802, t6803, t6804, t6805, 
            t6806, t6807, t6808, t6809, t6810, t6811, t6812, t6813, 
            t6814, t6815, t6816, t6817, t6818, t6819, t6820, t6821, 
            t6822, t6823, t6824, t6825, t6826, t6827, t6828, t6829, 
            t6830, t6831, t6832, t6833, t6834, t6835, t6836, t6837, 
            t6838, t6839, t6840, t6841, t6842, t6843, t6844, t6845, 
            t6846, t6847, t6848, t6849, t6850, t6851, t6852, t6853, 
            t6854, t6855, t6856, t6857, t6858, t6859, t6860, t6861, 
            t6862, t6863, t6864, t6865;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for (size_t k1 = 0; k1 < m1; k1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(m1 - k1);
        r225 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(k1))), vl1);
        s2694 = __riscv_vget_f64m1(r225, 0);
        s2695 = __riscv_vget_f64m1(r225, 1);
        r226 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((l1)*(m1)))))), vl1);
        s2696 = __riscv_vget_f64m1(r226, 0);
        s2697 = __riscv_vget_f64m1(r226, 1);
        r227 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((2)*(l1)))*(m1)))))), vl1);
        s2698 = __riscv_vget_f64m1(r227, 0);
        s2699 = __riscv_vget_f64m1(r227, 1);
        r228 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((3)*(l1)))*(m1)))))), vl1);
        s2700 = __riscv_vget_f64m1(r228, 0);
        s2701 = __riscv_vget_f64m1(r228, 1);
        r229 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((4)*(l1)))*(m1)))))), vl1);
        s2702 = __riscv_vget_f64m1(r229, 0);
        s2703 = __riscv_vget_f64m1(r229, 1);
        r230 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((5)*(l1)))*(m1)))))), vl1);
        s2704 = __riscv_vget_f64m1(r230, 0);
        s2705 = __riscv_vget_f64m1(r230, 1);
        r231 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((6)*(l1)))*(m1)))))), vl1);
        s2706 = __riscv_vget_f64m1(r231, 0);
        s2707 = __riscv_vget_f64m1(r231, 1);
        r232 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((7)*(l1)))*(m1)))))), vl1);
        s2708 = __riscv_vget_f64m1(r232, 0);
        s2709 = __riscv_vget_f64m1(r232, 1);
        r233 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((8)*(l1)))*(m1)))))), vl1);
        s2710 = __riscv_vget_f64m1(r233, 0);
        s2711 = __riscv_vget_f64m1(r233, 1);
        r234 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((9)*(l1)))*(m1)))))), vl1);
        s2712 = __riscv_vget_f64m1(r234, 0);
        s2713 = __riscv_vget_f64m1(r234, 1);
        r235 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((10)*(l1)))*(m1)))))), vl1);
        s2714 = __riscv_vget_f64m1(r235, 0);
        s2715 = __riscv_vget_f64m1(r235, 1);
        r236 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((11)*(l1)))*(m1)))))), vl1);
        s2716 = __riscv_vget_f64m1(r236, 0);
        s2717 = __riscv_vget_f64m1(r236, 1);
        r237 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((12)*(l1)))*(m1)))))), vl1);
        s2718 = __riscv_vget_f64m1(r237, 0);
        s2719 = __riscv_vget_f64m1(r237, 1);
        r238 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((13)*(l1)))*(m1)))))), vl1);
        s2720 = __riscv_vget_f64m1(r238, 0);
        s2721 = __riscv_vget_f64m1(r238, 1);
        t6734 = __riscv_vfadd(s2702, s2710, vl1);
        t6735 = __riscv_vfadd(s2703, s2711, vl1);
        t6736 = __riscv_vfadd(s2698, t6734, vl1);
        t6737 = __riscv_vfadd(s2699, t6735, vl1);
        t6738 = __riscv_vfnmsac(s2698, 0.5, t6734, vl1);
        t6739 = __riscv_vfnmsac(s2699, 0.5, t6735, vl1);
        s2722 = __riscv_vfmul(__riscv_vfsub(s2703, s2711, vl1), 0.8660254037844386, vl1);
        s2723 = __riscv_vfmul(__riscv_vfsub(s2702, s2710, vl1), 0.8660254037844386, vl1);
        t6740 = __riscv_vfadd(t6738, s2722, vl1);
        t6741 = __riscv_vfsub(t6739, s2723, vl1);
        t6742 = __riscv_vfsub(t6738, s2722, vl1);
        t6743 = __riscv_vfadd(t6739, s2723, vl1);
        t6744 = __riscv_vfadd(s2718, s2714, vl1);
        t6745 = __riscv_vfadd(s2719, s2715, vl1);
        t6746 = __riscv_vfadd(s2706, t6744, vl1);
        t6747 = __riscv_vfadd(s2707, t6745, vl1);
        t6748 = __riscv_vfnmsac(s2706, 0.5, t6744, vl1);
        t6749 = __riscv_vfnmsac(s2707, 0.5, t6745, vl1);
        s2724 = __riscv_vfmul(__riscv_vfsub(s2719, s2715, vl1), 0.8660254037844386, vl1);
        s2725 = __riscv_vfmul(__riscv_vfsub(s2718, s2714, vl1), 0.8660254037844386, vl1);
        t6750 = __riscv_vfadd(t6748, s2724, vl1);
        t6751 = __riscv_vfsub(t6749, s2725, vl1);
        t6752 = __riscv_vfsub(t6748, s2724, vl1);
        t6753 = __riscv_vfadd(t6749, s2725, vl1);
        s2786 = __riscv_vfmacc(t6750, 1.7320508075688772, t6751, vl1);
        s2726 = __riscv_vfmul(s2786, 0.5, vl1);
        s2787 = __riscv_vfnmsac(t6751, 1.7320508075688772, t6750, vl1);
        s2727 = __riscv_vfmul(s2787, 0.5, vl1);
        s2788 = __riscv_vfnmsac(t6753, 0.57735026918962584, t6752, vl1);
        s2728 = __riscv_vfmul(s2788, 0.8660254037844386, vl1);
        s2789 = __riscv_vfmacc(t6752, 0.57735026918962584, t6753, vl1);
        s2729 = __riscv_vfmul(s2789, 0.8660254037844386, vl1);
        t6754 = __riscv_vfadd(t6736, t6746, vl1);
        t6755 = __riscv_vfadd(t6737, t6747, vl1);
        t6756 = __riscv_vfadd(t6740, s2726, vl1);
        t6757 = __riscv_vfadd(t6741, s2727, vl1);
        t6758 = __riscv_vfsub(t6740, s2726, vl1);
        t6759 = __riscv_vfsub(t6741, s2727, vl1);
        t6760 = __riscv_vfadd(t6742, s2728, vl1);
        t6761 = __riscv_vfsub(t6743, s2729, vl1);
        t6762 = __riscv_vfsub(t6742, s2728, vl1);
        t6763 = __riscv_vfadd(t6743, s2729, vl1);
        t6764 = __riscv_vfadd(s2694, t6754, vl1);
        t6765 = __riscv_vfadd(s2695, t6755, vl1);
        t6766 = __riscv_vfnmsac(s2694, 0.16666666666666666, t6754, vl1);
        t6767 = __riscv_vfnmsac(s2695, 0.16666666666666666, t6755, vl1);
        s2790 = __riscv_vfmacc(t6756, 0.41908315722758338, t6757, vl1);
        s2730 = __riscv_vfmul(s2790, 0.4066888930575896, vl1);
        s2791 = __riscv_vfnmsac(t6757, 0.41908315722758338, t6756, vl1);
        s2731 = __riscv_vfmul(s2791, 0.4066888930575896, vl1);
        s2792 = __riscv_vfmacc(t6760, 0.49572725516748389, t6761, vl1);
        s2732 = __riscv_vfmul(s2792, 0.39507823426270006, vl1);
        s2793 = __riscv_vfnmsac(t6761, 0.49572725516748389, t6760, vl1);
        s2733 = __riscv_vfmul(s2793, 0.39507823426270006, vl1);
        s2734 = __riscv_vfmul(__riscv_vfsub(t6737, t6747, vl1), 0.44095855184409843, vl1);
        s2735 = __riscv_vfmul(__riscv_vfsub(t6736, t6746, vl1), 0.44095855184409843, vl1);
        s2794 = __riscv_vfnmsac(t6758, 0.49572725516748389, t6759, vl1);
        s2736 = __riscv_vfmul(s2794, 0.39507823426270006, vl1);
        s2795 = __riscv_vfmacc(t6758, 2.0172382889501304, t6759, vl1);
        s2737 = __riscv_vfmul(s2795, 0.1958510486474645, vl1);
        s2796 = __riscv_vfnmsac(t6763, 2.386161273135941, t6762, vl1);
        s2738 = __riscv_vfmul(s2796, 0.17043646531196566, vl1);
        s2797 = __riscv_vfmacc(t6762, 2.386161273135941, t6763, vl1);
        s2739 = __riscv_vfmul(s2797, 0.17043646531196566, vl1);
        t6768 = __riscv_vfadd(s2732, s2736, vl1);
        t6769 = __riscv_vfadd(s2733, s2737, vl1);
        t6770 = __riscv_vfadd(t6766, t6768, vl1);
        t6771 = __riscv_vfadd(t6767, t6769, vl1);
        t6772 = __riscv_vfnmsac(t6766, 0.5, t6768, vl1);
        t6773 = __riscv_vfnmsac(t6767, 0.5, t6769, vl1);
        s2740 = __riscv_vfmul(__riscv_vfsub(s2733, s2737, vl1), 0.8660254037844386, vl1);
        s2741 = __riscv_vfmul(__riscv_vfsub(s2732, s2736, vl1), 0.8660254037844386, vl1);
        t6774 = __riscv_vfadd(t6772, s2740, vl1);
        t6775 = __riscv_vfsub(t6773, s2741, vl1);
        t6776 = __riscv_vfsub(t6772, s2740, vl1);
        t6777 = __riscv_vfadd(t6773, s2741, vl1);
        t6778 = __riscv_vfadd(s2734, s2738, vl1);
        t6779 = __riscv_vfadd(s2735, s2739, vl1);
        t6780 = __riscv_vfadd(s2730, t6778, vl1);
        t6781 = __riscv_vfsub(s2731, t6779, vl1);
        t6782 = __riscv_vfnmsac(s2730, 0.5, t6778, vl1);
        t6783 = __riscv_vfmacc(s2731, 0.5, t6779, vl1);
        s2742 = __riscv_vfmul(__riscv_vfsub(s2739, s2735, vl1), 0.8660254037844386, vl1);
        s2743 = __riscv_vfmul(__riscv_vfsub(s2734, s2738, vl1), 0.8660254037844386, vl1);
        t6784 = __riscv_vfadd(t6782, s2742, vl1);
        t6785 = __riscv_vfsub(t6783, s2743, vl1);
        t6786 = __riscv_vfsub(t6782, s2742, vl1);
        t6787 = __riscv_vfadd(t6783, s2743, vl1);
        s2798 = __riscv_vfmacc(t6784, 1.7320508075688772, t6785, vl1);
        s2744 = __riscv_vfmul(s2798, 0.5, vl1);
        s2799 = __riscv_vfnmsac(t6785, 1.7320508075688772, t6784, vl1);
        s2745 = __riscv_vfmul(s2799, 0.5, vl1);
        s2800 = __riscv_vfnmsac(t6787, 0.57735026918962584, t6786, vl1);
        s2746 = __riscv_vfmul(s2800, 0.8660254037844386, vl1);
        s2801 = __riscv_vfmacc(t6786, 0.57735026918962584, t6787, vl1);
        s2747 = __riscv_vfmul(s2801, 0.8660254037844386, vl1);
        t6788 = __riscv_vfadd(t6770, t6780, vl1);
        t6789 = __riscv_vfadd(t6771, t6781, vl1);
        t6790 = __riscv_vfsub(t6770, t6780, vl1);
        t6791 = __riscv_vfsub(t6771, t6781, vl1);
        t6792 = __riscv_vfadd(t6774, s2744, vl1);
        t6793 = __riscv_vfadd(t6775, s2745, vl1);
        t6794 = __riscv_vfsub(t6774, s2744, vl1);
        t6795 = __riscv_vfsub(t6775, s2745, vl1);
        t6796 = __riscv_vfadd(t6776, s2746, vl1);
        t6797 = __riscv_vfsub(t6777, s2747, vl1);
        t6798 = __riscv_vfsub(t6776, s2746, vl1);
        t6799 = __riscv_vfadd(t6777, s2747, vl1);
        t6800 = __riscv_vfadd(s2704, s2712, vl1);
        t6801 = __riscv_vfadd(s2705, s2713, vl1);
        t6802 = __riscv_vfadd(s2700, t6800, vl1);
        t6803 = __riscv_vfadd(s2701, t6801, vl1);
        t6804 = __riscv_vfnmsac(s2700, 0.5, t6800, vl1);
        t6805 = __riscv_vfnmsac(s2701, 0.5, t6801, vl1);
        s2748 = __riscv_vfmul(__riscv_vfsub(s2705, s2713, vl1), 0.8660254037844386, vl1);
        s2749 = __riscv_vfmul(__riscv_vfsub(s2704, s2712, vl1), 0.8660254037844386, vl1);
        t6806 = __riscv_vfadd(t6804, s2748, vl1);
        t6807 = __riscv_vfsub(t6805, s2749, vl1);
        t6808 = __riscv_vfsub(t6804, s2748, vl1);
        t6809 = __riscv_vfadd(t6805, s2749, vl1);
        t6810 = __riscv_vfadd(s2720, s2716, vl1);
        t6811 = __riscv_vfadd(s2721, s2717, vl1);
        t6812 = __riscv_vfadd(s2708, t6810, vl1);
        t6813 = __riscv_vfadd(s2709, t6811, vl1);
        t6814 = __riscv_vfnmsac(s2708, 0.5, t6810, vl1);
        t6815 = __riscv_vfnmsac(s2709, 0.5, t6811, vl1);
        s2750 = __riscv_vfmul(__riscv_vfsub(s2721, s2717, vl1), 0.8660254037844386, vl1);
        s2751 = __riscv_vfmul(__riscv_vfsub(s2720, s2716, vl1), 0.8660254037844386, vl1);
        t6816 = __riscv_vfadd(t6814, s2750, vl1);
        t6817 = __riscv_vfsub(t6815, s2751, vl1);
        t6818 = __riscv_vfsub(t6814, s2750, vl1);
        t6819 = __riscv_vfadd(t6815, s2751, vl1);
        s2802 = __riscv_vfmacc(t6816, 1.7320508075688772, t6817, vl1);
        s2752 = __riscv_vfmul(s2802, 0.5, vl1);
        s2803 = __riscv_vfnmsac(t6817, 1.7320508075688772, t6816, vl1);
        s2753 = __riscv_vfmul(s2803, 0.5, vl1);
        s2804 = __riscv_vfnmsac(t6819, 0.57735026918962584, t6818, vl1);
        s2754 = __riscv_vfmul(s2804, 0.8660254037844386, vl1);
        s2805 = __riscv_vfmacc(t6818, 0.57735026918962584, t6819, vl1);
        s2755 = __riscv_vfmul(s2805, 0.8660254037844386, vl1);
        t6820 = __riscv_vfadd(t6802, t6812, vl1);
        t6821 = __riscv_vfadd(t6803, t6813, vl1);
        t6822 = __riscv_vfadd(t6806, s2752, vl1);
        t6823 = __riscv_vfadd(t6807, s2753, vl1);
        t6824 = __riscv_vfsub(t6806, s2752, vl1);
        t6825 = __riscv_vfsub(t6807, s2753, vl1);
        t6826 = __riscv_vfadd(t6808, s2754, vl1);
        t6827 = __riscv_vfsub(t6809, s2755, vl1);
        t6828 = __riscv_vfsub(t6808, s2754, vl1);
        t6829 = __riscv_vfadd(t6809, s2755, vl1);
        t6830 = __riscv_vfadd(s2696, t6820, vl1);
        t6831 = __riscv_vfadd(s2697, t6821, vl1);
        t6832 = __riscv_vfnmsac(s2696, 0.16666666666666666, t6820, vl1);
        t6833 = __riscv_vfnmsac(s2697, 0.16666666666666666, t6821, vl1);
        s2806 = __riscv_vfmacc(t6822, 0.41908315722758338, t6823, vl1);
        s2756 = __riscv_vfmul(s2806, 0.4066888930575896, vl1);
        s2807 = __riscv_vfnmsac(t6823, 0.41908315722758338, t6822, vl1);
        s2757 = __riscv_vfmul(s2807, 0.4066888930575896, vl1);
        s2808 = __riscv_vfmacc(t6826, 0.49572725516748389, t6827, vl1);
        s2758 = __riscv_vfmul(s2808, 0.39507823426270006, vl1);
        s2809 = __riscv_vfnmsac(t6827, 0.49572725516748389, t6826, vl1);
        s2759 = __riscv_vfmul(s2809, 0.39507823426270006, vl1);
        s2760 = __riscv_vfmul(__riscv_vfsub(t6803, t6813, vl1), 0.44095855184409843, vl1);
        s2761 = __riscv_vfmul(__riscv_vfsub(t6802, t6812, vl1), 0.44095855184409843, vl1);
        s2810 = __riscv_vfnmsac(t6824, 0.49572725516748389, t6825, vl1);
        s2762 = __riscv_vfmul(s2810, 0.39507823426270006, vl1);
        s2811 = __riscv_vfmacc(t6824, 2.0172382889501304, t6825, vl1);
        s2763 = __riscv_vfmul(s2811, 0.1958510486474645, vl1);
        s2812 = __riscv_vfnmsac(t6829, 2.386161273135941, t6828, vl1);
        s2764 = __riscv_vfmul(s2812, 0.17043646531196566, vl1);
        s2813 = __riscv_vfmacc(t6828, 2.386161273135941, t6829, vl1);
        s2765 = __riscv_vfmul(s2813, 0.17043646531196566, vl1);
        t6834 = __riscv_vfadd(s2758, s2762, vl1);
        t6835 = __riscv_vfadd(s2759, s2763, vl1);
        t6836 = __riscv_vfadd(t6832, t6834, vl1);
        t6837 = __riscv_vfadd(t6833, t6835, vl1);
        t6838 = __riscv_vfnmsac(t6832, 0.5, t6834, vl1);
        t6839 = __riscv_vfnmsac(t6833, 0.5, t6835, vl1);
        s2766 = __riscv_vfmul(__riscv_vfsub(s2759, s2763, vl1), 0.8660254037844386, vl1);
        s2767 = __riscv_vfmul(__riscv_vfsub(s2758, s2762, vl1), 0.8660254037844386, vl1);
        t6840 = __riscv_vfadd(t6838, s2766, vl1);
        t6841 = __riscv_vfsub(t6839, s2767, vl1);
        t6842 = __riscv_vfsub(t6838, s2766, vl1);
        t6843 = __riscv_vfadd(t6839, s2767, vl1);
        t6844 = __riscv_vfadd(s2760, s2764, vl1);
        t6845 = __riscv_vfadd(s2761, s2765, vl1);
        t6846 = __riscv_vfadd(s2756, t6844, vl1);
        t6847 = __riscv_vfsub(s2757, t6845, vl1);
        t6848 = __riscv_vfnmsac(s2756, 0.5, t6844, vl1);
        t6849 = __riscv_vfmacc(s2757, 0.5, t6845, vl1);
        s2768 = __riscv_vfmul(__riscv_vfsub(s2765, s2761, vl1), 0.8660254037844386, vl1);
        s2769 = __riscv_vfmul(__riscv_vfsub(s2760, s2764, vl1), 0.8660254037844386, vl1);
        t6850 = __riscv_vfadd(t6848, s2768, vl1);
        t6851 = __riscv_vfsub(t6849, s2769, vl1);
        t6852 = __riscv_vfsub(t6848, s2768, vl1);
        t6853 = __riscv_vfadd(t6849, s2769, vl1);
        s2814 = __riscv_vfmacc(t6850, 1.7320508075688772, t6851, vl1);
        s2770 = __riscv_vfmul(s2814, 0.5, vl1);
        s2815 = __riscv_vfnmsac(t6851, 1.7320508075688772, t6850, vl1);
        s2771 = __riscv_vfmul(s2815, 0.5, vl1);
        s2816 = __riscv_vfnmsac(t6853, 0.57735026918962584, t6852, vl1);
        s2772 = __riscv_vfmul(s2816, 0.8660254037844386, vl1);
        s2817 = __riscv_vfmacc(t6852, 0.57735026918962584, t6853, vl1);
        s2773 = __riscv_vfmul(s2817, 0.8660254037844386, vl1);
        t6854 = __riscv_vfadd(t6836, t6846, vl1);
        t6855 = __riscv_vfadd(t6837, t6847, vl1);
        t6856 = __riscv_vfsub(t6836, t6846, vl1);
        t6857 = __riscv_vfsub(t6837, t6847, vl1);
        s2818 = __riscv_vfmacc(t6854, 0.48157461880752861, t6855, vl1);
        s2774 = __riscv_vfmul(s2818, 0.90096886790241915, vl1);
        s2819 = __riscv_vfnmsac(t6855, 0.48157461880752861, t6854, vl1);
        s2775 = __riscv_vfmul(s2819, 0.90096886790241915, vl1);
        s2820 = __riscv_vfnmsac(t6857, 2.0765213965723368, t6856, vl1);
        s2776 = __riscv_vfmul(s2820, 0.43388373911755812, vl1);
        s2821 = __riscv_vfmacc(t6856, 2.0765213965723368, t6857, vl1);
        s2777 = __riscv_vfmul(s2821, 0.43388373911755812, vl1);
        t6858 = __riscv_vfadd(t6840, s2770, vl1);
        t6859 = __riscv_vfadd(t6841, s2771, vl1);
        t6860 = __riscv_vfsub(t6840, s2770, vl1);
        t6861 = __riscv_vfsub(t6841, s2771, vl1);
        s2822 = __riscv_vfmacc(t6858, 4.381286267534823, t6859, vl1);
        s2778 = __riscv_vfmul(s2822, 0.22252093395631439, vl1);
        s2823 = __riscv_vfnmsac(t6859, 4.381286267534823, t6858, vl1);
        s2779 = __riscv_vfmul(s2823, 0.22252093395631439, vl1);
        s2824 = __riscv_vfnmsac(t6861, 0.22824347439014991, t6860, vl1);
        s2780 = __riscv_vfmul(s2824, 0.97492791218182362, vl1);
        s2825 = __riscv_vfmacc(t6860, 0.22824347439014991, t6861, vl1);
        s2781 = __riscv_vfmul(s2825, 0.97492791218182362, vl1);
        t6862 = __riscv_vfadd(t6842, s2772, vl1);
        t6863 = __riscv_vfsub(t6843, s2773, vl1);
        t6864 = __riscv_vfsub(t6842, s2772, vl1);
        t6865 = __riscv_vfadd(t6843, s2773, vl1);
        s2826 = __riscv_vfmacc(t6862, 1.253960337662704, t6863, vl1);
        s2782 = __riscv_vfmul(s2826, 0.62348980185873348, vl1);
        s2827 = __riscv_vfnmsac(t6863, 1.253960337662704, t6862, vl1);
        s2783 = __riscv_vfmul(s2827, 0.62348980185873348, vl1);
        s2828 = __riscv_vfnmsac(t6865, 0.79747338888240393, t6864, vl1);
        s2784 = __riscv_vfmul(s2828, 0.7818314824680298, vl1);
        s2829 = __riscv_vfmacc(t6864, 0.79747338888240393, t6865, vl1);
        s2785 = __riscv_vfmul(s2829, 0.7818314824680298, vl1);
        r239 = __riscv_vset(__riscv_vset(rvvx2_15, 0, __riscv_vfadd(t6764, t6830, vl1)), 1, __riscv_vfadd(t6765, t6831, vl1));
        __riscv_vsseg2e64((Y + ((2)*(k1))), r239, vl1);
        r240 = __riscv_vset(__riscv_vset(rvvx2_16, 0, __riscv_vfadd(t6788, s2774, vl1)), 1, __riscv_vfadd(t6789, s2775, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + m1)))), r240, vl1);
        r241 = __riscv_vset(__riscv_vset(rvvx2_17, 0, __riscv_vfadd(t6796, s2782, vl1)), 1, __riscv_vfadd(t6797, s2783, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((2)*(m1)))))), r241, vl1);
        r242 = __riscv_vset(__riscv_vset(rvvx2_18, 0, __riscv_vfadd(t6792, s2778, vl1)), 1, __riscv_vfadd(t6793, s2779, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((3)*(m1)))))), r242, vl1);
        r243 = __riscv_vset(__riscv_vset(rvvx2_19, 0, __riscv_vfadd(t6794, s2780, vl1)), 1, __riscv_vfsub(t6795, s2781, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((4)*(m1)))))), r243, vl1);
        r244 = __riscv_vset(__riscv_vset(rvvx2_20, 0, __riscv_vfadd(t6798, s2784, vl1)), 1, __riscv_vfsub(t6799, s2785, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((5)*(m1)))))), r244, vl1);
        r245 = __riscv_vset(__riscv_vset(rvvx2_21, 0, __riscv_vfadd(t6790, s2776, vl1)), 1, __riscv_vfsub(t6791, s2777, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((6)*(m1)))))), r245, vl1);
        r246 = __riscv_vset(__riscv_vset(rvvx2_22, 0, __riscv_vfsub(t6764, t6830, vl1)), 1, __riscv_vfsub(t6765, t6831, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((7)*(m1)))))), r246, vl1);
        r247 = __riscv_vset(__riscv_vset(rvvx2_23, 0, __riscv_vfsub(t6788, s2774, vl1)), 1, __riscv_vfsub(t6789, s2775, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((8)*(m1)))))), r247, vl1);
        r248 = __riscv_vset(__riscv_vset(rvvx2_24, 0, __riscv_vfsub(t6796, s2782, vl1)), 1, __riscv_vfsub(t6797, s2783, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((9)*(m1)))))), r248, vl1);
        r249 = __riscv_vset(__riscv_vset(rvvx2_25, 0, __riscv_vfsub(t6792, s2778, vl1)), 1, __riscv_vfsub(t6793, s2779, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((10)*(m1)))))), r249, vl1);
        r250 = __riscv_vset(__riscv_vset(rvvx2_26, 0, __riscv_vfsub(t6794, s2780, vl1)), 1, __riscv_vfadd(t6795, s2781, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((11)*(m1)))))), r250, vl1);
        r251 = __riscv_vset(__riscv_vset(rvvx2_27, 0, __riscv_vfsub(t6798, s2784, vl1)), 1, __riscv_vfadd(t6799, s2785, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((12)*(m1)))))), r251, vl1);
        r252 = __riscv_vset(__riscv_vset(rvvx2_28, 0, __riscv_vfsub(t6790, s2776, vl1)), 1, __riscv_vfadd(t6791, s2777, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((13)*(m1)))))), r252, vl1);
    }
}
