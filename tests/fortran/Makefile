# --------------------------------------------------------------------------------------------------
# SPDX-FileCopyrightText: juFFTe developers
# SPDX-License-Identifier: Apache-2.0
# --------------------------------------------------------------------------------------------------

FC = gfortran
WITH_REFERENCE_FFTW  ?= 0 
FCFLAGS = -g -O3
# -g -O3 -ftree-vectorize -fopt-info-vec -mavx512f -fopt-info-vec-missed
# -fno-tree-vectorize -fno-openmp-simd  # disable vectorization
LIBDIR ?= ../../src
INCDIR ?= ../../src
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
	FCFLAGS = -g -O3  -qopt-zmm-usage=high -qopenmp -I../..
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

all: juffte_test_f

juffte_test_f : juffte_test.F90
	$(FC) $(FCFLAGS) $< $(LIBFLAGS) $(FFTWFLAGS) -o $@

# Same lengths and cases as CMakeLists.txt (JUFFTE_SIZES_*); see the comment there.
SIZES_1D = 2 9 96 100 120 1024
SIZES_2D = "2 2" "9 96" "20 60" "96 64" "120 100" "256 256"
SIZES_3D = "2 2 2" "9 16 20" "12 18 20" "32 32 32"
T = ./juffte_test_f

# Exit status 77: no reference at this size (N >= 4000 without FFTW), not a failure.
test : juffte_test_f
	set -e; t() { $(T) "$$@" || [ $$? -eq 77 ]; }; for d in fw bw; do \
	    for s in $(SIZES_1D); do t -t complex -d $$d $$s; t -t real -d $$d $$s; \
	        t -t complex -d $$d -a fftw $$s; t -t complex -d $$d -a simple $$s; done; \
	    for s in $(SIZES_2D) $(SIZES_3D); do t -t complex -d $$d $$s; t -t real -d $$d $$s; \
	        t -t complex -d $$d -a fftw $$s; done; \
	done

clean:
	rm -f juffte_test_f *.o *.mod
