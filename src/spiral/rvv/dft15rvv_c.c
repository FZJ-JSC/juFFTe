// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft15c_(double *Y, double *X, int *lp1, int *mp1) {
    int l1, m1;
    vfloat64m1x2_t r241, r242, r243, r244, r245, r246, r247, r248, 
            r249, r250, r251, r252, r253, r254, r255, r256, 
            r257, r258, r259, r260, r261, r262, r263, r264, 
            r265, r266, r267, r268, r269, r270, rvvx2_16, rvvx2_17, 
            rvvx2_18, rvvx2_19, rvvx2_20, rvvx2_21, rvvx2_22, rvvx2_23, rvvx2_24, rvvx2_25, 
            rvvx2_26, rvvx2_27, rvvx2_28, rvvx2_29, rvvx2_30;
    vfloat64m1_t  s872, s873, s874, s875, s876, s877, s878, s879, 
            s880, s881, s882, s883, s884, s885, s886, s887, 
            s888, s889, s890, s891, s892, s893, s894, s895, 
            s896, s897, s898, s899, s900, s901, s902, s903, 
            s904, s905, s906, s907, s908, s909, s910, s911, 
            s912, s913, s914, s915, s916, s917, s918, s919, 
            s920, s921, s922, s923, s924, s925, s926, s927, 
            s928, s929, s930, s931, s932, s933, s934, s935, 
            s936, s937, s938, s939, s940, s941, s942, s943, 
            s944, s945, s946, s947, s948, s949, s950, s951, 
            s952, s953, s954, s955, s956, s957, s958, s959, 
            s960, s961, s962, s963, s964, s965, s966, s967, 
            s968, s969, s970, s971, s972, s973, t2300, t2301, 
            t2302, t2303, t2304, t2305, t2306, t2307, t2308, t2309, 
            t2310, t2311, t2312, t2313, t2314, t2315, t2316, t2317, 
            t2318, t2319, t2320, t2321, t2322, t2323, t2324, t2325, 
            t2326, t2327, t2328, t2329, t2330, t2331, t2332, t2333, 
            t2334, t2335, t2336, t2337, t2338, t2339, t2340, t2341, 
            t2342, t2343, t2344, t2345, t2346, t2347, t2348, t2349, 
            t2350, t2351, t2352, t2353, t2354, t2355, t2356, t2357, 
            t2358, t2359, t2360, t2361, t2362, t2363, t2364, t2365, 
            t2366, t2367, t2368, t2369, t2370, t2371, t2372, t2373, 
            t2374, t2375, t2376, t2377, t2378, t2379, t2380, t2381, 
            t2382, t2383, t2384, t2385, t2386, t2387, t2388, t2389, 
            t2390, t2391, t2392, t2393, t2394, t2395, t2396, t2397, 
            t2398, t2399, t2400, t2401, t2402, t2403, t2404, t2405, 
            t2406, t2407, t2408, t2409, t2410, t2411, t2412, t2413, 
            t2414, t2415, t2416, t2417, t2418, t2419, t2420, t2421;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for (size_t k1 = 0; k1 < m1; k1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(m1 - k1);
        r241 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(k1))), vl1);
        s872 = __riscv_vget_f64m1(r241, 0);
        s873 = __riscv_vget_f64m1(r241, 1);
        r242 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((l1)*(m1)))))), vl1);
        s874 = __riscv_vget_f64m1(r242, 0);
        s875 = __riscv_vget_f64m1(r242, 1);
        r243 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((2)*(l1)))*(m1)))))), vl1);
        s876 = __riscv_vget_f64m1(r243, 0);
        s877 = __riscv_vget_f64m1(r243, 1);
        r244 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((3)*(l1)))*(m1)))))), vl1);
        s878 = __riscv_vget_f64m1(r244, 0);
        s879 = __riscv_vget_f64m1(r244, 1);
        r245 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((4)*(l1)))*(m1)))))), vl1);
        s880 = __riscv_vget_f64m1(r245, 0);
        s881 = __riscv_vget_f64m1(r245, 1);
        r246 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((5)*(l1)))*(m1)))))), vl1);
        s882 = __riscv_vget_f64m1(r246, 0);
        s883 = __riscv_vget_f64m1(r246, 1);
        r247 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((6)*(l1)))*(m1)))))), vl1);
        s884 = __riscv_vget_f64m1(r247, 0);
        s885 = __riscv_vget_f64m1(r247, 1);
        r248 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((7)*(l1)))*(m1)))))), vl1);
        s886 = __riscv_vget_f64m1(r248, 0);
        s887 = __riscv_vget_f64m1(r248, 1);
        r249 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((8)*(l1)))*(m1)))))), vl1);
        s888 = __riscv_vget_f64m1(r249, 0);
        s889 = __riscv_vget_f64m1(r249, 1);
        r250 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((9)*(l1)))*(m1)))))), vl1);
        s890 = __riscv_vget_f64m1(r250, 0);
        s891 = __riscv_vget_f64m1(r250, 1);
        r251 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((10)*(l1)))*(m1)))))), vl1);
        s892 = __riscv_vget_f64m1(r251, 0);
        s893 = __riscv_vget_f64m1(r251, 1);
        r252 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((11)*(l1)))*(m1)))))), vl1);
        s894 = __riscv_vget_f64m1(r252, 0);
        s895 = __riscv_vget_f64m1(r252, 1);
        r253 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((12)*(l1)))*(m1)))))), vl1);
        s896 = __riscv_vget_f64m1(r253, 0);
        s897 = __riscv_vget_f64m1(r253, 1);
        r254 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((13)*(l1)))*(m1)))))), vl1);
        s898 = __riscv_vget_f64m1(r254, 0);
        s899 = __riscv_vget_f64m1(r254, 1);
        r255 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((14)*(l1)))*(m1)))))), vl1);
        s900 = __riscv_vget_f64m1(r255, 0);
        s901 = __riscv_vget_f64m1(r255, 1);
        t2300 = __riscv_vfadd(s878, s896, vl1);
        t2301 = __riscv_vfadd(s879, s897, vl1);
        t2302 = __riscv_vfsub(s878, s896, vl1);
        t2303 = __riscv_vfsub(s879, s897, vl1);
        t2304 = __riscv_vfadd(s884, s890, vl1);
        t2305 = __riscv_vfadd(s885, s891, vl1);
        t2306 = __riscv_vfsub(s884, s890, vl1);
        t2307 = __riscv_vfsub(s885, s891, vl1);
        t2308 = __riscv_vfadd(t2300, t2304, vl1);
        t2309 = __riscv_vfadd(t2301, t2305, vl1);
        t2310 = __riscv_vfadd(t2302, t2307, vl1);
        t2311 = __riscv_vfsub(t2303, t2306, vl1);
        t2312 = __riscv_vfsub(t2302, t2307, vl1);
        t2313 = __riscv_vfadd(t2303, t2306, vl1);
        t2314 = __riscv_vfadd(s872, t2308, vl1);
        t2315 = __riscv_vfadd(s873, t2309, vl1);
        t2316 = __riscv_vfnmsac(s872, 0.25, t2308, vl1);
        t2317 = __riscv_vfnmsac(s873, 0.25, t2309, vl1);
        s946 = __riscv_vfmacc(t2310, 1.6180339887498947, t2311, vl1);
        s902 = __riscv_vfmul(s946, 0.29389262614623657, vl1);
        s947 = __riscv_vfnmsac(t2311, 1.6180339887498947, t2310, vl1);
        s903 = __riscv_vfmul(s947, 0.29389262614623657, vl1);
        s904 = __riscv_vfmul(__riscv_vfsub(t2300, t2304, vl1), 0.55901699437494745, vl1);
        s905 = __riscv_vfmul(__riscv_vfsub(t2301, t2305, vl1), 0.55901699437494745, vl1);
        s948 = __riscv_vfnmsac(t2313, 0.6180339887498949, t2312, vl1);
        s906 = __riscv_vfmul(s948, 0.47552825814757677, vl1);
        s949 = __riscv_vfmacc(t2312, 0.6180339887498949, t2313, vl1);
        s907 = __riscv_vfmul(s949, 0.47552825814757677, vl1);
        t2318 = __riscv_vfadd(t2316, s904, vl1);
        t2319 = __riscv_vfadd(t2317, s905, vl1);
        t2320 = __riscv_vfsub(t2316, s904, vl1);
        t2321 = __riscv_vfsub(t2317, s905, vl1);
        t2322 = __riscv_vfadd(s902, s906, vl1);
        t2323 = __riscv_vfsub(s903, s907, vl1);
        t2324 = __riscv_vfsub(s902, s906, vl1);
        t2325 = __riscv_vfadd(s903, s907, vl1);
        t2326 = __riscv_vfadd(t2318, t2322, vl1);
        t2327 = __riscv_vfadd(t2319, t2323, vl1);
        t2328 = __riscv_vfsub(t2318, t2322, vl1);
        t2329 = __riscv_vfsub(t2319, t2323, vl1);
        t2330 = __riscv_vfadd(t2320, t2325, vl1);
        t2331 = __riscv_vfsub(t2321, t2324, vl1);
        t2332 = __riscv_vfsub(t2320, t2325, vl1);
        t2333 = __riscv_vfadd(t2321, t2324, vl1);
        t2334 = __riscv_vfadd(s880, s898, vl1);
        t2335 = __riscv_vfadd(s881, s899, vl1);
        t2336 = __riscv_vfsub(s880, s898, vl1);
        t2337 = __riscv_vfsub(s881, s899, vl1);
        t2338 = __riscv_vfadd(s886, s892, vl1);
        t2339 = __riscv_vfadd(s887, s893, vl1);
        t2340 = __riscv_vfsub(s886, s892, vl1);
        t2341 = __riscv_vfsub(s887, s893, vl1);
        t2342 = __riscv_vfadd(t2334, t2338, vl1);
        t2343 = __riscv_vfadd(t2335, t2339, vl1);
        t2344 = __riscv_vfadd(t2336, t2341, vl1);
        t2345 = __riscv_vfsub(t2337, t2340, vl1);
        t2346 = __riscv_vfsub(t2336, t2341, vl1);
        t2347 = __riscv_vfadd(t2337, t2340, vl1);
        t2348 = __riscv_vfadd(s874, t2342, vl1);
        t2349 = __riscv_vfadd(s875, t2343, vl1);
        t2350 = __riscv_vfnmsac(s874, 0.25, t2342, vl1);
        t2351 = __riscv_vfnmsac(s875, 0.25, t2343, vl1);
        s950 = __riscv_vfmacc(t2344, 1.6180339887498947, t2345, vl1);
        s908 = __riscv_vfmul(s950, 0.29389262614623657, vl1);
        s951 = __riscv_vfnmsac(t2345, 1.6180339887498947, t2344, vl1);
        s909 = __riscv_vfmul(s951, 0.29389262614623657, vl1);
        s910 = __riscv_vfmul(__riscv_vfsub(t2334, t2338, vl1), 0.55901699437494745, vl1);
        s911 = __riscv_vfmul(__riscv_vfsub(t2335, t2339, vl1), 0.55901699437494745, vl1);
        s952 = __riscv_vfnmsac(t2347, 0.6180339887498949, t2346, vl1);
        s912 = __riscv_vfmul(s952, 0.47552825814757677, vl1);
        s953 = __riscv_vfmacc(t2346, 0.6180339887498949, t2347, vl1);
        s913 = __riscv_vfmul(s953, 0.47552825814757677, vl1);
        t2352 = __riscv_vfadd(t2350, s910, vl1);
        t2353 = __riscv_vfadd(t2351, s911, vl1);
        t2354 = __riscv_vfsub(t2350, s910, vl1);
        t2355 = __riscv_vfsub(t2351, s911, vl1);
        t2356 = __riscv_vfadd(s908, s912, vl1);
        t2357 = __riscv_vfsub(s909, s913, vl1);
        t2358 = __riscv_vfsub(s908, s912, vl1);
        t2359 = __riscv_vfadd(s909, s913, vl1);
        t2360 = __riscv_vfadd(t2352, t2356, vl1);
        t2361 = __riscv_vfadd(t2353, t2357, vl1);
        t2362 = __riscv_vfsub(t2352, t2356, vl1);
        t2363 = __riscv_vfsub(t2353, t2357, vl1);
        s954 = __riscv_vfmacc(t2360, 0.44522868530853615, t2361, vl1);
        s914 = __riscv_vfmul(s954, 0.91354545764260087, vl1);
        s955 = __riscv_vfnmsac(t2361, 0.44522868530853615, t2360, vl1);
        s915 = __riscv_vfmul(s955, 0.91354545764260087, vl1);
        s956 = __riscv_vfnmsac(t2363, 0.10510423526567647, t2362, vl1);
        s916 = __riscv_vfmul(s956, 0.99452189536827329, vl1);
        s957 = __riscv_vfmacc(t2362, 0.10510423526567647, t2363, vl1);
        s917 = __riscv_vfmul(s957, 0.99452189536827329, vl1);
        t2364 = __riscv_vfadd(t2354, t2359, vl1);
        t2365 = __riscv_vfsub(t2355, t2358, vl1);
        t2366 = __riscv_vfsub(t2354, t2359, vl1);
        t2367 = __riscv_vfadd(t2355, t2358, vl1);
        s958 = __riscv_vfmacc(t2364, 1.1106125148291928, t2365, vl1);
        s918 = __riscv_vfmul(s958, 0.66913060635885824, vl1);
        s959 = __riscv_vfnmsac(t2365, 1.1106125148291928, t2364, vl1);
        s919 = __riscv_vfmul(s959, 0.66913060635885824, vl1);
        s960 = __riscv_vfmacc(t2366, 3.0776835371752536, t2367, vl1);
        s920 = __riscv_vfmul(s960, 0.3090169943749474, vl1);
        s961 = __riscv_vfnmsac(t2367, 3.0776835371752536, t2366, vl1);
        s921 = __riscv_vfmul(s961, 0.3090169943749474, vl1);
        t2368 = __riscv_vfadd(s882, s900, vl1);
        t2369 = __riscv_vfadd(s883, s901, vl1);
        t2370 = __riscv_vfsub(s882, s900, vl1);
        t2371 = __riscv_vfsub(s883, s901, vl1);
        t2372 = __riscv_vfadd(s888, s894, vl1);
        t2373 = __riscv_vfadd(s889, s895, vl1);
        t2374 = __riscv_vfsub(s888, s894, vl1);
        t2375 = __riscv_vfsub(s889, s895, vl1);
        t2376 = __riscv_vfadd(t2368, t2372, vl1);
        t2377 = __riscv_vfadd(t2369, t2373, vl1);
        t2378 = __riscv_vfadd(t2370, t2375, vl1);
        t2379 = __riscv_vfsub(t2371, t2374, vl1);
        t2380 = __riscv_vfsub(t2370, t2375, vl1);
        t2381 = __riscv_vfadd(t2371, t2374, vl1);
        t2382 = __riscv_vfadd(s876, t2376, vl1);
        t2383 = __riscv_vfadd(s877, t2377, vl1);
        t2384 = __riscv_vfnmsac(s876, 0.25, t2376, vl1);
        t2385 = __riscv_vfnmsac(s877, 0.25, t2377, vl1);
        s962 = __riscv_vfmacc(t2378, 1.6180339887498947, t2379, vl1);
        s922 = __riscv_vfmul(s962, 0.29389262614623657, vl1);
        s963 = __riscv_vfnmsac(t2379, 1.6180339887498947, t2378, vl1);
        s923 = __riscv_vfmul(s963, 0.29389262614623657, vl1);
        s924 = __riscv_vfmul(__riscv_vfsub(t2368, t2372, vl1), 0.55901699437494745, vl1);
        s925 = __riscv_vfmul(__riscv_vfsub(t2369, t2373, vl1), 0.55901699437494745, vl1);
        s964 = __riscv_vfnmsac(t2381, 0.6180339887498949, t2380, vl1);
        s926 = __riscv_vfmul(s964, 0.47552825814757677, vl1);
        s965 = __riscv_vfmacc(t2380, 0.6180339887498949, t2381, vl1);
        s927 = __riscv_vfmul(s965, 0.47552825814757677, vl1);
        t2386 = __riscv_vfadd(t2384, s924, vl1);
        t2387 = __riscv_vfadd(t2385, s925, vl1);
        t2388 = __riscv_vfsub(t2384, s924, vl1);
        t2389 = __riscv_vfsub(t2385, s925, vl1);
        t2390 = __riscv_vfadd(s922, s926, vl1);
        t2391 = __riscv_vfsub(s923, s927, vl1);
        t2392 = __riscv_vfsub(s922, s926, vl1);
        t2393 = __riscv_vfadd(s923, s927, vl1);
        t2394 = __riscv_vfadd(t2386, t2390, vl1);
        t2395 = __riscv_vfadd(t2387, t2391, vl1);
        t2396 = __riscv_vfsub(t2386, t2390, vl1);
        t2397 = __riscv_vfsub(t2387, t2391, vl1);
        s966 = __riscv_vfmacc(t2394, 1.1106125148291928, t2395, vl1);
        s928 = __riscv_vfmul(s966, 0.66913060635885824, vl1);
        s967 = __riscv_vfnmsac(t2395, 1.1106125148291928, t2394, vl1);
        s929 = __riscv_vfmul(s967, 0.66913060635885824, vl1);
        s968 = __riscv_vfmacc(t2396, 0.21255656167002213, t2397, vl1);
        s930 = __riscv_vfmul(s968, 0.97814760073380569, vl1);
        s969 = __riscv_vfnmsac(t2396, 4.7046301094784546, t2397, vl1);
        s931 = __riscv_vfmul(s969, 0.20791169081775934, vl1);
        t2398 = __riscv_vfadd(t2388, t2393, vl1);
        t2399 = __riscv_vfsub(t2389, t2392, vl1);
        t2400 = __riscv_vfsub(t2388, t2393, vl1);
        t2401 = __riscv_vfadd(t2389, t2392, vl1);
        s970 = __riscv_vfnmsac(t2399, 0.10510423526567647, t2398, vl1);
        s932 = __riscv_vfmul(s970, 0.99452189536827329, vl1);
        s971 = __riscv_vfmacc(t2398, 0.10510423526567647, t2399, vl1);
        s933 = __riscv_vfmul(s971, 0.99452189536827329, vl1);
        s972 = __riscv_vfnmsac(t2401, 1.3763819204711736, t2400, vl1);
        s934 = __riscv_vfmul(s972, 0.58778525229247314, vl1);
        s973 = __riscv_vfmacc(t2400, 1.3763819204711736, t2401, vl1);
        s935 = __riscv_vfmul(s973, 0.58778525229247314, vl1);
        t2402 = __riscv_vfadd(t2348, t2382, vl1);
        t2403 = __riscv_vfadd(t2349, t2383, vl1);
        t2404 = __riscv_vfnmsac(t2314, 0.5, t2402, vl1);
        t2405 = __riscv_vfnmsac(t2315, 0.5, t2403, vl1);
        s936 = __riscv_vfmul(__riscv_vfsub(t2349, t2383, vl1), 0.8660254037844386, vl1);
        s937 = __riscv_vfmul(__riscv_vfsub(t2348, t2382, vl1), 0.8660254037844386, vl1);
        t2406 = __riscv_vfadd(s914, s928, vl1);
        t2407 = __riscv_vfadd(s915, s929, vl1);
        t2408 = __riscv_vfnmsac(t2326, 0.5, t2406, vl1);
        t2409 = __riscv_vfnmsac(t2327, 0.5, t2407, vl1);
        s938 = __riscv_vfmul(__riscv_vfsub(s915, s929, vl1), 0.8660254037844386, vl1);
        s939 = __riscv_vfmul(__riscv_vfsub(s914, s928, vl1), 0.8660254037844386, vl1);
        t2410 = __riscv_vfadd(s918, s932, vl1);
        t2411 = __riscv_vfsub(s919, s933, vl1);
        t2412 = __riscv_vfnmsac(t2330, 0.5, t2410, vl1);
        t2413 = __riscv_vfnmsac(t2331, 0.5, t2411, vl1);
        s940 = __riscv_vfmul(__riscv_vfadd(s919, s933, vl1), 0.8660254037844386, vl1);
        s941 = __riscv_vfmul(__riscv_vfsub(s918, s932, vl1), 0.8660254037844386, vl1);
        t2414 = __riscv_vfadd(s920, s934, vl1);
        t2415 = __riscv_vfsub(s921, s935, vl1);
        t2416 = __riscv_vfnmsac(t2332, 0.5, t2414, vl1);
        t2417 = __riscv_vfnmsac(t2333, 0.5, t2415, vl1);
        s942 = __riscv_vfmul(__riscv_vfadd(s921, s935, vl1), 0.8660254037844386, vl1);
        s943 = __riscv_vfmul(__riscv_vfsub(s920, s934, vl1), 0.8660254037844386, vl1);
        t2418 = __riscv_vfsub(s916, s930, vl1);
        t2419 = __riscv_vfsub(s931, s917, vl1);
        t2420 = __riscv_vfnmsac(t2328, 0.5, t2418, vl1);
        t2421 = __riscv_vfnmsac(t2329, 0.5, t2419, vl1);
        s944 = __riscv_vfmul(__riscv_vfadd(s917, s931, vl1), 0.8660254037844386, vl1);
        s945 = __riscv_vfmul(__riscv_vfadd(s916, s930, vl1), 0.8660254037844386, vl1);
        r256 = __riscv_vset(__riscv_vset(rvvx2_16, 0, __riscv_vfadd(t2314, t2402, vl1)), 1, __riscv_vfadd(t2315, t2403, vl1));
        __riscv_vsseg2e64((Y + ((2)*(k1))), r256, vl1);
        r257 = __riscv_vset(__riscv_vset(rvvx2_17, 0, __riscv_vfadd(t2326, t2406, vl1)), 1, __riscv_vfadd(t2327, t2407, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + m1)))), r257, vl1);
        r258 = __riscv_vset(__riscv_vset(rvvx2_18, 0, __riscv_vfadd(t2330, t2410, vl1)), 1, __riscv_vfadd(t2331, t2411, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((2)*(m1)))))), r258, vl1);
        r259 = __riscv_vset(__riscv_vset(rvvx2_19, 0, __riscv_vfadd(t2332, t2414, vl1)), 1, __riscv_vfadd(t2333, t2415, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((3)*(m1)))))), r259, vl1);
        r260 = __riscv_vset(__riscv_vset(rvvx2_20, 0, __riscv_vfadd(t2328, t2418, vl1)), 1, __riscv_vfadd(t2329, t2419, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((4)*(m1)))))), r260, vl1);
        r261 = __riscv_vset(__riscv_vset(rvvx2_21, 0, __riscv_vfadd(t2404, s936, vl1)), 1, __riscv_vfsub(t2405, s937, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((5)*(m1)))))), r261, vl1);
        r262 = __riscv_vset(__riscv_vset(rvvx2_22, 0, __riscv_vfadd(t2408, s938, vl1)), 1, __riscv_vfsub(t2409, s939, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((6)*(m1)))))), r262, vl1);
        r263 = __riscv_vset(__riscv_vset(rvvx2_23, 0, __riscv_vfadd(t2412, s940, vl1)), 1, __riscv_vfsub(t2413, s941, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((7)*(m1)))))), r263, vl1);
        r264 = __riscv_vset(__riscv_vset(rvvx2_24, 0, __riscv_vfadd(t2416, s942, vl1)), 1, __riscv_vfsub(t2417, s943, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((8)*(m1)))))), r264, vl1);
        r265 = __riscv_vset(__riscv_vset(rvvx2_25, 0, __riscv_vfsub(t2420, s944, vl1)), 1, __riscv_vfsub(t2421, s945, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((9)*(m1)))))), r265, vl1);
        r266 = __riscv_vset(__riscv_vset(rvvx2_26, 0, __riscv_vfsub(t2404, s936, vl1)), 1, __riscv_vfadd(t2405, s937, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((10)*(m1)))))), r266, vl1);
        r267 = __riscv_vset(__riscv_vset(rvvx2_27, 0, __riscv_vfsub(t2408, s938, vl1)), 1, __riscv_vfadd(t2409, s939, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((11)*(m1)))))), r267, vl1);
        r268 = __riscv_vset(__riscv_vset(rvvx2_28, 0, __riscv_vfsub(t2412, s940, vl1)), 1, __riscv_vfadd(t2413, s941, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((12)*(m1)))))), r268, vl1);
        r269 = __riscv_vset(__riscv_vset(rvvx2_29, 0, __riscv_vfsub(t2416, s942, vl1)), 1, __riscv_vfadd(t2417, s943, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((13)*(m1)))))), r269, vl1);
        r270 = __riscv_vset(__riscv_vset(rvvx2_30, 0, __riscv_vfadd(t2420, s944, vl1)), 1, __riscv_vfadd(t2421, s945, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((14)*(m1)))))), r270, vl1);
    }
}
