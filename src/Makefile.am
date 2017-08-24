bin_PROGRAMS = morse
noinst_PROGRAMS = buildtree
lib_LTLIBRARIES = libmorse.la

morse_SOURCES = main.c
morse_LDADD = libmorse.la
morse_LDFLAGS = -static

libmorse_la_SOURCES = morse.c data.c

BUILT_SOURCES = morsetree.bin
CLEANFILES = morsetree.bin

buildtree_SOURCES = buildtree.c
buildtree_LDADD = libmorse.la
buildtree_LDFLAGS = -static

morsetree.bin : buildtree
	./buildtree morsetree.bin
