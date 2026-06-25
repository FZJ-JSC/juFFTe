// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft16b_(double *Y, double *X, double *TW1, int *lp1, int *mp1) {
    double a2125, a2126, a2127, a2128, a2129, a2130, a2131, a2132, 
            a2133, a2134, a2135, a2136, a2137, a2138, a2139, a2140, 
            a2141, a2142, a2143, a2144, a2145, a2146, a2147, a2148, 
            a2149, a2150, a2151, a2152, a2153, a2154;
    int a2115, a2124, j1, l1, m1;
    vfloat64m1x2_t r257, r258, r259, r260, r261, r262, r263, r264, 
            r265, r266, r267, r268, r269, r270, r271, r272, 
            r273, r274, r275, r276, r277, r278, r279, r280, 
            r281, r282, r283, r284, r285, r286, r287, r288, 
            rvvx2_17, rvvx2_18, rvvx2_19, rvvx2_20, rvvx2_21, rvvx2_22, rvvx2_23, rvvx2_24, 
            rvvx2_25, rvvx2_26, rvvx2_27, rvvx2_28, rvvx2_29, rvvx2_30, rvvx2_31, rvvx2_32;
    vfloat64m1_t  a2116, a2117, a2118, a2119, a2120, a2121, a2122, a2123, 
            s812, s813, s814, s815, s816, s817, s818, s819, 
            s820, s821, s822, s823, s824, s825, s826, s827, 
            s828, s829, s830, s831, s832, s833, s834, s835, 
            s836, s837, s838, s839, s840, s841, s842, s843, 
            s844, s845, s846, s847, s848, s849, s850, s851, 
            s852, s853, s854, s855, s856, s857, s858, s859, 
            s860, s861, s862, s863, s864, s865, s866, s867, 
            s868, s869, s870, s871, s872, s873, s874, s875, 
            s876, s877, s878, s879, s880, s881, s882, s883, 
            s884, s885, s886, s887, s888, s889, s890, s891, 
            s892, s893, s894, s895, s896, s897, t3019, t3020, 
            t3021, t3022, t3023, t3024, t3025, t3026, t3027, t3028, 
            t3029, t3030, t3031, t3032, t3033, t3034, t3035, t3036, 
            t3037, t3038, t3039, t3040, t3041, t3042, t3043, t3044, 
            t3045, t3046, t3047, t3048, t3049, t3050, t3051, t3052, 
            t3053, t3054, t3055, t3056, t3057, t3058, t3059, t3060, 
            t3061, t3062, t3063, t3064, t3065, t3066, t3067, t3068, 
            t3069, t3070, t3071, t3072, t3073, t3074, t3075, t3076, 
            t3077, t3078, t3079, t3080, t3081, t3082, t3083, t3084, 
            t3085, t3086, t3087, t3088, t3089, t3090, t3091, t3092, 
            t3093, t3094, t3095, t3096, t3097, t3098, t3099, t3100, 
            t3101, t3102, t3103, t3104, t3105, t3106;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for(int j1 = 1; j1 < l1; j1++) {
        for (size_t k1 = 0; k1 < m1; k1 += vl1) {
            vl1 = __riscv_vsetvl_e64m1(m1 - k1);
            a2115 = (k1 + ((j1)*(m1)));
            r257 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(a2115))), vl1);
            s812 = __riscv_vget_f64m1(r257, 0);
            s813 = __riscv_vget_f64m1(r257, 1);
            r258 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((l1)*(m1)))))), vl1);
            s814 = __riscv_vget_f64m1(r258, 0);
            s815 = __riscv_vget_f64m1(r258, 1);
            r259 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((2)*(l1)))*(m1)))))), vl1);
            s816 = __riscv_vget_f64m1(r259, 0);
            s817 = __riscv_vget_f64m1(r259, 1);
            r260 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((3)*(l1)))*(m1)))))), vl1);
            s818 = __riscv_vget_f64m1(r260, 0);
            s819 = __riscv_vget_f64m1(r260, 1);
            r261 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((4)*(l1)))*(m1)))))), vl1);
            s820 = __riscv_vget_f64m1(r261, 0);
            s821 = __riscv_vget_f64m1(r261, 1);
            r262 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((5)*(l1)))*(m1)))))), vl1);
            s822 = __riscv_vget_f64m1(r262, 0);
            s823 = __riscv_vget_f64m1(r262, 1);
            r263 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((6)*(l1)))*(m1)))))), vl1);
            s824 = __riscv_vget_f64m1(r263, 0);
            s825 = __riscv_vget_f64m1(r263, 1);
            r264 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((7)*(l1)))*(m1)))))), vl1);
            s826 = __riscv_vget_f64m1(r264, 0);
            s827 = __riscv_vget_f64m1(r264, 1);
            r265 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((8)*(l1)))*(m1)))))), vl1);
            s828 = __riscv_vget_f64m1(r265, 0);
            s829 = __riscv_vget_f64m1(r265, 1);
            r266 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((9)*(l1)))*(m1)))))), vl1);
            s830 = __riscv_vget_f64m1(r266, 0);
            s831 = __riscv_vget_f64m1(r266, 1);
            r267 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((10)*(l1)))*(m1)))))), vl1);
            s832 = __riscv_vget_f64m1(r267, 0);
            s833 = __riscv_vget_f64m1(r267, 1);
            r268 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((11)*(l1)))*(m1)))))), vl1);
            s834 = __riscv_vget_f64m1(r268, 0);
            s835 = __riscv_vget_f64m1(r268, 1);
            r269 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((12)*(l1)))*(m1)))))), vl1);
            s836 = __riscv_vget_f64m1(r269, 0);
            s837 = __riscv_vget_f64m1(r269, 1);
            r270 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((13)*(l1)))*(m1)))))), vl1);
            s838 = __riscv_vget_f64m1(r270, 0);
            s839 = __riscv_vget_f64m1(r270, 1);
            r271 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((14)*(l1)))*(m1)))))), vl1);
            s840 = __riscv_vget_f64m1(r271, 0);
            s841 = __riscv_vget_f64m1(r271, 1);
            r272 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a2115 + ((((15)*(l1)))*(m1)))))), vl1);
            s842 = __riscv_vget_f64m1(r272, 0);
            s843 = __riscv_vget_f64m1(r272, 1);
            t3019 = __riscv_vfadd(s812, s828, vl1);
            t3020 = __riscv_vfadd(s813, s829, vl1);
            t3021 = __riscv_vfsub(s812, s828, vl1);
            t3022 = __riscv_vfsub(s813, s829, vl1);
            t3023 = __riscv_vfadd(s820, s836, vl1);
            t3024 = __riscv_vfadd(s821, s837, vl1);
            t3025 = __riscv_vfsub(s820, s836, vl1);
            t3026 = __riscv_vfsub(s821, s837, vl1);
            t3027 = __riscv_vfadd(t3019, t3023, vl1);
            t3028 = __riscv_vfadd(t3020, t3024, vl1);
            t3029 = __riscv_vfsub(t3019, t3023, vl1);
            t3030 = __riscv_vfsub(t3020, t3024, vl1);
            t3031 = __riscv_vfadd(t3021, t3026, vl1);
            t3032 = __riscv_vfsub(t3022, t3025, vl1);
            t3033 = __riscv_vfsub(t3021, t3026, vl1);
            t3034 = __riscv_vfadd(t3022, t3025, vl1);
            t3035 = __riscv_vfadd(s814, s830, vl1);
            t3036 = __riscv_vfadd(s815, s831, vl1);
            t3037 = __riscv_vfsub(s814, s830, vl1);
            t3038 = __riscv_vfsub(s815, s831, vl1);
            t3039 = __riscv_vfadd(s822, s838, vl1);
            t3040 = __riscv_vfadd(s823, s839, vl1);
            t3041 = __riscv_vfsub(s822, s838, vl1);
            t3042 = __riscv_vfsub(s823, s839, vl1);
            t3043 = __riscv_vfadd(t3035, t3039, vl1);
            t3044 = __riscv_vfadd(t3036, t3040, vl1);
            a2116 = __riscv_vfmul(__riscv_vfsub(t3035, t3039, vl1), 0.70710678118654757, vl1);
            a2117 = __riscv_vfmul(__riscv_vfsub(t3036, t3040, vl1), 0.70710678118654757, vl1);
            s844 = __riscv_vfadd(a2116, a2117, vl1);
            s845 = __riscv_vfsub(a2117, a2116, vl1);
            t3045 = __riscv_vfadd(t3037, t3042, vl1);
            t3046 = __riscv_vfsub(t3038, t3041, vl1);
            t3047 = __riscv_vfsub(t3037, t3042, vl1);
            t3048 = __riscv_vfadd(t3038, t3041, vl1);
            s890 = __riscv_vfmacc(t3045, 0.41421356237309509, t3046, vl1);
            s846 = __riscv_vfmul(s890, 0.92387953251128674, vl1);
            s891 = __riscv_vfnmsac(t3046, 0.41421356237309509, t3045, vl1);
            s847 = __riscv_vfmul(s891, 0.92387953251128674, vl1);
            s892 = __riscv_vfmacc(t3047, 2.4142135623730949, t3048, vl1);
            s848 = __riscv_vfmul(s892, 0.38268343236508978, vl1);
            s893 = __riscv_vfnmsac(t3048, 2.4142135623730949, t3047, vl1);
            s849 = __riscv_vfmul(s893, 0.38268343236508978, vl1);
            t3049 = __riscv_vfadd(s816, s832, vl1);
            t3050 = __riscv_vfadd(s817, s833, vl1);
            t3051 = __riscv_vfsub(s816, s832, vl1);
            t3052 = __riscv_vfsub(s817, s833, vl1);
            t3053 = __riscv_vfadd(s824, s840, vl1);
            t3054 = __riscv_vfadd(s825, s841, vl1);
            t3055 = __riscv_vfsub(s824, s840, vl1);
            t3056 = __riscv_vfsub(s825, s841, vl1);
            t3057 = __riscv_vfadd(t3049, t3053, vl1);
            t3058 = __riscv_vfadd(t3050, t3054, vl1);
            t3059 = __riscv_vfsub(t3049, t3053, vl1);
            t3060 = __riscv_vfsub(t3050, t3054, vl1);
            a2118 = __riscv_vfmul(__riscv_vfadd(t3051, t3056, vl1), 0.70710678118654757, vl1);
            a2119 = __riscv_vfmul(__riscv_vfsub(t3052, t3055, vl1), 0.70710678118654757, vl1);
            s850 = __riscv_vfadd(a2118, a2119, vl1);
            s851 = __riscv_vfsub(a2119, a2118, vl1);
            a2120 = __riscv_vfmul(__riscv_vfadd(t3052, t3055, vl1), 0.70710678118654757, vl1);
            a2121 = __riscv_vfmul(__riscv_vfsub(t3051, t3056, vl1), 0.70710678118654757, vl1);
            s852 = __riscv_vfsub(a2120, a2121, vl1);
            s853 = __riscv_vfadd(a2121, a2120, vl1);
            t3061 = __riscv_vfadd(s818, s834, vl1);
            t3062 = __riscv_vfadd(s819, s835, vl1);
            t3063 = __riscv_vfsub(s818, s834, vl1);
            t3064 = __riscv_vfsub(s819, s835, vl1);
            t3065 = __riscv_vfadd(s826, s842, vl1);
            t3066 = __riscv_vfadd(s827, s843, vl1);
            t3067 = __riscv_vfsub(s826, s842, vl1);
            t3068 = __riscv_vfsub(s827, s843, vl1);
            t3069 = __riscv_vfadd(t3061, t3065, vl1);
            t3070 = __riscv_vfadd(t3062, t3066, vl1);
            a2122 = __riscv_vfmul(__riscv_vfsub(t3062, t3066, vl1), 0.70710678118654757, vl1);
            a2123 = __riscv_vfmul(__riscv_vfsub(t3061, t3065, vl1), 0.70710678118654757, vl1);
            s854 = __riscv_vfsub(a2122, a2123, vl1);
            s855 = __riscv_vfadd(a2123, a2122, vl1);
            t3071 = __riscv_vfadd(t3063, t3068, vl1);
            t3072 = __riscv_vfsub(t3064, t3067, vl1);
            t3073 = __riscv_vfsub(t3063, t3068, vl1);
            t3074 = __riscv_vfadd(t3064, t3067, vl1);
            s894 = __riscv_vfmacc(t3071, 2.4142135623730949, t3072, vl1);
            s856 = __riscv_vfmul(s894, 0.38268343236508978, vl1);
            s895 = __riscv_vfnmsac(t3072, 2.4142135623730949, t3071, vl1);
            s857 = __riscv_vfmul(s895, 0.38268343236508978, vl1);
            s896 = __riscv_vfmacc(t3073, 0.41421356237309509, t3074, vl1);
            s858 = __riscv_vfmul(s896, 0.92387953251128674, vl1);
            s897 = __riscv_vfnmsac(t3073, 2.4142135623730949, t3074, vl1);
            s859 = __riscv_vfmul(s897, 0.38268343236508978, vl1);
            t3075 = __riscv_vfadd(t3027, t3057, vl1);
            t3076 = __riscv_vfadd(t3028, t3058, vl1);
            t3077 = __riscv_vfsub(t3027, t3057, vl1);
            t3078 = __riscv_vfsub(t3028, t3058, vl1);
            t3079 = __riscv_vfadd(t3043, t3069, vl1);
            t3080 = __riscv_vfadd(t3044, t3070, vl1);
            t3081 = __riscv_vfsub(t3043, t3069, vl1);
            t3082 = __riscv_vfsub(t3044, t3070, vl1);
            s860 = __riscv_vfsub(t3075, t3079, vl1);
            s861 = __riscv_vfsub(t3076, t3080, vl1);
            s862 = __riscv_vfadd(t3077, t3082, vl1);
            s863 = __riscv_vfsub(t3078, t3081, vl1);
            s864 = __riscv_vfsub(t3077, t3082, vl1);
            s865 = __riscv_vfadd(t3078, t3081, vl1);
            t3083 = __riscv_vfadd(t3031, s850, vl1);
            t3084 = __riscv_vfadd(t3032, s851, vl1);
            t3085 = __riscv_vfsub(t3031, s850, vl1);
            t3086 = __riscv_vfsub(t3032, s851, vl1);
            t3087 = __riscv_vfadd(s846, s856, vl1);
            t3088 = __riscv_vfadd(s847, s857, vl1);
            t3089 = __riscv_vfsub(s846, s856, vl1);
            t3090 = __riscv_vfsub(s847, s857, vl1);
            s866 = __riscv_vfadd(t3083, t3087, vl1);
            s867 = __riscv_vfadd(t3084, t3088, vl1);
            s868 = __riscv_vfsub(t3083, t3087, vl1);
            s869 = __riscv_vfsub(t3084, t3088, vl1);
            s870 = __riscv_vfadd(t3085, t3090, vl1);
            s871 = __riscv_vfsub(t3086, t3089, vl1);
            s872 = __riscv_vfsub(t3085, t3090, vl1);
            s873 = __riscv_vfadd(t3086, t3089, vl1);
            t3091 = __riscv_vfadd(t3029, t3060, vl1);
            t3092 = __riscv_vfsub(t3030, t3059, vl1);
            t3093 = __riscv_vfsub(t3029, t3060, vl1);
            t3094 = __riscv_vfadd(t3030, t3059, vl1);
            t3095 = __riscv_vfadd(s844, s854, vl1);
            t3096 = __riscv_vfsub(s845, s855, vl1);
            t3097 = __riscv_vfsub(s844, s854, vl1);
            t3098 = __riscv_vfadd(s845, s855, vl1);
            s874 = __riscv_vfadd(t3091, t3095, vl1);
            s875 = __riscv_vfadd(t3092, t3096, vl1);
            s876 = __riscv_vfsub(t3091, t3095, vl1);
            s877 = __riscv_vfsub(t3092, t3096, vl1);
            s878 = __riscv_vfadd(t3093, t3098, vl1);
            s879 = __riscv_vfsub(t3094, t3097, vl1);
            s880 = __riscv_vfsub(t3093, t3098, vl1);
            s881 = __riscv_vfadd(t3094, t3097, vl1);
            t3099 = __riscv_vfadd(t3033, s852, vl1);
            t3100 = __riscv_vfsub(t3034, s853, vl1);
            t3101 = __riscv_vfsub(t3033, s852, vl1);
            t3102 = __riscv_vfadd(t3034, s853, vl1);
            t3103 = __riscv_vfsub(s848, s858, vl1);
            t3104 = __riscv_vfadd(s849, s859, vl1);
            t3105 = __riscv_vfadd(s848, s858, vl1);
            t3106 = __riscv_vfsub(s849, s859, vl1);
            s882 = __riscv_vfadd(t3099, t3103, vl1);
            s883 = __riscv_vfadd(t3100, t3104, vl1);
            s884 = __riscv_vfsub(t3099, t3103, vl1);
            s885 = __riscv_vfsub(t3100, t3104, vl1);
            s886 = __riscv_vfadd(t3101, t3106, vl1);
            s887 = __riscv_vfsub(t3102, t3105, vl1);
            s888 = __riscv_vfsub(t3101, t3106, vl1);
            s889 = __riscv_vfadd(t3102, t3105, vl1);
            a2124 = ((30)*(j1));
            a2125 = TW1[a2124];
            a2126 = TW1[(a2124 + 1)];
            a2127 = TW1[(a2124 + 2)];
            a2128 = TW1[(a2124 + 3)];
            a2129 = TW1[(a2124 + 4)];
            a2130 = TW1[(a2124 + 5)];
            a2131 = TW1[(a2124 + 6)];
            a2132 = TW1[(a2124 + 7)];
            a2133 = TW1[(a2124 + 8)];
            a2134 = TW1[(a2124 + 9)];
            a2135 = TW1[(a2124 + 10)];
            a2136 = TW1[(a2124 + 11)];
            a2137 = TW1[(a2124 + 12)];
            a2138 = TW1[(a2124 + 13)];
            a2139 = TW1[(a2124 + 14)];
            a2140 = TW1[(a2124 + 15)];
            a2141 = TW1[(a2124 + 16)];
            a2142 = TW1[(a2124 + 17)];
            a2143 = TW1[(a2124 + 18)];
            a2144 = TW1[(a2124 + 19)];
            a2145 = TW1[(a2124 + 20)];
            a2146 = TW1[(a2124 + 21)];
            a2147 = TW1[(a2124 + 22)];
            a2148 = TW1[(a2124 + 23)];
            a2149 = TW1[(a2124 + 24)];
            a2150 = TW1[(a2124 + 25)];
            a2151 = TW1[(a2124 + 26)];
            a2152 = TW1[(a2124 + 27)];
            a2153 = TW1[(a2124 + 28)];
            a2154 = TW1[(a2124 + 29)];
            r273 = __riscv_vset(__riscv_vset(rvvx2_17, 0, __riscv_vfadd(t3075, t3079, vl1)), 1, __riscv_vfadd(t3076, t3080, vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)))))), r273, vl1);
            r274 = __riscv_vset(__riscv_vset(rvvx2_18, 0, __riscv_vfsub(__riscv_vfmul(s866, a2125, vl1), __riscv_vfmul(s867, a2126, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s866, a2126, vl1), __riscv_vfmul(s867, a2125, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + m1)))), r274, vl1);
            r275 = __riscv_vset(__riscv_vset(rvvx2_19, 0, __riscv_vfsub(__riscv_vfmul(s874, a2127, vl1), __riscv_vfmul(s875, a2128, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s874, a2128, vl1), __riscv_vfmul(s875, a2127, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((2)*(m1)))))), r275, vl1);
            r276 = __riscv_vset(__riscv_vset(rvvx2_20, 0, __riscv_vfsub(__riscv_vfmul(s882, a2129, vl1), __riscv_vfmul(s883, a2130, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s882, a2130, vl1), __riscv_vfmul(s883, a2129, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((3)*(m1)))))), r276, vl1);
            r277 = __riscv_vset(__riscv_vset(rvvx2_21, 0, __riscv_vfsub(__riscv_vfmul(s862, a2131, vl1), __riscv_vfmul(s863, a2132, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s862, a2132, vl1), __riscv_vfmul(s863, a2131, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((4)*(m1)))))), r277, vl1);
            r278 = __riscv_vset(__riscv_vset(rvvx2_22, 0, __riscv_vfsub(__riscv_vfmul(s870, a2133, vl1), __riscv_vfmul(s871, a2134, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s870, a2134, vl1), __riscv_vfmul(s871, a2133, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((5)*(m1)))))), r278, vl1);
            r279 = __riscv_vset(__riscv_vset(rvvx2_23, 0, __riscv_vfsub(__riscv_vfmul(s878, a2135, vl1), __riscv_vfmul(s879, a2136, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s878, a2136, vl1), __riscv_vfmul(s879, a2135, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((6)*(m1)))))), r279, vl1);
            r280 = __riscv_vset(__riscv_vset(rvvx2_24, 0, __riscv_vfsub(__riscv_vfmul(s886, a2137, vl1), __riscv_vfmul(s887, a2138, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s886, a2138, vl1), __riscv_vfmul(s887, a2137, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((7)*(m1)))))), r280, vl1);
            r281 = __riscv_vset(__riscv_vset(rvvx2_25, 0, __riscv_vfsub(__riscv_vfmul(s860, a2139, vl1), __riscv_vfmul(s861, a2140, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s860, a2140, vl1), __riscv_vfmul(s861, a2139, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((8)*(m1)))))), r281, vl1);
            r282 = __riscv_vset(__riscv_vset(rvvx2_26, 0, __riscv_vfsub(__riscv_vfmul(s868, a2141, vl1), __riscv_vfmul(s869, a2142, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s868, a2142, vl1), __riscv_vfmul(s869, a2141, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((9)*(m1)))))), r282, vl1);
            r283 = __riscv_vset(__riscv_vset(rvvx2_27, 0, __riscv_vfsub(__riscv_vfmul(s876, a2143, vl1), __riscv_vfmul(s877, a2144, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s876, a2144, vl1), __riscv_vfmul(s877, a2143, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((10)*(m1)))))), r283, vl1);
            r284 = __riscv_vset(__riscv_vset(rvvx2_28, 0, __riscv_vfsub(__riscv_vfmul(s884, a2145, vl1), __riscv_vfmul(s885, a2146, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s884, a2146, vl1), __riscv_vfmul(s885, a2145, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((11)*(m1)))))), r284, vl1);
            r285 = __riscv_vset(__riscv_vset(rvvx2_29, 0, __riscv_vfsub(__riscv_vfmul(s864, a2147, vl1), __riscv_vfmul(s865, a2148, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s864, a2148, vl1), __riscv_vfmul(s865, a2147, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((12)*(m1)))))), r285, vl1);
            r286 = __riscv_vset(__riscv_vset(rvvx2_30, 0, __riscv_vfsub(__riscv_vfmul(s872, a2149, vl1), __riscv_vfmul(s873, a2150, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s872, a2150, vl1), __riscv_vfmul(s873, a2149, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((13)*(m1)))))), r286, vl1);
            r287 = __riscv_vset(__riscv_vset(rvvx2_31, 0, __riscv_vfsub(__riscv_vfmul(s880, a2151, vl1), __riscv_vfmul(s881, a2152, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s880, a2152, vl1), __riscv_vfmul(s881, a2151, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((14)*(m1)))))), r287, vl1);
            r288 = __riscv_vset(__riscv_vset(rvvx2_32, 0, __riscv_vfsub(__riscv_vfmul(s888, a2153, vl1), __riscv_vfmul(s889, a2154, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s888, a2154, vl1), __riscv_vfmul(s889, a2153, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((16)*(j1)))*(m1)) + ((15)*(m1)))))), r288, vl1);
        }
    }
}
