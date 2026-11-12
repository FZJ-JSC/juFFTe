# --------------------------------------------------------------------------------------------------
# SPDX-FileCopyrightText: juFFTe developers
# SPDX-License-Identifier: Apache-2.0
# --------------------------------------------------------------------------------------------------

SUBDIRS := src benchmark tests/c tests/fortran examples/c examples/fortran

PREFIX ?= /usr/local

all:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

install:
	$(MAKE) -C src install PREFIX=$(PREFIX)

test: all
	$(MAKE) -C tests/c test
	$(MAKE) -C tests/fortran test

# The distributed transforms, with the library built by make WITHMPI=1 FC=mpif90.
mpitest:
	$(MAKE) -C tests/fortran mpitest

clean:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done

