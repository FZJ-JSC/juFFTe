# --------------------------------------------------------------------------------------------------
# SPDX-FileCopyrightText: juFFTe developers
# SPDX-License-Identifier: Apache-2.0
# --------------------------------------------------------------------------------------------------

WITHSPRL ?= 0
WITHSVE  ?= 0
WITHRVV  ?= 0 
LIBS = libjuffte.a


CC ?= gcc 
FC ?= gfortran
FCFLAGS = -g -O3 
CFLAGS  = -g -O3 
# -fno-tree-vectorize -fno-openmp-simd # disable vectorization
# -mavx512f
FCFLAGS1 = 
OMPFLAGS = -fopenmp 

ifeq ($(WITHSPRL), 1)
	FCFLAGS += -DSPRL
	SPRLPATH = spiral/c
	LIBS = libjufftesp.a
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

ifneq (,$(filter $(FC),ifort ifx))
	FCFLAGS += 
# add -xCORE-AVX512 -qopt-zmm-usage=high for AVX-512
	OMPFLAGS = -qopenmp
endif

ifneq (,$(filter $(FC),flang flang-new))
	FCFLAGS += -Wno-ignored-directive  -ffast-math -mepi 
endif

ifneq (,$(filter $(FC),nvfortran))
	FCFLAGS += 
endif
# -mprefer-vector-width=512
FCFLAGS  += $(OMPFLAGS)  

PREFIX ?= /usr/


OBJ    = utils_m.o param.o factor_m.o kernel_m.o fft235_m.o  zfft1d_m.o zfft2d_m.o zfft3d_m.o dzfft2d_m.o zdfft2d_m.o dzfft3d_m.o zdfft3d_m.o juffte.o
OBJSP  = utils_m.o param.o factor_m.o kernel_m.o fft235s_m.o zfft1d_m.o zfft2d_m.o zfft3d_m.o dzfft2d_m.o zdfft2d_m.o dzfft3d_m.o zdfft3d_m.o juffte.o
OBJSPC = $(patsubst %.c, %.o, $(notdir $(wildcard $(SPRLPATH)/*.c)))

all: $(LIBS)

install: all
	mkdir -p $(PREFIX)/lib && mkdir -p $(PREFIX)/include  && cp *.a $(PREFIX)/lib && cp *.mod $(PREFIX)/include && cp *.h $(PREFIX)/include
libjuffte.a: $(OBJ)
	ar rcs $@ $(OBJ)
libjufftesp.a: $(OBJSP) $(OBJSPC)
	ar rcs $@ $(OBJSP) $(OBJSPC)

param.o : param.F90
	$(FC) $(FCFLAGS) -c $<
utils_m.o : utils_m.F90 param.o
	$(FC) $(FCFLAGS) -I. -c $<
factor_m.o : factor_m.F90 param.o
	$(FC) $(FCFLAGS) -I. -c $<
kernel_m.o : kernel_m.F90 param.o
	$(FC) $(FCFLAGS) -I. -c $<
fft235_m.o : fft235_m.F90 kernel_m.o factor_m.o
	$(FC) $(FCFLAGS) -I. -c $<
fft235s_m.o : fft235s_m.F90 kernel_m.o factor_m.o
	$(FC) $(FCFLAGS) -I. -c $<
zfft1d_m.o : zfft1d_m.F90 fft235_m.o factor_m.o param.o
	$(FC) $(FCFLAGS) -I. -c $<
zfft2d_m.o : zfft2d_m.F90 zfft1d_m.o factor_m.o
	$(FC) $(FCFLAGS) -I. -c $<
zfft3d_m.o : zfft3d_m.F90 zfft2d_m.o zfft1d_m.o
	$(FC) $(FCFLAGS) -I. -c $<
dzfft2d_m.o : dzfft2d_m.F90 fft235_m.o zfft1d_m.o factor_m.o
	$(FC) $(FCFLAGS) -I. -c $<
zdfft2d_m.o : zdfft2d_m.F90 fft235_m.o zfft1d_m.o factor_m.o
	$(FC) $(FCFLAGS) -I. -c $<
dzfft3d_m.o : dzfft3d_m.F90 dzfft2d_m.o zfft1d_m.o
	$(FC) $(FCFLAGS) -I. -c $<
zdfft3d_m.o : zdfft3d_m.F90 zdfft2d_m.o zfft1d_m.o
	$(FC) $(FCFLAGS) -I. -c $<
juffte.o : juffte.F90 zfft1d_m.o zfft2d_m.o zfft3d_m.o dzfft2d_m.o zdfft2d_m.o dzfft3d_m.o zdfft3d_m.o utils_m.o
	$(FC) $(FCFLAGS) -I. -c $<
%.o : $(SPRLPATH)/%.c
	$(CC) $(CFLAGS) -c $< 

clean:
	rm -f *.o *.mod *.a 

docs:
	@cd .. && $(MAKE) -C docs docs

docs-clean:
	@cd .. && $(MAKE) -C docs docs-clean

.PHONY: docs docs-clean
