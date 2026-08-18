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
LIBFLAGS = -L $(LIBDIR)  -I $(INCDIR) -ljuffte

ifeq ($(WITHSPRL), 1)
    LIBFLAGS = -L $(LIBDIR) -I $(INCDIR) -ljufftesp
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

all: test1d-fftwint test1d-out test1d test1dni test2d test2d-out test3d test3d-out rtest1d rtest2d rtest3d 

test1d-fftwint : test1d-fftwint.F90  test_utils_m.o
	$(FC) $(FCFLAGS) $^ $(LIBFLAGS)  -o $@

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

test_utils_m.o : test_utils_m.F90 
	$(FC) -c $(FCFLAGS) $(FCFLAGS1) $< 

test  :   test1d test1d-out test1dni test1d-fftwint test2d test3d rtest1d rtest2d rtest3d
	./test1d 2 && ./test1d-out 2 && ./test1dni 2 &&  ./test2d 2 2  && ./test3d 2 2 2 && ./rtest1d 2 &&./rtest2d 2 2 && ./rtest3d 2 2 2 && ./test1d-fftwint 2

clean:
	rm -f test1d test1d-out test2d-out test3d-out test1d-fftwint test1dni test2d test3d rtest1d rtest2d rtest3d *.o *.mod 
