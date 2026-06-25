// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

/*
*/

#include <stdint.h>
#include <riscv_vector.h>

void dft6c_(double *Y, double *X, int *lp1, int *mp1) {
    int l1, m1;
    vfloat64m1x2_t r100, r101, r102, r103, r104, r105, r106, r107, 
            r108, r97, r98, r99, rvvx2_10, rvvx2_11, rvvx2_12, rvvx2_7, 
            rvvx2_8, rvvx2_9;
    vfloat64m1_t  s205, s206, s207, s208, s209, s210, s211, s212, 
            s213, s214, s215, s216, s217, s218, s219, s220, 
            s221, s222, s223, s224, s225, s226, s227, s228, 
            t494, t495, t496, t497, t498, t499, t500, t501, 
            t502, t503, t504, t505, t506, t507, t508, t509, 
            t510, t511, t512, t513;
    size_t vl1;
    l1 = *(lp1);
    m1 = *(mp1);
    for (size_t k1 = 0; k1 < m1; k1 += vl1) {
        vl1 = __riscv_vsetvl_e64m1(m1 - k1);
        r97 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*(k1))), vl1);
        s205 = __riscv_vget_f64m1(r97, 0);
        s206 = __riscv_vget_f64m1(r97, 1);
        r98 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((l1)*(m1)))))), vl1);
        s207 = __riscv_vget_f64m1(r98, 0);
        s208 = __riscv_vget_f64m1(r98, 1);
        r99 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((2)*(l1)))*(m1)))))), vl1);
        s209 = __riscv_vget_f64m1(r99, 0);
        s210 = __riscv_vget_f64m1(r99, 1);
        r100 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((3)*(l1)))*(m1)))))), vl1);
        s211 = __riscv_vget_f64m1(r100, 0);
        s212 = __riscv_vget_f64m1(r100, 1);
        r101 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((4)*(l1)))*(m1)))))), vl1);
        s213 = __riscv_vget_f64m1(r101, 0);
        s214 = __riscv_vget_f64m1(r101, 1);
        r102 = __riscv_vlseg2e64_v_f64m1x2((X + ((2)*((k1 + ((((5)*(l1)))*(m1)))))), vl1);
        s215 = __riscv_vget_f64m1(r102, 0);
        s216 = __riscv_vget_f64m1(r102, 1);
        t494 = __riscv_vfadd(s209, s213, vl1);
        t495 = __riscv_vfadd(s210, s214, vl1);
        t496 = __riscv_vfadd(s205, t494, vl1);
        t497 = __riscv_vfadd(s206, t495, vl1);
        t498 = __riscv_vfnmsac(s205, 0.5, t494, vl1);
        t499 = __riscv_vfnmsac(s206, 0.5, t495, vl1);
        s217 = __riscv_vfmul(__riscv_vfsub(s210, s214, vl1), 0.8660254037844386, vl1);
        s218 = __riscv_vfmul(__riscv_vfsub(s209, s213, vl1), 0.8660254037844386, vl1);
        t500 = __riscv_vfadd(t498, s217, vl1);
        t501 = __riscv_vfsub(t499, s218, vl1);
        t502 = __riscv_vfsub(t498, s217, vl1);
        t503 = __riscv_vfadd(t499, s218, vl1);
        t504 = __riscv_vfadd(s211, s215, vl1);
        t505 = __riscv_vfadd(s212, s216, vl1);
        t506 = __riscv_vfadd(s207, t504, vl1);
        t507 = __riscv_vfadd(s208, t505, vl1);
        t508 = __riscv_vfnmsac(s207, 0.5, t504, vl1);
        t509 = __riscv_vfnmsac(s208, 0.5, t505, vl1);
        s219 = __riscv_vfmul(__riscv_vfsub(s212, s216, vl1), 0.8660254037844386, vl1);
        s220 = __riscv_vfmul(__riscv_vfsub(s211, s215, vl1), 0.8660254037844386, vl1);
        t510 = __riscv_vfadd(t508, s219, vl1);
        t511 = __riscv_vfsub(t509, s220, vl1);
        t512 = __riscv_vfsub(t508, s219, vl1);
        t513 = __riscv_vfadd(t509, s220, vl1);
        s225 = __riscv_vfmacc(t510, 1.7320508075688772, t511, vl1);
        s221 = __riscv_vfmul(s225, 0.5, vl1);
        s226 = __riscv_vfnmsac(t511, 1.7320508075688772, t510, vl1);
        s222 = __riscv_vfmul(s226, 0.5, vl1);
        s227 = __riscv_vfnmsac(t513, 0.57735026918962584, t512, vl1);
        s223 = __riscv_vfmul(s227, 0.8660254037844386, vl1);
        s228 = __riscv_vfmacc(t512, 0.57735026918962584, t513, vl1);
        s224 = __riscv_vfmul(s228, 0.8660254037844386, vl1);
        r103 = __riscv_vset(__riscv_vset(rvvx2_7, 0, __riscv_vfadd(t496, t506, vl1)), 1, __riscv_vfadd(t497, t507, vl1));
        __riscv_vsseg2e64((Y + ((2)*(k1))), r103, vl1);
        r104 = __riscv_vset(__riscv_vset(rvvx2_8, 0, __riscv_vfadd(t500, s221, vl1)), 1, __riscv_vfadd(t501, s222, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + m1)))), r104, vl1);
        r105 = __riscv_vset(__riscv_vset(rvvx2_9, 0, __riscv_vfadd(t502, s223, vl1)), 1, __riscv_vfsub(t503, s224, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((2)*(m1)))))), r105, vl1);
        r106 = __riscv_vset(__riscv_vset(rvvx2_10, 0, __riscv_vfsub(t496, t506, vl1)), 1, __riscv_vfsub(t497, t507, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((3)*(m1)))))), r106, vl1);
        r107 = __riscv_vset(__riscv_vset(rvvx2_11, 0, __riscv_vfsub(t500, s221, vl1)), 1, __riscv_vfsub(t501, s222, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((4)*(m1)))))), r107, vl1);
        r108 = __riscv_vset(__riscv_vset(rvvx2_12, 0, __riscv_vfsub(t502, s223, vl1)), 1, __riscv_vfadd(t503, s224, vl1));
        __riscv_vsseg2e64((Y + ((2)*((k1 + ((5)*(m1)))))), r108, vl1);
    }
}
