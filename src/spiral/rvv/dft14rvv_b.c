// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft14b_(double *Y, double *X, double *TW1, int *lp1, int *mp1) {
    double a3703, a3704, a3705, a3706, a3707, a3708, a3709, a3710, 
            a3711, a3712, a3713, a3714, a3715, a3716, a3717, a3718, 
            a3719, a3720, a3721, a3722, a3723, a3724, a3725, a3726, 
            a3727, a3728;
    int a3701, a3702, j1, l1, m1;
    vfloat64m1x2_t r225, r226, r227, r228, r229, r230, r231, r232, 
            r233, r234, r235, r236, r237, r238, r239, r240, 
            r241, r242, r243, r244, r245, r246, r247, r248, 
            r249, r250, r251, r252, rvvx2_15, rvvx2_16, rvvx2_17, rvvx2_18, 
            rvvx2_19, rvvx2_20, rvvx2_21, rvvx2_22, rvvx2_23, rvvx2_24, rvvx2_25, rvvx2_26, 
            rvvx2_27, rvvx2_28;
    vfloat64m1_t  s2772, s2773, s2774, s2775, s2776, s2777, s2778, s2779, 
            s2780, s2781, s2782, s2783, s2784, s2785, s2786, s2787, 
            s2788, s2789, s2790, s2791, s2792, s2793, s2794, s2795, 
            s2796, s2797, s2798, s2799, s2800, s2801, s2802, s2803, 
            s2804, s2805, s2806, s2807, s2808, s2809, s2810, s2811, 
            s2812, s2813, s2814, s2815, s2816, s2817, s2818, s2819, 
            s2820, s2821, s2822, s2823, s2824, s2825, s2826, s2827, 
            s2828, s2829, s2830, s2831, s2832, s2833, s2834, s2835, 
            s2836, s2837, s2838, s2839, s2840, s2841, s2842, s2843, 
            s2844, s2845, s2846, s2847, s2848, s2849, s2850, s2851, 
            s2852, s2853, s2854, s2855, s2856, s2857, s2858, s2859, 
            s2860, s2861, s2862, s2863, s2864, s2865, s2866, s2867, 
            s2868, s2869, s2870, s2871, s2872, s2873, s2874, s2875, 
            s2876, s2877, s2878, s2879, s2880, s2881, s2882, s2883, 
            s2884, s2885, s2886, s2887, s2888, s2889, s2890, s2891, 
            s2892, s2893, s2894, s2895, s2896, s2897, s2898, s2899, 
            s2900, s2901, s2902, s2903, s2904, s2905, s2906, s2907, 
            s2908, s2909, s2910, s2911, s2912, s2913, s2914, s2915, 
            s2916, s2917, s2918, s2919, s2920, s2921, s2922, s2923, 
            s2924, s2925, s2926, s2927, s2928, s2929, s2930, s2931, 
            s2932, s2933, t6735, t6736, t6737, t6738, t6739, t6740, 
            t6741, t6742, t6743, t6744, t6745, t6746, t6747, t6748, 
            t6749, t6750, t6751, t6752, t6753, t6754, t6755, t6756, 
            t6757, t6758, t6759, t6760, t6761, t6762, t6763, t6764, 
            t6765, t6766, t6767, t6768, t6769, t6770, t6771, t6772, 
            t6773, t6774, t6775, t6776, t6777, t6778, t6779, t6780, 
            t6781, t6782, t6783, t6784, t6785, t6786, t6787, t6788, 
            t6789, t6790, t6791, t6792, t6793, t6794, t6795, t6796, 
            t6797, t6798, t6799, t6800, t6801, t6802, t6803, t6804, 
            t6805, t6806, t6807, t6808, t6809, t6810, t6811, t6812, 
            t6813, t6814, t6815, t6816, t6817, t6818, t6819, t6820, 
            t6821, t6822, t6823, t6824, t6825, t6826, t6827, t6828, 
            t6829, t6830, t6831, t6832, t6833, t6834, t6835, t6836, 
            t6837, t6838, t6839, t6840, t6841, t6842, t6843, t6844, 
            t6845, t6846, t6847, t6848, t6849, t6850, t6851, t6852, 
            t6853, t6854, t6855, t6856, t6857, t6858, t6859, t6860, 
            t6861, t6862, t6863, t6864, t6865, t6866;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for(int j1 = 1; j1 < l1; j1++) {
        for (size_t k1 = 0; k1 < m1; k1 += vl1) {
            vl1 = __riscv_vsetvl_e64m1(m1 - k1);
            a3701 = (k1 + ((j1)*(m1)));
            r225 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(a3701))), vl1);
            s2772 = __riscv_vget_f64m1(r225, 0);
            s2773 = __riscv_vget_f64m1(r225, 1);
            r226 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a3701 + ((l1)*(m1)))))), vl1);
            s2774 = __riscv_vget_f64m1(r226, 0);
            s2775 = __riscv_vget_f64m1(r226, 1);
            r227 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a3701 + ((((2)*(l1)))*(m1)))))), vl1);
            s2776 = __riscv_vget_f64m1(r227, 0);
            s2777 = __riscv_vget_f64m1(r227, 1);
            r228 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a3701 + ((((3)*(l1)))*(m1)))))), vl1);
            s2778 = __riscv_vget_f64m1(r228, 0);
            s2779 = __riscv_vget_f64m1(r228, 1);
            r229 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a3701 + ((((4)*(l1)))*(m1)))))), vl1);
            s2780 = __riscv_vget_f64m1(r229, 0);
            s2781 = __riscv_vget_f64m1(r229, 1);
            r230 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a3701 + ((((5)*(l1)))*(m1)))))), vl1);
            s2782 = __riscv_vget_f64m1(r230, 0);
            s2783 = __riscv_vget_f64m1(r230, 1);
            r231 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a3701 + ((((6)*(l1)))*(m1)))))), vl1);
            s2784 = __riscv_vget_f64m1(r231, 0);
            s2785 = __riscv_vget_f64m1(r231, 1);
            r232 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a3701 + ((((7)*(l1)))*(m1)))))), vl1);
            s2786 = __riscv_vget_f64m1(r232, 0);
            s2787 = __riscv_vget_f64m1(r232, 1);
            r233 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a3701 + ((((8)*(l1)))*(m1)))))), vl1);
            s2788 = __riscv_vget_f64m1(r233, 0);
            s2789 = __riscv_vget_f64m1(r233, 1);
            r234 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a3701 + ((((9)*(l1)))*(m1)))))), vl1);
            s2790 = __riscv_vget_f64m1(r234, 0);
            s2791 = __riscv_vget_f64m1(r234, 1);
            r235 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a3701 + ((((10)*(l1)))*(m1)))))), vl1);
            s2792 = __riscv_vget_f64m1(r235, 0);
            s2793 = __riscv_vget_f64m1(r235, 1);
            r236 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a3701 + ((((11)*(l1)))*(m1)))))), vl1);
            s2794 = __riscv_vget_f64m1(r236, 0);
            s2795 = __riscv_vget_f64m1(r236, 1);
            r237 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a3701 + ((((12)*(l1)))*(m1)))))), vl1);
            s2796 = __riscv_vget_f64m1(r237, 0);
            s2797 = __riscv_vget_f64m1(r237, 1);
            r238 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a3701 + ((((13)*(l1)))*(m1)))))), vl1);
            s2798 = __riscv_vget_f64m1(r238, 0);
            s2799 = __riscv_vget_f64m1(r238, 1);
            t6735 = __riscv_vfadd(s2780, s2788, vl1);
            t6736 = __riscv_vfadd(s2781, s2789, vl1);
            t6737 = __riscv_vfadd(s2776, t6735, vl1);
            t6738 = __riscv_vfadd(s2777, t6736, vl1);
            t6739 = __riscv_vfnmsac(s2776, 0.5, t6735, vl1);
            t6740 = __riscv_vfnmsac(s2777, 0.5, t6736, vl1);
            s2800 = __riscv_vfmul(__riscv_vfsub(s2781, s2789, vl1), 0.8660254037844386, vl1);
            s2801 = __riscv_vfmul(__riscv_vfsub(s2780, s2788, vl1), 0.8660254037844386, vl1);
            t6741 = __riscv_vfadd(t6739, s2800, vl1);
            t6742 = __riscv_vfsub(t6740, s2801, vl1);
            t6743 = __riscv_vfsub(t6739, s2800, vl1);
            t6744 = __riscv_vfadd(t6740, s2801, vl1);
            t6745 = __riscv_vfadd(s2796, s2792, vl1);
            t6746 = __riscv_vfadd(s2797, s2793, vl1);
            t6747 = __riscv_vfadd(s2784, t6745, vl1);
            t6748 = __riscv_vfadd(s2785, t6746, vl1);
            t6749 = __riscv_vfnmsac(s2784, 0.5, t6745, vl1);
            t6750 = __riscv_vfnmsac(s2785, 0.5, t6746, vl1);
            s2802 = __riscv_vfmul(__riscv_vfsub(s2797, s2793, vl1), 0.8660254037844386, vl1);
            s2803 = __riscv_vfmul(__riscv_vfsub(s2796, s2792, vl1), 0.8660254037844386, vl1);
            t6751 = __riscv_vfadd(t6749, s2802, vl1);
            t6752 = __riscv_vfsub(t6750, s2803, vl1);
            t6753 = __riscv_vfsub(t6749, s2802, vl1);
            t6754 = __riscv_vfadd(t6750, s2803, vl1);
            s2890 = __riscv_vfmacc(t6751, 1.7320508075688772, t6752, vl1);
            s2804 = __riscv_vfmul(s2890, 0.5, vl1);
            s2891 = __riscv_vfnmsac(t6752, 1.7320508075688772, t6751, vl1);
            s2805 = __riscv_vfmul(s2891, 0.5, vl1);
            s2892 = __riscv_vfnmsac(t6754, 0.57735026918962584, t6753, vl1);
            s2806 = __riscv_vfmul(s2892, 0.8660254037844386, vl1);
            s2893 = __riscv_vfmacc(t6753, 0.57735026918962584, t6754, vl1);
            s2807 = __riscv_vfmul(s2893, 0.8660254037844386, vl1);
            t6755 = __riscv_vfadd(t6737, t6747, vl1);
            t6756 = __riscv_vfadd(t6738, t6748, vl1);
            t6757 = __riscv_vfadd(t6741, s2804, vl1);
            t6758 = __riscv_vfadd(t6742, s2805, vl1);
            t6759 = __riscv_vfsub(t6741, s2804, vl1);
            t6760 = __riscv_vfsub(t6742, s2805, vl1);
            t6761 = __riscv_vfadd(t6743, s2806, vl1);
            t6762 = __riscv_vfsub(t6744, s2807, vl1);
            t6763 = __riscv_vfsub(t6743, s2806, vl1);
            t6764 = __riscv_vfadd(t6744, s2807, vl1);
            t6765 = __riscv_vfadd(s2772, t6755, vl1);
            t6766 = __riscv_vfadd(s2773, t6756, vl1);
            t6767 = __riscv_vfnmsac(s2772, 0.16666666666666666, t6755, vl1);
            t6768 = __riscv_vfnmsac(s2773, 0.16666666666666666, t6756, vl1);
            s2894 = __riscv_vfmacc(t6757, 0.41908315722758338, t6758, vl1);
            s2808 = __riscv_vfmul(s2894, 0.4066888930575896, vl1);
            s2895 = __riscv_vfnmsac(t6758, 0.41908315722758338, t6757, vl1);
            s2809 = __riscv_vfmul(s2895, 0.4066888930575896, vl1);
            s2896 = __riscv_vfmacc(t6761, 0.49572725516748389, t6762, vl1);
            s2810 = __riscv_vfmul(s2896, 0.39507823426270006, vl1);
            s2897 = __riscv_vfnmsac(t6762, 0.49572725516748389, t6761, vl1);
            s2811 = __riscv_vfmul(s2897, 0.39507823426270006, vl1);
            s2812 = __riscv_vfmul(__riscv_vfsub(t6738, t6748, vl1), 0.44095855184409843, vl1);
            s2813 = __riscv_vfmul(__riscv_vfsub(t6737, t6747, vl1), 0.44095855184409843, vl1);
            s2898 = __riscv_vfnmsac(t6759, 0.49572725516748389, t6760, vl1);
            s2814 = __riscv_vfmul(s2898, 0.39507823426270006, vl1);
            s2899 = __riscv_vfmacc(t6759, 2.0172382889501304, t6760, vl1);
            s2815 = __riscv_vfmul(s2899, 0.1958510486474645, vl1);
            s2900 = __riscv_vfnmsac(t6764, 2.386161273135941, t6763, vl1);
            s2816 = __riscv_vfmul(s2900, 0.17043646531196566, vl1);
            s2901 = __riscv_vfmacc(t6763, 2.386161273135941, t6764, vl1);
            s2817 = __riscv_vfmul(s2901, 0.17043646531196566, vl1);
            t6769 = __riscv_vfadd(s2810, s2814, vl1);
            t6770 = __riscv_vfadd(s2811, s2815, vl1);
            t6771 = __riscv_vfadd(t6767, t6769, vl1);
            t6772 = __riscv_vfadd(t6768, t6770, vl1);
            t6773 = __riscv_vfnmsac(t6767, 0.5, t6769, vl1);
            t6774 = __riscv_vfnmsac(t6768, 0.5, t6770, vl1);
            s2818 = __riscv_vfmul(__riscv_vfsub(s2811, s2815, vl1), 0.8660254037844386, vl1);
            s2819 = __riscv_vfmul(__riscv_vfsub(s2810, s2814, vl1), 0.8660254037844386, vl1);
            t6775 = __riscv_vfadd(t6773, s2818, vl1);
            t6776 = __riscv_vfsub(t6774, s2819, vl1);
            t6777 = __riscv_vfsub(t6773, s2818, vl1);
            t6778 = __riscv_vfadd(t6774, s2819, vl1);
            t6779 = __riscv_vfadd(s2812, s2816, vl1);
            t6780 = __riscv_vfadd(s2813, s2817, vl1);
            t6781 = __riscv_vfadd(s2808, t6779, vl1);
            t6782 = __riscv_vfsub(s2809, t6780, vl1);
            t6783 = __riscv_vfnmsac(s2808, 0.5, t6779, vl1);
            t6784 = __riscv_vfmacc(s2809, 0.5, t6780, vl1);
            s2820 = __riscv_vfmul(__riscv_vfsub(s2817, s2813, vl1), 0.8660254037844386, vl1);
            s2821 = __riscv_vfmul(__riscv_vfsub(s2812, s2816, vl1), 0.8660254037844386, vl1);
            t6785 = __riscv_vfadd(t6783, s2820, vl1);
            t6786 = __riscv_vfsub(t6784, s2821, vl1);
            t6787 = __riscv_vfsub(t6783, s2820, vl1);
            t6788 = __riscv_vfadd(t6784, s2821, vl1);
            s2902 = __riscv_vfmacc(t6785, 1.7320508075688772, t6786, vl1);
            s2822 = __riscv_vfmul(s2902, 0.5, vl1);
            s2903 = __riscv_vfnmsac(t6786, 1.7320508075688772, t6785, vl1);
            s2823 = __riscv_vfmul(s2903, 0.5, vl1);
            s2904 = __riscv_vfnmsac(t6788, 0.57735026918962584, t6787, vl1);
            s2824 = __riscv_vfmul(s2904, 0.8660254037844386, vl1);
            s2905 = __riscv_vfmacc(t6787, 0.57735026918962584, t6788, vl1);
            s2825 = __riscv_vfmul(s2905, 0.8660254037844386, vl1);
            t6789 = __riscv_vfadd(t6771, t6781, vl1);
            t6790 = __riscv_vfadd(t6772, t6782, vl1);
            t6791 = __riscv_vfsub(t6771, t6781, vl1);
            t6792 = __riscv_vfsub(t6772, t6782, vl1);
            t6793 = __riscv_vfadd(t6775, s2822, vl1);
            t6794 = __riscv_vfadd(t6776, s2823, vl1);
            t6795 = __riscv_vfsub(t6775, s2822, vl1);
            t6796 = __riscv_vfsub(t6776, s2823, vl1);
            t6797 = __riscv_vfadd(t6777, s2824, vl1);
            t6798 = __riscv_vfsub(t6778, s2825, vl1);
            t6799 = __riscv_vfsub(t6777, s2824, vl1);
            t6800 = __riscv_vfadd(t6778, s2825, vl1);
            t6801 = __riscv_vfadd(s2782, s2790, vl1);
            t6802 = __riscv_vfadd(s2783, s2791, vl1);
            t6803 = __riscv_vfadd(s2778, t6801, vl1);
            t6804 = __riscv_vfadd(s2779, t6802, vl1);
            t6805 = __riscv_vfnmsac(s2778, 0.5, t6801, vl1);
            t6806 = __riscv_vfnmsac(s2779, 0.5, t6802, vl1);
            s2826 = __riscv_vfmul(__riscv_vfsub(s2783, s2791, vl1), 0.8660254037844386, vl1);
            s2827 = __riscv_vfmul(__riscv_vfsub(s2782, s2790, vl1), 0.8660254037844386, vl1);
            t6807 = __riscv_vfadd(t6805, s2826, vl1);
            t6808 = __riscv_vfsub(t6806, s2827, vl1);
            t6809 = __riscv_vfsub(t6805, s2826, vl1);
            t6810 = __riscv_vfadd(t6806, s2827, vl1);
            t6811 = __riscv_vfadd(s2798, s2794, vl1);
            t6812 = __riscv_vfadd(s2799, s2795, vl1);
            t6813 = __riscv_vfadd(s2786, t6811, vl1);
            t6814 = __riscv_vfadd(s2787, t6812, vl1);
            t6815 = __riscv_vfnmsac(s2786, 0.5, t6811, vl1);
            t6816 = __riscv_vfnmsac(s2787, 0.5, t6812, vl1);
            s2828 = __riscv_vfmul(__riscv_vfsub(s2799, s2795, vl1), 0.8660254037844386, vl1);
            s2829 = __riscv_vfmul(__riscv_vfsub(s2798, s2794, vl1), 0.8660254037844386, vl1);
            t6817 = __riscv_vfadd(t6815, s2828, vl1);
            t6818 = __riscv_vfsub(t6816, s2829, vl1);
            t6819 = __riscv_vfsub(t6815, s2828, vl1);
            t6820 = __riscv_vfadd(t6816, s2829, vl1);
            s2906 = __riscv_vfmacc(t6817, 1.7320508075688772, t6818, vl1);
            s2830 = __riscv_vfmul(s2906, 0.5, vl1);
            s2907 = __riscv_vfnmsac(t6818, 1.7320508075688772, t6817, vl1);
            s2831 = __riscv_vfmul(s2907, 0.5, vl1);
            s2908 = __riscv_vfnmsac(t6820, 0.57735026918962584, t6819, vl1);
            s2832 = __riscv_vfmul(s2908, 0.8660254037844386, vl1);
            s2909 = __riscv_vfmacc(t6819, 0.57735026918962584, t6820, vl1);
            s2833 = __riscv_vfmul(s2909, 0.8660254037844386, vl1);
            t6821 = __riscv_vfadd(t6803, t6813, vl1);
            t6822 = __riscv_vfadd(t6804, t6814, vl1);
            t6823 = __riscv_vfadd(t6807, s2830, vl1);
            t6824 = __riscv_vfadd(t6808, s2831, vl1);
            t6825 = __riscv_vfsub(t6807, s2830, vl1);
            t6826 = __riscv_vfsub(t6808, s2831, vl1);
            t6827 = __riscv_vfadd(t6809, s2832, vl1);
            t6828 = __riscv_vfsub(t6810, s2833, vl1);
            t6829 = __riscv_vfsub(t6809, s2832, vl1);
            t6830 = __riscv_vfadd(t6810, s2833, vl1);
            t6831 = __riscv_vfadd(s2774, t6821, vl1);
            t6832 = __riscv_vfadd(s2775, t6822, vl1);
            t6833 = __riscv_vfnmsac(s2774, 0.16666666666666666, t6821, vl1);
            t6834 = __riscv_vfnmsac(s2775, 0.16666666666666666, t6822, vl1);
            s2910 = __riscv_vfmacc(t6823, 0.41908315722758338, t6824, vl1);
            s2834 = __riscv_vfmul(s2910, 0.4066888930575896, vl1);
            s2911 = __riscv_vfnmsac(t6824, 0.41908315722758338, t6823, vl1);
            s2835 = __riscv_vfmul(s2911, 0.4066888930575896, vl1);
            s2912 = __riscv_vfmacc(t6827, 0.49572725516748389, t6828, vl1);
            s2836 = __riscv_vfmul(s2912, 0.39507823426270006, vl1);
            s2913 = __riscv_vfnmsac(t6828, 0.49572725516748389, t6827, vl1);
            s2837 = __riscv_vfmul(s2913, 0.39507823426270006, vl1);
            s2838 = __riscv_vfmul(__riscv_vfsub(t6804, t6814, vl1), 0.44095855184409843, vl1);
            s2839 = __riscv_vfmul(__riscv_vfsub(t6803, t6813, vl1), 0.44095855184409843, vl1);
            s2914 = __riscv_vfnmsac(t6825, 0.49572725516748389, t6826, vl1);
            s2840 = __riscv_vfmul(s2914, 0.39507823426270006, vl1);
            s2915 = __riscv_vfmacc(t6825, 2.0172382889501304, t6826, vl1);
            s2841 = __riscv_vfmul(s2915, 0.1958510486474645, vl1);
            s2916 = __riscv_vfnmsac(t6830, 2.386161273135941, t6829, vl1);
            s2842 = __riscv_vfmul(s2916, 0.17043646531196566, vl1);
            s2917 = __riscv_vfmacc(t6829, 2.386161273135941, t6830, vl1);
            s2843 = __riscv_vfmul(s2917, 0.17043646531196566, vl1);
            t6835 = __riscv_vfadd(s2836, s2840, vl1);
            t6836 = __riscv_vfadd(s2837, s2841, vl1);
            t6837 = __riscv_vfadd(t6833, t6835, vl1);
            t6838 = __riscv_vfadd(t6834, t6836, vl1);
            t6839 = __riscv_vfnmsac(t6833, 0.5, t6835, vl1);
            t6840 = __riscv_vfnmsac(t6834, 0.5, t6836, vl1);
            s2844 = __riscv_vfmul(__riscv_vfsub(s2837, s2841, vl1), 0.8660254037844386, vl1);
            s2845 = __riscv_vfmul(__riscv_vfsub(s2836, s2840, vl1), 0.8660254037844386, vl1);
            t6841 = __riscv_vfadd(t6839, s2844, vl1);
            t6842 = __riscv_vfsub(t6840, s2845, vl1);
            t6843 = __riscv_vfsub(t6839, s2844, vl1);
            t6844 = __riscv_vfadd(t6840, s2845, vl1);
            t6845 = __riscv_vfadd(s2838, s2842, vl1);
            t6846 = __riscv_vfadd(s2839, s2843, vl1);
            t6847 = __riscv_vfadd(s2834, t6845, vl1);
            t6848 = __riscv_vfsub(s2835, t6846, vl1);
            t6849 = __riscv_vfnmsac(s2834, 0.5, t6845, vl1);
            t6850 = __riscv_vfmacc(s2835, 0.5, t6846, vl1);
            s2846 = __riscv_vfmul(__riscv_vfsub(s2843, s2839, vl1), 0.8660254037844386, vl1);
            s2847 = __riscv_vfmul(__riscv_vfsub(s2838, s2842, vl1), 0.8660254037844386, vl1);
            t6851 = __riscv_vfadd(t6849, s2846, vl1);
            t6852 = __riscv_vfsub(t6850, s2847, vl1);
            t6853 = __riscv_vfsub(t6849, s2846, vl1);
            t6854 = __riscv_vfadd(t6850, s2847, vl1);
            s2918 = __riscv_vfmacc(t6851, 1.7320508075688772, t6852, vl1);
            s2848 = __riscv_vfmul(s2918, 0.5, vl1);
            s2919 = __riscv_vfnmsac(t6852, 1.7320508075688772, t6851, vl1);
            s2849 = __riscv_vfmul(s2919, 0.5, vl1);
            s2920 = __riscv_vfnmsac(t6854, 0.57735026918962584, t6853, vl1);
            s2850 = __riscv_vfmul(s2920, 0.8660254037844386, vl1);
            s2921 = __riscv_vfmacc(t6853, 0.57735026918962584, t6854, vl1);
            s2851 = __riscv_vfmul(s2921, 0.8660254037844386, vl1);
            t6855 = __riscv_vfadd(t6837, t6847, vl1);
            t6856 = __riscv_vfadd(t6838, t6848, vl1);
            t6857 = __riscv_vfsub(t6837, t6847, vl1);
            t6858 = __riscv_vfsub(t6838, t6848, vl1);
            s2922 = __riscv_vfmacc(t6855, 0.48157461880752861, t6856, vl1);
            s2852 = __riscv_vfmul(s2922, 0.90096886790241915, vl1);
            s2923 = __riscv_vfnmsac(t6856, 0.48157461880752861, t6855, vl1);
            s2853 = __riscv_vfmul(s2923, 0.90096886790241915, vl1);
            s2924 = __riscv_vfnmsac(t6858, 2.0765213965723368, t6857, vl1);
            s2854 = __riscv_vfmul(s2924, 0.43388373911755812, vl1);
            s2925 = __riscv_vfmacc(t6857, 2.0765213965723368, t6858, vl1);
            s2855 = __riscv_vfmul(s2925, 0.43388373911755812, vl1);
            t6859 = __riscv_vfadd(t6841, s2848, vl1);
            t6860 = __riscv_vfadd(t6842, s2849, vl1);
            t6861 = __riscv_vfsub(t6841, s2848, vl1);
            t6862 = __riscv_vfsub(t6842, s2849, vl1);
            s2926 = __riscv_vfmacc(t6859, 4.381286267534823, t6860, vl1);
            s2856 = __riscv_vfmul(s2926, 0.22252093395631439, vl1);
            s2927 = __riscv_vfnmsac(t6860, 4.381286267534823, t6859, vl1);
            s2857 = __riscv_vfmul(s2927, 0.22252093395631439, vl1);
            s2928 = __riscv_vfnmsac(t6862, 0.22824347439014991, t6861, vl1);
            s2858 = __riscv_vfmul(s2928, 0.97492791218182362, vl1);
            s2929 = __riscv_vfmacc(t6861, 0.22824347439014991, t6862, vl1);
            s2859 = __riscv_vfmul(s2929, 0.97492791218182362, vl1);
            t6863 = __riscv_vfadd(t6843, s2850, vl1);
            t6864 = __riscv_vfsub(t6844, s2851, vl1);
            t6865 = __riscv_vfsub(t6843, s2850, vl1);
            t6866 = __riscv_vfadd(t6844, s2851, vl1);
            s2930 = __riscv_vfmacc(t6863, 1.253960337662704, t6864, vl1);
            s2860 = __riscv_vfmul(s2930, 0.62348980185873348, vl1);
            s2931 = __riscv_vfnmsac(t6864, 1.253960337662704, t6863, vl1);
            s2861 = __riscv_vfmul(s2931, 0.62348980185873348, vl1);
            s2932 = __riscv_vfnmsac(t6866, 0.79747338888240393, t6865, vl1);
            s2862 = __riscv_vfmul(s2932, 0.7818314824680298, vl1);
            s2933 = __riscv_vfmacc(t6865, 0.79747338888240393, t6866, vl1);
            s2863 = __riscv_vfmul(s2933, 0.7818314824680298, vl1);
            s2864 = __riscv_vfsub(t6765, t6831, vl1);
            s2865 = __riscv_vfsub(t6766, t6832, vl1);
            s2866 = __riscv_vfadd(t6789, s2852, vl1);
            s2867 = __riscv_vfadd(t6790, s2853, vl1);
            s2868 = __riscv_vfsub(t6789, s2852, vl1);
            s2869 = __riscv_vfsub(t6790, s2853, vl1);
            s2870 = __riscv_vfadd(t6797, s2860, vl1);
            s2871 = __riscv_vfadd(t6798, s2861, vl1);
            s2872 = __riscv_vfsub(t6797, s2860, vl1);
            s2873 = __riscv_vfsub(t6798, s2861, vl1);
            s2874 = __riscv_vfadd(t6793, s2856, vl1);
            s2875 = __riscv_vfadd(t6794, s2857, vl1);
            s2876 = __riscv_vfsub(t6793, s2856, vl1);
            s2877 = __riscv_vfsub(t6794, s2857, vl1);
            s2878 = __riscv_vfadd(t6795, s2858, vl1);
            s2879 = __riscv_vfsub(t6796, s2859, vl1);
            s2880 = __riscv_vfsub(t6795, s2858, vl1);
            s2881 = __riscv_vfadd(t6796, s2859, vl1);
            s2882 = __riscv_vfadd(t6799, s2862, vl1);
            s2883 = __riscv_vfsub(t6800, s2863, vl1);
            s2884 = __riscv_vfsub(t6799, s2862, vl1);
            s2885 = __riscv_vfadd(t6800, s2863, vl1);
            s2886 = __riscv_vfadd(t6791, s2854, vl1);
            s2887 = __riscv_vfsub(t6792, s2855, vl1);
            s2888 = __riscv_vfsub(t6791, s2854, vl1);
            s2889 = __riscv_vfadd(t6792, s2855, vl1);
            a3702 = ((26)*(j1));
            a3703 = TW1[a3702];
            a3704 = TW1[(a3702 + 1)];
            a3705 = TW1[(a3702 + 2)];
            a3706 = TW1[(a3702 + 3)];
            a3707 = TW1[(a3702 + 4)];
            a3708 = TW1[(a3702 + 5)];
            a3709 = TW1[(a3702 + 6)];
            a3710 = TW1[(a3702 + 7)];
            a3711 = TW1[(a3702 + 8)];
            a3712 = TW1[(a3702 + 9)];
            a3713 = TW1[(a3702 + 10)];
            a3714 = TW1[(a3702 + 11)];
            a3715 = TW1[(a3702 + 12)];
            a3716 = TW1[(a3702 + 13)];
            a3717 = TW1[(a3702 + 14)];
            a3718 = TW1[(a3702 + 15)];
            a3719 = TW1[(a3702 + 16)];
            a3720 = TW1[(a3702 + 17)];
            a3721 = TW1[(a3702 + 18)];
            a3722 = TW1[(a3702 + 19)];
            a3723 = TW1[(a3702 + 20)];
            a3724 = TW1[(a3702 + 21)];
            a3725 = TW1[(a3702 + 22)];
            a3726 = TW1[(a3702 + 23)];
            a3727 = TW1[(a3702 + 24)];
            a3728 = TW1[(a3702 + 25)];
            r239 = __riscv_vset(__riscv_vset(rvvx2_15, 0, __riscv_vfadd(t6765, t6831, vl1)), 1, __riscv_vfadd(t6766, t6832, vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)))))), r239, vl1);
            r240 = __riscv_vset(__riscv_vset(rvvx2_16, 0, __riscv_vfsub(__riscv_vfmul(s2866, a3703, vl1), __riscv_vfmul(s2867, a3704, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s2866, a3704, vl1), __riscv_vfmul(s2867, a3703, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)) + m1)))), r240, vl1);
            r241 = __riscv_vset(__riscv_vset(rvvx2_17, 0, __riscv_vfsub(__riscv_vfmul(s2870, a3705, vl1), __riscv_vfmul(s2871, a3706, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s2870, a3706, vl1), __riscv_vfmul(s2871, a3705, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)) + ((2)*(m1)))))), r241, vl1);
            r242 = __riscv_vset(__riscv_vset(rvvx2_18, 0, __riscv_vfsub(__riscv_vfmul(s2874, a3707, vl1), __riscv_vfmul(s2875, a3708, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s2874, a3708, vl1), __riscv_vfmul(s2875, a3707, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)) + ((3)*(m1)))))), r242, vl1);
            r243 = __riscv_vset(__riscv_vset(rvvx2_19, 0, __riscv_vfsub(__riscv_vfmul(s2878, a3709, vl1), __riscv_vfmul(s2879, a3710, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s2878, a3710, vl1), __riscv_vfmul(s2879, a3709, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)) + ((4)*(m1)))))), r243, vl1);
            r244 = __riscv_vset(__riscv_vset(rvvx2_20, 0, __riscv_vfsub(__riscv_vfmul(s2882, a3711, vl1), __riscv_vfmul(s2883, a3712, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s2882, a3712, vl1), __riscv_vfmul(s2883, a3711, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)) + ((5)*(m1)))))), r244, vl1);
            r245 = __riscv_vset(__riscv_vset(rvvx2_21, 0, __riscv_vfsub(__riscv_vfmul(s2886, a3713, vl1), __riscv_vfmul(s2887, a3714, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s2886, a3714, vl1), __riscv_vfmul(s2887, a3713, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)) + ((6)*(m1)))))), r245, vl1);
            r246 = __riscv_vset(__riscv_vset(rvvx2_22, 0, __riscv_vfsub(__riscv_vfmul(s2864, a3715, vl1), __riscv_vfmul(s2865, a3716, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s2864, a3716, vl1), __riscv_vfmul(s2865, a3715, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)) + ((7)*(m1)))))), r246, vl1);
            r247 = __riscv_vset(__riscv_vset(rvvx2_23, 0, __riscv_vfsub(__riscv_vfmul(s2868, a3717, vl1), __riscv_vfmul(s2869, a3718, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s2868, a3718, vl1), __riscv_vfmul(s2869, a3717, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)) + ((8)*(m1)))))), r247, vl1);
            r248 = __riscv_vset(__riscv_vset(rvvx2_24, 0, __riscv_vfsub(__riscv_vfmul(s2872, a3719, vl1), __riscv_vfmul(s2873, a3720, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s2872, a3720, vl1), __riscv_vfmul(s2873, a3719, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)) + ((9)*(m1)))))), r248, vl1);
            r249 = __riscv_vset(__riscv_vset(rvvx2_25, 0, __riscv_vfsub(__riscv_vfmul(s2876, a3721, vl1), __riscv_vfmul(s2877, a3722, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s2876, a3722, vl1), __riscv_vfmul(s2877, a3721, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)) + ((10)*(m1)))))), r249, vl1);
            r250 = __riscv_vset(__riscv_vset(rvvx2_26, 0, __riscv_vfsub(__riscv_vfmul(s2880, a3723, vl1), __riscv_vfmul(s2881, a3724, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s2880, a3724, vl1), __riscv_vfmul(s2881, a3723, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)) + ((11)*(m1)))))), r250, vl1);
            r251 = __riscv_vset(__riscv_vset(rvvx2_27, 0, __riscv_vfsub(__riscv_vfmul(s2884, a3725, vl1), __riscv_vfmul(s2885, a3726, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s2884, a3726, vl1), __riscv_vfmul(s2885, a3725, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)) + ((12)*(m1)))))), r251, vl1);
            r252 = __riscv_vset(__riscv_vset(rvvx2_28, 0, __riscv_vfsub(__riscv_vfmul(s2888, a3727, vl1), __riscv_vfmul(s2889, a3728, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s2888, a3728, vl1), __riscv_vfmul(s2889, a3727, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((14)*(j1)))*(m1)) + ((13)*(m1)))))), r252, vl1);
        }
    }
}
