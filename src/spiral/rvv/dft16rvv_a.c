// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft16a_(double *Y, double *X, double *TW1, int *lp1) {
    int l1;
    double *a1978;
    vfloat64m1x2_t r113, r114, r115, r116, r117, r118, r119, r120, 
            r121, r122, r123, r124, r125, r126, r127, r128;
    vfloat64m1_t  a1970, a1971, a1972, a1973, a1974, a1975, a1976, a1977, 
            a1979, a1980, a1981, a1982, a1983, a1984, a1985, a1986, 
            a1987, a1988, a1989, a1990, a1991, a1992, a1993, a1994, 
            a1995, a1996, a1997, a1998, a1999, a2000, a2001, a2002, 
            a2003, a2004, a2005, a2006, a2007, a2008, s844, s845, 
            s846, s847, s848, s849, s850, s851, s852, s853, 
            s854, s855, s856, s857, s858, s859, s860, s861, 
            s862, s863, s864, s865, s866, s867, s868, s869, 
            s870, s871, s872, s873, s874, s875, s876, s877, 
            s878, s879, s880, s881, s882, s883, s884, s885, 
            s886, s887, s888, s889, s890, s891, s892, s893, 
            s894, s895, s896, s897, s898, s899, s900, s901, 
            s902, s903, s904, s905, s906, s907, s908, s909, 
            s910, s911, s912, s913, s914, s915, s916, s917, 
            s918, s919, s920, s921, s922, s923, s924, s925, 
            s926, s927, s928, s929, s930, s931, s932, s933, 
            s934, s935, s936, s937, s938, s939, s940, s941, 
            s942, s943, s944, s945, s946, s947, s948, s949, 
            s950, s951, s952, s953, s954, s955, s956, s957, 
            s958, s959, s960, s961, t3019, t3020, t3021, t3022, 
            t3023, t3024, t3025, t3026, t3027, t3028, t3029, t3030, 
            t3031, t3032, t3033, t3034, t3035, t3036, t3037, t3038, 
            t3039, t3040, t3041, t3042, t3043, t3044, t3045, t3046, 
            t3047, t3048, t3049, t3050, t3051, t3052, t3053, t3054, 
            t3055, t3056, t3057, t3058, t3059, t3060, t3061, t3062, 
            t3063, t3064, t3065, t3066, t3067, t3068, t3069, t3070, 
            t3071, t3072, t3073, t3074, t3075, t3076, t3077, t3078, 
            t3079, t3080, t3081, t3082, t3083, t3084, t3085, t3086, 
            t3087, t3088, t3089, t3090, t3091, t3092, t3093, t3094, 
            t3095, t3096, t3097, t3098, t3099, t3100, t3101, t3102, 
            t3103, t3104, t3105, t3106;
    size_t vl1;
    l1 = *(lp1);
    for (size_t j1 = 0; j1 < l1; j1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(l1 - j1);
        r113 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(j1))), vl1);
        s844 = __riscv_vget_f64m1(r113, 0);
        s845 = __riscv_vget_f64m1(r113, 1);
        r114 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + l1)))), vl1);
        s846 = __riscv_vget_f64m1(r114, 0);
        s847 = __riscv_vget_f64m1(r114, 1);
        r115 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((2)*(l1)))))), vl1);
        s848 = __riscv_vget_f64m1(r115, 0);
        s849 = __riscv_vget_f64m1(r115, 1);
        r116 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((3)*(l1)))))), vl1);
        s850 = __riscv_vget_f64m1(r116, 0);
        s851 = __riscv_vget_f64m1(r116, 1);
        r117 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((4)*(l1)))))), vl1);
        s852 = __riscv_vget_f64m1(r117, 0);
        s853 = __riscv_vget_f64m1(r117, 1);
        r118 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((5)*(l1)))))), vl1);
        s854 = __riscv_vget_f64m1(r118, 0);
        s855 = __riscv_vget_f64m1(r118, 1);
        r119 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((6)*(l1)))))), vl1);
        s856 = __riscv_vget_f64m1(r119, 0);
        s857 = __riscv_vget_f64m1(r119, 1);
        r120 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((7)*(l1)))))), vl1);
        s858 = __riscv_vget_f64m1(r120, 0);
        s859 = __riscv_vget_f64m1(r120, 1);
        r121 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((8)*(l1)))))), vl1);
        s860 = __riscv_vget_f64m1(r121, 0);
        s861 = __riscv_vget_f64m1(r121, 1);
        r122 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((9)*(l1)))))), vl1);
        s862 = __riscv_vget_f64m1(r122, 0);
        s863 = __riscv_vget_f64m1(r122, 1);
        r123 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((10)*(l1)))))), vl1);
        s864 = __riscv_vget_f64m1(r123, 0);
        s865 = __riscv_vget_f64m1(r123, 1);
        r124 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((11)*(l1)))))), vl1);
        s866 = __riscv_vget_f64m1(r124, 0);
        s867 = __riscv_vget_f64m1(r124, 1);
        r125 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((12)*(l1)))))), vl1);
        s868 = __riscv_vget_f64m1(r125, 0);
        s869 = __riscv_vget_f64m1(r125, 1);
        r126 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((13)*(l1)))))), vl1);
        s870 = __riscv_vget_f64m1(r126, 0);
        s871 = __riscv_vget_f64m1(r126, 1);
        r127 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((14)*(l1)))))), vl1);
        s872 = __riscv_vget_f64m1(r127, 0);
        s873 = __riscv_vget_f64m1(r127, 1);
        r128 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((j1 + ((15)*(l1)))))), vl1);
        s874 = __riscv_vget_f64m1(r128, 0);
        s875 = __riscv_vget_f64m1(r128, 1);
        t3019 = __riscv_vfadd(s844, s860, vl1);
        t3020 = __riscv_vfadd(s845, s861, vl1);
        t3021 = __riscv_vfsub(s844, s860, vl1);
        t3022 = __riscv_vfsub(s845, s861, vl1);
        t3023 = __riscv_vfadd(s852, s868, vl1);
        t3024 = __riscv_vfadd(s853, s869, vl1);
        t3025 = __riscv_vfsub(s852, s868, vl1);
        t3026 = __riscv_vfsub(s853, s869, vl1);
        t3027 = __riscv_vfadd(t3019, t3023, vl1);
        t3028 = __riscv_vfadd(t3020, t3024, vl1);
        t3029 = __riscv_vfsub(t3019, t3023, vl1);
        t3030 = __riscv_vfsub(t3020, t3024, vl1);
        t3031 = __riscv_vfadd(t3021, t3026, vl1);
        t3032 = __riscv_vfsub(t3022, t3025, vl1);
        t3033 = __riscv_vfsub(t3021, t3026, vl1);
        t3034 = __riscv_vfadd(t3022, t3025, vl1);
        t3035 = __riscv_vfadd(s846, s862, vl1);
        t3036 = __riscv_vfadd(s847, s863, vl1);
        t3037 = __riscv_vfsub(s846, s862, vl1);
        t3038 = __riscv_vfsub(s847, s863, vl1);
        t3039 = __riscv_vfadd(s854, s870, vl1);
        t3040 = __riscv_vfadd(s855, s871, vl1);
        t3041 = __riscv_vfsub(s854, s870, vl1);
        t3042 = __riscv_vfsub(s855, s871, vl1);
        t3043 = __riscv_vfadd(t3035, t3039, vl1);
        t3044 = __riscv_vfadd(t3036, t3040, vl1);
        a1970 = __riscv_vfmul(__riscv_vfsub(t3035, t3039, vl1), 0.70710678118654757, vl1);
        a1971 = __riscv_vfmul(__riscv_vfsub(t3036, t3040, vl1), 0.70710678118654757, vl1);
        s876 = __riscv_vfadd(a1970, a1971, vl1);
        s877 = __riscv_vfsub(a1971, a1970, vl1);
        t3045 = __riscv_vfadd(t3037, t3042, vl1);
        t3046 = __riscv_vfsub(t3038, t3041, vl1);
        t3047 = __riscv_vfsub(t3037, t3042, vl1);
        t3048 = __riscv_vfadd(t3038, t3041, vl1);
        s954 = __riscv_vfmacc(t3045, 0.41421356237309509, t3046, vl1);
        s878 = __riscv_vfmul(s954, 0.92387953251128674, vl1);
        s955 = __riscv_vfnmsac(t3046, 0.41421356237309509, t3045, vl1);
        s879 = __riscv_vfmul(s955, 0.92387953251128674, vl1);
        s956 = __riscv_vfmacc(t3047, 2.4142135623730949, t3048, vl1);
        s880 = __riscv_vfmul(s956, 0.38268343236508978, vl1);
        s957 = __riscv_vfnmsac(t3048, 2.4142135623730949, t3047, vl1);
        s881 = __riscv_vfmul(s957, 0.38268343236508978, vl1);
        t3049 = __riscv_vfadd(s848, s864, vl1);
        t3050 = __riscv_vfadd(s849, s865, vl1);
        t3051 = __riscv_vfsub(s848, s864, vl1);
        t3052 = __riscv_vfsub(s849, s865, vl1);
        t3053 = __riscv_vfadd(s856, s872, vl1);
        t3054 = __riscv_vfadd(s857, s873, vl1);
        t3055 = __riscv_vfsub(s856, s872, vl1);
        t3056 = __riscv_vfsub(s857, s873, vl1);
        t3057 = __riscv_vfadd(t3049, t3053, vl1);
        t3058 = __riscv_vfadd(t3050, t3054, vl1);
        t3059 = __riscv_vfsub(t3049, t3053, vl1);
        t3060 = __riscv_vfsub(t3050, t3054, vl1);
        a1972 = __riscv_vfmul(__riscv_vfadd(t3051, t3056, vl1), 0.70710678118654757, vl1);
        a1973 = __riscv_vfmul(__riscv_vfsub(t3052, t3055, vl1), 0.70710678118654757, vl1);
        s882 = __riscv_vfadd(a1972, a1973, vl1);
        s883 = __riscv_vfsub(a1973, a1972, vl1);
        a1974 = __riscv_vfmul(__riscv_vfadd(t3052, t3055, vl1), 0.70710678118654757, vl1);
        a1975 = __riscv_vfmul(__riscv_vfsub(t3051, t3056, vl1), 0.70710678118654757, vl1);
        s884 = __riscv_vfsub(a1974, a1975, vl1);
        s885 = __riscv_vfadd(a1975, a1974, vl1);
        t3061 = __riscv_vfadd(s850, s866, vl1);
        t3062 = __riscv_vfadd(s851, s867, vl1);
        t3063 = __riscv_vfsub(s850, s866, vl1);
        t3064 = __riscv_vfsub(s851, s867, vl1);
        t3065 = __riscv_vfadd(s858, s874, vl1);
        t3066 = __riscv_vfadd(s859, s875, vl1);
        t3067 = __riscv_vfsub(s858, s874, vl1);
        t3068 = __riscv_vfsub(s859, s875, vl1);
        t3069 = __riscv_vfadd(t3061, t3065, vl1);
        t3070 = __riscv_vfadd(t3062, t3066, vl1);
        a1976 = __riscv_vfmul(__riscv_vfsub(t3062, t3066, vl1), 0.70710678118654757, vl1);
        a1977 = __riscv_vfmul(__riscv_vfsub(t3061, t3065, vl1), 0.70710678118654757, vl1);
        s886 = __riscv_vfsub(a1976, a1977, vl1);
        s887 = __riscv_vfadd(a1977, a1976, vl1);
        t3071 = __riscv_vfadd(t3063, t3068, vl1);
        t3072 = __riscv_vfsub(t3064, t3067, vl1);
        t3073 = __riscv_vfsub(t3063, t3068, vl1);
        t3074 = __riscv_vfadd(t3064, t3067, vl1);
        s958 = __riscv_vfmacc(t3071, 2.4142135623730949, t3072, vl1);
        s888 = __riscv_vfmul(s958, 0.38268343236508978, vl1);
        s959 = __riscv_vfnmsac(t3072, 2.4142135623730949, t3071, vl1);
        s889 = __riscv_vfmul(s959, 0.38268343236508978, vl1);
        s960 = __riscv_vfmacc(t3073, 0.41421356237309509, t3074, vl1);
        s890 = __riscv_vfmul(s960, 0.92387953251128674, vl1);
        s961 = __riscv_vfnmsac(t3073, 2.4142135623730949, t3074, vl1);
        s891 = __riscv_vfmul(s961, 0.38268343236508978, vl1);
        t3075 = __riscv_vfadd(t3027, t3057, vl1);
        t3076 = __riscv_vfadd(t3028, t3058, vl1);
        t3077 = __riscv_vfsub(t3027, t3057, vl1);
        t3078 = __riscv_vfsub(t3028, t3058, vl1);
        t3079 = __riscv_vfadd(t3043, t3069, vl1);
        t3080 = __riscv_vfadd(t3044, t3070, vl1);
        t3081 = __riscv_vfsub(t3043, t3069, vl1);
        t3082 = __riscv_vfsub(t3044, t3070, vl1);
        s892 = __riscv_vfadd(t3075, t3079, vl1);
        s893 = __riscv_vfadd(t3076, t3080, vl1);
        s894 = __riscv_vfsub(t3075, t3079, vl1);
        s895 = __riscv_vfsub(t3076, t3080, vl1);
        s896 = __riscv_vfadd(t3077, t3082, vl1);
        s897 = __riscv_vfsub(t3078, t3081, vl1);
        s898 = __riscv_vfsub(t3077, t3082, vl1);
        s899 = __riscv_vfadd(t3078, t3081, vl1);
        t3083 = __riscv_vfadd(t3031, s882, vl1);
        t3084 = __riscv_vfadd(t3032, s883, vl1);
        t3085 = __riscv_vfsub(t3031, s882, vl1);
        t3086 = __riscv_vfsub(t3032, s883, vl1);
        t3087 = __riscv_vfadd(s878, s888, vl1);
        t3088 = __riscv_vfadd(s879, s889, vl1);
        t3089 = __riscv_vfsub(s878, s888, vl1);
        t3090 = __riscv_vfsub(s879, s889, vl1);
        s900 = __riscv_vfadd(t3083, t3087, vl1);
        s901 = __riscv_vfadd(t3084, t3088, vl1);
        s902 = __riscv_vfsub(t3083, t3087, vl1);
        s903 = __riscv_vfsub(t3084, t3088, vl1);
        s904 = __riscv_vfadd(t3085, t3090, vl1);
        s905 = __riscv_vfsub(t3086, t3089, vl1);
        s906 = __riscv_vfsub(t3085, t3090, vl1);
        s907 = __riscv_vfadd(t3086, t3089, vl1);
        t3091 = __riscv_vfadd(t3029, t3060, vl1);
        t3092 = __riscv_vfsub(t3030, t3059, vl1);
        t3093 = __riscv_vfsub(t3029, t3060, vl1);
        t3094 = __riscv_vfadd(t3030, t3059, vl1);
        t3095 = __riscv_vfadd(s876, s886, vl1);
        t3096 = __riscv_vfsub(s877, s887, vl1);
        t3097 = __riscv_vfsub(s876, s886, vl1);
        t3098 = __riscv_vfadd(s877, s887, vl1);
        s908 = __riscv_vfadd(t3091, t3095, vl1);
        s909 = __riscv_vfadd(t3092, t3096, vl1);
        s910 = __riscv_vfsub(t3091, t3095, vl1);
        s911 = __riscv_vfsub(t3092, t3096, vl1);
        s912 = __riscv_vfadd(t3093, t3098, vl1);
        s913 = __riscv_vfsub(t3094, t3097, vl1);
        s914 = __riscv_vfsub(t3093, t3098, vl1);
        s915 = __riscv_vfadd(t3094, t3097, vl1);
        t3099 = __riscv_vfadd(t3033, s884, vl1);
        t3100 = __riscv_vfsub(t3034, s885, vl1);
        t3101 = __riscv_vfsub(t3033, s884, vl1);
        t3102 = __riscv_vfadd(t3034, s885, vl1);
        t3103 = __riscv_vfsub(s880, s890, vl1);
        t3104 = __riscv_vfadd(s881, s891, vl1);
        t3105 = __riscv_vfadd(s880, s890, vl1);
        t3106 = __riscv_vfsub(s881, s891, vl1);
        s916 = __riscv_vfadd(t3099, t3103, vl1);
        s917 = __riscv_vfadd(t3100, t3104, vl1);
        s918 = __riscv_vfsub(t3099, t3103, vl1);
        s919 = __riscv_vfsub(t3100, t3104, vl1);
        s920 = __riscv_vfadd(t3101, t3106, vl1);
        s921 = __riscv_vfsub(t3102, t3105, vl1);
        s922 = __riscv_vfsub(t3101, t3106, vl1);
        s923 = __riscv_vfadd(t3102, t3105, vl1);
        a1978 = (TW1 + ((30)*(j1)));
        a1979 = __riscv_vlse64_v_f64m1(a1978, sizeof(double) * 30, vl1);
        a1980 = __riscv_vlse64_v_f64m1((a1978 + 1), sizeof(double) * 30, vl1);
        s924 = __riscv_vfmsac(__riscv_vfmul(a1980, s901, vl1), a1979, s900, vl1);
        s925 = __riscv_vfmacc(__riscv_vfmul(a1979, s901, vl1), a1980, s900, vl1);
        a1981 = __riscv_vlse64_v_f64m1((a1978 + 2), sizeof(double) * 30, vl1);
        a1982 = __riscv_vlse64_v_f64m1((a1978 + 3), sizeof(double) * 30, vl1);
        s926 = __riscv_vfmsac(__riscv_vfmul(a1982, s909, vl1), a1981, s908, vl1);
        s927 = __riscv_vfmacc(__riscv_vfmul(a1981, s909, vl1), a1982, s908, vl1);
        a1983 = __riscv_vlse64_v_f64m1((a1978 + 4), sizeof(double) * 30, vl1);
        a1984 = __riscv_vlse64_v_f64m1((a1978 + 5), sizeof(double) * 30, vl1);
        s928 = __riscv_vfmsac(__riscv_vfmul(a1984, s917, vl1), a1983, s916, vl1);
        s929 = __riscv_vfmacc(__riscv_vfmul(a1983, s917, vl1), a1984, s916, vl1);
        a1985 = __riscv_vlse64_v_f64m1((a1978 + 6), sizeof(double) * 30, vl1);
        a1986 = __riscv_vlse64_v_f64m1((a1978 + 7), sizeof(double) * 30, vl1);
        s930 = __riscv_vfmsac(__riscv_vfmul(a1986, s897, vl1), a1985, s896, vl1);
        s931 = __riscv_vfmacc(__riscv_vfmul(a1985, s897, vl1), a1986, s896, vl1);
        a1987 = __riscv_vlse64_v_f64m1((a1978 + 8), sizeof(double) * 30, vl1);
        a1988 = __riscv_vlse64_v_f64m1((a1978 + 9), sizeof(double) * 30, vl1);
        s932 = __riscv_vfmsac(__riscv_vfmul(a1988, s905, vl1), a1987, s904, vl1);
        s933 = __riscv_vfmacc(__riscv_vfmul(a1987, s905, vl1), a1988, s904, vl1);
        a1989 = __riscv_vlse64_v_f64m1((a1978 + 10), sizeof(double) * 30, vl1);
        a1990 = __riscv_vlse64_v_f64m1((a1978 + 11), sizeof(double) * 30, vl1);
        s934 = __riscv_vfmsac(__riscv_vfmul(a1990, s913, vl1), a1989, s912, vl1);
        s935 = __riscv_vfmacc(__riscv_vfmul(a1989, s913, vl1), a1990, s912, vl1);
        a1991 = __riscv_vlse64_v_f64m1((a1978 + 12), sizeof(double) * 30, vl1);
        a1992 = __riscv_vlse64_v_f64m1((a1978 + 13), sizeof(double) * 30, vl1);
        s936 = __riscv_vfmsac(__riscv_vfmul(a1992, s921, vl1), a1991, s920, vl1);
        s937 = __riscv_vfmacc(__riscv_vfmul(a1991, s921, vl1), a1992, s920, vl1);
        a1993 = __riscv_vlse64_v_f64m1((a1978 + 14), sizeof(double) * 30, vl1);
        a1994 = __riscv_vlse64_v_f64m1((a1978 + 15), sizeof(double) * 30, vl1);
        s938 = __riscv_vfmsac(__riscv_vfmul(a1994, s895, vl1), a1993, s894, vl1);
        s939 = __riscv_vfmacc(__riscv_vfmul(a1993, s895, vl1), a1994, s894, vl1);
        a1995 = __riscv_vlse64_v_f64m1((a1978 + 16), sizeof(double) * 30, vl1);
        a1996 = __riscv_vlse64_v_f64m1((a1978 + 17), sizeof(double) * 30, vl1);
        s940 = __riscv_vfmsac(__riscv_vfmul(a1996, s903, vl1), a1995, s902, vl1);
        s941 = __riscv_vfmacc(__riscv_vfmul(a1995, s903, vl1), a1996, s902, vl1);
        a1997 = __riscv_vlse64_v_f64m1((a1978 + 18), sizeof(double) * 30, vl1);
        a1998 = __riscv_vlse64_v_f64m1((a1978 + 19), sizeof(double) * 30, vl1);
        s942 = __riscv_vfmsac(__riscv_vfmul(a1998, s911, vl1), a1997, s910, vl1);
        s943 = __riscv_vfmacc(__riscv_vfmul(a1997, s911, vl1), a1998, s910, vl1);
        a1999 = __riscv_vlse64_v_f64m1((a1978 + 20), sizeof(double) * 30, vl1);
        a2000 = __riscv_vlse64_v_f64m1((a1978 + 21), sizeof(double) * 30, vl1);
        s944 = __riscv_vfmsac(__riscv_vfmul(a2000, s919, vl1), a1999, s918, vl1);
        s945 = __riscv_vfmacc(__riscv_vfmul(a1999, s919, vl1), a2000, s918, vl1);
        a2001 = __riscv_vlse64_v_f64m1((a1978 + 22), sizeof(double) * 30, vl1);
        a2002 = __riscv_vlse64_v_f64m1((a1978 + 23), sizeof(double) * 30, vl1);
        s946 = __riscv_vfmsac(__riscv_vfmul(a2002, s899, vl1), a2001, s898, vl1);
        s947 = __riscv_vfmacc(__riscv_vfmul(a2001, s899, vl1), a2002, s898, vl1);
        a2003 = __riscv_vlse64_v_f64m1((a1978 + 24), sizeof(double) * 30, vl1);
        a2004 = __riscv_vlse64_v_f64m1((a1978 + 25), sizeof(double) * 30, vl1);
        s948 = __riscv_vfmsac(__riscv_vfmul(a2004, s907, vl1), a2003, s906, vl1);
        s949 = __riscv_vfmacc(__riscv_vfmul(a2003, s907, vl1), a2004, s906, vl1);
        a2005 = __riscv_vlse64_v_f64m1((a1978 + 26), sizeof(double) * 30, vl1);
        a2006 = __riscv_vlse64_v_f64m1((a1978 + 27), sizeof(double) * 30, vl1);
        s950 = __riscv_vfmsac(__riscv_vfmul(a2006, s915, vl1), a2005, s914, vl1);
        s951 = __riscv_vfmacc(__riscv_vfmul(a2005, s915, vl1), a2006, s914, vl1);
        a2007 = __riscv_vlse64_v_f64m1((a1978 + 28), sizeof(double) * 30, vl1);
        a2008 = __riscv_vlse64_v_f64m1((a1978 + 29), sizeof(double) * 30, vl1);
        s952 = __riscv_vfmsac(__riscv_vfmul(a2008, s923, vl1), a2007, s922, vl1);
        s953 = __riscv_vfmacc(__riscv_vfmul(a2007, s923, vl1), a2008, s922, vl1);
        __riscv_vsse64((Y + ((32)*(j1))), sizeof(double) * 32, s892, vl1);
        __riscv_vsse64((1 + Y + ((32)*(j1))), sizeof(double) * 32, s893, vl1);
        __riscv_vsse64((2 + Y + ((32)*(j1))), sizeof(double) * 32, s924, vl1);
        __riscv_vsse64((3 + Y + ((32)*(j1))), sizeof(double) * 32, s925, vl1);
        __riscv_vsse64((4 + Y + ((32)*(j1))), sizeof(double) * 32, s926, vl1);
        __riscv_vsse64((5 + Y + ((32)*(j1))), sizeof(double) * 32, s927, vl1);
        __riscv_vsse64((6 + Y + ((32)*(j1))), sizeof(double) * 32, s928, vl1);
        __riscv_vsse64((7 + Y + ((32)*(j1))), sizeof(double) * 32, s929, vl1);
        __riscv_vsse64((8 + Y + ((32)*(j1))), sizeof(double) * 32, s930, vl1);
        __riscv_vsse64((9 + Y + ((32)*(j1))), sizeof(double) * 32, s931, vl1);
        __riscv_vsse64((10 + Y + ((32)*(j1))), sizeof(double) * 32, s932, vl1);
        __riscv_vsse64((11 + Y + ((32)*(j1))), sizeof(double) * 32, s933, vl1);
        __riscv_vsse64((12 + Y + ((32)*(j1))), sizeof(double) * 32, s934, vl1);
        __riscv_vsse64((13 + Y + ((32)*(j1))), sizeof(double) * 32, s935, vl1);
        __riscv_vsse64((14 + Y + ((32)*(j1))), sizeof(double) * 32, s936, vl1);
        __riscv_vsse64((15 + Y + ((32)*(j1))), sizeof(double) * 32, s937, vl1);
        __riscv_vsse64((16 + Y + ((32)*(j1))), sizeof(double) * 32, s938, vl1);
        __riscv_vsse64((17 + Y + ((32)*(j1))), sizeof(double) * 32, s939, vl1);
        __riscv_vsse64((18 + Y + ((32)*(j1))), sizeof(double) * 32, s940, vl1);
        __riscv_vsse64((19 + Y + ((32)*(j1))), sizeof(double) * 32, s941, vl1);
        __riscv_vsse64((20 + Y + ((32)*(j1))), sizeof(double) * 32, s942, vl1);
        __riscv_vsse64((21 + Y + ((32)*(j1))), sizeof(double) * 32, s943, vl1);
        __riscv_vsse64((22 + Y + ((32)*(j1))), sizeof(double) * 32, s944, vl1);
        __riscv_vsse64((23 + Y + ((32)*(j1))), sizeof(double) * 32, s945, vl1);
        __riscv_vsse64((24 + Y + ((32)*(j1))), sizeof(double) * 32, s946, vl1);
        __riscv_vsse64((25 + Y + ((32)*(j1))), sizeof(double) * 32, s947, vl1);
        __riscv_vsse64((26 + Y + ((32)*(j1))), sizeof(double) * 32, s948, vl1);
        __riscv_vsse64((27 + Y + ((32)*(j1))), sizeof(double) * 32, s949, vl1);
        __riscv_vsse64((28 + Y + ((32)*(j1))), sizeof(double) * 32, s950, vl1);
        __riscv_vsse64((29 + Y + ((32)*(j1))), sizeof(double) * 32, s951, vl1);
        __riscv_vsse64((30 + Y + ((32)*(j1))), sizeof(double) * 32, s952, vl1);
        __riscv_vsse64((31 + Y + ((32)*(j1))), sizeof(double) * 32, s953, vl1);
    }
}
