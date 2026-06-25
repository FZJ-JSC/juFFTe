# --------------------------------------------------------------------------------------------------
# SPDX-FileCopyrightText: juFFTe developers
# SPDX-License-Identifier: Apache-2.0
# --------------------------------------------------------------------------------------------------

SUBDIRS := src benchmark ctests tests

PREFIX ?= /usr/local

all:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

install:
	$(MAKE) -C src install PREFIX=$(PREFIX)

test: all
	$(MAKE) -C ctests test
	$(MAKE) -C tests test

clean:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir clean; done

