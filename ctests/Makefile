# --------------------------------------------------------------------------------------------------
# SPDX-FileCopyrightText: juFFTe developers
# SPDX-License-Identifier: Apache-2.0
# --------------------------------------------------------------------------------------------------

CC ?= gcc
CFLAGS = -g -O3
WITHFFTW  ?= 0
# -g -O3 -ftree-vectorize -fopt-info-vec -mavx512f -fopt-info-vec-missed
# -fno-tree-vectorize -fno-openmp-simd  # disable vectorization
LIBDIR ?= ../src
INCDIR ?= ../src
LIBFLAGS = -L $(LIBDIR)  -I $(INCDIR) -ljuffte -lm -lgfortran
LIBFLAGSSP = -L $(LIBDIR) -I $(INCDIR) -ljufftesp -lm -lgfortran

CFLAGS1 = 
OMPFLAGS = -fopenmp -fopenmp-simd
 
ifeq ($(WITHFFTW), 1)
	FFTWINC ?= /usr/include
	FFTWLIB ?= /usr/lib
	FFTWFLAGS = -I $(FFTWINC) -L $(FFTWLIB) -lfftw3 -DWITHFFTW
	LIBFLAGS = $(FFTWINC FFTWLIB) $(FFTWFLAGS)
endif

ifneq (,$(filter $(CC),icx icx-cc))
	CFLAGS = -g -O3 -qopt-zmm-usage=high -I..
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

test1d : test1d.c  
	$(CC) $(CFLAGS) $< $(LIBFLAGS)  -o $@

test2d : test2d.c 
	$(CC) $(CFLAGS) $< $(LIBFLAGS) -o $@

test3d : test3d.c 
	$(CC) $(CFLAGS) $< $(LIBFLAGS) -o $@

rtest1d : rtest1d.c 
	$(CC) $(CFLAGS) $< $(LIBFLAGS) -o $@

rtest2d : rtest2d.c 
	$(CC) $(CFLAGS) $< $(LIBFLAGS) -o $@

rtest3d : rtest3d.c 
	$(CC) $(CFLAGS) $< $(LIBFLAGS) -o $@

fftw-test : fftw-test.c
	$(CC) $(CFLAGS) -DFFTW $< $(LIBFLAGS) -o $@

fftw-test2d : fftw-test2d.c
	$(CC) $(CFLAGS) -DFFTW $< $(LIBFLAGS) -o $@

fftw-test3d : fftw-test3d.c
	$(CC) $(CFLAGS) -DFFTW $< $(LIBFLAGS) -o $@

test  :   test1d test2d test3d rtest1d rtest2d rtest3d fftw-test fftw-test2d fftw-test3d
	./test1d 2 && ./test2d 2 2 && ./test3d 2 2 2 && ./rtest1d 2 && ./rtest2d 2 2 && ./rtest3d 2 2 2 && ./fftw-test 2 && ./fftw-test2d 2 2 && ./fftw-test3d 2 2 2

clean:
	rm -f test1d test1dni test2d test3d rtest1d rtest2d rtest3d fftw-test fftw-test2d fftw-test3d *.o *.mod 
