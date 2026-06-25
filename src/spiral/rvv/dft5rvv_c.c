// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft5c_(double *Y, double *X, int *lp1, int *mp1) {
    int l1, m1;
    vfloat64m1x2_t r81, r82, r83, r84, r85, r86, r87, r88, 
            r89, r90, rvvx2_10, rvvx2_6, rvvx2_7, rvvx2_8, rvvx2_9;
    vfloat64m1_t  s137, s138, s139, s140, s141, s142, s143, s144, 
            s145, s146, s147, s148, s149, s150, s151, s152, 
            s153, s154, s155, s156, t394, t395, t396, t397, 
            t398, t399, t400, t401, t402, t403, t404, t405, 
            t406, t407, t408, t409, t410, t411, t412, t413, 
            t414, t415, t416, t417;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for (size_t k1 = 0; k1 < m1; k1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(m1 - k1);
        r81 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(k1))), vl1);
        s137 = __riscv_vget_f64m1(r81, 0);
        s138 = __riscv_vget_f64m1(r81, 1);
        r82 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((l1)*(m1)))))), vl1);
        s139 = __riscv_vget_f64m1(r82, 0);
        s140 = __riscv_vget_f64m1(r82, 1);
        r83 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((2)*(l1)))*(m1)))))), vl1);
        s141 = __riscv_vget_f64m1(r83, 0);
        s142 = __riscv_vget_f64m1(r83, 1);
        r84 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((3)*(l1)))*(m1)))))), vl1);
        s143 = __riscv_vget_f64m1(r84, 0);
        s144 = __riscv_vget_f64m1(r84, 1);
        r85 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((4)*(l1)))*(m1)))))), vl1);
        s145 = __riscv_vget_f64m1(r85, 0);
        s146 = __riscv_vget_f64m1(r85, 1);
        t394 = __riscv_vfadd(s139, s145, vl1);
        t395 = __riscv_vfadd(s140, s146, vl1);
        t396 = __riscv_vfsub(s139, s145, vl1);
        t397 = __riscv_vfsub(s140, s146, vl1);
        t398 = __riscv_vfadd(s141, s143, vl1);
        t399 = __riscv_vfadd(s142, s144, vl1);
        t400 = __riscv_vfsub(s141, s143, vl1);
        t401 = __riscv_vfsub(s142, s144, vl1);
        t402 = __riscv_vfadd(t394, t398, vl1);
        t403 = __riscv_vfadd(t395, t399, vl1);
        t404 = __riscv_vfadd(t396, t401, vl1);
        t405 = __riscv_vfsub(t397, t400, vl1);
        t406 = __riscv_vfsub(t396, t401, vl1);
        t407 = __riscv_vfadd(t397, t400, vl1);
        t408 = __riscv_vfnmsac(s137, 0.25, t402, vl1);
        t409 = __riscv_vfnmsac(s138, 0.25, t403, vl1);
        s153 = __riscv_vfmacc(t404, 1.6180339887498947, t405, vl1);
        s147 = __riscv_vfmul(s153, 0.29389262614623657, vl1);
        s154 = __riscv_vfnmsac(t405, 1.6180339887498947, t404, vl1);
        s148 = __riscv_vfmul(s154, 0.29389262614623657, vl1);
        s149 = __riscv_vfmul(__riscv_vfsub(t394, t398, vl1), 0.55901699437494745, vl1);
        s150 = __riscv_vfmul(__riscv_vfsub(t395, t399, vl1), 0.55901699437494745, vl1);
        s155 = __riscv_vfnmsac(t407, 0.6180339887498949, t406, vl1);
        s151 = __riscv_vfmul(s155, 0.47552825814757677, vl1);
        s156 = __riscv_vfmacc(t406, 0.6180339887498949, t407, vl1);
        s152 = __riscv_vfmul(s156, 0.47552825814757677, vl1);
        t410 = __riscv_vfadd(t408, s149, vl1);
        t411 = __riscv_vfadd(t409, s150, vl1);
        t412 = __riscv_vfsub(t408, s149, vl1);
        t413 = __riscv_vfsub(t409, s150, vl1);
        t414 = __riscv_vfadd(s147, s151, vl1);
        t415 = __riscv_vfsub(s148, s152, vl1);
        t416 = __riscv_vfsub(s147, s151, vl1);
        t417 = __riscv_vfadd(s148, s152, vl1);
        r86 = __riscv_vset(__riscv_vset(rvvx2_6, 0, __riscv_vfadd(s137, t402, vl1)), 1, __riscv_vfadd(s138, t403, vl1));
        __riscv_vsseg2e64((Y + ((2)*(k1))), r86, vl1);
        r87 = __riscv_vset(__riscv_vset(rvvx2_7, 0, __riscv_vfadd(t410, t414, vl1)), 1, __riscv_vfadd(t411, t415, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + m1)))), r87, vl1);
        r88 = __riscv_vset(__riscv_vset(rvvx2_8, 0, __riscv_vfadd(t412, t417, vl1)), 1, __riscv_vfsub(t413, t416, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((2)*(m1)))))), r88, vl1);
        r89 = __riscv_vset(__riscv_vset(rvvx2_9, 0, __riscv_vfsub(t412, t417, vl1)), 1, __riscv_vfadd(t413, t416, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((3)*(m1)))))), r89, vl1);
        r90 = __riscv_vset(__riscv_vset(rvvx2_10, 0, __riscv_vfsub(t410, t414, vl1)), 1, __riscv_vfsub(t411, t415, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((4)*(m1)))))), r90, vl1);
    }
}
