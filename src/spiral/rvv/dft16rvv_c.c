// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft16c_(double *Y, double *X, int *lp1, int *mp1) {
    int l1, m1;
    vfloat64m1x2_t r257, r258, r259, r260, r261, r262, r263, r264, 
            r265, r266, r267, r268, r269, r270, r271, r272, 
            r273, r274, r275, r276, r277, r278, r279, r280, 
            r281, r282, r283, r284, r285, r286, r287, r288, 
            rvvx2_17, rvvx2_18, rvvx2_19, rvvx2_20, rvvx2_21, rvvx2_22, rvvx2_23, rvvx2_24, 
            rvvx2_25, rvvx2_26, rvvx2_27, rvvx2_28, rvvx2_29, rvvx2_30, rvvx2_31, rvvx2_32;
    vfloat64m1_t  a1338, a1339, a1340, a1341, a1342, a1343, a1344, a1345, 
            s722, s723, s724, s725, s726, s727, s728, s729, 
            s730, s731, s732, s733, s734, s735, s736, s737, 
            s738, s739, s740, s741, s742, s743, s744, s745, 
            s746, s747, s748, s749, s750, s751, s752, s753, 
            s754, s755, s756, s757, s758, s759, s760, s761, 
            s762, s763, s764, s765, s766, s767, s768, s769, 
            s770, s771, s772, s773, s774, s775, s776, s777, 
            t3018, t3019, t3020, t3021, t3022, t3023, t3024, t3025, 
            t3026, t3027, t3028, t3029, t3030, t3031, t3032, t3033, 
            t3034, t3035, t3036, t3037, t3038, t3039, t3040, t3041, 
            t3042, t3043, t3044, t3045, t3046, t3047, t3048, t3049, 
            t3050, t3051, t3052, t3053, t3054, t3055, t3056, t3057, 
            t3058, t3059, t3060, t3061, t3062, t3063, t3064, t3065, 
            t3066, t3067, t3068, t3069, t3070, t3071, t3072, t3073, 
            t3074, t3075, t3076, t3077, t3078, t3079, t3080, t3081, 
            t3082, t3083, t3084, t3085, t3086, t3087, t3088, t3089, 
            t3090, t3091, t3092, t3093, t3094, t3095, t3096, t3097, 
            t3098, t3099, t3100, t3101, t3102, t3103, t3104, t3105;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for (size_t k1 = 0; k1 < m1; k1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(m1 - k1);
        r257 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(k1))), vl1);
        s722 = __riscv_vget_f64m1(r257, 0);
        s723 = __riscv_vget_f64m1(r257, 1);
        r258 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((l1)*(m1)))))), vl1);
        s724 = __riscv_vget_f64m1(r258, 0);
        s725 = __riscv_vget_f64m1(r258, 1);
        r259 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((2)*(l1)))*(m1)))))), vl1);
        s726 = __riscv_vget_f64m1(r259, 0);
        s727 = __riscv_vget_f64m1(r259, 1);
        r260 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((3)*(l1)))*(m1)))))), vl1);
        s728 = __riscv_vget_f64m1(r260, 0);
        s729 = __riscv_vget_f64m1(r260, 1);
        r261 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((4)*(l1)))*(m1)))))), vl1);
        s730 = __riscv_vget_f64m1(r261, 0);
        s731 = __riscv_vget_f64m1(r261, 1);
        r262 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((5)*(l1)))*(m1)))))), vl1);
        s732 = __riscv_vget_f64m1(r262, 0);
        s733 = __riscv_vget_f64m1(r262, 1);
        r263 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((6)*(l1)))*(m1)))))), vl1);
        s734 = __riscv_vget_f64m1(r263, 0);
        s735 = __riscv_vget_f64m1(r263, 1);
        r264 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((7)*(l1)))*(m1)))))), vl1);
        s736 = __riscv_vget_f64m1(r264, 0);
        s737 = __riscv_vget_f64m1(r264, 1);
        r265 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((8)*(l1)))*(m1)))))), vl1);
        s738 = __riscv_vget_f64m1(r265, 0);
        s739 = __riscv_vget_f64m1(r265, 1);
        r266 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((9)*(l1)))*(m1)))))), vl1);
        s740 = __riscv_vget_f64m1(r266, 0);
        s741 = __riscv_vget_f64m1(r266, 1);
        r267 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((10)*(l1)))*(m1)))))), vl1);
        s742 = __riscv_vget_f64m1(r267, 0);
        s743 = __riscv_vget_f64m1(r267, 1);
        r268 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((11)*(l1)))*(m1)))))), vl1);
        s744 = __riscv_vget_f64m1(r268, 0);
        s745 = __riscv_vget_f64m1(r268, 1);
        r269 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((12)*(l1)))*(m1)))))), vl1);
        s746 = __riscv_vget_f64m1(r269, 0);
        s747 = __riscv_vget_f64m1(r269, 1);
        r270 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((13)*(l1)))*(m1)))))), vl1);
        s748 = __riscv_vget_f64m1(r270, 0);
        s749 = __riscv_vget_f64m1(r270, 1);
        r271 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((14)*(l1)))*(m1)))))), vl1);
        s750 = __riscv_vget_f64m1(r271, 0);
        s751 = __riscv_vget_f64m1(r271, 1);
        r272 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((15)*(l1)))*(m1)))))), vl1);
        s752 = __riscv_vget_f64m1(r272, 0);
        s753 = __riscv_vget_f64m1(r272, 1);
        t3018 = __riscv_vfadd(s722, s738, vl1);
        t3019 = __riscv_vfadd(s723, s739, vl1);
        t3020 = __riscv_vfsub(s722, s738, vl1);
        t3021 = __riscv_vfsub(s723, s739, vl1);
        t3022 = __riscv_vfadd(s730, s746, vl1);
        t3023 = __riscv_vfadd(s731, s747, vl1);
        t3024 = __riscv_vfsub(s730, s746, vl1);
        t3025 = __riscv_vfsub(s731, s747, vl1);
        t3026 = __riscv_vfadd(t3018, t3022, vl1);
        t3027 = __riscv_vfadd(t3019, t3023, vl1);
        t3028 = __riscv_vfsub(t3018, t3022, vl1);
        t3029 = __riscv_vfsub(t3019, t3023, vl1);
        t3030 = __riscv_vfadd(t3020, t3025, vl1);
        t3031 = __riscv_vfsub(t3021, t3024, vl1);
        t3032 = __riscv_vfsub(t3020, t3025, vl1);
        t3033 = __riscv_vfadd(t3021, t3024, vl1);
        t3034 = __riscv_vfadd(s724, s740, vl1);
        t3035 = __riscv_vfadd(s725, s741, vl1);
        t3036 = __riscv_vfsub(s724, s740, vl1);
        t3037 = __riscv_vfsub(s725, s741, vl1);
        t3038 = __riscv_vfadd(s732, s748, vl1);
        t3039 = __riscv_vfadd(s733, s749, vl1);
        t3040 = __riscv_vfsub(s732, s748, vl1);
        t3041 = __riscv_vfsub(s733, s749, vl1);
        t3042 = __riscv_vfadd(t3034, t3038, vl1);
        t3043 = __riscv_vfadd(t3035, t3039, vl1);
        a1338 = __riscv_vfmul(__riscv_vfsub(t3034, t3038, vl1), 0.70710678118654757, vl1);
        a1339 = __riscv_vfmul(__riscv_vfsub(t3035, t3039, vl1), 0.70710678118654757, vl1);
        s754 = __riscv_vfadd(a1338, a1339, vl1);
        s755 = __riscv_vfsub(a1339, a1338, vl1);
        t3044 = __riscv_vfadd(t3036, t3041, vl1);
        t3045 = __riscv_vfsub(t3037, t3040, vl1);
        t3046 = __riscv_vfsub(t3036, t3041, vl1);
        t3047 = __riscv_vfadd(t3037, t3040, vl1);
        s770 = __riscv_vfmacc(t3044, 0.41421356237309509, t3045, vl1);
        s756 = __riscv_vfmul(s770, 0.92387953251128674, vl1);
        s771 = __riscv_vfnmsac(t3045, 0.41421356237309509, t3044, vl1);
        s757 = __riscv_vfmul(s771, 0.92387953251128674, vl1);
        s772 = __riscv_vfmacc(t3046, 2.4142135623730949, t3047, vl1);
        s758 = __riscv_vfmul(s772, 0.38268343236508978, vl1);
        s773 = __riscv_vfnmsac(t3047, 2.4142135623730949, t3046, vl1);
        s759 = __riscv_vfmul(s773, 0.38268343236508978, vl1);
        t3048 = __riscv_vfadd(s726, s742, vl1);
        t3049 = __riscv_vfadd(s727, s743, vl1);
        t3050 = __riscv_vfsub(s726, s742, vl1);
        t3051 = __riscv_vfsub(s727, s743, vl1);
        t3052 = __riscv_vfadd(s734, s750, vl1);
        t3053 = __riscv_vfadd(s735, s751, vl1);
        t3054 = __riscv_vfsub(s734, s750, vl1);
        t3055 = __riscv_vfsub(s735, s751, vl1);
        t3056 = __riscv_vfadd(t3048, t3052, vl1);
        t3057 = __riscv_vfadd(t3049, t3053, vl1);
        t3058 = __riscv_vfsub(t3048, t3052, vl1);
        t3059 = __riscv_vfsub(t3049, t3053, vl1);
        a1340 = __riscv_vfmul(__riscv_vfadd(t3050, t3055, vl1), 0.70710678118654757, vl1);
        a1341 = __riscv_vfmul(__riscv_vfsub(t3051, t3054, vl1), 0.70710678118654757, vl1);
        s760 = __riscv_vfadd(a1340, a1341, vl1);
        s761 = __riscv_vfsub(a1341, a1340, vl1);
        a1342 = __riscv_vfmul(__riscv_vfadd(t3051, t3054, vl1), 0.70710678118654757, vl1);
        a1343 = __riscv_vfmul(__riscv_vfsub(t3050, t3055, vl1), 0.70710678118654757, vl1);
        s762 = __riscv_vfsub(a1342, a1343, vl1);
        s763 = __riscv_vfadd(a1343, a1342, vl1);
        t3060 = __riscv_vfadd(s728, s744, vl1);
        t3061 = __riscv_vfadd(s729, s745, vl1);
        t3062 = __riscv_vfsub(s728, s744, vl1);
        t3063 = __riscv_vfsub(s729, s745, vl1);
        t3064 = __riscv_vfadd(s736, s752, vl1);
        t3065 = __riscv_vfadd(s737, s753, vl1);
        t3066 = __riscv_vfsub(s736, s752, vl1);
        t3067 = __riscv_vfsub(s737, s753, vl1);
        t3068 = __riscv_vfadd(t3060, t3064, vl1);
        t3069 = __riscv_vfadd(t3061, t3065, vl1);
        a1344 = __riscv_vfmul(__riscv_vfsub(t3061, t3065, vl1), 0.70710678118654757, vl1);
        a1345 = __riscv_vfmul(__riscv_vfsub(t3060, t3064, vl1), 0.70710678118654757, vl1);
        s764 = __riscv_vfsub(a1344, a1345, vl1);
        s765 = __riscv_vfadd(a1345, a1344, vl1);
        t3070 = __riscv_vfadd(t3062, t3067, vl1);
        t3071 = __riscv_vfsub(t3063, t3066, vl1);
        t3072 = __riscv_vfsub(t3062, t3067, vl1);
        t3073 = __riscv_vfadd(t3063, t3066, vl1);
        s774 = __riscv_vfmacc(t3070, 2.4142135623730949, t3071, vl1);
        s766 = __riscv_vfmul(s774, 0.38268343236508978, vl1);
        s775 = __riscv_vfnmsac(t3071, 2.4142135623730949, t3070, vl1);
        s767 = __riscv_vfmul(s775, 0.38268343236508978, vl1);
        s776 = __riscv_vfmacc(t3072, 0.41421356237309509, t3073, vl1);
        s768 = __riscv_vfmul(s776, 0.92387953251128674, vl1);
        s777 = __riscv_vfnmsac(t3072, 2.4142135623730949, t3073, vl1);
        s769 = __riscv_vfmul(s777, 0.38268343236508978, vl1);
        t3074 = __riscv_vfadd(t3026, t3056, vl1);
        t3075 = __riscv_vfadd(t3027, t3057, vl1);
        t3076 = __riscv_vfsub(t3026, t3056, vl1);
        t3077 = __riscv_vfsub(t3027, t3057, vl1);
        t3078 = __riscv_vfadd(t3042, t3068, vl1);
        t3079 = __riscv_vfadd(t3043, t3069, vl1);
        t3080 = __riscv_vfsub(t3042, t3068, vl1);
        t3081 = __riscv_vfsub(t3043, t3069, vl1);
        t3082 = __riscv_vfadd(t3030, s760, vl1);
        t3083 = __riscv_vfadd(t3031, s761, vl1);
        t3084 = __riscv_vfsub(t3030, s760, vl1);
        t3085 = __riscv_vfsub(t3031, s761, vl1);
        t3086 = __riscv_vfadd(s756, s766, vl1);
        t3087 = __riscv_vfadd(s757, s767, vl1);
        t3088 = __riscv_vfsub(s756, s766, vl1);
        t3089 = __riscv_vfsub(s757, s767, vl1);
        t3090 = __riscv_vfadd(t3028, t3059, vl1);
        t3091 = __riscv_vfsub(t3029, t3058, vl1);
        t3092 = __riscv_vfsub(t3028, t3059, vl1);
        t3093 = __riscv_vfadd(t3029, t3058, vl1);
        t3094 = __riscv_vfadd(s754, s764, vl1);
        t3095 = __riscv_vfsub(s755, s765, vl1);
        t3096 = __riscv_vfsub(s754, s764, vl1);
        t3097 = __riscv_vfadd(s755, s765, vl1);
        t3098 = __riscv_vfadd(t3032, s762, vl1);
        t3099 = __riscv_vfsub(t3033, s763, vl1);
        t3100 = __riscv_vfsub(t3032, s762, vl1);
        t3101 = __riscv_vfadd(t3033, s763, vl1);
        t3102 = __riscv_vfsub(s758, s768, vl1);
        t3103 = __riscv_vfadd(s759, s769, vl1);
        t3104 = __riscv_vfadd(s758, s768, vl1);
        t3105 = __riscv_vfsub(s759, s769, vl1);
        r273 = __riscv_vset(__riscv_vset(rvvx2_17, 0, __riscv_vfadd(t3074, t3078, vl1)), 1, __riscv_vfadd(t3075, t3079, vl1));
        __riscv_vsseg2e64((Y + ((2)*(k1))), r273, vl1);
        r274 = __riscv_vset(__riscv_vset(rvvx2_18, 0, __riscv_vfadd(t3082, t3086, vl1)), 1, __riscv_vfadd(t3083, t3087, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + m1)))), r274, vl1);
        r275 = __riscv_vset(__riscv_vset(rvvx2_19, 0, __riscv_vfadd(t3090, t3094, vl1)), 1, __riscv_vfadd(t3091, t3095, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((2)*(m1)))))), r275, vl1);
        r276 = __riscv_vset(__riscv_vset(rvvx2_20, 0, __riscv_vfadd(t3098, t3102, vl1)), 1, __riscv_vfadd(t3099, t3103, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((3)*(m1)))))), r276, vl1);
        r277 = __riscv_vset(__riscv_vset(rvvx2_21, 0, __riscv_vfadd(t3076, t3081, vl1)), 1, __riscv_vfsub(t3077, t3080, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((4)*(m1)))))), r277, vl1);
        r278 = __riscv_vset(__riscv_vset(rvvx2_22, 0, __riscv_vfadd(t3084, t3089, vl1)), 1, __riscv_vfsub(t3085, t3088, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((5)*(m1)))))), r278, vl1);
        r279 = __riscv_vset(__riscv_vset(rvvx2_23, 0, __riscv_vfadd(t3092, t3097, vl1)), 1, __riscv_vfsub(t3093, t3096, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((6)*(m1)))))), r279, vl1);
        r280 = __riscv_vset(__riscv_vset(rvvx2_24, 0, __riscv_vfadd(t3100, t3105, vl1)), 1, __riscv_vfsub(t3101, t3104, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((7)*(m1)))))), r280, vl1);
        r281 = __riscv_vset(__riscv_vset(rvvx2_25, 0, __riscv_vfsub(t3074, t3078, vl1)), 1, __riscv_vfsub(t3075, t3079, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((8)*(m1)))))), r281, vl1);
        r282 = __riscv_vset(__riscv_vset(rvvx2_26, 0, __riscv_vfsub(t3082, t3086, vl1)), 1, __riscv_vfsub(t3083, t3087, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((9)*(m1)))))), r282, vl1);
        r283 = __riscv_vset(__riscv_vset(rvvx2_27, 0, __riscv_vfsub(t3090, t3094, vl1)), 1, __riscv_vfsub(t3091, t3095, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((10)*(m1)))))), r283, vl1);
        r284 = __riscv_vset(__riscv_vset(rvvx2_28, 0, __riscv_vfsub(t3098, t3102, vl1)), 1, __riscv_vfsub(t3099, t3103, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((11)*(m1)))))), r284, vl1);
        r285 = __riscv_vset(__riscv_vset(rvvx2_29, 0, __riscv_vfsub(t3076, t3081, vl1)), 1, __riscv_vfadd(t3077, t3080, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((12)*(m1)))))), r285, vl1);
        r286 = __riscv_vset(__riscv_vset(rvvx2_30, 0, __riscv_vfsub(t3084, t3089, vl1)), 1, __riscv_vfadd(t3085, t3088, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((13)*(m1)))))), r286, vl1);
        r287 = __riscv_vset(__riscv_vset(rvvx2_31, 0, __riscv_vfsub(t3092, t3097, vl1)), 1, __riscv_vfadd(t3093, t3096, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((14)*(m1)))))), r287, vl1);
        r288 = __riscv_vset(__riscv_vset(rvvx2_32, 0, __riscv_vfsub(t3100, t3105, vl1)), 1, __riscv_vfadd(t3101, t3104, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((15)*(m1)))))), r288, vl1);
    }
}
