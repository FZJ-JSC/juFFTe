// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft15b_(double *Y, double *X, double *TW1, int *lp1, int *mp1) {
    double a1862, a1863, a1864, a1865, a1866, a1867, a1868, a1869, 
            a1870, a1871, a1872, a1873, a1874, a1875, a1876, a1877, 
            a1878, a1879, a1880, a1881, a1882, a1883, a1884, a1885, 
            a1886, a1887, a1888, a1889;
    int a1860, a1861, j1, l1, m1;
    vfloat64m1x2_t r241, r242, r243, r244, r245, r246, r247, r248, 
            r249, r250, r251, r252, r253, r254, r255, r256, 
            r257, r258, r259, r260, r261, r262, r263, r264, 
            r265, r266, r267, r268, r269, r270, rvvx2_16, rvvx2_17, 
            rvvx2_18, rvvx2_19, rvvx2_20, rvvx2_21, rvvx2_22, rvvx2_23, rvvx2_24, rvvx2_25, 
            rvvx2_26, rvvx2_27, rvvx2_28, rvvx2_29, rvvx2_30;
    vfloat64m1_t  s1000, s1001, s1002, s1003, s1004, s1005, s1006, s1007, 
            s1008, s1009, s1010, s1011, s1012, s1013, s1014, s1015, 
            s1016, s1017, s1018, s1019, s1020, s1021, s1022, s1023, 
            s1024, s1025, s1026, s1027, s1028, s1029, s1030, s1031, 
            s1032, s1033, s1034, s1035, s1036, s1037, s1038, s1039, 
            s1040, s1041, s1042, s1043, s1044, s1045, s1046, s1047, 
            s1048, s1049, s1050, s1051, s1052, s1053, s1054, s1055, 
            s1056, s1057, s1058, s1059, s1060, s1061, s1062, s1063, 
            s1064, s1065, s1066, s1067, s1068, s1069, s1070, s1071, 
            s1072, s1073, s1074, s1075, s1076, s1077, s1078, s1079, 
            s1080, s1081, s1082, s1083, s1084, s1085, s956, s957, 
            s958, s959, s960, s961, s962, s963, s964, s965, 
            s966, s967, s968, s969, s970, s971, s972, s973, 
            s974, s975, s976, s977, s978, s979, s980, s981, 
            s982, s983, s984, s985, s986, s987, s988, s989, 
            s990, s991, s992, s993, s994, s995, s996, s997, 
            s998, s999, t2301, t2302, t2303, t2304, t2305, t2306, 
            t2307, t2308, t2309, t2310, t2311, t2312, t2313, t2314, 
            t2315, t2316, t2317, t2318, t2319, t2320, t2321, t2322, 
            t2323, t2324, t2325, t2326, t2327, t2328, t2329, t2330, 
            t2331, t2332, t2333, t2334, t2335, t2336, t2337, t2338, 
            t2339, t2340, t2341, t2342, t2343, t2344, t2345, t2346, 
            t2347, t2348, t2349, t2350, t2351, t2352, t2353, t2354, 
            t2355, t2356, t2357, t2358, t2359, t2360, t2361, t2362, 
            t2363, t2364, t2365, t2366, t2367, t2368, t2369, t2370, 
            t2371, t2372, t2373, t2374, t2375, t2376, t2377, t2378, 
            t2379, t2380, t2381, t2382, t2383, t2384, t2385, t2386, 
            t2387, t2388, t2389, t2390, t2391, t2392, t2393, t2394, 
            t2395, t2396, t2397, t2398, t2399, t2400, t2401, t2402, 
            t2403, t2404, t2405, t2406, t2407, t2408, t2409, t2410, 
            t2411, t2412, t2413, t2414, t2415, t2416, t2417, t2418, 
            t2419, t2420, t2421, t2422;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for(int j1 = 1; j1 < l1; j1++) {
        for (size_t k1 = 0; k1 < m1; k1 += vl1) {
            vl1 = __riscv_vsetvl_e64m1(m1 - k1);
            a1860 = (k1 + ((j1)*(m1)));
            r241 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(a1860))), vl1);
            s956 = __riscv_vget_f64m1(r241, 0);
            s957 = __riscv_vget_f64m1(r241, 1);
            r242 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((l1)*(m1)))))), vl1);
            s958 = __riscv_vget_f64m1(r242, 0);
            s959 = __riscv_vget_f64m1(r242, 1);
            r243 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((((2)*(l1)))*(m1)))))), vl1);
            s960 = __riscv_vget_f64m1(r243, 0);
            s961 = __riscv_vget_f64m1(r243, 1);
            r244 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((((3)*(l1)))*(m1)))))), vl1);
            s962 = __riscv_vget_f64m1(r244, 0);
            s963 = __riscv_vget_f64m1(r244, 1);
            r245 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((((4)*(l1)))*(m1)))))), vl1);
            s964 = __riscv_vget_f64m1(r245, 0);
            s965 = __riscv_vget_f64m1(r245, 1);
            r246 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((((5)*(l1)))*(m1)))))), vl1);
            s966 = __riscv_vget_f64m1(r246, 0);
            s967 = __riscv_vget_f64m1(r246, 1);
            r247 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((((6)*(l1)))*(m1)))))), vl1);
            s968 = __riscv_vget_f64m1(r247, 0);
            s969 = __riscv_vget_f64m1(r247, 1);
            r248 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((((7)*(l1)))*(m1)))))), vl1);
            s970 = __riscv_vget_f64m1(r248, 0);
            s971 = __riscv_vget_f64m1(r248, 1);
            r249 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((((8)*(l1)))*(m1)))))), vl1);
            s972 = __riscv_vget_f64m1(r249, 0);
            s973 = __riscv_vget_f64m1(r249, 1);
            r250 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((((9)*(l1)))*(m1)))))), vl1);
            s974 = __riscv_vget_f64m1(r250, 0);
            s975 = __riscv_vget_f64m1(r250, 1);
            r251 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((((10)*(l1)))*(m1)))))), vl1);
            s976 = __riscv_vget_f64m1(r251, 0);
            s977 = __riscv_vget_f64m1(r251, 1);
            r252 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((((11)*(l1)))*(m1)))))), vl1);
            s978 = __riscv_vget_f64m1(r252, 0);
            s979 = __riscv_vget_f64m1(r252, 1);
            r253 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((((12)*(l1)))*(m1)))))), vl1);
            s980 = __riscv_vget_f64m1(r253, 0);
            s981 = __riscv_vget_f64m1(r253, 1);
            r254 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((((13)*(l1)))*(m1)))))), vl1);
            s982 = __riscv_vget_f64m1(r254, 0);
            s983 = __riscv_vget_f64m1(r254, 1);
            r255 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((a1860 + ((((14)*(l1)))*(m1)))))), vl1);
            s984 = __riscv_vget_f64m1(r255, 0);
            s985 = __riscv_vget_f64m1(r255, 1);
            t2301 = __riscv_vfadd(s962, s980, vl1);
            t2302 = __riscv_vfadd(s963, s981, vl1);
            t2303 = __riscv_vfsub(s962, s980, vl1);
            t2304 = __riscv_vfsub(s963, s981, vl1);
            t2305 = __riscv_vfadd(s968, s974, vl1);
            t2306 = __riscv_vfadd(s969, s975, vl1);
            t2307 = __riscv_vfsub(s968, s974, vl1);
            t2308 = __riscv_vfsub(s969, s975, vl1);
            t2309 = __riscv_vfadd(t2301, t2305, vl1);
            t2310 = __riscv_vfadd(t2302, t2306, vl1);
            t2311 = __riscv_vfadd(t2303, t2308, vl1);
            t2312 = __riscv_vfsub(t2304, t2307, vl1);
            t2313 = __riscv_vfsub(t2303, t2308, vl1);
            t2314 = __riscv_vfadd(t2304, t2307, vl1);
            t2315 = __riscv_vfadd(s956, t2309, vl1);
            t2316 = __riscv_vfadd(s957, t2310, vl1);
            t2317 = __riscv_vfnmsac(s956, 0.25, t2309, vl1);
            t2318 = __riscv_vfnmsac(s957, 0.25, t2310, vl1);
            s1058 = __riscv_vfmacc(t2311, 1.6180339887498947, t2312, vl1);
            s986 = __riscv_vfmul(s1058, 0.29389262614623657, vl1);
            s1059 = __riscv_vfnmsac(t2312, 1.6180339887498947, t2311, vl1);
            s987 = __riscv_vfmul(s1059, 0.29389262614623657, vl1);
            s988 = __riscv_vfmul(__riscv_vfsub(t2301, t2305, vl1), 0.55901699437494745, vl1);
            s989 = __riscv_vfmul(__riscv_vfsub(t2302, t2306, vl1), 0.55901699437494745, vl1);
            s1060 = __riscv_vfnmsac(t2314, 0.6180339887498949, t2313, vl1);
            s990 = __riscv_vfmul(s1060, 0.47552825814757677, vl1);
            s1061 = __riscv_vfmacc(t2313, 0.6180339887498949, t2314, vl1);
            s991 = __riscv_vfmul(s1061, 0.47552825814757677, vl1);
            t2319 = __riscv_vfadd(t2317, s988, vl1);
            t2320 = __riscv_vfadd(t2318, s989, vl1);
            t2321 = __riscv_vfsub(t2317, s988, vl1);
            t2322 = __riscv_vfsub(t2318, s989, vl1);
            t2323 = __riscv_vfadd(s986, s990, vl1);
            t2324 = __riscv_vfsub(s987, s991, vl1);
            t2325 = __riscv_vfsub(s986, s990, vl1);
            t2326 = __riscv_vfadd(s987, s991, vl1);
            t2327 = __riscv_vfadd(t2319, t2323, vl1);
            t2328 = __riscv_vfadd(t2320, t2324, vl1);
            t2329 = __riscv_vfsub(t2319, t2323, vl1);
            t2330 = __riscv_vfsub(t2320, t2324, vl1);
            t2331 = __riscv_vfadd(t2321, t2326, vl1);
            t2332 = __riscv_vfsub(t2322, t2325, vl1);
            t2333 = __riscv_vfsub(t2321, t2326, vl1);
            t2334 = __riscv_vfadd(t2322, t2325, vl1);
            t2335 = __riscv_vfadd(s964, s982, vl1);
            t2336 = __riscv_vfadd(s965, s983, vl1);
            t2337 = __riscv_vfsub(s964, s982, vl1);
            t2338 = __riscv_vfsub(s965, s983, vl1);
            t2339 = __riscv_vfadd(s970, s976, vl1);
            t2340 = __riscv_vfadd(s971, s977, vl1);
            t2341 = __riscv_vfsub(s970, s976, vl1);
            t2342 = __riscv_vfsub(s971, s977, vl1);
            t2343 = __riscv_vfadd(t2335, t2339, vl1);
            t2344 = __riscv_vfadd(t2336, t2340, vl1);
            t2345 = __riscv_vfadd(t2337, t2342, vl1);
            t2346 = __riscv_vfsub(t2338, t2341, vl1);
            t2347 = __riscv_vfsub(t2337, t2342, vl1);
            t2348 = __riscv_vfadd(t2338, t2341, vl1);
            t2349 = __riscv_vfadd(s958, t2343, vl1);
            t2350 = __riscv_vfadd(s959, t2344, vl1);
            t2351 = __riscv_vfnmsac(s958, 0.25, t2343, vl1);
            t2352 = __riscv_vfnmsac(s959, 0.25, t2344, vl1);
            s1062 = __riscv_vfmacc(t2345, 1.6180339887498947, t2346, vl1);
            s992 = __riscv_vfmul(s1062, 0.29389262614623657, vl1);
            s1063 = __riscv_vfnmsac(t2346, 1.6180339887498947, t2345, vl1);
            s993 = __riscv_vfmul(s1063, 0.29389262614623657, vl1);
            s994 = __riscv_vfmul(__riscv_vfsub(t2335, t2339, vl1), 0.55901699437494745, vl1);
            s995 = __riscv_vfmul(__riscv_vfsub(t2336, t2340, vl1), 0.55901699437494745, vl1);
            s1064 = __riscv_vfnmsac(t2348, 0.6180339887498949, t2347, vl1);
            s996 = __riscv_vfmul(s1064, 0.47552825814757677, vl1);
            s1065 = __riscv_vfmacc(t2347, 0.6180339887498949, t2348, vl1);
            s997 = __riscv_vfmul(s1065, 0.47552825814757677, vl1);
            t2353 = __riscv_vfadd(t2351, s994, vl1);
            t2354 = __riscv_vfadd(t2352, s995, vl1);
            t2355 = __riscv_vfsub(t2351, s994, vl1);
            t2356 = __riscv_vfsub(t2352, s995, vl1);
            t2357 = __riscv_vfadd(s992, s996, vl1);
            t2358 = __riscv_vfsub(s993, s997, vl1);
            t2359 = __riscv_vfsub(s992, s996, vl1);
            t2360 = __riscv_vfadd(s993, s997, vl1);
            t2361 = __riscv_vfadd(t2353, t2357, vl1);
            t2362 = __riscv_vfadd(t2354, t2358, vl1);
            t2363 = __riscv_vfsub(t2353, t2357, vl1);
            t2364 = __riscv_vfsub(t2354, t2358, vl1);
            s1066 = __riscv_vfmacc(t2361, 0.44522868530853615, t2362, vl1);
            s998 = __riscv_vfmul(s1066, 0.91354545764260087, vl1);
            s1067 = __riscv_vfnmsac(t2362, 0.44522868530853615, t2361, vl1);
            s999 = __riscv_vfmul(s1067, 0.91354545764260087, vl1);
            s1068 = __riscv_vfnmsac(t2364, 0.10510423526567647, t2363, vl1);
            s1000 = __riscv_vfmul(s1068, 0.99452189536827329, vl1);
            s1069 = __riscv_vfmacc(t2363, 0.10510423526567647, t2364, vl1);
            s1001 = __riscv_vfmul(s1069, 0.99452189536827329, vl1);
            t2365 = __riscv_vfadd(t2355, t2360, vl1);
            t2366 = __riscv_vfsub(t2356, t2359, vl1);
            t2367 = __riscv_vfsub(t2355, t2360, vl1);
            t2368 = __riscv_vfadd(t2356, t2359, vl1);
            s1070 = __riscv_vfmacc(t2365, 1.1106125148291928, t2366, vl1);
            s1002 = __riscv_vfmul(s1070, 0.66913060635885824, vl1);
            s1071 = __riscv_vfnmsac(t2366, 1.1106125148291928, t2365, vl1);
            s1003 = __riscv_vfmul(s1071, 0.66913060635885824, vl1);
            s1072 = __riscv_vfmacc(t2367, 3.0776835371752536, t2368, vl1);
            s1004 = __riscv_vfmul(s1072, 0.3090169943749474, vl1);
            s1073 = __riscv_vfnmsac(t2368, 3.0776835371752536, t2367, vl1);
            s1005 = __riscv_vfmul(s1073, 0.3090169943749474, vl1);
            t2369 = __riscv_vfadd(s966, s984, vl1);
            t2370 = __riscv_vfadd(s967, s985, vl1);
            t2371 = __riscv_vfsub(s966, s984, vl1);
            t2372 = __riscv_vfsub(s967, s985, vl1);
            t2373 = __riscv_vfadd(s972, s978, vl1);
            t2374 = __riscv_vfadd(s973, s979, vl1);
            t2375 = __riscv_vfsub(s972, s978, vl1);
            t2376 = __riscv_vfsub(s973, s979, vl1);
            t2377 = __riscv_vfadd(t2369, t2373, vl1);
            t2378 = __riscv_vfadd(t2370, t2374, vl1);
            t2379 = __riscv_vfadd(t2371, t2376, vl1);
            t2380 = __riscv_vfsub(t2372, t2375, vl1);
            t2381 = __riscv_vfsub(t2371, t2376, vl1);
            t2382 = __riscv_vfadd(t2372, t2375, vl1);
            t2383 = __riscv_vfadd(s960, t2377, vl1);
            t2384 = __riscv_vfadd(s961, t2378, vl1);
            t2385 = __riscv_vfnmsac(s960, 0.25, t2377, vl1);
            t2386 = __riscv_vfnmsac(s961, 0.25, t2378, vl1);
            s1074 = __riscv_vfmacc(t2379, 1.6180339887498947, t2380, vl1);
            s1006 = __riscv_vfmul(s1074, 0.29389262614623657, vl1);
            s1075 = __riscv_vfnmsac(t2380, 1.6180339887498947, t2379, vl1);
            s1007 = __riscv_vfmul(s1075, 0.29389262614623657, vl1);
            s1008 = __riscv_vfmul(__riscv_vfsub(t2369, t2373, vl1), 0.55901699437494745, vl1);
            s1009 = __riscv_vfmul(__riscv_vfsub(t2370, t2374, vl1), 0.55901699437494745, vl1);
            s1076 = __riscv_vfnmsac(t2382, 0.6180339887498949, t2381, vl1);
            s1010 = __riscv_vfmul(s1076, 0.47552825814757677, vl1);
            s1077 = __riscv_vfmacc(t2381, 0.6180339887498949, t2382, vl1);
            s1011 = __riscv_vfmul(s1077, 0.47552825814757677, vl1);
            t2387 = __riscv_vfadd(t2385, s1008, vl1);
            t2388 = __riscv_vfadd(t2386, s1009, vl1);
            t2389 = __riscv_vfsub(t2385, s1008, vl1);
            t2390 = __riscv_vfsub(t2386, s1009, vl1);
            t2391 = __riscv_vfadd(s1006, s1010, vl1);
            t2392 = __riscv_vfsub(s1007, s1011, vl1);
            t2393 = __riscv_vfsub(s1006, s1010, vl1);
            t2394 = __riscv_vfadd(s1007, s1011, vl1);
            t2395 = __riscv_vfadd(t2387, t2391, vl1);
            t2396 = __riscv_vfadd(t2388, t2392, vl1);
            t2397 = __riscv_vfsub(t2387, t2391, vl1);
            t2398 = __riscv_vfsub(t2388, t2392, vl1);
            s1078 = __riscv_vfmacc(t2395, 1.1106125148291928, t2396, vl1);
            s1012 = __riscv_vfmul(s1078, 0.66913060635885824, vl1);
            s1079 = __riscv_vfnmsac(t2396, 1.1106125148291928, t2395, vl1);
            s1013 = __riscv_vfmul(s1079, 0.66913060635885824, vl1);
            s1080 = __riscv_vfmacc(t2397, 0.21255656167002213, t2398, vl1);
            s1014 = __riscv_vfmul(s1080, 0.97814760073380569, vl1);
            s1081 = __riscv_vfnmsac(t2397, 4.7046301094784546, t2398, vl1);
            s1015 = __riscv_vfmul(s1081, 0.20791169081775934, vl1);
            t2399 = __riscv_vfadd(t2389, t2394, vl1);
            t2400 = __riscv_vfsub(t2390, t2393, vl1);
            t2401 = __riscv_vfsub(t2389, t2394, vl1);
            t2402 = __riscv_vfadd(t2390, t2393, vl1);
            s1082 = __riscv_vfnmsac(t2400, 0.10510423526567647, t2399, vl1);
            s1016 = __riscv_vfmul(s1082, 0.99452189536827329, vl1);
            s1083 = __riscv_vfmacc(t2399, 0.10510423526567647, t2400, vl1);
            s1017 = __riscv_vfmul(s1083, 0.99452189536827329, vl1);
            s1084 = __riscv_vfnmsac(t2402, 1.3763819204711736, t2401, vl1);
            s1018 = __riscv_vfmul(s1084, 0.58778525229247314, vl1);
            s1085 = __riscv_vfmacc(t2401, 1.3763819204711736, t2402, vl1);
            s1019 = __riscv_vfmul(s1085, 0.58778525229247314, vl1);
            t2403 = __riscv_vfadd(t2349, t2383, vl1);
            t2404 = __riscv_vfadd(t2350, t2384, vl1);
            t2405 = __riscv_vfnmsac(t2315, 0.5, t2403, vl1);
            t2406 = __riscv_vfnmsac(t2316, 0.5, t2404, vl1);
            s1020 = __riscv_vfmul(__riscv_vfsub(t2350, t2384, vl1), 0.8660254037844386, vl1);
            s1021 = __riscv_vfmul(__riscv_vfsub(t2349, t2383, vl1), 0.8660254037844386, vl1);
            s1022 = __riscv_vfadd(t2405, s1020, vl1);
            s1023 = __riscv_vfsub(t2406, s1021, vl1);
            s1024 = __riscv_vfsub(t2405, s1020, vl1);
            s1025 = __riscv_vfadd(t2406, s1021, vl1);
            t2407 = __riscv_vfadd(s998, s1012, vl1);
            t2408 = __riscv_vfadd(s999, s1013, vl1);
            t2409 = __riscv_vfnmsac(t2327, 0.5, t2407, vl1);
            t2410 = __riscv_vfnmsac(t2328, 0.5, t2408, vl1);
            s1026 = __riscv_vfmul(__riscv_vfsub(s999, s1013, vl1), 0.8660254037844386, vl1);
            s1027 = __riscv_vfmul(__riscv_vfsub(s998, s1012, vl1), 0.8660254037844386, vl1);
            s1028 = __riscv_vfadd(t2327, t2407, vl1);
            s1029 = __riscv_vfadd(t2328, t2408, vl1);
            s1030 = __riscv_vfadd(t2409, s1026, vl1);
            s1031 = __riscv_vfsub(t2410, s1027, vl1);
            s1032 = __riscv_vfsub(t2409, s1026, vl1);
            s1033 = __riscv_vfadd(t2410, s1027, vl1);
            t2411 = __riscv_vfadd(s1002, s1016, vl1);
            t2412 = __riscv_vfsub(s1003, s1017, vl1);
            t2413 = __riscv_vfnmsac(t2331, 0.5, t2411, vl1);
            t2414 = __riscv_vfnmsac(t2332, 0.5, t2412, vl1);
            s1034 = __riscv_vfmul(__riscv_vfadd(s1003, s1017, vl1), 0.8660254037844386, vl1);
            s1035 = __riscv_vfmul(__riscv_vfsub(s1002, s1016, vl1), 0.8660254037844386, vl1);
            s1036 = __riscv_vfadd(t2331, t2411, vl1);
            s1037 = __riscv_vfadd(t2332, t2412, vl1);
            s1038 = __riscv_vfadd(t2413, s1034, vl1);
            s1039 = __riscv_vfsub(t2414, s1035, vl1);
            s1040 = __riscv_vfsub(t2413, s1034, vl1);
            s1041 = __riscv_vfadd(t2414, s1035, vl1);
            t2415 = __riscv_vfadd(s1004, s1018, vl1);
            t2416 = __riscv_vfsub(s1005, s1019, vl1);
            t2417 = __riscv_vfnmsac(t2333, 0.5, t2415, vl1);
            t2418 = __riscv_vfnmsac(t2334, 0.5, t2416, vl1);
            s1042 = __riscv_vfmul(__riscv_vfadd(s1005, s1019, vl1), 0.8660254037844386, vl1);
            s1043 = __riscv_vfmul(__riscv_vfsub(s1004, s1018, vl1), 0.8660254037844386, vl1);
            s1044 = __riscv_vfadd(t2333, t2415, vl1);
            s1045 = __riscv_vfadd(t2334, t2416, vl1);
            s1046 = __riscv_vfadd(t2417, s1042, vl1);
            s1047 = __riscv_vfsub(t2418, s1043, vl1);
            s1048 = __riscv_vfsub(t2417, s1042, vl1);
            s1049 = __riscv_vfadd(t2418, s1043, vl1);
            t2419 = __riscv_vfsub(s1000, s1014, vl1);
            t2420 = __riscv_vfsub(s1015, s1001, vl1);
            t2421 = __riscv_vfnmsac(t2329, 0.5, t2419, vl1);
            t2422 = __riscv_vfnmsac(t2330, 0.5, t2420, vl1);
            s1050 = __riscv_vfmul(__riscv_vfadd(s1001, s1015, vl1), 0.8660254037844386, vl1);
            s1051 = __riscv_vfmul(__riscv_vfadd(s1000, s1014, vl1), 0.8660254037844386, vl1);
            s1052 = __riscv_vfadd(t2329, t2419, vl1);
            s1053 = __riscv_vfadd(t2330, t2420, vl1);
            s1054 = __riscv_vfsub(t2421, s1050, vl1);
            s1055 = __riscv_vfsub(t2422, s1051, vl1);
            s1056 = __riscv_vfadd(t2421, s1050, vl1);
            s1057 = __riscv_vfadd(t2422, s1051, vl1);
            a1861 = ((28)*(j1));
            a1862 = TW1[a1861];
            a1863 = TW1[(a1861 + 1)];
            a1864 = TW1[(a1861 + 2)];
            a1865 = TW1[(a1861 + 3)];
            a1866 = TW1[(a1861 + 4)];
            a1867 = TW1[(a1861 + 5)];
            a1868 = TW1[(a1861 + 6)];
            a1869 = TW1[(a1861 + 7)];
            a1870 = TW1[(a1861 + 8)];
            a1871 = TW1[(a1861 + 9)];
            a1872 = TW1[(a1861 + 10)];
            a1873 = TW1[(a1861 + 11)];
            a1874 = TW1[(a1861 + 12)];
            a1875 = TW1[(a1861 + 13)];
            a1876 = TW1[(a1861 + 14)];
            a1877 = TW1[(a1861 + 15)];
            a1878 = TW1[(a1861 + 16)];
            a1879 = TW1[(a1861 + 17)];
            a1880 = TW1[(a1861 + 18)];
            a1881 = TW1[(a1861 + 19)];
            a1882 = TW1[(a1861 + 20)];
            a1883 = TW1[(a1861 + 21)];
            a1884 = TW1[(a1861 + 22)];
            a1885 = TW1[(a1861 + 23)];
            a1886 = TW1[(a1861 + 24)];
            a1887 = TW1[(a1861 + 25)];
            a1888 = TW1[(a1861 + 26)];
            a1889 = TW1[(a1861 + 27)];
            r256 = __riscv_vset(__riscv_vset(rvvx2_16, 0, __riscv_vfadd(t2315, t2403, vl1)), 1, __riscv_vfadd(t2316, t2404, vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)))))), r256, vl1);
            r257 = __riscv_vset(__riscv_vset(rvvx2_17, 0, __riscv_vfsub(__riscv_vfmul(s1028, a1862, vl1), __riscv_vfmul(s1029, a1863, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1028, a1863, vl1), __riscv_vfmul(s1029, a1862, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + m1)))), r257, vl1);
            r258 = __riscv_vset(__riscv_vset(rvvx2_18, 0, __riscv_vfsub(__riscv_vfmul(s1036, a1864, vl1), __riscv_vfmul(s1037, a1865, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1036, a1865, vl1), __riscv_vfmul(s1037, a1864, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + ((2)*(m1)))))), r258, vl1);
            r259 = __riscv_vset(__riscv_vset(rvvx2_19, 0, __riscv_vfsub(__riscv_vfmul(s1044, a1866, vl1), __riscv_vfmul(s1045, a1867, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1044, a1867, vl1), __riscv_vfmul(s1045, a1866, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + ((3)*(m1)))))), r259, vl1);
            r260 = __riscv_vset(__riscv_vset(rvvx2_20, 0, __riscv_vfsub(__riscv_vfmul(s1052, a1868, vl1), __riscv_vfmul(s1053, a1869, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1052, a1869, vl1), __riscv_vfmul(s1053, a1868, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + ((4)*(m1)))))), r260, vl1);
            r261 = __riscv_vset(__riscv_vset(rvvx2_21, 0, __riscv_vfsub(__riscv_vfmul(s1022, a1870, vl1), __riscv_vfmul(s1023, a1871, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1022, a1871, vl1), __riscv_vfmul(s1023, a1870, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + ((5)*(m1)))))), r261, vl1);
            r262 = __riscv_vset(__riscv_vset(rvvx2_22, 0, __riscv_vfsub(__riscv_vfmul(s1030, a1872, vl1), __riscv_vfmul(s1031, a1873, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1030, a1873, vl1), __riscv_vfmul(s1031, a1872, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + ((6)*(m1)))))), r262, vl1);
            r263 = __riscv_vset(__riscv_vset(rvvx2_23, 0, __riscv_vfsub(__riscv_vfmul(s1038, a1874, vl1), __riscv_vfmul(s1039, a1875, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1038, a1875, vl1), __riscv_vfmul(s1039, a1874, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + ((7)*(m1)))))), r263, vl1);
            r264 = __riscv_vset(__riscv_vset(rvvx2_24, 0, __riscv_vfsub(__riscv_vfmul(s1046, a1876, vl1), __riscv_vfmul(s1047, a1877, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1046, a1877, vl1), __riscv_vfmul(s1047, a1876, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + ((8)*(m1)))))), r264, vl1);
            r265 = __riscv_vset(__riscv_vset(rvvx2_25, 0, __riscv_vfsub(__riscv_vfmul(s1054, a1878, vl1), __riscv_vfmul(s1055, a1879, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1054, a1879, vl1), __riscv_vfmul(s1055, a1878, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + ((9)*(m1)))))), r265, vl1);
            r266 = __riscv_vset(__riscv_vset(rvvx2_26, 0, __riscv_vfsub(__riscv_vfmul(s1024, a1880, vl1), __riscv_vfmul(s1025, a1881, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1024, a1881, vl1), __riscv_vfmul(s1025, a1880, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + ((10)*(m1)))))), r266, vl1);
            r267 = __riscv_vset(__riscv_vset(rvvx2_27, 0, __riscv_vfsub(__riscv_vfmul(s1032, a1882, vl1), __riscv_vfmul(s1033, a1883, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1032, a1883, vl1), __riscv_vfmul(s1033, a1882, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + ((11)*(m1)))))), r267, vl1);
            r268 = __riscv_vset(__riscv_vset(rvvx2_28, 0, __riscv_vfsub(__riscv_vfmul(s1040, a1884, vl1), __riscv_vfmul(s1041, a1885, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1040, a1885, vl1), __riscv_vfmul(s1041, a1884, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + ((12)*(m1)))))), r268, vl1);
            r269 = __riscv_vset(__riscv_vset(rvvx2_29, 0, __riscv_vfsub(__riscv_vfmul(s1048, a1886, vl1), __riscv_vfmul(s1049, a1887, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1048, a1887, vl1), __riscv_vfmul(s1049, a1886, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + ((13)*(m1)))))), r269, vl1);
            r270 = __riscv_vset(__riscv_vset(rvvx2_30, 0, __riscv_vfsub(__riscv_vfmul(s1056, a1888, vl1), __riscv_vfmul(s1057, a1889, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s1056, a1889, vl1), __riscv_vfmul(s1057, a1888, vl1), vl1));
            __riscv_vsseg2e64((Y + ((2)*((k1 + ((((15)*(j1)))*(m1)) + ((14)*(m1)))))), r270, vl1);
        }
    }
}
