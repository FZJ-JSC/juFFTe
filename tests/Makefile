# --------------------------------------------------------------------------------------------------
# SPDX-FileCopyrightText: juFFTe developers
# SPDX-License-Identifier: Apache-2.0
# --------------------------------------------------------------------------------------------------

FC = gfortran
WITH_REFERENCE_FFTW  ?= 0 
FCFLAGS = -g -O3
# -g -O3 -ftree-vectorize -fopt-info-vec -mavx512f -fopt-info-vec-missed
# -fno-tree-vectorize -fno-openmp-simd  # disable vectorization
LIBDIR ?= ../src
INCDIR ?= ../src
LIBFLAGS = -L $(LIBDIR)  -I $(INCDIR) -ljuffte

ifeq ($(WITHSPRL), 1)
    LIBFLAGS = -L $(LIBDIR) -I $(INCDIR) -ljuffte
endif
ifeq ($(WITH_REFERENCE_FFTW), 1)
	FFTWINC ?= /usr/include
	FFTWFLAGS = -I $(FFTWINC) -lfftw3 -DUSE_REFERENCE_FFTW
endif

OMPFLAGS = -fopenmp
 

ifneq (,$(filter $(FC),ifort ifx))
	FCFLAGS = -g -O3  -qopt-zmm-usage=high -qopenmp -I..
# -xCORE-AVX512  
endif

ifneq (,$(filter $(FC),flang flang-new))
	FCFLAGS = -g -O3 -Wno-ignored-directive   
	LIBFLAGS = -L $(LIBDIR)  -I $(INCDIR) -ljuffte -ffast-math -mepi -L/apps/riscv/llvm/EPI/development/lib -lprovector-vecclonevp
endif

ifneq (,$(filter $(FC),nvfortran))
	FCFLAGS = -g -O3   
	LIBFLAGS = -L $(LIBDIR)  -I $(INCDIR) -ljuffte 
endif

FCFLAGS  += $(OMPFLAGS) 
# -mprefer-vector-width=512

all: test1d-fftwint test2d-fftwint test3d-fftwint test1d-out test1d test1dni test2d test2d-out test3d test3d-out rtest1d rtest2d rtest3d accuracy

test1d-fftwint : test1d-fftwint.F90  test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS) $(FFTWFLAGS)  -o $@

test2d-fftwint : test2d-fftwint.F90  test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS) $(FFTWFLAGS)  -o $@

test3d-fftwint : test3d-fftwint.F90  test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS) $(FFTWFLAGS)  -o $@

test1d-out : test1d-out.F90 test_utils_m.o 
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS)  -o $@

test1dni : test1dni.F90 test_utils_m.o 
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS)  -o $@

test1d : test1d.F90  test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS)  -o $@

test2d : test2d.F90 test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS) -o $@

test2d-out : test2d-out.F90 test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS) -o $@

test3d : test3d.F90 test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS) -o $@

test3d-out : test3d-out.F90 test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS) -o $@

rtest1d : rtest1d.F90 test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS) -o $@

rtest2d : rtest2d.F90 test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS) -o $@

rtest3d : rtest3d.F90 test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS) -o $@

accuracy : accuracy.F90
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS) -o $@

test_utils_m.o : test_utils_m.F90 
	$(FC) -c $(FCFLAGS) $(FCFLAGS1) $< 

# Same lengths as CMakeLists.txt (JUFFTE_SIZES_*); see the comment there.
SIZES_1D = 2 9 96 100 120 1024
SIZES_2D = "2 2" "9 96" "96 64" "120 100" "256 256"
SIZES_3D = "2 2 2" "9 16 20" "12 18 20" "32 32 32"

test  :   test1d test1d-out test1dni test1d-fftwint test2d test2d-out test2d-fftwint test3d test3d-out test3d-fftwint rtest1d rtest2d rtest3d accuracy
	for t in test1d test1d-out test1dni test1d-fftwint rtest1d; do for s in $(SIZES_1D); do ./$$t $$s || exit 1; done; done
	for t in test2d test2d-out test2d-fftwint rtest2d; do for s in $(SIZES_2D); do ./$$t $$s || exit 1; done; done
	for t in test3d test3d-out test3d-fftwint rtest3d; do for s in $(SIZES_3D); do ./$$t $$s || exit 1; done; done
	for s in $(SIZES_1D) $(SIZES_2D) $(SIZES_3D); do ./accuracy $$s || exit 1; done

clean:
	rm -f accuracy test1d test1d-out test2d-out test3d-out test1d-fftwint test2d-fftwint test3d-fftwint test1dni test2d test3d rtest1d rtest2d rtest3d *.o *.mod 
