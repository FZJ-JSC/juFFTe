# --------------------------------------------------------------------------------------------------
# SPDX-FileCopyrightText: juFFTe developers
# SPDX-License-Identifier: Apache-2.0
# --------------------------------------------------------------------------------------------------

CC ?= gcc
CFLAGS = -g -O3
WITH_REFERENCE_FFTW  ?= 0
# -g -O3 -ftree-vectorize -fopt-info-vec -mavx512f -fopt-info-vec-missed
# -fno-tree-vectorize -fno-openmp-simd  # disable vectorization
LIBDIR ?= ../../src
INCDIR ?= ../../src
LIBFLAGS = -L $(LIBDIR)  -I $(INCDIR) -ljuffte -lm -lgfortran
LIBFLAGSSP = -L $(LIBDIR) -I $(INCDIR) -ljuffte -lm -lgfortran

CFLAGS1 = 
OMPFLAGS = -fopenmp -fopenmp-simd
 
ifeq ($(WITH_REFERENCE_FFTW), 1)
	FFTWINC ?= /usr/include
	FFTWLIB ?= /usr/lib
	FFTWFLAGS = -I $(FFTWINC) -L $(FFTWLIB) -lfftw3 -DUSE_REFERENCE_FFTW
endif

ifneq (,$(filter $(CC),icx icx-cc))
	CFLAGS = -g -O3 -qopt-zmm-usage=high -I../..
#-xCORE-AVX512
	LIBFLAGS = -L $(LIBDIR)  -I $(INCDIR) -ljuffte -lifcore -lifport 
	OMPFLAGS = -qopenmp
endif

ifneq (,$(filter $(CC),clang clang-22))
	CFLAGS = -g -O3 -ffast-math -mepi 
	LIBFLAGS = -L $(LIBDIR)  -I $(INCDIR) -ljuffte  -L/apps/riscv/llvm/EPI/development/lib -lprovector-vecclonevp  -lm -lflang_rt.runtime
	OMPFLAGS = -fopenmp
endif

ifneq (,$(filter $(CC),nvc nvcc))
	CFLAGS = -g -O3 
#-mavx512f
	LIBFLAGS = -L $(LIBDIR)  -I $(INCDIR) -ljuffte -lm -fortranlibs
	OMPFLAGS = -fopenmp
endif

# -mprefer-vector-width=512
CFLAGS  += $(OMPFLAGS) 
all: test1d test2d test3d rtest1d rtest2d rtest3d fftw-test fftw-test2d fftw-test3d

test1d test2d test3d rtest1d rtest2d rtest3d : % : %.c test_utils.h
	$(CC) $(CFLAGS) $< $(LIBFLAGS) -o $@

fftw-test fftw-test2d fftw-test3d : % : %.c
	$(CC) $(CFLAGS) $< $(LIBFLAGS) $(FFTWFLAGS) -o $@

# Runs every example once.
run : all
	./test1d 16 && ./test2d 8 6 && ./test3d 4 6 5
	./rtest1d 16 && ./rtest2d 8 6 && ./rtest3d 4 6 5
	./fftw-test 8 && ./fftw-test2d 4 6 && ./fftw-test3d 2 3 4

clean:
	rm -f test1d test2d test3d rtest1d rtest2d rtest3d fftw-test fftw-test2d fftw-test3d *.o
