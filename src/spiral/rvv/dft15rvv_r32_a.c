// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft15a_r32_(float *Y, float *X, float *TW1, int64_t *lp1) {
    int64_t l1;
    float *a1724;
    vfloat32m1x2_t r106, r107, r108, r109, r110, r111, r112, r113, 
            r114, r115, r116, r117, r118, r119, r120;
    vfloat32m1_t  a1725, a1726, a1727, a1728, a1729, a1730, a1731, a1732, 
            a1733, a1734, a1735, a1736, a1737, a1738, a1739, a1740, 
            a1741, a1742, a1743, a1744, a1745, a1746, a1747, a1748, 
            a1749, a1750, a1751, a1752, s1000, s1001, s1002, s1003, 
            s1004, s1005, s1006, s1007, s1008, s1009, s1010, s1011, 
            s1012, s1013, s1014, s1015, s1016, s1017, s1018, s1019, 
            s1020, s1021, s1022, s1023, s1024, s1025, s1026, s1027, 
            s1028, s1029, s1030, s1031, s1032, s1033, s1034, s1035, 
            s1036, s1037, s1038, s1039, s1040, s1041, s1042, s1043, 
            s1044, s1045, s1046, s1047, s1048, s1049, s1050, s1051, 
            s1052, s1053, s1054, s1055, s1056, s1057, s1058, s1059, 
            s1060, s1061, s1062, s1063, s1064, s1065, s1066, s1067, 
            s1068, s1069, s1070, s1071, s1072, s1073, s1074, s1075, 
            s1076, s1077, s1078, s1079, s1080, s1081, s1082, s1083, 
            s1084, s1085, s1086, s1087, s1088, s1089, s1090, s1091, 
            s1092, s1093, s1094, s1095, s1096, s1097, s1098, s1099, 
            s1100, s1101, s1102, s1103, s1104, s1105, s1106, s1107, 
            s1108, s1109, s1110, s1111, s1112, s1113, s1114, s1115, 
            s1116, s1117, s1118, s1119, s1120, s1121, s1122, s1123, 
            s1124, s1125, s1126, s1127, s1128, s1129, s1130, s1131, 
            s1132, s1133, s1134, s1135, s1136, s1137, s1138, s1139, 
            s1140, s1141, s1142, s1143, s1144, s1145, s986, s987, 
            s988, s989, s990, s991, s992, s993, s994, s995, 
            s996, s997, s998, s999, t2301, t2302, t2303, t2304, 
            t2305, t2306, t2307, t2308, t2309, t2310, t2311, t2312, 
            t2313, t2314, t2315, t2316, t2317, t2318, t2319, t2320, 
            t2321, t2322, t2323, t2324, t2325, t2326, t2327, t2328, 
            t2329, t2330, t2331, t2332, t2333, t2334, t2335, t2336, 
            t2337, t2338, t2339, t2340, t2341, t2342, t2343, t2344, 
            t2345, t2346, t2347, t2348, t2349, t2350, t2351, t2352, 
            t2353, t2354, t2355, t2356, t2357, t2358, t2359, t2360, 
            t2361, t2362, t2363, t2364, t2365, t2366, t2367, t2368, 
            t2369, t2370, t2371, t2372, t2373, t2374, t2375, t2376, 
            t2377, t2378, t2379, t2380, t2381, t2382, t2383, t2384, 
            t2385, t2386, t2387, t2388, t2389, t2390, t2391, t2392, 
            t2393, t2394, t2395, t2396, t2397, t2398, t2399, t2400, 
            t2401, t2402, t2403, t2404, t2405, t2406, t2407, t2408, 
            t2409, t2410, t2411, t2412, t2413, t2414, t2415, t2416, 
            t2417, t2418, t2419, t2420, t2421, t2422;
    size_t vl1;
    l1 = *(lp1);
    for (size_t j1 = 0; j1 < l1; j1 += vl1) {
        vl1 = __riscv_vsetvl_e32m1(l1 - j1);
        r106 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*(j1))), vl1);
        s986 = __riscv_vget_f32m1(r106, 0);
        s987 = __riscv_vget_f32m1(r106, 1);
        r107 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + l1)))), vl1);
        s988 = __riscv_vget_f32m1(r107, 0);
        s989 = __riscv_vget_f32m1(r107, 1);
        r108 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((2)*(l1)))))), vl1);
        s990 = __riscv_vget_f32m1(r108, 0);
        s991 = __riscv_vget_f32m1(r108, 1);
        r109 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((3)*(l1)))))), vl1);
        s992 = __riscv_vget_f32m1(r109, 0);
        s993 = __riscv_vget_f32m1(r109, 1);
        r110 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((4)*(l1)))))), vl1);
        s994 = __riscv_vget_f32m1(r110, 0);
        s995 = __riscv_vget_f32m1(r110, 1);
        r111 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((5)*(l1)))))), vl1);
        s996 = __riscv_vget_f32m1(r111, 0);
        s997 = __riscv_vget_f32m1(r111, 1);
        r112 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((6)*(l1)))))), vl1);
        s998 = __riscv_vget_f32m1(r112, 0);
        s999 = __riscv_vget_f32m1(r112, 1);
        r113 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((7)*(l1)))))), vl1);
        s1000 = __riscv_vget_f32m1(r113, 0);
        s1001 = __riscv_vget_f32m1(r113, 1);
        r114 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((8)*(l1)))))), vl1);
        s1002 = __riscv_vget_f32m1(r114, 0);
        s1003 = __riscv_vget_f32m1(r114, 1);
        r115 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((9)*(l1)))))), vl1);
        s1004 = __riscv_vget_f32m1(r115, 0);
        s1005 = __riscv_vget_f32m1(r115, 1);
        r116 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((10)*(l1)))))), vl1);
        s1006 = __riscv_vget_f32m1(r116, 0);
        s1007 = __riscv_vget_f32m1(r116, 1);
        r117 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((11)*(l1)))))), vl1);
        s1008 = __riscv_vget_f32m1(r117, 0);
        s1009 = __riscv_vget_f32m1(r117, 1);
        r118 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((12)*(l1)))))), vl1);
        s1010 = __riscv_vget_f32m1(r118, 0);
        s1011 = __riscv_vget_f32m1(r118, 1);
        r119 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((13)*(l1)))))), vl1);
        s1012 = __riscv_vget_f32m1(r119, 0);
        s1013 = __riscv_vget_f32m1(r119, 1);
        r120 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((14)*(l1)))))), vl1);
        s1014 = __riscv_vget_f32m1(r120, 0);
        s1015 = __riscv_vget_f32m1(r120, 1);
        t2301 = __riscv_vfadd(s992, s1010, vl1);
        t2302 = __riscv_vfadd(s993, s1011, vl1);
        t2303 = __riscv_vfsub(s992, s1010, vl1);
        t2304 = __riscv_vfsub(s993, s1011, vl1);
        t2305 = __riscv_vfadd(s998, s1004, vl1);
        t2306 = __riscv_vfadd(s999, s1005, vl1);
        t2307 = __riscv_vfsub(s998, s1004, vl1);
        t2308 = __riscv_vfsub(s999, s1005, vl1);
        t2309 = __riscv_vfadd(t2301, t2305, vl1);
        t2310 = __riscv_vfadd(t2302, t2306, vl1);
        t2311 = __riscv_vfadd(t2303, t2308, vl1);
        t2312 = __riscv_vfsub(t2304, t2307, vl1);
        t2313 = __riscv_vfsub(t2303, t2308, vl1);
        t2314 = __riscv_vfadd(t2304, t2307, vl1);
        t2315 = __riscv_vfadd(s986, t2309, vl1);
        t2316 = __riscv_vfadd(s987, t2310, vl1);
        t2317 = __riscv_vfnmsac(s986, 0.25, t2309, vl1);
        t2318 = __riscv_vfnmsac(s987, 0.25, t2310, vl1);
        s1118 = __riscv_vfmacc(t2311, 1.6180339887498947, t2312, vl1);
        s1016 = __riscv_vfmul(s1118, 0.29389262614623657, vl1);
        s1119 = __riscv_vfnmsac(t2312, 1.6180339887498947, t2311, vl1);
        s1017 = __riscv_vfmul(s1119, 0.29389262614623657, vl1);
        s1018 = __riscv_vfmul(__riscv_vfsub(t2301, t2305, vl1), 0.55901699437494745, vl1);
        s1019 = __riscv_vfmul(__riscv_vfsub(t2302, t2306, vl1), 0.55901699437494745, vl1);
        s1120 = __riscv_vfnmsac(t2314, 0.6180339887498949, t2313, vl1);
        s1020 = __riscv_vfmul(s1120, 0.47552825814757677, vl1);
        s1121 = __riscv_vfmacc(t2313, 0.6180339887498949, t2314, vl1);
        s1021 = __riscv_vfmul(s1121, 0.47552825814757677, vl1);
        t2319 = __riscv_vfadd(t2317, s1018, vl1);
        t2320 = __riscv_vfadd(t2318, s1019, vl1);
        t2321 = __riscv_vfsub(t2317, s1018, vl1);
        t2322 = __riscv_vfsub(t2318, s1019, vl1);
        t2323 = __riscv_vfadd(s1016, s1020, vl1);
        t2324 = __riscv_vfsub(s1017, s1021, vl1);
        t2325 = __riscv_vfsub(s1016, s1020, vl1);
        t2326 = __riscv_vfadd(s1017, s1021, vl1);
        t2327 = __riscv_vfadd(t2319, t2323, vl1);
        t2328 = __riscv_vfadd(t2320, t2324, vl1);
        t2329 = __riscv_vfsub(t2319, t2323, vl1);
        t2330 = __riscv_vfsub(t2320, t2324, vl1);
        t2331 = __riscv_vfadd(t2321, t2326, vl1);
        t2332 = __riscv_vfsub(t2322, t2325, vl1);
        t2333 = __riscv_vfsub(t2321, t2326, vl1);
        t2334 = __riscv_vfadd(t2322, t2325, vl1);
        t2335 = __riscv_vfadd(s994, s1012, vl1);
        t2336 = __riscv_vfadd(s995, s1013, vl1);
        t2337 = __riscv_vfsub(s994, s1012, vl1);
        t2338 = __riscv_vfsub(s995, s1013, vl1);
        t2339 = __riscv_vfadd(s1000, s1006, vl1);
        t2340 = __riscv_vfadd(s1001, s1007, vl1);
        t2341 = __riscv_vfsub(s1000, s1006, vl1);
        t2342 = __riscv_vfsub(s1001, s1007, vl1);
        t2343 = __riscv_vfadd(t2335, t2339, vl1);
        t2344 = __riscv_vfadd(t2336, t2340, vl1);
        t2345 = __riscv_vfadd(t2337, t2342, vl1);
        t2346 = __riscv_vfsub(t2338, t2341, vl1);
        t2347 = __riscv_vfsub(t2337, t2342, vl1);
        t2348 = __riscv_vfadd(t2338, t2341, vl1);
        t2349 = __riscv_vfadd(s988, t2343, vl1);
        t2350 = __riscv_vfadd(s989, t2344, vl1);
        t2351 = __riscv_vfnmsac(s988, 0.25, t2343, vl1);
        t2352 = __riscv_vfnmsac(s989, 0.25, t2344, vl1);
        s1122 = __riscv_vfmacc(t2345, 1.6180339887498947, t2346, vl1);
        s1022 = __riscv_vfmul(s1122, 0.29389262614623657, vl1);
        s1123 = __riscv_vfnmsac(t2346, 1.6180339887498947, t2345, vl1);
        s1023 = __riscv_vfmul(s1123, 0.29389262614623657, vl1);
        s1024 = __riscv_vfmul(__riscv_vfsub(t2335, t2339, vl1), 0.55901699437494745, vl1);
        s1025 = __riscv_vfmul(__riscv_vfsub(t2336, t2340, vl1), 0.55901699437494745, vl1);
        s1124 = __riscv_vfnmsac(t2348, 0.6180339887498949, t2347, vl1);
        s1026 = __riscv_vfmul(s1124, 0.47552825814757677, vl1);
        s1125 = __riscv_vfmacc(t2347, 0.6180339887498949, t2348, vl1);
        s1027 = __riscv_vfmul(s1125, 0.47552825814757677, vl1);
        t2353 = __riscv_vfadd(t2351, s1024, vl1);
        t2354 = __riscv_vfadd(t2352, s1025, vl1);
        t2355 = __riscv_vfsub(t2351, s1024, vl1);
        t2356 = __riscv_vfsub(t2352, s1025, vl1);
        t2357 = __riscv_vfadd(s1022, s1026, vl1);
        t2358 = __riscv_vfsub(s1023, s1027, vl1);
        t2359 = __riscv_vfsub(s1022, s1026, vl1);
        t2360 = __riscv_vfadd(s1023, s1027, vl1);
        t2361 = __riscv_vfadd(t2353, t2357, vl1);
        t2362 = __riscv_vfadd(t2354, t2358, vl1);
        t2363 = __riscv_vfsub(t2353, t2357, vl1);
        t2364 = __riscv_vfsub(t2354, t2358, vl1);
        s1126 = __riscv_vfmacc(t2361, 0.44522868530853615, t2362, vl1);
        s1028 = __riscv_vfmul(s1126, 0.91354545764260087, vl1);
        s1127 = __riscv_vfnmsac(t2362, 0.44522868530853615, t2361, vl1);
        s1029 = __riscv_vfmul(s1127, 0.91354545764260087, vl1);
        s1128 = __riscv_vfnmsac(t2364, 0.10510423526567647, t2363, vl1);
        s1030 = __riscv_vfmul(s1128, 0.99452189536827329, vl1);
        s1129 = __riscv_vfmacc(t2363, 0.10510423526567647, t2364, vl1);
        s1031 = __riscv_vfmul(s1129, 0.99452189536827329, vl1);
        t2365 = __riscv_vfadd(t2355, t2360, vl1);
        t2366 = __riscv_vfsub(t2356, t2359, vl1);
        t2367 = __riscv_vfsub(t2355, t2360, vl1);
        t2368 = __riscv_vfadd(t2356, t2359, vl1);
        s1130 = __riscv_vfmacc(t2365, 1.1106125148291928, t2366, vl1);
        s1032 = __riscv_vfmul(s1130, 0.66913060635885824, vl1);
        s1131 = __riscv_vfnmsac(t2366, 1.1106125148291928, t2365, vl1);
        s1033 = __riscv_vfmul(s1131, 0.66913060635885824, vl1);
        s1132 = __riscv_vfmacc(t2367, 3.0776835371752536, t2368, vl1);
        s1034 = __riscv_vfmul(s1132, 0.3090169943749474, vl1);
        s1133 = __riscv_vfnmsac(t2368, 3.0776835371752536, t2367, vl1);
        s1035 = __riscv_vfmul(s1133, 0.3090169943749474, vl1);
        t2369 = __riscv_vfadd(s996, s1014, vl1);
        t2370 = __riscv_vfadd(s997, s1015, vl1);
        t2371 = __riscv_vfsub(s996, s1014, vl1);
        t2372 = __riscv_vfsub(s997, s1015, vl1);
        t2373 = __riscv_vfadd(s1002, s1008, vl1);
        t2374 = __riscv_vfadd(s1003, s1009, vl1);
        t2375 = __riscv_vfsub(s1002, s1008, vl1);
        t2376 = __riscv_vfsub(s1003, s1009, vl1);
        t2377 = __riscv_vfadd(t2369, t2373, vl1);
        t2378 = __riscv_vfadd(t2370, t2374, vl1);
        t2379 = __riscv_vfadd(t2371, t2376, vl1);
        t2380 = __riscv_vfsub(t2372, t2375, vl1);
        t2381 = __riscv_vfsub(t2371, t2376, vl1);
        t2382 = __riscv_vfadd(t2372, t2375, vl1);
        t2383 = __riscv_vfadd(s990, t2377, vl1);
        t2384 = __riscv_vfadd(s991, t2378, vl1);
        t2385 = __riscv_vfnmsac(s990, 0.25, t2377, vl1);
        t2386 = __riscv_vfnmsac(s991, 0.25, t2378, vl1);
        s1134 = __riscv_vfmacc(t2379, 1.6180339887498947, t2380, vl1);
        s1036 = __riscv_vfmul(s1134, 0.29389262614623657, vl1);
        s1135 = __riscv_vfnmsac(t2380, 1.6180339887498947, t2379, vl1);
        s1037 = __riscv_vfmul(s1135, 0.29389262614623657, vl1);
        s1038 = __riscv_vfmul(__riscv_vfsub(t2369, t2373, vl1), 0.55901699437494745, vl1);
        s1039 = __riscv_vfmul(__riscv_vfsub(t2370, t2374, vl1), 0.55901699437494745, vl1);
        s1136 = __riscv_vfnmsac(t2382, 0.6180339887498949, t2381, vl1);
        s1040 = __riscv_vfmul(s1136, 0.47552825814757677, vl1);
        s1137 = __riscv_vfmacc(t2381, 0.6180339887498949, t2382, vl1);
        s1041 = __riscv_vfmul(s1137, 0.47552825814757677, vl1);
        t2387 = __riscv_vfadd(t2385, s1038, vl1);
        t2388 = __riscv_vfadd(t2386, s1039, vl1);
        t2389 = __riscv_vfsub(t2385, s1038, vl1);
        t2390 = __riscv_vfsub(t2386, s1039, vl1);
        t2391 = __riscv_vfadd(s1036, s1040, vl1);
        t2392 = __riscv_vfsub(s1037, s1041, vl1);
        t2393 = __riscv_vfsub(s1036, s1040, vl1);
        t2394 = __riscv_vfadd(s1037, s1041, vl1);
        t2395 = __riscv_vfadd(t2387, t2391, vl1);
        t2396 = __riscv_vfadd(t2388, t2392, vl1);
        t2397 = __riscv_vfsub(t2387, t2391, vl1);
        t2398 = __riscv_vfsub(t2388, t2392, vl1);
        s1138 = __riscv_vfmacc(t2395, 1.1106125148291928, t2396, vl1);
        s1042 = __riscv_vfmul(s1138, 0.66913060635885824, vl1);
        s1139 = __riscv_vfnmsac(t2396, 1.1106125148291928, t2395, vl1);
        s1043 = __riscv_vfmul(s1139, 0.66913060635885824, vl1);
        s1140 = __riscv_vfmacc(t2397, 0.21255656167002213, t2398, vl1);
        s1044 = __riscv_vfmul(s1140, 0.97814760073380569, vl1);
        s1141 = __riscv_vfnmsac(t2397, 4.7046301094784546, t2398, vl1);
        s1045 = __riscv_vfmul(s1141, 0.20791169081775934, vl1);
        t2399 = __riscv_vfadd(t2389, t2394, vl1);
        t2400 = __riscv_vfsub(t2390, t2393, vl1);
        t2401 = __riscv_vfsub(t2389, t2394, vl1);
        t2402 = __riscv_vfadd(t2390, t2393, vl1);
        s1142 = __riscv_vfnmsac(t2400, 0.10510423526567647, t2399, vl1);
        s1046 = __riscv_vfmul(s1142, 0.99452189536827329, vl1);
        s1143 = __riscv_vfmacc(t2399, 0.10510423526567647, t2400, vl1);
        s1047 = __riscv_vfmul(s1143, 0.99452189536827329, vl1);
        s1144 = __riscv_vfnmsac(t2402, 1.3763819204711736, t2401, vl1);
        s1048 = __riscv_vfmul(s1144, 0.58778525229247314, vl1);
        s1145 = __riscv_vfmacc(t2401, 1.3763819204711736, t2402, vl1);
        s1049 = __riscv_vfmul(s1145, 0.58778525229247314, vl1);
        t2403 = __riscv_vfadd(t2349, t2383, vl1);
        t2404 = __riscv_vfadd(t2350, t2384, vl1);
        t2405 = __riscv_vfnmsac(t2315, 0.5, t2403, vl1);
        t2406 = __riscv_vfnmsac(t2316, 0.5, t2404, vl1);
        s1050 = __riscv_vfmul(__riscv_vfsub(t2350, t2384, vl1), 0.8660254037844386, vl1);
        s1051 = __riscv_vfmul(__riscv_vfsub(t2349, t2383, vl1), 0.8660254037844386, vl1);
        s1052 = __riscv_vfadd(t2315, t2403, vl1);
        s1053 = __riscv_vfadd(t2316, t2404, vl1);
        s1054 = __riscv_vfadd(t2405, s1050, vl1);
        s1055 = __riscv_vfsub(t2406, s1051, vl1);
        s1056 = __riscv_vfsub(t2405, s1050, vl1);
        s1057 = __riscv_vfadd(t2406, s1051, vl1);
        t2407 = __riscv_vfadd(s1028, s1042, vl1);
        t2408 = __riscv_vfadd(s1029, s1043, vl1);
        t2409 = __riscv_vfnmsac(t2327, 0.5, t2407, vl1);
        t2410 = __riscv_vfnmsac(t2328, 0.5, t2408, vl1);
        s1058 = __riscv_vfmul(__riscv_vfsub(s1029, s1043, vl1), 0.8660254037844386, vl1);
        s1059 = __riscv_vfmul(__riscv_vfsub(s1028, s1042, vl1), 0.8660254037844386, vl1);
        s1060 = __riscv_vfadd(t2327, t2407, vl1);
        s1061 = __riscv_vfadd(t2328, t2408, vl1);
        s1062 = __riscv_vfadd(t2409, s1058, vl1);
        s1063 = __riscv_vfsub(t2410, s1059, vl1);
        s1064 = __riscv_vfsub(t2409, s1058, vl1);
        s1065 = __riscv_vfadd(t2410, s1059, vl1);
        t2411 = __riscv_vfadd(s1032, s1046, vl1);
        t2412 = __riscv_vfsub(s1033, s1047, vl1);
        t2413 = __riscv_vfnmsac(t2331, 0.5, t2411, vl1);
        t2414 = __riscv_vfnmsac(t2332, 0.5, t2412, vl1);
        s1066 = __riscv_vfmul(__riscv_vfadd(s1033, s1047, vl1), 0.8660254037844386, vl1);
        s1067 = __riscv_vfmul(__riscv_vfsub(s1032, s1046, vl1), 0.8660254037844386, vl1);
        s1068 = __riscv_vfadd(t2331, t2411, vl1);
        s1069 = __riscv_vfadd(t2332, t2412, vl1);
        s1070 = __riscv_vfadd(t2413, s1066, vl1);
        s1071 = __riscv_vfsub(t2414, s1067, vl1);
        s1072 = __riscv_vfsub(t2413, s1066, vl1);
        s1073 = __riscv_vfadd(t2414, s1067, vl1);
        t2415 = __riscv_vfadd(s1034, s1048, vl1);
        t2416 = __riscv_vfsub(s1035, s1049, vl1);
        t2417 = __riscv_vfnmsac(t2333, 0.5, t2415, vl1);
        t2418 = __riscv_vfnmsac(t2334, 0.5, t2416, vl1);
        s1074 = __riscv_vfmul(__riscv_vfadd(s1035, s1049, vl1), 0.8660254037844386, vl1);
        s1075 = __riscv_vfmul(__riscv_vfsub(s1034, s1048, vl1), 0.8660254037844386, vl1);
        s1076 = __riscv_vfadd(t2333, t2415, vl1);
        s1077 = __riscv_vfadd(t2334, t2416, vl1);
        s1078 = __riscv_vfadd(t2417, s1074, vl1);
        s1079 = __riscv_vfsub(t2418, s1075, vl1);
        s1080 = __riscv_vfsub(t2417, s1074, vl1);
        s1081 = __riscv_vfadd(t2418, s1075, vl1);
        t2419 = __riscv_vfsub(s1030, s1044, vl1);
        t2420 = __riscv_vfsub(s1045, s1031, vl1);
        t2421 = __riscv_vfnmsac(t2329, 0.5, t2419, vl1);
        t2422 = __riscv_vfnmsac(t2330, 0.5, t2420, vl1);
        s1082 = __riscv_vfmul(__riscv_vfadd(s1031, s1045, vl1), 0.8660254037844386, vl1);
        s1083 = __riscv_vfmul(__riscv_vfadd(s1030, s1044, vl1), 0.8660254037844386, vl1);
        s1084 = __riscv_vfadd(t2329, t2419, vl1);
        s1085 = __riscv_vfadd(t2330, t2420, vl1);
        s1086 = __riscv_vfsub(t2421, s1082, vl1);
        s1087 = __riscv_vfsub(t2422, s1083, vl1);
        s1088 = __riscv_vfadd(t2421, s1082, vl1);
        s1089 = __riscv_vfadd(t2422, s1083, vl1);
        a1724 = (TW1 + ((28)*(j1)));
        a1725 = __riscv_vlse32_v_f32m1(a1724, sizeof(double) * 28, vl1);
        a1726 = __riscv_vlse32_v_f32m1((a1724 + 1), sizeof(double) * 28, vl1);
        s1090 = __riscv_vfmsac(__riscv_vfmul(a1726, s1061, vl1), a1725, s1060, vl1);
        s1091 = __riscv_vfmacc(__riscv_vfmul(a1725, s1061, vl1), a1726, s1060, vl1);
        a1727 = __riscv_vlse32_v_f32m1((a1724 + 2), sizeof(double) * 28, vl1);
        a1728 = __riscv_vlse32_v_f32m1((a1724 + 3), sizeof(double) * 28, vl1);
        s1092 = __riscv_vfmsac(__riscv_vfmul(a1728, s1069, vl1), a1727, s1068, vl1);
        s1093 = __riscv_vfmacc(__riscv_vfmul(a1727, s1069, vl1), a1728, s1068, vl1);
        a1729 = __riscv_vlse32_v_f32m1((a1724 + 4), sizeof(double) * 28, vl1);
        a1730 = __riscv_vlse32_v_f32m1((a1724 + 5), sizeof(double) * 28, vl1);
        s1094 = __riscv_vfmsac(__riscv_vfmul(a1730, s1077, vl1), a1729, s1076, vl1);
        s1095 = __riscv_vfmacc(__riscv_vfmul(a1729, s1077, vl1), a1730, s1076, vl1);
        a1731 = __riscv_vlse32_v_f32m1((a1724 + 6), sizeof(double) * 28, vl1);
        a1732 = __riscv_vlse32_v_f32m1((a1724 + 7), sizeof(double) * 28, vl1);
        s1096 = __riscv_vfmsac(__riscv_vfmul(a1732, s1085, vl1), a1731, s1084, vl1);
        s1097 = __riscv_vfmacc(__riscv_vfmul(a1731, s1085, vl1), a1732, s1084, vl1);
        a1733 = __riscv_vlse32_v_f32m1((a1724 + 8), sizeof(double) * 28, vl1);
        a1734 = __riscv_vlse32_v_f32m1((a1724 + 9), sizeof(double) * 28, vl1);
        s1098 = __riscv_vfmsac(__riscv_vfmul(a1734, s1055, vl1), a1733, s1054, vl1);
        s1099 = __riscv_vfmacc(__riscv_vfmul(a1733, s1055, vl1), a1734, s1054, vl1);
        a1735 = __riscv_vlse32_v_f32m1((a1724 + 10), sizeof(double) * 28, vl1);
        a1736 = __riscv_vlse32_v_f32m1((a1724 + 11), sizeof(double) * 28, vl1);
        s1100 = __riscv_vfmsac(__riscv_vfmul(a1736, s1063, vl1), a1735, s1062, vl1);
        s1101 = __riscv_vfmacc(__riscv_vfmul(a1735, s1063, vl1), a1736, s1062, vl1);
        a1737 = __riscv_vlse32_v_f32m1((a1724 + 12), sizeof(double) * 28, vl1);
        a1738 = __riscv_vlse32_v_f32m1((a1724 + 13), sizeof(double) * 28, vl1);
        s1102 = __riscv_vfmsac(__riscv_vfmul(a1738, s1071, vl1), a1737, s1070, vl1);
        s1103 = __riscv_vfmacc(__riscv_vfmul(a1737, s1071, vl1), a1738, s1070, vl1);
        a1739 = __riscv_vlse32_v_f32m1((a1724 + 14), sizeof(double) * 28, vl1);
        a1740 = __riscv_vlse32_v_f32m1((a1724 + 15), sizeof(double) * 28, vl1);
        s1104 = __riscv_vfmsac(__riscv_vfmul(a1740, s1079, vl1), a1739, s1078, vl1);
        s1105 = __riscv_vfmacc(__riscv_vfmul(a1739, s1079, vl1), a1740, s1078, vl1);
        a1741 = __riscv_vlse32_v_f32m1((a1724 + 16), sizeof(double) * 28, vl1);
        a1742 = __riscv_vlse32_v_f32m1((a1724 + 17), sizeof(double) * 28, vl1);
        s1106 = __riscv_vfmsac(__riscv_vfmul(a1742, s1087, vl1), a1741, s1086, vl1);
        s1107 = __riscv_vfmacc(__riscv_vfmul(a1741, s1087, vl1), a1742, s1086, vl1);
        a1743 = __riscv_vlse32_v_f32m1((a1724 + 18), sizeof(double) * 28, vl1);
        a1744 = __riscv_vlse32_v_f32m1((a1724 + 19), sizeof(double) * 28, vl1);
        s1108 = __riscv_vfmsac(__riscv_vfmul(a1744, s1057, vl1), a1743, s1056, vl1);
        s1109 = __riscv_vfmacc(__riscv_vfmul(a1743, s1057, vl1), a1744, s1056, vl1);
        a1745 = __riscv_vlse32_v_f32m1((a1724 + 20), sizeof(double) * 28, vl1);
        a1746 = __riscv_vlse32_v_f32m1((a1724 + 21), sizeof(double) * 28, vl1);
        s1110 = __riscv_vfmsac(__riscv_vfmul(a1746, s1065, vl1), a1745, s1064, vl1);
        s1111 = __riscv_vfmacc(__riscv_vfmul(a1745, s1065, vl1), a1746, s1064, vl1);
        a1747 = __riscv_vlse32_v_f32m1((a1724 + 22), sizeof(double) * 28, vl1);
        a1748 = __riscv_vlse32_v_f32m1((a1724 + 23), sizeof(double) * 28, vl1);
        s1112 = __riscv_vfmsac(__riscv_vfmul(a1748, s1073, vl1), a1747, s1072, vl1);
        s1113 = __riscv_vfmacc(__riscv_vfmul(a1747, s1073, vl1), a1748, s1072, vl1);
        a1749 = __riscv_vlse32_v_f32m1((a1724 + 24), sizeof(double) * 28, vl1);
        a1750 = __riscv_vlse32_v_f32m1((a1724 + 25), sizeof(double) * 28, vl1);
        s1114 = __riscv_vfmsac(__riscv_vfmul(a1750, s1081, vl1), a1749, s1080, vl1);
        s1115 = __riscv_vfmacc(__riscv_vfmul(a1749, s1081, vl1), a1750, s1080, vl1);
        a1751 = __riscv_vlse32_v_f32m1((a1724 + 26), sizeof(double) * 28, vl1);
        a1752 = __riscv_vlse32_v_f32m1((a1724 + 27), sizeof(double) * 28, vl1);
        s1116 = __riscv_vfmsac(__riscv_vfmul(a1752, s1089, vl1), a1751, s1088, vl1);
        s1117 = __riscv_vfmacc(__riscv_vfmul(a1751, s1089, vl1), a1752, s1088, vl1);
        __riscv_vsse32((Y + ((30)*(j1))), sizeof(double) * 30, s1052, vl1);
        __riscv_vsse32((1 + Y + ((30)*(j1))), sizeof(double) * 30, s1053, vl1);
        __riscv_vsse32((2 + Y + ((30)*(j1))), sizeof(double) * 30, s1090, vl1);
        __riscv_vsse32((3 + Y + ((30)*(j1))), sizeof(double) * 30, s1091, vl1);
        __riscv_vsse32((4 + Y + ((30)*(j1))), sizeof(double) * 30, s1092, vl1);
        __riscv_vsse32((5 + Y + ((30)*(j1))), sizeof(double) * 30, s1093, vl1);
        __riscv_vsse32((6 + Y + ((30)*(j1))), sizeof(double) * 30, s1094, vl1);
        __riscv_vsse32((7 + Y + ((30)*(j1))), sizeof(double) * 30, s1095, vl1);
        __riscv_vsse32((8 + Y + ((30)*(j1))), sizeof(double) * 30, s1096, vl1);
        __riscv_vsse32((9 + Y + ((30)*(j1))), sizeof(double) * 30, s1097, vl1);
        __riscv_vsse32((10 + Y + ((30)*(j1))), sizeof(double) * 30, s1098, vl1);
        __riscv_vsse32((11 + Y + ((30)*(j1))), sizeof(double) * 30, s1099, vl1);
        __riscv_vsse32((12 + Y + ((30)*(j1))), sizeof(double) * 30, s1100, vl1);
        __riscv_vsse32((13 + Y + ((30)*(j1))), sizeof(double) * 30, s1101, vl1);
        __riscv_vsse32((14 + Y + ((30)*(j1))), sizeof(double) * 30, s1102, vl1);
        __riscv_vsse32((15 + Y + ((30)*(j1))), sizeof(double) * 30, s1103, vl1);
        __riscv_vsse32((16 + Y + ((30)*(j1))), sizeof(double) * 30, s1104, vl1);
        __riscv_vsse32((17 + Y + ((30)*(j1))), sizeof(double) * 30, s1105, vl1);
        __riscv_vsse32((18 + Y + ((30)*(j1))), sizeof(double) * 30, s1106, vl1);
        __riscv_vsse32((19 + Y + ((30)*(j1))), sizeof(double) * 30, s1107, vl1);
        __riscv_vsse32((20 + Y + ((30)*(j1))), sizeof(double) * 30, s1108, vl1);
        __riscv_vsse32((21 + Y + ((30)*(j1))), sizeof(double) * 30, s1109, vl1);
        __riscv_vsse32((22 + Y + ((30)*(j1))), sizeof(double) * 30, s1110, vl1);
        __riscv_vsse32((23 + Y + ((30)*(j1))), sizeof(double) * 30, s1111, vl1);
        __riscv_vsse32((24 + Y + ((30)*(j1))), sizeof(double) * 30, s1112, vl1);
        __riscv_vsse32((25 + Y + ((30)*(j1))), sizeof(double) * 30, s1113, vl1);
        __riscv_vsse32((26 + Y + ((30)*(j1))), sizeof(double) * 30, s1114, vl1);
        __riscv_vsse32((27 + Y + ((30)*(j1))), sizeof(double) * 30, s1115, vl1);
        __riscv_vsse32((28 + Y + ((30)*(j1))), sizeof(double) * 30, s1116, vl1);
        __riscv_vsse32((29 + Y + ((30)*(j1))), sizeof(double) * 30, s1117, vl1);
    }
}
