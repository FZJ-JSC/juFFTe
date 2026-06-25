// --------------------------------------------------------------------------------------------------
// SPDX-FileCopyrightText: juFFTe developers
// SPDX-License-Identifier: Apache-2.0
// --------------------------------------------------------------------------------------------------

#include <stddef.h>
#include <complex.h>
#include <riscv_vector.h>

// Now handling both the j and i loops for the complex double arrays
void pack_c(double complex * restrict cy, const double complex * restrict a,
	    int ii, int nx, int nblk, int ny, int ld)
{
	int end_i = (ii + nblk - 1 < nx) ? (ii + nblk - 1) : nx;
    
	// Convert base-1 Fortran 'ii' to base-0 C index
	int ii_c = ii - 1;
	
	size_t vl = 0;
	
	for (int j_c = 0; j_c < ny; ++j_c) {
		for (int i_c = ii_c; i_c < end_i; i_c += vl) {
			vl = __riscv_vsetvl_e64m1(end_i - i_c);
			int k_c = i_c - ii_c;
			
			// cy[k_c * ld + j_c] = a[j_c * nx + i_c];			
			vfloat64m1x2_t a_j = __riscv_vlseg2e64_v_f64m1x2((double *) &a[j_c * nx + i_c], vl);
			__riscv_vssseg2e64((double *) &cy[k_c * ld + j_c], sizeof(double complex) * ld, a_j, vl);
		}
	}
}

void packstr_c(double complex * restrict cy, const double complex * restrict a,
	       int ii, int nx, int nblk, int ny, int ld)
{
	int end_i = (ii + nblk - 1 < nx) ? (ii + nblk - 1) : nx;
    
	// Convert base-1 Fortran 'ii' to base-0 C index
	int ii_c = ii - 1;

	size_t vl = 0;

#pragma GCC unroll 2
	for (int jj_c = 0; jj_c < ny; jj_c += vl) {
		vl = __riscv_vsetvl_e64m2(ny - jj_c);

#pragma GCC unroll 4
		for (int i_c = ii_c; i_c < end_i; i_c++) {
			int k_c = i_c - ii_c;
			
			// cy[k_c * ld + j_c] = a[j_c * nx + i_c];			
			vfloat64m2x2_t a_i = __riscv_vlsseg2e64_v_f64m2x2((double *) &a[jj_c * nx + i_c], sizeof(double complex) * nx, vl);
			__riscv_vsseg2e64((double *) &cy[k_c * ld + jj_c], a_i, vl);
		}
	}
}

void unpack_c(double complex * restrict b, const double complex * restrict cy, 
	      int ii, int nx, int nblk, int ny, int ld) {
    
	int end_i = (ii + nblk - 1 < nx) ? (ii + nblk - 1) : nx;
	
	// Fortran 1-based to C 0-based
	int ii_c = ii - 1;

	size_t vl = 0;

	for (int j_c = 0; j_c < ny; j_c++) {
		for (int i_c = ii_c; i_c < end_i; i_c += vl) {
			vl = __riscv_vsetvl_e64m1(end_i - i_c);
			int k_c = i_c - ii_c;
			
			//b[j_c * nx + i_c] = cy[k_c * ld + j_c];
			vfloat64m1x2_t c_j = __riscv_vlsseg2e64_v_f64m1x2((double *) &cy[k_c * ld + j_c], sizeof(double complex) * ld, vl);
			__riscv_vsseg2e64((double *) &b[j_c * nx + i_c], c_j, vl);
		}
	}
}

void unpackstr_c(double complex * restrict b, const double complex * restrict cy, 
		 int ii, int nx, int nblk, int ny, int ld) {
    
	int end_i = (ii + nblk - 1 < nx) ? (ii + nblk - 1) : nx;
	
	// Fortran 1-based to C 0-based
	int ii_c = ii - 1;

	size_t vl = 0;

#pragma GCC unroll 2
	for (int jj_c = 0; jj_c < ny; jj_c += vl) {
		vl = __riscv_vsetvl_e64m2(ny - jj_c);

#pragma GCC unroll 4
		for (int i_c = ii_c; i_c < end_i; i_c++) {
			int k_c = i_c - ii_c;
			
			//b[j_c * nx + i_c] = cy[k_c * ld + j_c];
			vfloat64m2x2_t c_j = __riscv_vlseg2e64_v_f64m2x2((double *) &cy[k_c * ld + jj_c], vl);
			__riscv_vssseg2e64((double *) &b[jj_c * nx + i_c], sizeof(double complex) * nx, c_j, vl);
		}
	}
}

