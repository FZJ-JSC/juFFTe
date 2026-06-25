// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft10a_r32_(float *Y, float *X, float *TW1, int64_t *lp1) {
    int64_t l1;
    float *a1022;
    vfloat32m1x2_t r71, r72, r73, r74, r75, r76, r77, r78, 
            r79, r80;
    vfloat32m1_t  a1023, a1024, a1025, a1026, a1027, a1028, a1029, a1030, 
            a1031, a1032, a1033, a1034, a1035, a1036, a1037, a1038, 
            a1039, a1040, s516, s517, s518, s519, s520, s521, 
            s522, s523, s524, s525, s526, s527, s528, s529, 
            s530, s531, s532, s533, s534, s535, s536, s537, 
            s538, s539, s540, s541, s542, s543, s544, s545, 
            s546, s547, s548, s549, s550, s551, s552, s553, 
            s554, s555, s556, s557, s558, s559, s560, s561, 
            s562, s563, s564, s565, s566, s567, s568, s569, 
            s570, s571, s572, s573, s574, s575, s576, s577, 
            s578, s579, s580, s581, s582, s583, s584, s585, 
            s586, s587, s588, s589, s590, s591, s592, s593, 
            s594, s595, s596, s597, s598, s599, s600, s601, 
            s602, s603, s604, s605, s606, s607, s608, s609, 
            t1311, t1312, t1313, t1314, t1315, t1316, t1317, t1318, 
            t1319, t1320, t1321, t1322, t1323, t1324, t1325, t1326, 
            t1327, t1328, t1329, t1330, t1331, t1332, t1333, t1334, 
            t1335, t1336, t1337, t1338, t1339, t1340, t1341, t1342, 
            t1343, t1344, t1345, t1346, t1347, t1348, t1349, t1350, 
            t1351, t1352, t1353, t1354, t1355, t1356, t1357, t1358, 
            t1359, t1360, t1361, t1362, t1363, t1364, t1365, t1366, 
            t1367, t1368, t1369, t1370, t1371, t1372, t1373, t1374, 
            t1375, t1376, t1377, t1378;
    size_t vl1;
    l1 = *(lp1);
    for (size_t j1 = 0; j1 < l1; j1 += vl1) {
        vl1 = __riscv_vsetvl_e32m1(l1 - j1);
        r71 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*(j1))), vl1);
        s516 = __riscv_vget_f32m1(r71, 0);
        s517 = __riscv_vget_f32m1(r71, 1);
        r72 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + l1)))), vl1);
        s518 = __riscv_vget_f32m1(r72, 0);
        s519 = __riscv_vget_f32m1(r72, 1);
        r73 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((2)*(l1)))))), vl1);
        s520 = __riscv_vget_f32m1(r73, 0);
        s521 = __riscv_vget_f32m1(r73, 1);
        r74 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((3)*(l1)))))), vl1);
        s522 = __riscv_vget_f32m1(r74, 0);
        s523 = __riscv_vget_f32m1(r74, 1);
        r75 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((4)*(l1)))))), vl1);
        s524 = __riscv_vget_f32m1(r75, 0);
        s525 = __riscv_vget_f32m1(r75, 1);
        r76 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((5)*(l1)))))), vl1);
        s526 = __riscv_vget_f32m1(r76, 0);
        s527 = __riscv_vget_f32m1(r76, 1);
        r77 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((6)*(l1)))))), vl1);
        s528 = __riscv_vget_f32m1(r77, 0);
        s529 = __riscv_vget_f32m1(r77, 1);
        r78 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((7)*(l1)))))), vl1);
        s530 = __riscv_vget_f32m1(r78, 0);
        s531 = __riscv_vget_f32m1(r78, 1);
        r79 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((8)*(l1)))))), vl1);
        s532 = __riscv_vget_f32m1(r79, 0);
        s533 = __riscv_vget_f32m1(r79, 1);
        r80 = __riscv_vlseg2e32_v_f32m1x2((X + ((2)*((j1 + ((9)*(l1)))))), vl1);
        s534 = __riscv_vget_f32m1(r80, 0);
        s535 = __riscv_vget_f32m1(r80, 1);
        t1311 = __riscv_vfadd(s520, s532, vl1);
        t1312 = __riscv_vfadd(s521, s533, vl1);
        t1313 = __riscv_vfsub(s520, s532, vl1);
        t1314 = __riscv_vfsub(s521, s533, vl1);
        t1315 = __riscv_vfadd(s524, s528, vl1);
        t1316 = __riscv_vfadd(s525, s529, vl1);
        t1317 = __riscv_vfsub(s524, s528, vl1);
        t1318 = __riscv_vfsub(s525, s529, vl1);
        t1319 = __riscv_vfadd(t1311, t1315, vl1);
        t1320 = __riscv_vfadd(t1312, t1316, vl1);
        t1321 = __riscv_vfadd(t1313, t1318, vl1);
        t1322 = __riscv_vfsub(t1314, t1317, vl1);
        t1323 = __riscv_vfsub(t1313, t1318, vl1);
        t1324 = __riscv_vfadd(t1314, t1317, vl1);
        t1325 = __riscv_vfadd(s516, t1319, vl1);
        t1326 = __riscv_vfadd(s517, t1320, vl1);
        t1327 = __riscv_vfnmsac(s516, 0.25, t1319, vl1);
        t1328 = __riscv_vfnmsac(s517, 0.25, t1320, vl1);
        s594 = __riscv_vfmacc(t1321, 1.6180339887498947, t1322, vl1);
        s536 = __riscv_vfmul(s594, 0.29389262614623657, vl1);
        s595 = __riscv_vfnmsac(t1322, 1.6180339887498947, t1321, vl1);
        s537 = __riscv_vfmul(s595, 0.29389262614623657, vl1);
        s538 = __riscv_vfmul(__riscv_vfsub(t1311, t1315, vl1), 0.55901699437494745, vl1);
        s539 = __riscv_vfmul(__riscv_vfsub(t1312, t1316, vl1), 0.55901699437494745, vl1);
        s596 = __riscv_vfnmsac(t1324, 0.6180339887498949, t1323, vl1);
        s540 = __riscv_vfmul(s596, 0.47552825814757677, vl1);
        s597 = __riscv_vfmacc(t1323, 0.6180339887498949, t1324, vl1);
        s541 = __riscv_vfmul(s597, 0.47552825814757677, vl1);
        t1329 = __riscv_vfadd(t1327, s538, vl1);
        t1330 = __riscv_vfadd(t1328, s539, vl1);
        t1331 = __riscv_vfsub(t1327, s538, vl1);
        t1332 = __riscv_vfsub(t1328, s539, vl1);
        t1333 = __riscv_vfadd(s536, s540, vl1);
        t1334 = __riscv_vfsub(s537, s541, vl1);
        t1335 = __riscv_vfsub(s536, s540, vl1);
        t1336 = __riscv_vfadd(s537, s541, vl1);
        t1337 = __riscv_vfadd(t1329, t1333, vl1);
        t1338 = __riscv_vfadd(t1330, t1334, vl1);
        t1339 = __riscv_vfsub(t1329, t1333, vl1);
        t1340 = __riscv_vfsub(t1330, t1334, vl1);
        t1341 = __riscv_vfadd(t1331, t1336, vl1);
        t1342 = __riscv_vfsub(t1332, t1335, vl1);
        t1343 = __riscv_vfsub(t1331, t1336, vl1);
        t1344 = __riscv_vfadd(t1332, t1335, vl1);
        t1345 = __riscv_vfadd(s522, s534, vl1);
        t1346 = __riscv_vfadd(s523, s535, vl1);
        t1347 = __riscv_vfsub(s522, s534, vl1);
        t1348 = __riscv_vfsub(s523, s535, vl1);
        t1349 = __riscv_vfadd(s526, s530, vl1);
        t1350 = __riscv_vfadd(s527, s531, vl1);
        t1351 = __riscv_vfsub(s526, s530, vl1);
        t1352 = __riscv_vfsub(s527, s531, vl1);
        t1353 = __riscv_vfadd(t1345, t1349, vl1);
        t1354 = __riscv_vfadd(t1346, t1350, vl1);
        t1355 = __riscv_vfadd(t1347, t1352, vl1);
        t1356 = __riscv_vfsub(t1348, t1351, vl1);
        t1357 = __riscv_vfsub(t1347, t1352, vl1);
        t1358 = __riscv_vfadd(t1348, t1351, vl1);
        t1359 = __riscv_vfadd(s518, t1353, vl1);
        t1360 = __riscv_vfadd(s519, t1354, vl1);
        t1361 = __riscv_vfnmsac(s518, 0.25, t1353, vl1);
        t1362 = __riscv_vfnmsac(s519, 0.25, t1354, vl1);
        s598 = __riscv_vfmacc(t1355, 1.6180339887498947, t1356, vl1);
        s542 = __riscv_vfmul(s598, 0.29389262614623657, vl1);
        s599 = __riscv_vfnmsac(t1356, 1.6180339887498947, t1355, vl1);
        s543 = __riscv_vfmul(s599, 0.29389262614623657, vl1);
        s544 = __riscv_vfmul(__riscv_vfsub(t1345, t1349, vl1), 0.55901699437494745, vl1);
        s545 = __riscv_vfmul(__riscv_vfsub(t1346, t1350, vl1), 0.55901699437494745, vl1);
        s600 = __riscv_vfnmsac(t1358, 0.6180339887498949, t1357, vl1);
        s546 = __riscv_vfmul(s600, 0.47552825814757677, vl1);
        s601 = __riscv_vfmacc(t1357, 0.6180339887498949, t1358, vl1);
        s547 = __riscv_vfmul(s601, 0.47552825814757677, vl1);
        t1363 = __riscv_vfadd(t1361, s544, vl1);
        t1364 = __riscv_vfadd(t1362, s545, vl1);
        t1365 = __riscv_vfsub(t1361, s544, vl1);
        t1366 = __riscv_vfsub(t1362, s545, vl1);
        t1367 = __riscv_vfadd(s542, s546, vl1);
        t1368 = __riscv_vfsub(s543, s547, vl1);
        t1369 = __riscv_vfsub(s542, s546, vl1);
        t1370 = __riscv_vfadd(s543, s547, vl1);
        t1371 = __riscv_vfadd(t1363, t1367, vl1);
        t1372 = __riscv_vfadd(t1364, t1368, vl1);
        t1373 = __riscv_vfsub(t1363, t1367, vl1);
        t1374 = __riscv_vfsub(t1364, t1368, vl1);
        s602 = __riscv_vfmacc(t1371, 0.7265425280053609, t1372, vl1);
        s548 = __riscv_vfmul(s602, 0.80901699437494745, vl1);
        s603 = __riscv_vfnmsac(t1372, 0.7265425280053609, t1371, vl1);
        s549 = __riscv_vfmul(s603, 0.80901699437494745, vl1);
        s604 = __riscv_vfnmsac(t1374, 1.3763819204711736, t1373, vl1);
        s550 = __riscv_vfmul(s604, 0.58778525229247314, vl1);
        s605 = __riscv_vfmacc(t1373, 1.3763819204711736, t1374, vl1);
        s551 = __riscv_vfmul(s605, 0.58778525229247314, vl1);
        t1375 = __riscv_vfadd(t1365, t1370, vl1);
        t1376 = __riscv_vfsub(t1366, t1369, vl1);
        t1377 = __riscv_vfsub(t1365, t1370, vl1);
        t1378 = __riscv_vfadd(t1366, t1369, vl1);
        s606 = __riscv_vfmacc(t1375, 3.0776835371752536, t1376, vl1);
        s552 = __riscv_vfmul(s606, 0.3090169943749474, vl1);
        s607 = __riscv_vfnmsac(t1376, 3.0776835371752536, t1375, vl1);
        s553 = __riscv_vfmul(s607, 0.3090169943749474, vl1);
        s608 = __riscv_vfnmsac(t1378, 0.32491969623290629, t1377, vl1);
        s554 = __riscv_vfmul(s608, 0.95105651629515353, vl1);
        s609 = __riscv_vfmacc(t1377, 0.32491969623290629, t1378, vl1);
        s555 = __riscv_vfmul(s609, 0.95105651629515353, vl1);
        s556 = __riscv_vfadd(t1325, t1359, vl1);
        s557 = __riscv_vfadd(t1326, t1360, vl1);
        s558 = __riscv_vfsub(t1325, t1359, vl1);
        s559 = __riscv_vfsub(t1326, t1360, vl1);
        s560 = __riscv_vfadd(t1337, s548, vl1);
        s561 = __riscv_vfadd(t1338, s549, vl1);
        s562 = __riscv_vfsub(t1337, s548, vl1);
        s563 = __riscv_vfsub(t1338, s549, vl1);
        s564 = __riscv_vfadd(t1341, s552, vl1);
        s565 = __riscv_vfadd(t1342, s553, vl1);
        s566 = __riscv_vfsub(t1341, s552, vl1);
        s567 = __riscv_vfsub(t1342, s553, vl1);
        s568 = __riscv_vfadd(t1343, s554, vl1);
        s569 = __riscv_vfsub(t1344, s555, vl1);
        s570 = __riscv_vfsub(t1343, s554, vl1);
        s571 = __riscv_vfadd(t1344, s555, vl1);
        s572 = __riscv_vfadd(t1339, s550, vl1);
        s573 = __riscv_vfsub(t1340, s551, vl1);
        s574 = __riscv_vfsub(t1339, s550, vl1);
        s575 = __riscv_vfadd(t1340, s551, vl1);
        a1022 = (TW1 + ((18)*(j1)));
        a1023 = __riscv_vlse32_v_f32m1(a1022, sizeof(double) * 18, vl1);
        a1024 = __riscv_vlse32_v_f32m1((a1022 + 1), sizeof(double) * 18, vl1);
        s576 = __riscv_vfmsac(__riscv_vfmul(a1024, s561, vl1), a1023, s560, vl1);
        s577 = __riscv_vfmacc(__riscv_vfmul(a1023, s561, vl1), a1024, s560, vl1);
        a1025 = __riscv_vlse32_v_f32m1((a1022 + 2), sizeof(double) * 18, vl1);
        a1026 = __riscv_vlse32_v_f32m1((a1022 + 3), sizeof(double) * 18, vl1);
        s578 = __riscv_vfmsac(__riscv_vfmul(a1026, s565, vl1), a1025, s564, vl1);
        s579 = __riscv_vfmacc(__riscv_vfmul(a1025, s565, vl1), a1026, s564, vl1);
        a1027 = __riscv_vlse32_v_f32m1((a1022 + 4), sizeof(double) * 18, vl1);
        a1028 = __riscv_vlse32_v_f32m1((a1022 + 5), sizeof(double) * 18, vl1);
        s580 = __riscv_vfmsac(__riscv_vfmul(a1028, s569, vl1), a1027, s568, vl1);
        s581 = __riscv_vfmacc(__riscv_vfmul(a1027, s569, vl1), a1028, s568, vl1);
        a1029 = __riscv_vlse32_v_f32m1((a1022 + 6), sizeof(double) * 18, vl1);
        a1030 = __riscv_vlse32_v_f32m1((a1022 + 7), sizeof(double) * 18, vl1);
        s582 = __riscv_vfmsac(__riscv_vfmul(a1030, s573, vl1), a1029, s572, vl1);
        s583 = __riscv_vfmacc(__riscv_vfmul(a1029, s573, vl1), a1030, s572, vl1);
        a1031 = __riscv_vlse32_v_f32m1((a1022 + 8), sizeof(double) * 18, vl1);
        a1032 = __riscv_vlse32_v_f32m1((a1022 + 9), sizeof(double) * 18, vl1);
        s584 = __riscv_vfmsac(__riscv_vfmul(a1032, s559, vl1), a1031, s558, vl1);
        s585 = __riscv_vfmacc(__riscv_vfmul(a1031, s559, vl1), a1032, s558, vl1);
        a1033 = __riscv_vlse32_v_f32m1((a1022 + 10), sizeof(double) * 18, vl1);
        a1034 = __riscv_vlse32_v_f32m1((a1022 + 11), sizeof(double) * 18, vl1);
        s586 = __riscv_vfmsac(__riscv_vfmul(a1034, s563, vl1), a1033, s562, vl1);
        s587 = __riscv_vfmacc(__riscv_vfmul(a1033, s563, vl1), a1034, s562, vl1);
        a1035 = __riscv_vlse32_v_f32m1((a1022 + 12), sizeof(double) * 18, vl1);
        a1036 = __riscv_vlse32_v_f32m1((a1022 + 13), sizeof(double) * 18, vl1);
        s588 = __riscv_vfmsac(__riscv_vfmul(a1036, s567, vl1), a1035, s566, vl1);
        s589 = __riscv_vfmacc(__riscv_vfmul(a1035, s567, vl1), a1036, s566, vl1);
        a1037 = __riscv_vlse32_v_f32m1((a1022 + 14), sizeof(double) * 18, vl1);
        a1038 = __riscv_vlse32_v_f32m1((a1022 + 15), sizeof(double) * 18, vl1);
        s590 = __riscv_vfmsac(__riscv_vfmul(a1038, s571, vl1), a1037, s570, vl1);
        s591 = __riscv_vfmacc(__riscv_vfmul(a1037, s571, vl1), a1038, s570, vl1);
        a1039 = __riscv_vlse32_v_f32m1((a1022 + 16), sizeof(double) * 18, vl1);
        a1040 = __riscv_vlse32_v_f32m1((a1022 + 17), sizeof(double) * 18, vl1);
        s592 = __riscv_vfmsac(__riscv_vfmul(a1040, s575, vl1), a1039, s574, vl1);
        s593 = __riscv_vfmacc(__riscv_vfmul(a1039, s575, vl1), a1040, s574, vl1);
        __riscv_vsse32((Y + ((20)*(j1))), sizeof(double) * 20, s556, vl1);
        __riscv_vsse32((1 + Y + ((20)*(j1))), sizeof(double) * 20, s557, vl1);
        __riscv_vsse32((2 + Y + ((20)*(j1))), sizeof(double) * 20, s576, vl1);
        __riscv_vsse32((3 + Y + ((20)*(j1))), sizeof(double) * 20, s577, vl1);
        __riscv_vsse32((4 + Y + ((20)*(j1))), sizeof(double) * 20, s578, vl1);
        __riscv_vsse32((5 + Y + ((20)*(j1))), sizeof(double) * 20, s579, vl1);
        __riscv_vsse32((6 + Y + ((20)*(j1))), sizeof(double) * 20, s580, vl1);
        __riscv_vsse32((7 + Y + ((20)*(j1))), sizeof(double) * 20, s581, vl1);
        __riscv_vsse32((8 + Y + ((20)*(j1))), sizeof(double) * 20, s582, vl1);
        __riscv_vsse32((9 + Y + ((20)*(j1))), sizeof(double) * 20, s583, vl1);
        __riscv_vsse32((10 + Y + ((20)*(j1))), sizeof(double) * 20, s584, vl1);
        __riscv_vsse32((11 + Y + ((20)*(j1))), sizeof(double) * 20, s585, vl1);
        __riscv_vsse32((12 + Y + ((20)*(j1))), sizeof(double) * 20, s586, vl1);
        __riscv_vsse32((13 + Y + ((20)*(j1))), sizeof(double) * 20, s587, vl1);
        __riscv_vsse32((14 + Y + ((20)*(j1))), sizeof(double) * 20, s588, vl1);
        __riscv_vsse32((15 + Y + ((20)*(j1))), sizeof(double) * 20, s589, vl1);
        __riscv_vsse32((16 + Y + ((20)*(j1))), sizeof(double) * 20, s590, vl1);
        __riscv_vsse32((17 + Y + ((20)*(j1))), sizeof(double) * 20, s591, vl1);
        __riscv_vsse32((18 + Y + ((20)*(j1))), sizeof(double) * 20, s592, vl1);
        __riscv_vsse32((19 + Y + ((20)*(j1))), sizeof(double) * 20, s593, vl1);
    }
}
