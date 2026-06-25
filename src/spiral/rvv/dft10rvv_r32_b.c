// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft10b_r32_(float *Y, float *X, float *TW1, int64_t *lp1, int64_t *mp1) {
    float a1115, a1116, a1117, a1118, a1119, a1120, a1121, a1122, 
            a1123, a1124, a1125, a1126, a1127, a1128, a1129, a1130, 
            a1131, a1132;
    int64_t a1113, a1114, j1, l1, m1;
    vfloat32m1x2_t r161, r162, r163, r164, r165, r166, r167, r168, 
            r169, r170, r171, r172, r173, r174, r175, r176, 
            r177, r178, r179, r180, rvvx2_11, rvvx2_12, rvvx2_13, rvvx2_14, 
            rvvx2_15, rvvx2_16, rvvx2_17, rvvx2_18, rvvx2_19, rvvx2_20;
    vfloat32m1_t  s496, s497, s498, s499, s500, s501, s502, s503, 
            s504, s505, s506, s507, s508, s509, s510, s511, 
            s512, s513, s514, s515, s516, s517, s518, s519, 
            s520, s521, s522, s523, s524, s525, s526, s527, 
            s528, s529, s530, s531, s532, s533, s534, s535, 
            s536, s537, s538, s539, s540, s541, s542, s543, 
            s544, s545, s546, s547, s548, s549, s550, s551, 
            s552, s553, s554, s555, s556, s557, s558, s559, 
            s560, s561, s562, s563, s564, s565, s566, s567, 
            s568, s569, t1311, t1312, t1313, t1314, t1315, t1316, 
            t1317, t1318, t1319, t1320, t1321, t1322, t1323, t1324, 
            t1325, t1326, t1327, t1328, t1329, t1330, t1331, t1332, 
            t1333, t1334, t1335, t1336, t1337, t1338, t1339, t1340, 
            t1341, t1342, t1343, t1344, t1345, t1346, t1347, t1348, 
            t1349, t1350, t1351, t1352, t1353, t1354, t1355, t1356, 
            t1357, t1358, t1359, t1360, t1361, t1362, t1363, t1364, 
            t1365, t1366, t1367, t1368, t1369, t1370, t1371, t1372, 
            t1373, t1374, t1375, t1376, t1377, t1378;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for(int j2 = 0; j2 < (l1 - 1); j2++) {
        j1 = (j2 + 1);
        for(int j2 = 0; j2 < l1; j2++) {
            for (size_t k1 = 0; k1 < m1; k1 += vl1) {
                vl1 = __riscv_vsetvl_e32m1(m1 - k1);
                a1113 = (k1 + ((j1)*(m1)));
                r161 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*(a1113))), vl1);
                s496 = __riscv_vget_f32m1(r161, 0);
                s497 = __riscv_vget_f32m1(r161, 1);
                r162 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a1113 + ((l1)*(m1)))))), vl1);
                s498 = __riscv_vget_f32m1(r162, 0);
                s499 = __riscv_vget_f32m1(r162, 1);
                r163 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a1113 + ((((2)*(l1)))*(m1)))))), vl1);
                s500 = __riscv_vget_f32m1(r163, 0);
                s501 = __riscv_vget_f32m1(r163, 1);
                r164 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a1113 + ((((3)*(l1)))*(m1)))))), vl1);
                s502 = __riscv_vget_f32m1(r164, 0);
                s503 = __riscv_vget_f32m1(r164, 1);
                r165 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a1113 + ((((4)*(l1)))*(m1)))))), vl1);
                s504 = __riscv_vget_f32m1(r165, 0);
                s505 = __riscv_vget_f32m1(r165, 1);
                r166 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a1113 + ((((5)*(l1)))*(m1)))))), vl1);
                s506 = __riscv_vget_f32m1(r166, 0);
                s507 = __riscv_vget_f32m1(r166, 1);
                r167 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a1113 + ((((6)*(l1)))*(m1)))))), vl1);
                s508 = __riscv_vget_f32m1(r167, 0);
                s509 = __riscv_vget_f32m1(r167, 1);
                r168 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a1113 + ((((7)*(l1)))*(m1)))))), vl1);
                s510 = __riscv_vget_f32m1(r168, 0);
                s511 = __riscv_vget_f32m1(r168, 1);
                r169 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a1113 + ((((8)*(l1)))*(m1)))))), vl1);
                s512 = __riscv_vget_f32m1(r169, 0);
                s513 = __riscv_vget_f32m1(r169, 1);
                r170 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((a1113 + ((((9)*(l1)))*(m1)))))), vl1);
                s514 = __riscv_vget_f32m1(r170, 0);
                s515 = __riscv_vget_f32m1(r170, 1);
                t1311 = __riscv_vfadd(s500, s512, vl1);
                t1312 = __riscv_vfadd(s501, s513, vl1);
                t1313 = __riscv_vfsub(s500, s512, vl1);
                t1314 = __riscv_vfsub(s501, s513, vl1);
                t1315 = __riscv_vfadd(s504, s508, vl1);
                t1316 = __riscv_vfadd(s505, s509, vl1);
                t1317 = __riscv_vfsub(s504, s508, vl1);
                t1318 = __riscv_vfsub(s505, s509, vl1);
                t1319 = __riscv_vfadd(t1311, t1315, vl1);
                t1320 = __riscv_vfadd(t1312, t1316, vl1);
                t1321 = __riscv_vfadd(t1313, t1318, vl1);
                t1322 = __riscv_vfsub(t1314, t1317, vl1);
                t1323 = __riscv_vfsub(t1313, t1318, vl1);
                t1324 = __riscv_vfadd(t1314, t1317, vl1);
                t1325 = __riscv_vfadd(s496, t1319, vl1);
                t1326 = __riscv_vfadd(s497, t1320, vl1);
                t1327 = __riscv_vfnmsac(s496, 0.25, t1319, vl1);
                t1328 = __riscv_vfnmsac(s497, 0.25, t1320, vl1);
                s554 = __riscv_vfmacc(t1321, 1.6180339887498947, t1322, vl1);
                s516 = __riscv_vfmul(s554, 0.29389262614623657, vl1);
                s555 = __riscv_vfnmsac(t1322, 1.6180339887498947, t1321, vl1);
                s517 = __riscv_vfmul(s555, 0.29389262614623657, vl1);
                s518 = __riscv_vfmul(__riscv_vfsub(t1311, t1315, vl1), 0.55901699437494745, vl1);
                s519 = __riscv_vfmul(__riscv_vfsub(t1312, t1316, vl1), 0.55901699437494745, vl1);
                s556 = __riscv_vfnmsac(t1324, 0.6180339887498949, t1323, vl1);
                s520 = __riscv_vfmul(s556, 0.47552825814757677, vl1);
                s557 = __riscv_vfmacc(t1323, 0.6180339887498949, t1324, vl1);
                s521 = __riscv_vfmul(s557, 0.47552825814757677, vl1);
                t1329 = __riscv_vfadd(t1327, s518, vl1);
                t1330 = __riscv_vfadd(t1328, s519, vl1);
                t1331 = __riscv_vfsub(t1327, s518, vl1);
                t1332 = __riscv_vfsub(t1328, s519, vl1);
                t1333 = __riscv_vfadd(s516, s520, vl1);
                t1334 = __riscv_vfsub(s517, s521, vl1);
                t1335 = __riscv_vfsub(s516, s520, vl1);
                t1336 = __riscv_vfadd(s517, s521, vl1);
                t1337 = __riscv_vfadd(t1329, t1333, vl1);
                t1338 = __riscv_vfadd(t1330, t1334, vl1);
                t1339 = __riscv_vfsub(t1329, t1333, vl1);
                t1340 = __riscv_vfsub(t1330, t1334, vl1);
                t1341 = __riscv_vfadd(t1331, t1336, vl1);
                t1342 = __riscv_vfsub(t1332, t1335, vl1);
                t1343 = __riscv_vfsub(t1331, t1336, vl1);
                t1344 = __riscv_vfadd(t1332, t1335, vl1);
                t1345 = __riscv_vfadd(s502, s514, vl1);
                t1346 = __riscv_vfadd(s503, s515, vl1);
                t1347 = __riscv_vfsub(s502, s514, vl1);
                t1348 = __riscv_vfsub(s503, s515, vl1);
                t1349 = __riscv_vfadd(s506, s510, vl1);
                t1350 = __riscv_vfadd(s507, s511, vl1);
                t1351 = __riscv_vfsub(s506, s510, vl1);
                t1352 = __riscv_vfsub(s507, s511, vl1);
                t1353 = __riscv_vfadd(t1345, t1349, vl1);
                t1354 = __riscv_vfadd(t1346, t1350, vl1);
                t1355 = __riscv_vfadd(t1347, t1352, vl1);
                t1356 = __riscv_vfsub(t1348, t1351, vl1);
                t1357 = __riscv_vfsub(t1347, t1352, vl1);
                t1358 = __riscv_vfadd(t1348, t1351, vl1);
                t1359 = __riscv_vfadd(s498, t1353, vl1);
                t1360 = __riscv_vfadd(s499, t1354, vl1);
                t1361 = __riscv_vfnmsac(s498, 0.25, t1353, vl1);
                t1362 = __riscv_vfnmsac(s499, 0.25, t1354, vl1);
                s558 = __riscv_vfmacc(t1355, 1.6180339887498947, t1356, vl1);
                s522 = __riscv_vfmul(s558, 0.29389262614623657, vl1);
                s559 = __riscv_vfnmsac(t1356, 1.6180339887498947, t1355, vl1);
                s523 = __riscv_vfmul(s559, 0.29389262614623657, vl1);
                s524 = __riscv_vfmul(__riscv_vfsub(t1345, t1349, vl1), 0.55901699437494745, vl1);
                s525 = __riscv_vfmul(__riscv_vfsub(t1346, t1350, vl1), 0.55901699437494745, vl1);
                s560 = __riscv_vfnmsac(t1358, 0.6180339887498949, t1357, vl1);
                s526 = __riscv_vfmul(s560, 0.47552825814757677, vl1);
                s561 = __riscv_vfmacc(t1357, 0.6180339887498949, t1358, vl1);
                s527 = __riscv_vfmul(s561, 0.47552825814757677, vl1);
                t1363 = __riscv_vfadd(t1361, s524, vl1);
                t1364 = __riscv_vfadd(t1362, s525, vl1);
                t1365 = __riscv_vfsub(t1361, s524, vl1);
                t1366 = __riscv_vfsub(t1362, s525, vl1);
                t1367 = __riscv_vfadd(s522, s526, vl1);
                t1368 = __riscv_vfsub(s523, s527, vl1);
                t1369 = __riscv_vfsub(s522, s526, vl1);
                t1370 = __riscv_vfadd(s523, s527, vl1);
                t1371 = __riscv_vfadd(t1363, t1367, vl1);
                t1372 = __riscv_vfadd(t1364, t1368, vl1);
                t1373 = __riscv_vfsub(t1363, t1367, vl1);
                t1374 = __riscv_vfsub(t1364, t1368, vl1);
                s562 = __riscv_vfmacc(t1371, 0.7265425280053609, t1372, vl1);
                s528 = __riscv_vfmul(s562, 0.80901699437494745, vl1);
                s563 = __riscv_vfnmsac(t1372, 0.7265425280053609, t1371, vl1);
                s529 = __riscv_vfmul(s563, 0.80901699437494745, vl1);
                s564 = __riscv_vfnmsac(t1374, 1.3763819204711736, t1373, vl1);
                s530 = __riscv_vfmul(s564, 0.58778525229247314, vl1);
                s565 = __riscv_vfmacc(t1373, 1.3763819204711736, t1374, vl1);
                s531 = __riscv_vfmul(s565, 0.58778525229247314, vl1);
                t1375 = __riscv_vfadd(t1365, t1370, vl1);
                t1376 = __riscv_vfsub(t1366, t1369, vl1);
                t1377 = __riscv_vfsub(t1365, t1370, vl1);
                t1378 = __riscv_vfadd(t1366, t1369, vl1);
                s566 = __riscv_vfmacc(t1375, 3.0776835371752536, t1376, vl1);
                s532 = __riscv_vfmul(s566, 0.3090169943749474, vl1);
                s567 = __riscv_vfnmsac(t1376, 3.0776835371752536, t1375, vl1);
                s533 = __riscv_vfmul(s567, 0.3090169943749474, vl1);
                s568 = __riscv_vfnmsac(t1378, 0.32491969623290629, t1377, vl1);
                s534 = __riscv_vfmul(s568, 0.95105651629515353, vl1);
                s569 = __riscv_vfmacc(t1377, 0.32491969623290629, t1378, vl1);
                s535 = __riscv_vfmul(s569, 0.95105651629515353, vl1);
                s536 = __riscv_vfsub(t1325, t1359, vl1);
                s537 = __riscv_vfsub(t1326, t1360, vl1);
                s538 = __riscv_vfadd(t1337, s528, vl1);
                s539 = __riscv_vfadd(t1338, s529, vl1);
                s540 = __riscv_vfsub(t1337, s528, vl1);
                s541 = __riscv_vfsub(t1338, s529, vl1);
                s542 = __riscv_vfadd(t1341, s532, vl1);
                s543 = __riscv_vfadd(t1342, s533, vl1);
                s544 = __riscv_vfsub(t1341, s532, vl1);
                s545 = __riscv_vfsub(t1342, s533, vl1);
                s546 = __riscv_vfadd(t1343, s534, vl1);
                s547 = __riscv_vfsub(t1344, s535, vl1);
                s548 = __riscv_vfsub(t1343, s534, vl1);
                s549 = __riscv_vfadd(t1344, s535, vl1);
                s550 = __riscv_vfadd(t1339, s530, vl1);
                s551 = __riscv_vfsub(t1340, s531, vl1);
                s552 = __riscv_vfsub(t1339, s530, vl1);
                s553 = __riscv_vfadd(t1340, s531, vl1);
                a1114 = ((18)*(j1));
                a1115 = TW1[a1114];
                a1116 = TW1[(a1114 + 1)];
                a1117 = TW1[(a1114 + 2)];
                a1118 = TW1[(a1114 + 3)];
                a1119 = TW1[(a1114 + 4)];
                a1120 = TW1[(a1114 + 5)];
                a1121 = TW1[(a1114 + 6)];
                a1122 = TW1[(a1114 + 7)];
                a1123 = TW1[(a1114 + 8)];
                a1124 = TW1[(a1114 + 9)];
                a1125 = TW1[(a1114 + 10)];
                a1126 = TW1[(a1114 + 11)];
                a1127 = TW1[(a1114 + 12)];
                a1128 = TW1[(a1114 + 13)];
                a1129 = TW1[(a1114 + 14)];
                a1130 = TW1[(a1114 + 15)];
                a1131 = TW1[(a1114 + 16)];
                a1132 = TW1[(a1114 + 17)];
                r171 = __riscv_vset(__riscv_vset(rvvx2_11, 0, __riscv_vfadd(t1325, t1359, vl1)), 1, __riscv_vfadd(t1326, t1360, vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((10)*(j1)))*(m1)))))), r171, vl1);
                r172 = __riscv_vset(__riscv_vset(rvvx2_12, 0, __riscv_vfsub(__riscv_vfmul(s538, a1115, vl1), __riscv_vfmul(s539, a1116, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s538, a1116, vl1), __riscv_vfmul(s539, a1115, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((10)*(j1)))*(m1)) + m1)))), r172, vl1);
                r173 = __riscv_vset(__riscv_vset(rvvx2_13, 0, __riscv_vfsub(__riscv_vfmul(s542, a1117, vl1), __riscv_vfmul(s543, a1118, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s542, a1118, vl1), __riscv_vfmul(s543, a1117, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((10)*(j1)))*(m1)) + ((2)*(m1)))))), r173, vl1);
                r174 = __riscv_vset(__riscv_vset(rvvx2_14, 0, __riscv_vfsub(__riscv_vfmul(s546, a1119, vl1), __riscv_vfmul(s547, a1120, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s546, a1120, vl1), __riscv_vfmul(s547, a1119, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((10)*(j1)))*(m1)) + ((3)*(m1)))))), r174, vl1);
                r175 = __riscv_vset(__riscv_vset(rvvx2_15, 0, __riscv_vfsub(__riscv_vfmul(s550, a1121, vl1), __riscv_vfmul(s551, a1122, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s550, a1122, vl1), __riscv_vfmul(s551, a1121, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((10)*(j1)))*(m1)) + ((4)*(m1)))))), r175, vl1);
                r176 = __riscv_vset(__riscv_vset(rvvx2_16, 0, __riscv_vfsub(__riscv_vfmul(s536, a1123, vl1), __riscv_vfmul(s537, a1124, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s536, a1124, vl1), __riscv_vfmul(s537, a1123, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((10)*(j1)))*(m1)) + ((5)*(m1)))))), r176, vl1);
                r177 = __riscv_vset(__riscv_vset(rvvx2_17, 0, __riscv_vfsub(__riscv_vfmul(s540, a1125, vl1), __riscv_vfmul(s541, a1126, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s540, a1126, vl1), __riscv_vfmul(s541, a1125, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((10)*(j1)))*(m1)) + ((6)*(m1)))))), r177, vl1);
                r178 = __riscv_vset(__riscv_vset(rvvx2_18, 0, __riscv_vfsub(__riscv_vfmul(s544, a1127, vl1), __riscv_vfmul(s545, a1128, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s544, a1128, vl1), __riscv_vfmul(s545, a1127, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((10)*(j1)))*(m1)) + ((7)*(m1)))))), r178, vl1);
                r179 = __riscv_vset(__riscv_vset(rvvx2_19, 0, __riscv_vfsub(__riscv_vfmul(s548, a1129, vl1), __riscv_vfmul(s549, a1130, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s548, a1130, vl1), __riscv_vfmul(s549, a1129, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((10)*(j1)))*(m1)) + ((8)*(m1)))))), r179, vl1);
                r180 = __riscv_vset(__riscv_vset(rvvx2_20, 0, __riscv_vfsub(__riscv_vfmul(s552, a1131, vl1), __riscv_vfmul(s553, a1132, vl1), vl1)), 1, __riscv_vfadd(__riscv_vfmul(s552, a1132, vl1), __riscv_vfmul(s553, a1131, vl1), vl1));
                __riscv_vsseg2e32((Y + ((2)*((k1 + ((((10)*(j1)))*(m1)) + ((9)*(m1)))))), r180, vl1);
            }
        }
    }
}
