# --------------------------------------------------------------------------------------------------
# SPDX-FileCopyrightText: juFFTe developers
# SPDX-License-Identifier: Apache-2.0
# --------------------------------------------------------------------------------------------------

FC = gfortran

FCFLAGS = -g -O3
# -g -O3 -ftree-vectorize -fopt-info-vec -mavx512f -fopt-info-vec-missed
# -fno-tree-vectorize -fno-openmp-simd  # disable vectorization
LIBDIR ?= ../src
INCDIR ?= ../src
WITHFFTW ?= 0
LIBFLAGS = -L $(LIBDIR)  -I $(INCDIR) -ljuffte
ifeq ($(WITHSPRL), 1)
    LIBFLAGS = -L $(LIBDIR) -I $(INCDIR) -ljufftesp
endif
FCFLAGS1 = 
OMPFLAGS = -fopenmp
 
ifeq ($(WITHFFTW), 1)
    FCFLAGS += -DFFTW
	LIBFLAGS += -lfftw3_omp -lfftw3 -I $(FFTWDIR)/include -I $(FFTWDIR)/lib
endif

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
DEP = bench_utils_m.o  

ifeq ($(WITHFFTW), 1)
	DEP += fftw_m.o 
endif


fftbench : $(DEP) fftbench.F90
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS)  -o $@
bench_utils_m.o : bench_utils_m.F90  
	$(FC) $(FCFLAGS) -c  $< 
fftw_m.o : fftw_m.F90
	$(FC) $(FCFLAGS) -I $(FFTWDIR)/include -c  $< 

clean:
	rm -f fftbench *.o *.mod 
