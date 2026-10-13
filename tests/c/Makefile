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
all: juffte_test_c

juffte_test_c : juffte_test.c
	$(CC) $(CFLAGS) $< $(LIBFLAGS) $(FFTWFLAGS) -o $@

# Size lists shared with CMakeLists.txt; THOROUGH=1 adds the long ones.
include ../sizes.mk
ifeq ($(THOROUGH), 1)
    SIZES_1D += $(THOROUGH_1D)
    SIZES_2D += $(THOROUGH_2D)
    SIZES_3D += $(THOROUGH_3D)
    SIZES_SIXSTEP += $(THOROUGH_SIXSTEP)
endif
T = ./juffte_test_c

# Exit status 77: no reference at this size (N >= 4000 without FFTW), not a failure.
test : juffte_test_c
	set -e; t() { $(T) "$$@" || [ $$? -eq 77 ]; }; for d in fw bw; do \
	    for s in $(SIZES_1D); do t -t complex -d $$d $$s; t -t real -d $$d $$s; \
	        t -t complex -d $$d -a fftw $$s; done; \
	    for s in $(SIZES_2D) $(SIZES_3D); do t -t complex -d $$d $$s; t -t real -d $$d $$s; \
	        t -t complex -d $$d -a fftw $$s; done; \
	    for s in $(SIZES_SIXSTEP); do t -t complex -d $$d $$s; t -t complex -d $$d -a fftw $$s; \
	        done; \
	done; \
	$(T) 14 2>&1 | grep 'length 14 is not a product of 2, 3 and 5'

clean:
	rm -f juffte_test_c *.o
