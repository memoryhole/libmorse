bin_PROGRAMS = morse
noinst_PROGRAMS = buildtree
lib_LTLIBRARIES = libmorse.la

morse_SOURCES = main.c
morse_LDADD = libmorse.la
morse_LDFLAGS = -static

libmorse_la_SOURCES = morse.c data.c morsetree.c

BUILT_SOURCES = morsetree.c
CLEANFILES = morsetree.c

buildtree_SOURCES = buildtree.c data.c
buildtree_CFLAGS = $(AM_CFLAGS)

morsetree.c : buildtree
	./buildtree morsetree.bin
	xxd -i morsetree.bin > $@
