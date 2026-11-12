# --------------------------------------------------------------------------------------------------
# SPDX-FileCopyrightText: juFFTe developers
# SPDX-License-Identifier: Apache-2.0
# --------------------------------------------------------------------------------------------------

WITHSPRL ?= 0
WITHSVE  ?= 0
WITHRVV  ?= 0 
LIBS = libjuffte.a


CC ?= gcc 
FC = gfortran
FCFLAGS = -g -O3 
CFLAGS  = -g -O3 
# -fno-tree-vectorize -fno-openmp-simd # disable vectorization
# -mavx512f
FCFLAGS1 = 
OMPFLAGS = -fopenmp 

ifeq ($(WITHSPRL), 1)
	FCFLAGS += -DSPRL
	SPRLPATH = spiral/c
	FILE_EXISTS := $(wildcard spiral/c/dft2c_a.c)

	ifeq ($(WITHSVE), 1)
		SPRLPATH = spiral/sve
		FILE_EXISTS := $(wildcard spiral/sve/dft2sve_a.c)
	endif

	ifeq ($(WITHRVV), 1)
		SPRLPATH = spiral/rvv
		FCFLAGS += -march=rv64gcv
        CFLAGS  += -march=rv64gcv
		FILE_EXISTS := $(wildcard spiral/rvv/dft2rvv_a.c)
	endif

	ifeq ($(wildcard $(FILE_EXISTS)),)
       $(error No spiral file found for architecture)
	endif
endif

# The distributed transforms, built into the library with the MPI compiler wrapper:
# make WITHMPI=1 FC=mpif90.
WITHMPI ?= 0
MPIOBJ =
ifeq ($(WITHMPI), 1)
	FCFLAGS += -DUSE_MPI
	MPIOBJ = pzfft3d_m.o
endif

ifneq (,$(filter $(FC),ifort ifx))
	FCFLAGS += 
# add -xCORE-AVX512 -qopt-zmm-usage=high for AVX-512
	OMPFLAGS = -qopenmp
endif

ifneq (,$(filter flang flang-new,$(notdir $(FC))))
	FCFLAGS += -Wno-ignored-directive
endif

# EPI's LLVM (BSC) vectorises for RVV with -mepi, after which the library needs EPI's
# vector math library from next to the compiler. Upstream flang rejects -mepi, so try a
# compile with it (not for every compiler: ifx only warns about unknown options).
# juffte.mk passes the link flags on to the programs, from their own directories, hence
# the absolute path.
EPI_LIBS =
ifneq (,$(filter flang flang-new,$(notdir $(FC))))
ifeq ($(shell $(FC) -mepi -c -x f95 /dev/null -o /dev/null > /dev/null 2>&1 && echo yes),yes)
ifndef EPI_LIBDIR
	EPI_LIBDIR := $(dir $(realpath $(shell command -v $(FC))))../lib
