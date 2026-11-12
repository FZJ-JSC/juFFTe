! --------------------------------------------------------------------------------------------------
! SPDX-FileCopyrightText: juFFTe developers
! SPDX-License-Identifier: Apache-2.0
! --------------------------------------------------------------------------------------------------

module param

use, intrinsic :: iso_fortran_env
implicit none

integer, parameter :: MAXNPU = 65536
! The parameter NBLK is a blocking parameter.
integer, parameter :: NBLK = 16
! The parameter NB is a blocking parameter for NVIDIA GPUs.
integer, parameter :: NB = 128
! The parameter NP is a padding parameter to avoid cache conflicts in
! the FFT routines.
integer, parameter :: NP = 8
! Size of L2 cache
integer, parameter :: L2SIZE = 8388608
! Memory Alignment
integer, parameter :: ALN = 64

integer, parameter       :: juffte_fw = -1
integer, parameter       :: juffte_bw = 1
integer, parameter       :: juffte_init = 0
! Undoes one juffte_init: the plan of that shape is freed with the last.
integer, parameter       :: juffte_destroy = 2

! FFTW interface
integer, parameter       :: FFTW_FORWARD    = -1
integer, parameter       :: FFTW_BACKWARD   = 1
! Values taken from fftw3.h so that flags compare and combine identically.
integer, parameter       :: FFTW_MEASURE    = 0
integer, parameter       :: FFTW_EXHAUSTIVE = 8
integer, parameter       :: FFTW_PATIENT    = 32
integer, parameter       :: FFTW_ESTIMATE   = 64

end module param
