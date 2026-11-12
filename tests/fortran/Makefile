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
	LIBFLAGS = -L $(LIBDIR)  -I $(INCDIR) -ljuffte
endif

ifneq (,$(filter $(FC),nvfortran))
	FCFLAGS = -g -O3   
	LIBFLAGS = -L $(LIBDIR)  -I $(INCDIR) -ljuffte 
endif

# Link flags the library needs beyond -ljuffte, such as EPI's vector math library;
# written by src/Makefile next to the library.
-include $(LIBDIR)/juffte.mk
LIBFLAGS += $(JUFFTE_LIBS)
FCFLAGS  += $(OMPFLAGS) 
# -mprefer-vector-width=512

all: juffte_test_f plan_test

juffte_test_f : juffte_test.F90
	$(FC) $(FCFLAGS) $< $(LIBFLAGS) $(FFTWFLAGS) -o $@

plan_test : plan_test.F90
	$(FC) $(FCFLAGS) $< $(LIBFLAGS) -o $@

# Size lists shared with CMakeLists.txt; THOROUGH=1 adds the long ones.
include ../sizes.mk
ifeq ($(THOROUGH), 1)
    SIZES_1D += $(THOROUGH_1D)
    SIZES_2D += $(THOROUGH_2D)
    SIZES_3D += $(THOROUGH_3D)
    SIZES_SIXSTEP += $(THOROUGH_SIXSTEP)
endif
T = ./juffte_test_f

# Exit status 77: no reference at this size (N >= 4000 without FFTW), not a failure.
# fft_init/fft_execute (-a simple) only take 1-D shapes: those without a blank or an x.
test : juffte_test_f plan_test
	set -e; t() { $(T) "$$@" || [ $$? -eq 77 ]; }; for d in fw bw; do \
	    for s in $(SIZES_1D) $(SIZES_2D) $(SIZES_3D) $(SIZES_SIXSTEP); do \
	        for a in native plan; do t -t complex -d $$d -a $$a $$s; t -t real -d $$d -a $$a $$s; done; \
	        t -t complex -d $$d -a fftw $$s; \
	        case "$$s" in *' '*) ;; *) t -t complex -d $$d -a simple $$s;; esac; done; \
	    for s in $(THREADS); do \
	        for a in native plan; do t -t complex -d $$d -a $$a -p $$s; t -t real -d $$d -a $$a -p $$s; done; \
	        t -t complex -d $$d -a fftw -p $$s; \
	        case "$$s" in *' '*) ;; *) t -t complex -d $$d -a simple -p $$s;; esac; done; \
	done; \
	for p in $(PLANS); do set -- $$p; s=$$(echo $$1 | tr x ' '); \
	    for a in native plan; do t -a $$a -o $$2 $$s; t -t real -a $$a -o $$2 $$s; done; \
	    t -a fftw -o $$2 $$s; \
	    case $$1$$2 in *x*) ;; *) t -a simple -o $$2 $$s;; esac; done; \
	MALLOC_PERTURB_=165 ./plan_test; \
	$(T) 14 2>&1 | grep 'length 14 is not a product of 2, 3 and 5'; \
	./plan_test unmade 2>&1 | grep 'zfft1d: plan= holds no plan'; \
	./plan_test other-shape 2>&1 | grep 'zfft1d: plan= holds a zfft1d plan for length 16 in FP64, not a zfft1d plan for length 32'; \
	./plan_test other-transform 2>&1 | grep 'dzfft2d: plan= holds a zfft2d plan for 4 x 4 in FP64, not a dzfft2d plan'; \
	./plan_test too-large 2>&1 | grep 'zfft3d: 2048 x 2048 x 1024 has more than 2147483647 elements'; \
	./plan_test work-too-large 2>&1 | grep 'zfft2d: 2 x 134217728 needs per-thread work arrays of more than'; \
	./plan_test bad-iopt 2>&1 | grep 'zfft1d: iopt is -2; use juffte_init (0), juffte_fw (-1), juffte_bw (1) or juffte_destroy (2)'

# The distributed transforms, against a library built with WITHMPI=1:
#   make mpitest FC=mpif90 [MPIEXEC="mpiexec --oversubscribe"]
MPIEXEC ?= mpiexec
juffte_mpi_test_f : juffte_mpi_test.F90
	$(FC) $(FCFLAGS) $< $(LIBFLAGS) -o $@

mpitest : juffte_mpi_test_f
	set -e; for np in $(MPI_RANKS); do for s in $(MPI_2D) $(MPI_3D); do for d in fw bw; do \
	    OMP_NUM_THREADS=2 $(MPIEXEC) -n $$np ./juffte_mpi_test_f -d $$d $$s; \
	done; done; done; \
	$(MPIEXEC) -n 4 ./juffte_mpi_test_f 12 12 10 2>&1 | grep 'pzfft3d: nx = 12 and nz = 10 on 4 ranks'; \
	$(MPIEXEC) -n 4 ./juffte_mpi_test_f 12 10 2>&1 | grep 'pzfft2d: nx = 12 and ny = 10 on 4 ranks'; \
	$(MPIEXEC) -n 2 ./juffte_mpi_test_f -c 12 12 12 2>&1 | grep 'pzfft3d: plan= was made on another communicator'

clean:
	rm -f juffte_test_f plan_test juffte_mpi_test_f *.o *.mod
