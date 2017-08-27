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

BUILT_SOURCES = src/morsetree.c morse.h
CLEANFILES = src/morsetree.c morsetree.bin morse.h src/morse.h.raw

buildtree_SOURCES = src/buildtree.c src/data.c
buildtree_CFLAGS = $(AM_CFLAGS)

#
# TEST
#
check_PROGRAMS = morse_test morse_test_single_header
TESTS = morse_test morse_test_single_header

morse_test_SOURCES = test/morse.c
morse_test_LDADD = libmorse.la
morse_test_CFLAGS =  -I$(top_srcdir)/src
morse_test_LDFLAGS = -lmorse -lcmocka -static

morse_test_single_header_SOURCES = test/morse.c morse.h
morse_test_single_header_CFLAGS =  -I$(top_srcdir)
morse_test_single_header_LDFLAGS = -lcmocka


EXTRA_DIST = README.md

src/morse.h.raw: src/morsetree.c
	cat src/morsetree.c src/data.h src/data.c src/morse_parser.h src/morse.h src/morse.c > src/morse.h.raw
	- unifdef -UDATA_H -UMORSE_H -DSINGLE_HEADER -o $@ $@

morse.h: src/morse.h.raw src/morse_h.m4
	m4 -Isrc src/morse_h.m4 > morse.h

src/morsetree.c: buildtree
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
