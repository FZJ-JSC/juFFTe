// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft10c_(double *Y, double *X, int *lp1, int *mp1) {
    int l1, m1;
    vfloat64m1x2_t r161, r162, r163, r164, r165, r166, r167, r168, 
            r169, r170, r171, r172, r173, r174, r175, r176, 
            r177, r178, r179, r180, rvvx2_11, rvvx2_12, rvvx2_13, rvvx2_14, 
            rvvx2_15, rvvx2_16, rvvx2_17, rvvx2_18, rvvx2_19, rvvx2_20;
    vfloat64m1_t  s442, s443, s444, s445, s446, s447, s448, s449, 
            s450, s451, s452, s453, s454, s455, s456, s457, 
            s458, s459, s460, s461, s462, s463, s464, s465, 
            s466, s467, s468, s469, s470, s471, s472, s473, 
            s474, s475, s476, s477, s478, s479, s480, s481, 
            s482, s483, s484, s485, s486, s487, s488, s489, 
            s490, s491, s492, s493, s494, s495, s496, s497, 
            t1310, t1311, t1312, t1313, t1314, t1315, t1316, t1317, 
            t1318, t1319, t1320, t1321, t1322, t1323, t1324, t1325, 
            t1326, t1327, t1328, t1329, t1330, t1331, t1332, t1333, 
            t1334, t1335, t1336, t1337, t1338, t1339, t1340, t1341, 
            t1342, t1343, t1344, t1345, t1346, t1347, t1348, t1349, 
            t1350, t1351, t1352, t1353, t1354, t1355, t1356, t1357, 
            t1358, t1359, t1360, t1361, t1362, t1363, t1364, t1365, 
            t1366, t1367, t1368, t1369, t1370, t1371, t1372, t1373, 
            t1374, t1375, t1376, t1377;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for (size_t k1 = 0; k1 < m1; k1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(m1 - k1);
        r161 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(k1))), vl1);
        s442 = __riscv_vget_f64m1(r161, 0);
        s443 = __riscv_vget_f64m1(r161, 1);
        r162 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((l1)*(m1)))))), vl1);
        s444 = __riscv_vget_f64m1(r162, 0);
        s445 = __riscv_vget_f64m1(r162, 1);
        r163 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((2)*(l1)))*(m1)))))), vl1);
        s446 = __riscv_vget_f64m1(r163, 0);
        s447 = __riscv_vget_f64m1(r163, 1);
        r164 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((3)*(l1)))*(m1)))))), vl1);
        s448 = __riscv_vget_f64m1(r164, 0);
        s449 = __riscv_vget_f64m1(r164, 1);
        r165 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((4)*(l1)))*(m1)))))), vl1);
        s450 = __riscv_vget_f64m1(r165, 0);
        s451 = __riscv_vget_f64m1(r165, 1);
        r166 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((5)*(l1)))*(m1)))))), vl1);
        s452 = __riscv_vget_f64m1(r166, 0);
        s453 = __riscv_vget_f64m1(r166, 1);
        r167 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((6)*(l1)))*(m1)))))), vl1);
        s454 = __riscv_vget_f64m1(r167, 0);
        s455 = __riscv_vget_f64m1(r167, 1);
        r168 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((7)*(l1)))*(m1)))))), vl1);
        s456 = __riscv_vget_f64m1(r168, 0);
        s457 = __riscv_vget_f64m1(r168, 1);
        r169 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((8)*(l1)))*(m1)))))), vl1);
        s458 = __riscv_vget_f64m1(r169, 0);
        s459 = __riscv_vget_f64m1(r169, 1);
        r170 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((9)*(l1)))*(m1)))))), vl1);
        s460 = __riscv_vget_f64m1(r170, 0);
        s461 = __riscv_vget_f64m1(r170, 1);
        t1310 = __riscv_vfadd(s446, s458, vl1);
        t1311 = __riscv_vfadd(s447, s459, vl1);
        t1312 = __riscv_vfsub(s446, s458, vl1);
        t1313 = __riscv_vfsub(s447, s459, vl1);
        t1314 = __riscv_vfadd(s450, s454, vl1);
        t1315 = __riscv_vfadd(s451, s455, vl1);
        t1316 = __riscv_vfsub(s450, s454, vl1);
        t1317 = __riscv_vfsub(s451, s455, vl1);
        t1318 = __riscv_vfadd(t1310, t1314, vl1);
        t1319 = __riscv_vfadd(t1311, t1315, vl1);
        t1320 = __riscv_vfadd(t1312, t1317, vl1);
        t1321 = __riscv_vfsub(t1313, t1316, vl1);
        t1322 = __riscv_vfsub(t1312, t1317, vl1);
        t1323 = __riscv_vfadd(t1313, t1316, vl1);
        t1324 = __riscv_vfadd(s442, t1318, vl1);
        t1325 = __riscv_vfadd(s443, t1319, vl1);
        t1326 = __riscv_vfnmsac(s442, 0.25, t1318, vl1);
        t1327 = __riscv_vfnmsac(s443, 0.25, t1319, vl1);
        s482 = __riscv_vfmacc(t1320, 1.6180339887498947, t1321, vl1);
        s462 = __riscv_vfmul(s482, 0.29389262614623657, vl1);
        s483 = __riscv_vfnmsac(t1321, 1.6180339887498947, t1320, vl1);
        s463 = __riscv_vfmul(s483, 0.29389262614623657, vl1);
        s464 = __riscv_vfmul(__riscv_vfsub(t1310, t1314, vl1), 0.55901699437494745, vl1);
        s465 = __riscv_vfmul(__riscv_vfsub(t1311, t1315, vl1), 0.55901699437494745, vl1);
        s484 = __riscv_vfnmsac(t1323, 0.6180339887498949, t1322, vl1);
        s466 = __riscv_vfmul(s484, 0.47552825814757677, vl1);
        s485 = __riscv_vfmacc(t1322, 0.6180339887498949, t1323, vl1);
        s467 = __riscv_vfmul(s485, 0.47552825814757677, vl1);
        t1328 = __riscv_vfadd(t1326, s464, vl1);
        t1329 = __riscv_vfadd(t1327, s465, vl1);
        t1330 = __riscv_vfsub(t1326, s464, vl1);
        t1331 = __riscv_vfsub(t1327, s465, vl1);
        t1332 = __riscv_vfadd(s462, s466, vl1);
        t1333 = __riscv_vfsub(s463, s467, vl1);
        t1334 = __riscv_vfsub(s462, s466, vl1);
        t1335 = __riscv_vfadd(s463, s467, vl1);
        t1336 = __riscv_vfadd(t1328, t1332, vl1);
        t1337 = __riscv_vfadd(t1329, t1333, vl1);
        t1338 = __riscv_vfsub(t1328, t1332, vl1);
        t1339 = __riscv_vfsub(t1329, t1333, vl1);
        t1340 = __riscv_vfadd(t1330, t1335, vl1);
        t1341 = __riscv_vfsub(t1331, t1334, vl1);
        t1342 = __riscv_vfsub(t1330, t1335, vl1);
        t1343 = __riscv_vfadd(t1331, t1334, vl1);
        t1344 = __riscv_vfadd(s448, s460, vl1);
        t1345 = __riscv_vfadd(s449, s461, vl1);
        t1346 = __riscv_vfsub(s448, s460, vl1);
        t1347 = __riscv_vfsub(s449, s461, vl1);
        t1348 = __riscv_vfadd(s452, s456, vl1);
        t1349 = __riscv_vfadd(s453, s457, vl1);
        t1350 = __riscv_vfsub(s452, s456, vl1);
        t1351 = __riscv_vfsub(s453, s457, vl1);
        t1352 = __riscv_vfadd(t1344, t1348, vl1);
        t1353 = __riscv_vfadd(t1345, t1349, vl1);
        t1354 = __riscv_vfadd(t1346, t1351, vl1);
        t1355 = __riscv_vfsub(t1347, t1350, vl1);
        t1356 = __riscv_vfsub(t1346, t1351, vl1);
        t1357 = __riscv_vfadd(t1347, t1350, vl1);
        t1358 = __riscv_vfadd(s444, t1352, vl1);
        t1359 = __riscv_vfadd(s445, t1353, vl1);
        t1360 = __riscv_vfnmsac(s444, 0.25, t1352, vl1);
        t1361 = __riscv_vfnmsac(s445, 0.25, t1353, vl1);
        s486 = __riscv_vfmacc(t1354, 1.6180339887498947, t1355, vl1);
        s468 = __riscv_vfmul(s486, 0.29389262614623657, vl1);
        s487 = __riscv_vfnmsac(t1355, 1.6180339887498947, t1354, vl1);
        s469 = __riscv_vfmul(s487, 0.29389262614623657, vl1);
        s470 = __riscv_vfmul(__riscv_vfsub(t1344, t1348, vl1), 0.55901699437494745, vl1);
        s471 = __riscv_vfmul(__riscv_vfsub(t1345, t1349, vl1), 0.55901699437494745, vl1);
        s488 = __riscv_vfnmsac(t1357, 0.6180339887498949, t1356, vl1);
        s472 = __riscv_vfmul(s488, 0.47552825814757677, vl1);
        s489 = __riscv_vfmacc(t1356, 0.6180339887498949, t1357, vl1);
        s473 = __riscv_vfmul(s489, 0.47552825814757677, vl1);
        t1362 = __riscv_vfadd(t1360, s470, vl1);
        t1363 = __riscv_vfadd(t1361, s471, vl1);
        t1364 = __riscv_vfsub(t1360, s470, vl1);
        t1365 = __riscv_vfsub(t1361, s471, vl1);
        t1366 = __riscv_vfadd(s468, s472, vl1);
        t1367 = __riscv_vfsub(s469, s473, vl1);
        t1368 = __riscv_vfsub(s468, s472, vl1);
        t1369 = __riscv_vfadd(s469, s473, vl1);
        t1370 = __riscv_vfadd(t1362, t1366, vl1);
        t1371 = __riscv_vfadd(t1363, t1367, vl1);
        t1372 = __riscv_vfsub(t1362, t1366, vl1);
        t1373 = __riscv_vfsub(t1363, t1367, vl1);
        s490 = __riscv_vfmacc(t1370, 0.7265425280053609, t1371, vl1);
        s474 = __riscv_vfmul(s490, 0.80901699437494745, vl1);
        s491 = __riscv_vfnmsac(t1371, 0.7265425280053609, t1370, vl1);
        s475 = __riscv_vfmul(s491, 0.80901699437494745, vl1);
        s492 = __riscv_vfnmsac(t1373, 1.3763819204711736, t1372, vl1);
        s476 = __riscv_vfmul(s492, 0.58778525229247314, vl1);
        s493 = __riscv_vfmacc(t1372, 1.3763819204711736, t1373, vl1);
        s477 = __riscv_vfmul(s493, 0.58778525229247314, vl1);
        t1374 = __riscv_vfadd(t1364, t1369, vl1);
        t1375 = __riscv_vfsub(t1365, t1368, vl1);
        t1376 = __riscv_vfsub(t1364, t1369, vl1);
        t1377 = __riscv_vfadd(t1365, t1368, vl1);
        s494 = __riscv_vfmacc(t1374, 3.0776835371752536, t1375, vl1);
        s478 = __riscv_vfmul(s494, 0.3090169943749474, vl1);
        s495 = __riscv_vfnmsac(t1375, 3.0776835371752536, t1374, vl1);
        s479 = __riscv_vfmul(s495, 0.3090169943749474, vl1);
        s496 = __riscv_vfnmsac(t1377, 0.32491969623290629, t1376, vl1);
        s480 = __riscv_vfmul(s496, 0.95105651629515353, vl1);
        s497 = __riscv_vfmacc(t1376, 0.32491969623290629, t1377, vl1);
        s481 = __riscv_vfmul(s497, 0.95105651629515353, vl1);
        r171 = __riscv_vset(__riscv_vset(rvvx2_11, 0, __riscv_vfadd(t1324, t1358, vl1)), 1, __riscv_vfadd(t1325, t1359, vl1));
        __riscv_vsseg2e64((Y + ((2)*(k1))), r171, vl1);
        r172 = __riscv_vset(__riscv_vset(rvvx2_12, 0, __riscv_vfadd(t1336, s474, vl1)), 1, __riscv_vfadd(t1337, s475, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + m1)))), r172, vl1);
        r173 = __riscv_vset(__riscv_vset(rvvx2_13, 0, __riscv_vfadd(t1340, s478, vl1)), 1, __riscv_vfadd(t1341, s479, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((2)*(m1)))))), r173, vl1);
        r174 = __riscv_vset(__riscv_vset(rvvx2_14, 0, __riscv_vfadd(t1342, s480, vl1)), 1, __riscv_vfsub(t1343, s481, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((3)*(m1)))))), r174, vl1);
        r175 = __riscv_vset(__riscv_vset(rvvx2_15, 0, __riscv_vfadd(t1338, s476, vl1)), 1, __riscv_vfsub(t1339, s477, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((4)*(m1)))))), r175, vl1);
        r176 = __riscv_vset(__riscv_vset(rvvx2_16, 0, __riscv_vfsub(t1324, t1358, vl1)), 1, __riscv_vfsub(t1325, t1359, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((5)*(m1)))))), r176, vl1);
        r177 = __riscv_vset(__riscv_vset(rvvx2_17, 0, __riscv_vfsub(t1336, s474, vl1)), 1, __riscv_vfsub(t1337, s475, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((6)*(m1)))))), r177, vl1);
        r178 = __riscv_vset(__riscv_vset(rvvx2_18, 0, __riscv_vfsub(t1340, s478, vl1)), 1, __riscv_vfsub(t1341, s479, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((7)*(m1)))))), r178, vl1);
        r179 = __riscv_vset(__riscv_vset(rvvx2_19, 0, __riscv_vfsub(t1342, s480, vl1)), 1, __riscv_vfadd(t1343, s481, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((8)*(m1)))))), r179, vl1);
        r180 = __riscv_vset(__riscv_vset(rvvx2_20, 0, __riscv_vfsub(t1338, s476, vl1)), 1, __riscv_vfadd(t1339, s477, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((9)*(m1)))))), r180, vl1);
    }
}
