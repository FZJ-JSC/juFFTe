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

clean:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done