void cmplx_mul_c(double complex * restrict cx, const double complex * restrict b,
		 const double complex * restrict w, int j, int jj, int nx, int nblk, int ny,
		 int ld)
{
	int j_c = j - 1;
	
	const size_t vl = __riscv_vsetvlmax_e64m1(), BLKX = 4 * vl;
	int end_i = nx - nx % BLKX;

	// cx[i + (j - jj) * ld] = b[i + j_c * nx] * w[i + j_c * nx]
	for (int i = 0; i < end_i; i += BLKX) {
		vfloat64m1x2_t b0, b1, w0, w1, cx0, cx1, b2, w2, cx2, b3, w3, cx3;
		vfloat64m1_t b0_i, b0_r, b1_r, b1_i, w0_i, w0_r, w1_r, w1_i, cx0_i, cx0_r, cx1_r, cx1_i, b2_r, b2_i, w2_r, w2_i, cx2_r, cx2_i, b3_r, b3_i, w3_r, w3_i, cx3_r, cx3_i;

		b0 = __riscv_vlseg2e64_v_f64m1x2((double *) &b[i + j_c * nx], vl);
		b0_r = __riscv_vget_f64m1(b0, 0);
		b0_i = __riscv_vget_f64m1(b0, 1);
		w0 = __riscv_vlseg2e64_v_f64m1x2((double *) &w[i + j_c * nx], vl);
		w0_r = __riscv_vget_f64m1(w0, 0);
		w0_i = __riscv_vget_f64m1(w0, 1);
		b1 = __riscv_vlseg2e64_v_f64m1x2((double *) &b[i + vl + j_c * nx], vl);
		b1_r = __riscv_vget_f64m1(b1, 0);
		b1_i = __riscv_vget_f64m1(b1, 1);
		w1 = __riscv_vlseg2e64_v_f64m1x2((double *) &w[i + vl + j_c * nx], vl);
		w1_r = __riscv_vget_f64m1(w1, 0);
		w1_i = __riscv_vget_f64m1(w1, 1);
		b2 = __riscv_vlseg2e64_v_f64m1x2((double *) &b[i + 2 * vl + j_c * nx], vl);
		b2_r = __riscv_vget_f64m1(b2, 0);
		b2_i = __riscv_vget_f64m1(b2, 1);
		w2 = __riscv_vlseg2e64_v_f64m1x2((double *) &w[i + 2 * vl + j_c * nx], vl);
		w2_r = __riscv_vget_f64m1(w2, 0);
		w2_i = __riscv_vget_f64m1(w2, 1);
		b3 = __riscv_vlseg2e64_v_f64m1x2((double *) &b[i + 3 * vl + j_c * nx], vl);
		b3_r = __riscv_vget_f64m1(b3, 0);
		b3_i = __riscv_vget_f64m1(b3, 1);
		w3 = __riscv_vlseg2e64_v_f64m1x2((double *) &w[i + 3 * vl + j_c * nx], vl);
		w3_r = __riscv_vget_f64m1(w3, 0);
		w3_i = __riscv_vget_f64m1(w3, 1);

		cx0_r = __riscv_vfmul(b0_r, w0_r, vl);
		cx0_i = __riscv_vfmul(b0_i, w0_r, vl);
		cx1_r = __riscv_vfmul(b1_r, w1_r, vl);
		cx1_i = __riscv_vfmul(b1_i, w1_r, vl);
 		cx2_r = __riscv_vfmul(b2_r, w2_r, vl);
		cx2_i = __riscv_vfmul(b2_i, w2_r, vl);
 		cx3_r = __riscv_vfmul(b3_r, w3_r, vl);
		cx3_i = __riscv_vfmul(b3_i, w3_r, vl);
		cx0_r = __riscv_vfnmsac(cx0_r, b0_i, w0_i, vl);
		cx0_i = __riscv_vfmacc(cx0_i, b0_r, w0_i, vl);
		cx1_r = __riscv_vfnmsac(cx1_r, b1_i, w1_i, vl);
		cx1_i = __riscv_vfmacc(cx1_i, b1_r, w1_i, vl);
		cx2_r = __riscv_vfnmsac(cx2_r, b2_i, w2_i, vl);
		cx2_i = __riscv_vfmacc(cx2_i, b2_r, w2_i, vl);
		cx3_r = __riscv_vfnmsac(cx3_r, b3_i, w3_i, vl);
		cx3_i = __riscv_vfmacc(cx3_i, b3_r, w3_i, vl);

		cx0 = __riscv_vset(cx0, 0, cx0_r);
		cx0 = __riscv_vset(cx0, 1, cx0_i);
		__riscv_vsseg2e64((double *) &cx[i + (j - jj) * ld], cx0, vl);
		cx1 = __riscv_vset(cx1, 0, cx1_r);
		cx1 = __riscv_vset(cx1, 1, cx1_i);
		__riscv_vsseg2e64((double *) &cx[i + vl + (j - jj) * ld], cx1, vl);
		cx2 = __riscv_vset(cx2, 0, cx2_r);
		cx2 = __riscv_vset(cx2, 1, cx2_i);
		__riscv_vsseg2e64((double *) &cx[i + 2 * vl + (j - jj) * ld], cx2, vl);
		cx3 = __riscv_vset(cx3, 0, cx3_r);
		cx3 = __riscv_vset(cx3, 1, cx3_i);
		__riscv_vsseg2e64((double *) &cx[i + 3 * vl + (j - jj) * ld], cx3, vl);
	}

	// Manual tail loop
	for (int i = end_i; i < nx; i += vl) {
		size_t vl_tail = __riscv_vsetvl_e64m1(nx - i);
		
		vfloat64m1x2_t b0, w0, cx0;
		vfloat64m1_t b0_i, b0_r, w0_i, w0_r, cx0_i, cx0_r;

		b0 = __riscv_vlseg2e64_v_f64m1x2((double *) &b[i + j_c * nx], vl_tail);
		b0_r = __riscv_vget_f64m1(b0, 0);
		b0_i = __riscv_vget_f64m1(b0, 1);
		w0 = __riscv_vlseg2e64_v_f64m1x2((double *) &w[i + j_c * nx], vl_tail);
		w0_r = __riscv_vget_f64m1(w0, 0);
		w0_i = __riscv_vget_f64m1(w0, 1);

		cx0_r = __riscv_vfmul(b0_r, w0_r, vl_tail);
		cx0_i = __riscv_vfmul(b0_i, w0_r, vl_tail);
		cx0_r = __riscv_vfnmsac(cx0_r, b0_i, w0_i, vl_tail);
		cx0_i = __riscv_vfmacc(cx0_i, b0_r, w0_i, vl_tail);

		cx0 = __riscv_vset(cx0, 0, cx0_r);
		cx0 = __riscv_vset(cx0, 1, cx0_i);
		__riscv_vsseg2e64((double *) &cx[i + (j - jj) * ld], cx0, vl_tail);
	}
}

