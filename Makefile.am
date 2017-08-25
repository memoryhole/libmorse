#
# BUILD
#
bin_PROGRAMS = morse
noinst_PROGRAMS = buildtree
lib_LTLIBRARIES = libmorse.la

morse_SOURCES = src/main.c
morse_LDADD = libmorse.la
morse_LDFLAGS = -static

libmorse_la_SOURCES = src/morse.c src/data.c src/morsetree.c

BUILT_SOURCES = src/morsetree.c
CLEANFILES = src/morsetree.c morsetree.bin

buildtree_SOURCES = src/buildtree.c src/data.c
buildtree_CFLAGS = $(AM_CFLAGS)

#
# TEST
#
check_PROGRAMS = morse_test
TESTS = morse_test

morse_test_SOURCES = test/morse.c
morse_test_LDADD = libmorse.la
morse_test_CFLAGS =  -I$(top_srcdir)/src --coverage
morse_test_LDFLAGS = -lmorse -lcmocka -static


EXTRA_DIST = README.md

src/morsetree.c : buildtree
	./buildtree morsetree.bin
	xxd -i morsetree.bin > $@

maintainer-clean-local:
	rm -rf aclocal.m4 \
		configure \
		Makefile.in \
		autotools \
		m4 \
		config.h.in* \
		autom4te.cache
