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

PROGRAMS = test1d test1d-out test1dni test2d test2d-out test3d test3d-out rtest1d rtest2d rtest3d
FFTW_PROGRAMS = test1d-fftwint test2d-fftwint test3d-fftwint

all: $(PROGRAMS) $(FFTW_PROGRAMS)

$(PROGRAMS) : % : %.F90 test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS) -o $@

$(FFTW_PROGRAMS) : % : %.F90 test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS) $(FFTWFLAGS) -o $@

test_utils_m.o : test_utils_m.F90
	$(FC) -c $(FCFLAGS) $<

# Runs every example once.
run : all
	./test1d 16 && ./test1d-out 16 && ./test1dni 16 && ./test1d-fftwint 16
	./test2d 8 6 && ./test2d-out 8 6 && ./test2d-fftwint 8 6
	./test3d 4 6 5 && ./test3d-out 4 6 5 && ./test3d-fftwint 4 6 5
	./rtest1d 16 && ./rtest2d 8 6 && ./rtest3d 4 6 5

clean:
	rm -f $(PROGRAMS) $(FFTW_PROGRAMS) *.o *.mod