endif
ifeq (,$(wildcard $(EPI_LIBDIR)/libprovector-vecclonevp.*))
$(error EPI's flang needs libprovector-vecclonevp, which is not in $(EPI_LIBDIR): set EPI_LIBDIR to its directory)
endif
	FCFLAGS += -ffast-math -mepi
	EPI_LIBS = -L $(abspath $(EPI_LIBDIR)) -lprovector-vecclonevp
endif
endif

ifneq (,$(filter $(FC),nvfortran))
	FCFLAGS += 
endif
# -mprefer-vector-width=512
FCFLAGS  += $(OMPFLAGS)  

PREFIX ?= /usr/


OBJ    = utils_m.o param.o factor_m.o plan_m.o kernel_m.o fft235_m.o  zfft1d_m.o zfft2d_m.o zfft3d_m.o dzfft2d_m.o zdfft2d_m.o dzfft3d_m.o zdfft3d_m.o $(MPIOBJ) juffte.o juffte_fftw.o
OBJSP  = utils_m.o param.o factor_m.o plan_m.o kernel_m.o fft235s_m.o zfft1d_m.o zfft2d_m.o zfft3d_m.o dzfft2d_m.o zdfft2d_m.o dzfft3d_m.o zdfft3d_m.o $(MPIOBJ) juffte.o juffte_fftw.o
OBJSPC = $(patsubst %.c, %.o, $(notdir $(wildcard $(SPRLPATH)/*.c)))

all: $(LIBS) juffte.mk

install: all
	mkdir -p $(PREFIX)/lib && mkdir -p $(PREFIX)/include  && cp *.a juffte.mk $(PREFIX)/lib && cp *.mod $(PREFIX)/include && cp *.h $(PREFIX)/include

# Link flags beyond -ljuffte that a program needs, for the Makefiles that link the
# library (include $(LIBDIR)/juffte.mk, then add $(JUFFTE_LIBS)). Written with the
# library, so that a later make or make install without the same FC keeps it.
juffte.mk: $(LIBS)
	echo 'JUFFTE_LIBS = $(EPI_LIBS)' > $@
# One library for every backend; the Spiral build only swaps the object list, and the
# fft235 driver the transforms use.
LIBOBJ = $(OBJ)
FFT235 = fft235_m.o
ifeq ($(WITHSPRL), 1)
LIBOBJ = $(OBJSP) $(OBJSPC)
FFT235 = fft235s_m.o
endif

libjuffte.a: $(LIBOBJ)
	ar rcs $@ $(LIBOBJ)

param.o : param.F90
	$(FC) $(FCFLAGS) -c $<
utils_m.o : utils_m.F90 param.o
	$(FC) $(FCFLAGS) -I. -c $<
factor_m.o : factor_m.F90 param.o
	$(FC) $(FCFLAGS) -I. -c $<
plan_m.o : plan_m.F90 $(FFT235) factor_m.o param.o
	$(FC) $(FCFLAGS) -I. -c $<
kernel_m.o : kernel_m.F90 param.o
	$(FC) $(FCFLAGS) -I. -c $<
fft235_m.o : fft235_m.F90 kernel_m.o factor_m.o
	$(FC) $(FCFLAGS) -I. -c $<
fft235s_m.o : fft235s_m.F90 kernel_m.o factor_m.o
	$(FC) $(FCFLAGS) -I. -c $<
zfft1d_m.o : zfft1d_m.F90 $(FFT235) factor_m.o plan_m.o param.o
	$(FC) $(FCFLAGS) -I. -c $<
zfft2d_m.o : zfft2d_m.F90 $(FFT235) plan_m.o param.o
	$(FC) $(FCFLAGS) -I. -c $<
zfft3d_m.o : zfft3d_m.F90 $(FFT235) plan_m.o param.o
	$(FC) $(FCFLAGS) -I. -c $<
dzfft2d_m.o : dzfft2d_m.F90 $(FFT235) plan_m.o param.o
	$(FC) $(FCFLAGS) -I. -c $<
zdfft2d_m.o : zdfft2d_m.F90 $(FFT235) plan_m.o param.o
	$(FC) $(FCFLAGS) -I. -c $<
dzfft3d_m.o : dzfft3d_m.F90 $(FFT235) plan_m.o param.o
	$(FC) $(FCFLAGS) -I. -c $<
zdfft3d_m.o : zdfft3d_m.F90 $(FFT235) plan_m.o param.o
	$(FC) $(FCFLAGS) -I. -c $<
pzfft3d_m.o : pzfft3d_m.F90 $(FFT235) factor_m.o plan_m.o param.o
	$(FC) $(FCFLAGS) -I. -c $<
juffte.o : juffte.F90 zfft1d_m.o zfft2d_m.o zfft3d_m.o dzfft2d_m.o zdfft2d_m.o dzfft3d_m.o zdfft3d_m.o \
           $(MPIOBJ) plan_m.o factor_m.o utils_m.o param.o
	$(FC) $(FCFLAGS) -I. -c $<
juffte_fftw.o : juffte_fftw.c juffte.h
	$(CC) $(CFLAGS) -c $<

%.o : $(SPRLPATH)/%.c
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -f *.o *.mod *.a juffte.mk

docs:
	@cd .. && $(MAKE) -C docs docs

docs-clean:
	@cd .. && $(MAKE) -C docs docs-clean

.PHONY: docs docs-clean
