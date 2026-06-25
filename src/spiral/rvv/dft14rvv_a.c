// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft14a_(double *Y, double *X, double *TW1, int *lp1) {
    int l1;
    double *a3574;
    vfloat64m1x2_t r100, r101, r102, r103, r104, r105, r106, r107, 
            r108, r109, r110, r111, r112, r99;
    vfloat64m1_t  a3575, a3576, a3577, a3578, a3579, a3580, a3581, a3582, 
            a3583, a3584, a3585, a3586, a3587, a3588, a3589, a3590, 
            a3591, a3592, a3593, a3594, a3595, a3596, a3597, a3598, 
            a3599, a3600, s2800, s2801, s2802, s2803, s2804, s2805, 
            s2806, s2807, s2808, s2809, s2810, s2811, s2812, s2813, 
            s2814, s2815, s2816, s2817, s2818, s2819, s2820, s2821, 
            s2822, s2823, s2824, s2825, s2826, s2827, s2828, s2829, 
            s2830, s2831, s2832, s2833, s2834, s2835, s2836, s2837, 
            s2838, s2839, s2840, s2841, s2842, s2843, s2844, s2845, 
            s2846, s2847, s2848, s2849, s2850, s2851, s2852, s2853, 
            s2854, s2855, s2856, s2857, s2858, s2859, s2860, s2861, 
            s2862, s2863, s2864, s2865, s2866, s2867, s2868, s2869, 
            s2870, s2871, s2872, s2873, s2874, s2875, s2876, s2877, 
            s2878, s2879, s2880, s2881, s2882, s2883, s2884, s2885, 
            s2886, s2887, s2888, s2889, s2890, s2891, s2892, s2893, 
            s2894, s2895, s2896, s2897, s2898, s2899, s2900, s2901, 
            s2902, s2903, s2904, s2905, s2906, s2907, s2908, s2909, 
            s2910, s2911, s2912, s2913, s2914, s2915, s2916, s2917, 
            s2918, s2919, s2920, s2921, s2922, s2923, s2924, s2925, 
            s2926, s2927, s2928, s2929, s2930, s2931, s2932, s2933, 
            s2934, s2935, s2936, s2937, s2938, s2939, s2940, s2941, 
            s2942, s2943, s2944, s2945, s2946, s2947, s2948, s2949, 
            s2950, s2951, s2952, s2953, s2954, s2955, s2956, s2957, 
            s2958, s2959, s2960, s2961, s2962, s2963, s2964, s2965, 
            s2966, s2967, s2968, s2969, s2970, s2971, s2972, s2973, 
            s2974, s2975, s2976, s2977, s2978, s2979, s2980, s2981, 
            s2982, s2983, s2984, s2985, s2986, s2987, s2988, s2989, 
            t6735, t6736, t6737, t6738, t6739, t6740, t6741, t6742, 
            t6743, t6744, t6745, t6746, t6747, t6748, t6749, t6750, 
            t6751, t6752, t6753, t6754, t6755, t6756, t6757, t6758, 
            t6759, t6760, t6761, t6762, t6763, t6764, t6765, t6766, 
            t6767, t6768, t6769, t6770, t6771, t6772, t6773, t6774, 
            t6775, t6776, t6777, t6778, t6779, t6780, t6781, t6782, 
            t6783, t6784, t6785, t6786, t6787, t6788, t6789, t6790, 
            t6791, t6792, t6793, t6794, t6795, t6796, t6797, t6798, 
            t6799, t6800, t6801, t6802, t6803, t6804, t6805, t6806, 
            t6807, t6808, t6809, t6810, t6811, t6812, t6813, t6814, 
            t6815, t6816, t6817, t6818, t6819, t6820, t6821, t6822, 
            t6823, t6824, t6825, t6826, t6827, t6828, t6829, t6830, 
            t6831, t6832, t6833, t6834, t6835, t6836, t6837, t6838, 
            t6839, t6840, t6841, t6842, t6843, t6844, t6845, t6846, 
            t6847, t6848, t6849, t6850, t6851, t6852, t6853, t6854, 
            t6855, t6856, t6857, t6858, t6859, t6860, t6861, t6862, 
            t6863, t6864, t6865, t6866;
    size_t vl1;
    l1 = *(lp1);
    for (size_t j1 = 0; j1 < l1; j1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(l1 - j1);
        r99 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(j1))), vl1);
        s2800 = __riscv_vget_f64m1(r99, 0);
        s2801 = __riscv_vget_f64m1(r99, 1);
        r100 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + l1)))), vl1);
        s2802 = __riscv_vget_f64m1(r100, 0);
        s2803 = __riscv_vget_f64m1(r100, 1);
        r101 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((2)*(l1)))))), vl1);
        s2804 = __riscv_vget_f64m1(r101, 0);
        s2805 = __riscv_vget_f64m1(r101, 1);
        r102 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((3)*(l1)))))), vl1);
        s2806 = __riscv_vget_f64m1(r102, 0);
        s2807 = __riscv_vget_f64m1(r102, 1);
        r103 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((4)*(l1)))))), vl1);
        s2808 = __riscv_vget_f64m1(r103, 0);
        s2809 = __riscv_vget_f64m1(r103, 1);
        r104 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((5)*(l1)))))), vl1);
        s2810 = __riscv_vget_f64m1(r104, 0);
        s2811 = __riscv_vget_f64m1(r104, 1);
        r105 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((6)*(l1)))))), vl1);
        s2812 = __riscv_vget_f64m1(r105, 0);
        s2813 = __riscv_vget_f64m1(r105, 1);
        r106 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((7)*(l1)))))), vl1);
        s2814 = __riscv_vget_f64m1(r106, 0);
        s2815 = __riscv_vget_f64m1(r106, 1);
        r107 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((8)*(l1)))))), vl1);
        s2816 = __riscv_vget_f64m1(r107, 0);
        s2817 = __riscv_vget_f64m1(r107, 1);
        r108 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((9)*(l1)))))), vl1);
        s2818 = __riscv_vget_f64m1(r108, 0);
        s2819 = __riscv_vget_f64m1(r108, 1);
        r109 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((10)*(l1)))))), vl1);
        s2820 = __riscv_vget_f64m1(r109, 0);
        s2821 = __riscv_vget_f64m1(r109, 1);
        r110 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((11)*(l1)))))), vl1);
        s2822 = __riscv_vget_f64m1(r110, 0);
        s2823 = __riscv_vget_f64m1(r110, 1);
        r111 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((12)*(l1)))))), vl1);
        s2824 = __riscv_vget_f64m1(r111, 0);
        s2825 = __riscv_vget_f64m1(r111, 1);
        r112 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((13)*(l1)))))), vl1);
        s2826 = __riscv_vget_f64m1(r112, 0);
        s2827 = __riscv_vget_f64m1(r112, 1);
        t6735 = __riscv_vfadd(s2808, s2816, vl1);
        t6736 = __riscv_vfadd(s2809, s2817, vl1);
        t6737 = __riscv_vfadd(s2804, t6735, vl1);
        t6738 = __riscv_vfadd(s2805, t6736, vl1);
        t6739 = __riscv_vfnmsac(s2804, 0.5, t6735, vl1);
        t6740 = __riscv_vfnmsac(s2805, 0.5, t6736, vl1);
        s2828 = __riscv_vfmul(__riscv_vfsub(s2809, s2817, vl1), 0.8660254037844386, vl1);
        s2829 = __riscv_vfmul(__riscv_vfsub(s2808, s2816, vl1), 0.8660254037844386, vl1);
        t6741 = __riscv_vfadd(t6739, s2828, vl1);
        t6742 = __riscv_vfsub(t6740, s2829, vl1);
        t6743 = __riscv_vfsub(t6739, s2828, vl1);
        t6744 = __riscv_vfadd(t6740, s2829, vl1);
        t6745 = __riscv_vfadd(s2824, s2820, vl1);
        t6746 = __riscv_vfadd(s2825, s2821, vl1);
        t6747 = __riscv_vfadd(s2812, t6745, vl1);
        t6748 = __riscv_vfadd(s2813, t6746, vl1);
        t6749 = __riscv_vfnmsac(s2812, 0.5, t6745, vl1);
        t6750 = __riscv_vfnmsac(s2813, 0.5, t6746, vl1);
        s2830 = __riscv_vfmul(__riscv_vfsub(s2825, s2821, vl1), 0.8660254037844386, vl1);
        s2831 = __riscv_vfmul(__riscv_vfsub(s2824, s2820, vl1), 0.8660254037844386, vl1);
        t6751 = __riscv_vfadd(t6749, s2830, vl1);
        t6752 = __riscv_vfsub(t6750, s2831, vl1);
        t6753 = __riscv_vfsub(t6749, s2830, vl1);
        t6754 = __riscv_vfadd(t6750, s2831, vl1);
        s2946 = __riscv_vfmacc(t6751, 1.7320508075688772, t6752, vl1);
        s2832 = __riscv_vfmul(s2946, 0.5, vl1);
        s2947 = __riscv_vfnmsac(t6752, 1.7320508075688772, t6751, vl1);
        s2833 = __riscv_vfmul(s2947, 0.5, vl1);
        s2948 = __riscv_vfnmsac(t6754, 0.57735026918962584, t6753, vl1);
        s2834 = __riscv_vfmul(s2948, 0.8660254037844386, vl1);
        s2949 = __riscv_vfmacc(t6753, 0.57735026918962584, t6754, vl1);
        s2835 = __riscv_vfmul(s2949, 0.8660254037844386, vl1);
        t6755 = __riscv_vfadd(t6737, t6747, vl1);
        t6756 = __riscv_vfadd(t6738, t6748, vl1);
        t6757 = __riscv_vfadd(t6741, s2832, vl1);
        t6758 = __riscv_vfadd(t6742, s2833, vl1);
        t6759 = __riscv_vfsub(t6741, s2832, vl1);
        t6760 = __riscv_vfsub(t6742, s2833, vl1);
        t6761 = __riscv_vfadd(t6743, s2834, vl1);
        t6762 = __riscv_vfsub(t6744, s2835, vl1);
        t6763 = __riscv_vfsub(t6743, s2834, vl1);
        t6764 = __riscv_vfadd(t6744, s2835, vl1);
        t6765 = __riscv_vfadd(s2800, t6755, vl1);
        t6766 = __riscv_vfadd(s2801, t6756, vl1);
        t6767 = __riscv_vfnmsac(s2800, 0.16666666666666666, t6755, vl1);
        t6768 = __riscv_vfnmsac(s2801, 0.16666666666666666, t6756, vl1);
        s2950 = __riscv_vfmacc(t6757, 0.41908315722758338, t6758, vl1);
        s2836 = __riscv_vfmul(s2950, 0.4066888930575896, vl1);
        s2951 = __riscv_vfnmsac(t6758, 0.41908315722758338, t6757, vl1);
        s2837 = __riscv_vfmul(s2951, 0.4066888930575896, vl1);
        s2952 = __riscv_vfmacc(t6761, 0.49572725516748389, t6762, vl1);
        s2838 = __riscv_vfmul(s2952, 0.39507823426270006, vl1);
        s2953 = __riscv_vfnmsac(t6762, 0.49572725516748389, t6761, vl1);
        s2839 = __riscv_vfmul(s2953, 0.39507823426270006, vl1);
        s2840 = __riscv_vfmul(__riscv_vfsub(t6738, t6748, vl1), 0.44095855184409843, vl1);
        s2841 = __riscv_vfmul(__riscv_vfsub(t6737, t6747, vl1), 0.44095855184409843, vl1);
        s2954 = __riscv_vfnmsac(t6759, 0.49572725516748389, t6760, vl1);
        s2842 = __riscv_vfmul(s2954, 0.39507823426270006, vl1);
        s2955 = __riscv_vfmacc(t6759, 2.0172382889501304, t6760, vl1);
        s2843 = __riscv_vfmul(s2955, 0.1958510486474645, vl1);
        s2956 = __riscv_vfnmsac(t6764, 2.386161273135941, t6763, vl1);
        s2844 = __riscv_vfmul(s2956, 0.17043646531196566, vl1);
        s2957 = __riscv_vfmacc(t6763, 2.386161273135941, t6764, vl1);
        s2845 = __riscv_vfmul(s2957, 0.17043646531196566, vl1);
        t6769 = __riscv_vfadd(s2838, s2842, vl1);
        t6770 = __riscv_vfadd(s2839, s2843, vl1);
        t6771 = __riscv_vfadd(t6767, t6769, vl1);
        t6772 = __riscv_vfadd(t6768, t6770, vl1);
        t6773 = __riscv_vfnmsac(t6767, 0.5, t6769, vl1);
        t6774 = __riscv_vfnmsac(t6768, 0.5, t6770, vl1);
        s2846 = __riscv_vfmul(__riscv_vfsub(s2839, s2843, vl1), 0.8660254037844386, vl1);
        s2847 = __riscv_vfmul(__riscv_vfsub(s2838, s2842, vl1), 0.8660254037844386, vl1);
        t6775 = __riscv_vfadd(t6773, s2846, vl1);
        t6776 = __riscv_vfsub(t6774, s2847, vl1);
        t6777 = __riscv_vfsub(t6773, s2846, vl1);
        t6778 = __riscv_vfadd(t6774, s2847, vl1);
        t6779 = __riscv_vfadd(s2840, s2844, vl1);
        t6780 = __riscv_vfadd(s2841, s2845, vl1);
        t6781 = __riscv_vfadd(s2836, t6779, vl1);
        t6782 = __riscv_vfsub(s2837, t6780, vl1);
        t6783 = __riscv_vfnmsac(s2836, 0.5, t6779, vl1);
        t6784 = __riscv_vfmacc(s2837, 0.5, t6780, vl1);
        s2848 = __riscv_vfmul(__riscv_vfsub(s2845, s2841, vl1), 0.8660254037844386, vl1);
        s2849 = __riscv_vfmul(__riscv_vfsub(s2840, s2844, vl1), 0.8660254037844386, vl1);
        t6785 = __riscv_vfadd(t6783, s2848, vl1);
        t6786 = __riscv_vfsub(t6784, s2849, vl1);
        t6787 = __riscv_vfsub(t6783, s2848, vl1);
        t6788 = __riscv_vfadd(t6784, s2849, vl1);
        s2958 = __riscv_vfmacc(t6785, 1.7320508075688772, t6786, vl1);
        s2850 = __riscv_vfmul(s2958, 0.5, vl1);
        s2959 = __riscv_vfnmsac(t6786, 1.7320508075688772, t6785, vl1);
        s2851 = __riscv_vfmul(s2959, 0.5, vl1);
        s2960 = __riscv_vfnmsac(t6788, 0.57735026918962584, t6787, vl1);
        s2852 = __riscv_vfmul(s2960, 0.8660254037844386, vl1);
        s2961 = __riscv_vfmacc(t6787, 0.57735026918962584, t6788, vl1);
        s2853 = __riscv_vfmul(s2961, 0.8660254037844386, vl1);
        t6789 = __riscv_vfadd(t6771, t6781, vl1);
        t6790 = __riscv_vfadd(t6772, t6782, vl1);
        t6791 = __riscv_vfsub(t6771, t6781, vl1);
        t6792 = __riscv_vfsub(t6772, t6782, vl1);
        t6793 = __riscv_vfadd(t6775, s2850, vl1);
        t6794 = __riscv_vfadd(t6776, s2851, vl1);
        t6795 = __riscv_vfsub(t6775, s2850, vl1);
        t6796 = __riscv_vfsub(t6776, s2851, vl1);
        t6797 = __riscv_vfadd(t6777, s2852, vl1);
        t6798 = __riscv_vfsub(t6778, s2853, vl1);
        t6799 = __riscv_vfsub(t6777, s2852, vl1);
        t6800 = __riscv_vfadd(t6778, s2853, vl1);
        t6801 = __riscv_vfadd(s2810, s2818, vl1);
        t6802 = __riscv_vfadd(s2811, s2819, vl1);
        t6803 = __riscv_vfadd(s2806, t6801, vl1);
        t6804 = __riscv_vfadd(s2807, t6802, vl1);
        t6805 = __riscv_vfnmsac(s2806, 0.5, t6801, vl1);
        t6806 = __riscv_vfnmsac(s2807, 0.5, t6802, vl1);
        s2854 = __riscv_vfmul(__riscv_vfsub(s2811, s2819, vl1), 0.8660254037844386, vl1);
        s2855 = __riscv_vfmul(__riscv_vfsub(s2810, s2818, vl1), 0.8660254037844386, vl1);
        t6807 = __riscv_vfadd(t6805, s2854, vl1);
        t6808 = __riscv_vfsub(t6806, s2855, vl1);
        t6809 = __riscv_vfsub(t6805, s2854, vl1);
        t6810 = __riscv_vfadd(t6806, s2855, vl1);
        t6811 = __riscv_vfadd(s2826, s2822, vl1);
        t6812 = __riscv_vfadd(s2827, s2823, vl1);
        t6813 = __riscv_vfadd(s2814, t6811, vl1);
        t6814 = __riscv_vfadd(s2815, t6812, vl1);
        t6815 = __riscv_vfnmsac(s2814, 0.5, t6811, vl1);
        t6816 = __riscv_vfnmsac(s2815, 0.5, t6812, vl1);
        s2856 = __riscv_vfmul(__riscv_vfsub(s2827, s2823, vl1), 0.8660254037844386, vl1);
        s2857 = __riscv_vfmul(__riscv_vfsub(s2826, s2822, vl1), 0.8660254037844386, vl1);
        t6817 = __riscv_vfadd(t6815, s2856, vl1);
        t6818 = __riscv_vfsub(t6816, s2857, vl1);
        t6819 = __riscv_vfsub(t6815, s2856, vl1);
        t6820 = __riscv_vfadd(t6816, s2857, vl1);
        s2962 = __riscv_vfmacc(t6817, 1.7320508075688772, t6818, vl1);
        s2858 = __riscv_vfmul(s2962, 0.5, vl1);
        s2963 = __riscv_vfnmsac(t6818, 1.7320508075688772, t6817, vl1);
        s2859 = __riscv_vfmul(s2963, 0.5, vl1);
        s2964 = __riscv_vfnmsac(t6820, 0.57735026918962584, t6819, vl1);
        s2860 = __riscv_vfmul(s2964, 0.8660254037844386, vl1);
        s2965 = __riscv_vfmacc(t6819, 0.57735026918962584, t6820, vl1);
        s2861 = __riscv_vfmul(s2965, 0.8660254037844386, vl1);
        t6821 = __riscv_vfadd(t6803, t6813, vl1);
        t6822 = __riscv_vfadd(t6804, t6814, vl1);
        t6823 = __riscv_vfadd(t6807, s2858, vl1);
        t6824 = __riscv_vfadd(t6808, s2859, vl1);
        t6825 = __riscv_vfsub(t6807, s2858, vl1);
        t6826 = __riscv_vfsub(t6808, s2859, vl1);
        t6827 = __riscv_vfadd(t6809, s2860, vl1);
        t6828 = __riscv_vfsub(t6810, s2861, vl1);
        t6829 = __riscv_vfsub(t6809, s2860, vl1);
        t6830 = __riscv_vfadd(t6810, s2861, vl1);
        t6831 = __riscv_vfadd(s2802, t6821, vl1);
        t6832 = __riscv_vfadd(s2803, t6822, vl1);
        t6833 = __riscv_vfnmsac(s2802, 0.16666666666666666, t6821, vl1);
        t6834 = __riscv_vfnmsac(s2803, 0.16666666666666666, t6822, vl1);
        s2966 = __riscv_vfmacc(t6823, 0.41908315722758338, t6824, vl1);
        s2862 = __riscv_vfmul(s2966, 0.4066888930575896, vl1);
        s2967 = __riscv_vfnmsac(t6824, 0.41908315722758338, t6823, vl1);
        s2863 = __riscv_vfmul(s2967, 0.4066888930575896, vl1);
        s2968 = __riscv_vfmacc(t6827, 0.49572725516748389, t6828, vl1);
        s2864 = __riscv_vfmul(s2968, 0.39507823426270006, vl1);
        s2969 = __riscv_vfnmsac(t6828, 0.49572725516748389, t6827, vl1);
        s2865 = __riscv_vfmul(s2969, 0.39507823426270006, vl1);
        s2866 = __riscv_vfmul(__riscv_vfsub(t6804, t6814, vl1), 0.44095855184409843, vl1);
        s2867 = __riscv_vfmul(__riscv_vfsub(t6803, t6813, vl1), 0.44095855184409843, vl1);
        s2970 = __riscv_vfnmsac(t6825, 0.49572725516748389, t6826, vl1);
        s2868 = __riscv_vfmul(s2970, 0.39507823426270006, vl1);
        s2971 = __riscv_vfmacc(t6825, 2.0172382889501304, t6826, vl1);
        s2869 = __riscv_vfmul(s2971, 0.1958510486474645, vl1);
        s2972 = __riscv_vfnmsac(t6830, 2.386161273135941, t6829, vl1);
        s2870 = __riscv_vfmul(s2972, 0.17043646531196566, vl1);
        s2973 = __riscv_vfmacc(t6829, 2.386161273135941, t6830, vl1);
        s2871 = __riscv_vfmul(s2973, 0.17043646531196566, vl1);
        t6835 = __riscv_vfadd(s2864, s2868, vl1);
        t6836 = __riscv_vfadd(s2865, s2869, vl1);
        t6837 = __riscv_vfadd(t6833, t6835, vl1);
        t6838 = __riscv_vfadd(t6834, t6836, vl1);
        t6839 = __riscv_vfnmsac(t6833, 0.5, t6835, vl1);
        t6840 = __riscv_vfnmsac(t6834, 0.5, t6836, vl1);
        s2872 = __riscv_vfmul(__riscv_vfsub(s2865, s2869, vl1), 0.8660254037844386, vl1);
        s2873 = __riscv_vfmul(__riscv_vfsub(s2864, s2868, vl1), 0.8660254037844386, vl1);
        t6841 = __riscv_vfadd(t6839, s2872, vl1);
        t6842 = __riscv_vfsub(t6840, s2873, vl1);
        t6843 = __riscv_vfsub(t6839, s2872, vl1);
        t6844 = __riscv_vfadd(t6840, s2873, vl1);
        t6845 = __riscv_vfadd(s2866, s2870, vl1);
        t6846 = __riscv_vfadd(s2867, s2871, vl1);
        t6847 = __riscv_vfadd(s2862, t6845, vl1);
        t6848 = __riscv_vfsub(s2863, t6846, vl1);
        t6849 = __riscv_vfnmsac(s2862, 0.5, t6845, vl1);
        t6850 = __riscv_vfmacc(s2863, 0.5, t6846, vl1);
        s2874 = __riscv_vfmul(__riscv_vfsub(s2871, s2867, vl1), 0.8660254037844386, vl1);
        s2875 = __riscv_vfmul(__riscv_vfsub(s2866, s2870, vl1), 0.8660254037844386, vl1);
        t6851 = __riscv_vfadd(t6849, s2874, vl1);
        t6852 = __riscv_vfsub(t6850, s2875, vl1);
        t6853 = __riscv_vfsub(t6849, s2874, vl1);
        t6854 = __riscv_vfadd(t6850, s2875, vl1);
        s2974 = __riscv_vfmacc(t6851, 1.7320508075688772, t6852, vl1);
        s2876 = __riscv_vfmul(s2974, 0.5, vl1);
        s2975 = __riscv_vfnmsac(t6852, 1.7320508075688772, t6851, vl1);
        s2877 = __riscv_vfmul(s2975, 0.5, vl1);
        s2976 = __riscv_vfnmsac(t6854, 0.57735026918962584, t6853, vl1);
        s2878 = __riscv_vfmul(s2976, 0.8660254037844386, vl1);
        s2977 = __riscv_vfmacc(t6853, 0.57735026918962584, t6854, vl1);
        s2879 = __riscv_vfmul(s2977, 0.8660254037844386, vl1);
        t6855 = __riscv_vfadd(t6837, t6847, vl1);
        t6856 = __riscv_vfadd(t6838, t6848, vl1);
        t6857 = __riscv_vfsub(t6837, t6847, vl1);
        t6858 = __riscv_vfsub(t6838, t6848, vl1);
        s2978 = __riscv_vfmacc(t6855, 0.48157461880752861, t6856, vl1);
        s2880 = __riscv_vfmul(s2978, 0.90096886790241915, vl1);
        s2979 = __riscv_vfnmsac(t6856, 0.48157461880752861, t6855, vl1);
        s2881 = __riscv_vfmul(s2979, 0.90096886790241915, vl1);
        s2980 = __riscv_vfnmsac(t6858, 2.0765213965723368, t6857, vl1);
        s2882 = __riscv_vfmul(s2980, 0.43388373911755812, vl1);
        s2981 = __riscv_vfmacc(t6857, 2.0765213965723368, t6858, vl1);
        s2883 = __riscv_vfmul(s2981, 0.43388373911755812, vl1);
        t6859 = __riscv_vfadd(t6841, s2876, vl1);
        t6860 = __riscv_vfadd(t6842, s2877, vl1);
        t6861 = __riscv_vfsub(t6841, s2876, vl1);
        t6862 = __riscv_vfsub(t6842, s2877, vl1);
        s2982 = __riscv_vfmacc(t6859, 4.381286267534823, t6860, vl1);
        s2884 = __riscv_vfmul(s2982, 0.22252093395631439, vl1);
        s2983 = __riscv_vfnmsac(t6860, 4.381286267534823, t6859, vl1);
        s2885 = __riscv_vfmul(s2983, 0.22252093395631439, vl1);
        s2984 = __riscv_vfnmsac(t6862, 0.22824347439014991, t6861, vl1);
        s2886 = __riscv_vfmul(s2984, 0.97492791218182362, vl1);
        s2985 = __riscv_vfmacc(t6861, 0.22824347439014991, t6862, vl1);
        s2887 = __riscv_vfmul(s2985, 0.97492791218182362, vl1);
        t6863 = __riscv_vfadd(t6843, s2878, vl1);
        t6864 = __riscv_vfsub(t6844, s2879, vl1);
        t6865 = __riscv_vfsub(t6843, s2878, vl1);
        t6866 = __riscv_vfadd(t6844, s2879, vl1);
        s2986 = __riscv_vfmacc(t6863, 1.253960337662704, t6864, vl1);
        s2888 = __riscv_vfmul(s2986, 0.62348980185873348, vl1);
        s2987 = __riscv_vfnmsac(t6864, 1.253960337662704, t6863, vl1);
        s2889 = __riscv_vfmul(s2987, 0.62348980185873348, vl1);
        s2988 = __riscv_vfnmsac(t6866, 0.79747338888240393, t6865, vl1);
        s2890 = __riscv_vfmul(s2988, 0.7818314824680298, vl1);
        s2989 = __riscv_vfmacc(t6865, 0.79747338888240393, t6866, vl1);
        s2891 = __riscv_vfmul(s2989, 0.7818314824680298, vl1);
        s2892 = __riscv_vfadd(t6765, t6831, vl1);
        s2893 = __riscv_vfadd(t6766, t6832, vl1);
        s2894 = __riscv_vfsub(t6765, t6831, vl1);
        s2895 = __riscv_vfsub(t6766, t6832, vl1);
        s2896 = __riscv_vfadd(t6789, s2880, vl1);
        s2897 = __riscv_vfadd(t6790, s2881, vl1);
        s2898 = __riscv_vfsub(t6789, s2880, vl1);
        s2899 = __riscv_vfsub(t6790, s2881, vl1);
        s2900 = __riscv_vfadd(t6797, s2888, vl1);
        s2901 = __riscv_vfadd(t6798, s2889, vl1);
        s2902 = __riscv_vfsub(t6797, s2888, vl1);
        s2903 = __riscv_vfsub(t6798, s2889, vl1);
        s2904 = __riscv_vfadd(t6793, s2884, vl1);
        s2905 = __riscv_vfadd(t6794, s2885, vl1);
        s2906 = __riscv_vfsub(t6793, s2884, vl1);
        s2907 = __riscv_vfsub(t6794, s2885, vl1);
        s2908 = __riscv_vfadd(t6795, s2886, vl1);
        s2909 = __riscv_vfsub(t6796, s2887, vl1);
        s2910 = __riscv_vfsub(t6795, s2886, vl1);
        s2911 = __riscv_vfadd(t6796, s2887, vl1);
        s2912 = __riscv_vfadd(t6799, s2890, vl1);
        s2913 = __riscv_vfsub(t6800, s2891, vl1);
        s2914 = __riscv_vfsub(t6799, s2890, vl1);
        s2915 = __riscv_vfadd(t6800, s2891, vl1);
        s2916 = __riscv_vfadd(t6791, s2882, vl1);
        s2917 = __riscv_vfsub(t6792, s2883, vl1);
        s2918 = __riscv_vfsub(t6791, s2882, vl1);
        s2919 = __riscv_vfadd(t6792, s2883, vl1);
        a3574 = (TW1 + ((26)*(j1)));
        a3575 = __riscv_vlse64_v_f64m1(a3574, sizeof(double) * 26, vl1);
        a3576 = __riscv_vlse64_v_f64m1((a3574 + 1), sizeof(double) * 26, vl1);
        s2920 = __riscv_vfmsac(__riscv_vfmul(a3576, s2897, vl1), a3575, s2896, vl1);
        s2921 = __riscv_vfmacc(__riscv_vfmul(a3575, s2897, vl1), a3576, s2896, vl1);
        a3577 = __riscv_vlse64_v_f64m1((a3574 + 2), sizeof(double) * 26, vl1);
        a3578 = __riscv_vlse64_v_f64m1((a3574 + 3), sizeof(double) * 26, vl1);
        s2922 = __riscv_vfmsac(__riscv_vfmul(a3578, s2901, vl1), a3577, s2900, vl1);
        s2923 = __riscv_vfmacc(__riscv_vfmul(a3577, s2901, vl1), a3578, s2900, vl1);
        a3579 = __riscv_vlse64_v_f64m1((a3574 + 4), sizeof(double) * 26, vl1);
        a3580 = __riscv_vlse64_v_f64m1((a3574 + 5), sizeof(double) * 26, vl1);
        s2924 = __riscv_vfmsac(__riscv_vfmul(a3580, s2905, vl1), a3579, s2904, vl1);
        s2925 = __riscv_vfmacc(__riscv_vfmul(a3579, s2905, vl1), a3580, s2904, vl1);
        a3581 = __riscv_vlse64_v_f64m1((a3574 + 6), sizeof(double) * 26, vl1);
        a3582 = __riscv_vlse64_v_f64m1((a3574 + 7), sizeof(double) * 26, vl1);
        s2926 = __riscv_vfmsac(__riscv_vfmul(a3582, s2909, vl1), a3581, s2908, vl1);
        s2927 = __riscv_vfmacc(__riscv_vfmul(a3581, s2909, vl1), a3582, s2908, vl1);
        a3583 = __riscv_vlse64_v_f64m1((a3574 + 8), sizeof(double) * 26, vl1);
        a3584 = __riscv_vlse64_v_f64m1((a3574 + 9), sizeof(double) * 26, vl1);
        s2928 = __riscv_vfmsac(__riscv_vfmul(a3584, s2913, vl1), a3583, s2912, vl1);
        s2929 = __riscv_vfmacc(__riscv_vfmul(a3583, s2913, vl1), a3584, s2912, vl1);
        a3585 = __riscv_vlse64_v_f64m1((a3574 + 10), sizeof(double) * 26, vl1);
        a3586 = __riscv_vlse64_v_f64m1((a3574 + 11), sizeof(double) * 26, vl1);
        s2930 = __riscv_vfmsac(__riscv_vfmul(a3586, s2917, vl1), a3585, s2916, vl1);
        s2931 = __riscv_vfmacc(__riscv_vfmul(a3585, s2917, vl1), a3586, s2916, vl1);
        a3587 = __riscv_vlse64_v_f64m1((a3574 + 12), sizeof(double) * 26, vl1);
        a3588 = __riscv_vlse64_v_f64m1((a3574 + 13), sizeof(double) * 26, vl1);
        s2932 = __riscv_vfmsac(__riscv_vfmul(a3588, s2895, vl1), a3587, s2894, vl1);
        s2933 = __riscv_vfmacc(__riscv_vfmul(a3587, s2895, vl1), a3588, s2894, vl1);
        a3589 = __riscv_vlse64_v_f64m1((a3574 + 14), sizeof(double) * 26, vl1);
        a3590 = __riscv_vlse64_v_f64m1((a3574 + 15), sizeof(double) * 26, vl1);
        s2934 = __riscv_vfmsac(__riscv_vfmul(a3590, s2899, vl1), a3589, s2898, vl1);
        s2935 = __riscv_vfmacc(__riscv_vfmul(a3589, s2899, vl1), a3590, s2898, vl1);
        a3591 = __riscv_vlse64_v_f64m1((a3574 + 16), sizeof(double) * 26, vl1);
        a3592 = __riscv_vlse64_v_f64m1((a3574 + 17), sizeof(double) * 26, vl1);
        s2936 = __riscv_vfmsac(__riscv_vfmul(a3592, s2903, vl1), a3591, s2902, vl1);
        s2937 = __riscv_vfmacc(__riscv_vfmul(a3591, s2903, vl1), a3592, s2902, vl1);
        a3593 = __riscv_vlse64_v_f64m1((a3574 + 18), sizeof(double) * 26, vl1);
        a3594 = __riscv_vlse64_v_f64m1((a3574 + 19), sizeof(double) * 26, vl1);
        s2938 = __riscv_vfmsac(__riscv_vfmul(a3594, s2907, vl1), a3593, s2906, vl1);
        s2939 = __riscv_vfmacc(__riscv_vfmul(a3593, s2907, vl1), a3594, s2906, vl1);
        a3595 = __riscv_vlse64_v_f64m1((a3574 + 20), sizeof(double) * 26, vl1);
        a3596 = __riscv_vlse64_v_f64m1((a3574 + 21), sizeof(double) * 26, vl1);
        s2940 = __riscv_vfmsac(__riscv_vfmul(a3596, s2911, vl1), a3595, s2910, vl1);
        s2941 = __riscv_vfmacc(__riscv_vfmul(a3595, s2911, vl1), a3596, s2910, vl1);
        a3597 = __riscv_vlse64_v_f64m1((a3574 + 22), sizeof(double) * 26, vl1);
        a3598 = __riscv_vlse64_v_f64m1((a3574 + 23), sizeof(double) * 26, vl1);
        s2942 = __riscv_vfmsac(__riscv_vfmul(a3598, s2915, vl1), a3597, s2914, vl1);
        s2943 = __riscv_vfmacc(__riscv_vfmul(a3597, s2915, vl1), a3598, s2914, vl1);
        a3599 = __riscv_vlse64_v_f64m1((a3574 + 24), sizeof(double) * 26, vl1);
        a3600 = __riscv_vlse64_v_f64m1((a3574 + 25), sizeof(double) * 26, vl1);
        s2944 = __riscv_vfmsac(__riscv_vfmul(a3600, s2919, vl1), a3599, s2918, vl1);
        s2945 = __riscv_vfmacc(__riscv_vfmul(a3599, s2919, vl1), a3600, s2918, vl1);
        __riscv_vsse64((Y + ((28)*(j1))), sizeof(double) * 28, s2892, vl1);
        __riscv_vsse64((1 + Y + ((28)*(j1))), sizeof(double) * 28, s2893, vl1);
        __riscv_vsse64((2 + Y + ((28)*(j1))), sizeof(double) * 28, s2920, vl1);
        __riscv_vsse64((3 + Y + ((28)*(j1))), sizeof(double) * 28, s2921, vl1);
        __riscv_vsse64((4 + Y + ((28)*(j1))), sizeof(double) * 28, s2922, vl1);
        __riscv_vsse64((5 + Y + ((28)*(j1))), sizeof(double) * 28, s2923, vl1);
        __riscv_vsse64((6 + Y + ((28)*(j1))), sizeof(double) * 28, s2924, vl1);
        __riscv_vsse64((7 + Y + ((28)*(j1))), sizeof(double) * 28, s2925, vl1);
        __riscv_vsse64((8 + Y + ((28)*(j1))), sizeof(double) * 28, s2926, vl1);
        __riscv_vsse64((9 + Y + ((28)*(j1))), sizeof(double) * 28, s2927, vl1);
        __riscv_vsse64((10 + Y + ((28)*(j1))), sizeof(double) * 28, s2928, vl1);
        __riscv_vsse64((11 + Y + ((28)*(j1))), sizeof(double) * 28, s2929, vl1);
        __riscv_vsse64((12 + Y + ((28)*(j1))), sizeof(double) * 28, s2930, vl1);
        __riscv_vsse64((13 + Y + ((28)*(j1))), sizeof(double) * 28, s2931, vl1);
        __riscv_vsse64((14 + Y + ((28)*(j1))), sizeof(double) * 28, s2932, vl1);
        __riscv_vsse64((15 + Y + ((28)*(j1))), sizeof(double) * 28, s2933, vl1);
        __riscv_vsse64((16 + Y + ((28)*(j1))), sizeof(double) * 28, s2934, vl1);
        __riscv_vsse64((17 + Y + ((28)*(j1))), sizeof(double) * 28, s2935, vl1);
        __riscv_vsse64((18 + Y + ((28)*(j1))), sizeof(double) * 28, s2936, vl1);
        __riscv_vsse64((19 + Y + ((28)*(j1))), sizeof(double) * 28, s2937, vl1);
        __riscv_vsse64((20 + Y + ((28)*(j1))), sizeof(double) * 28, s2938, vl1);
        __riscv_vsse64((21 + Y + ((28)*(j1))), sizeof(double) * 28, s2939, vl1);
        __riscv_vsse64((22 + Y + ((28)*(j1))), sizeof(double) * 28, s2940, vl1);
        __riscv_vsse64((23 + Y + ((28)*(j1))), sizeof(double) * 28, s2941, vl1);
        __riscv_vsse64((24 + Y + ((28)*(j1))), sizeof(double) * 28, s2942, vl1);
        __riscv_vsse64((25 + Y + ((28)*(j1))), sizeof(double) * 28, s2943, vl1);
        __riscv_vsse64((26 + Y + ((28)*(j1))), sizeof(double) * 28, s2944, vl1);
        __riscv_vsse64((27 + Y + ((28)*(j1))), sizeof(double) * 28, s2945, vl1);
    }
}
