#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([morse], [1.0])

AC_CHECK_PROG(XXD,[xxd],[xxd],[no])
test "$XXD" == "no" && AC_MSG_ERROR([Required program 'xxd' not found.])

CFLAGS=${CFLAGS="-O3 -Wall -Wextra -Werror"} 

AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE
LT_INIT

AC_CONFIG_SRCDIR([src/morse.h])
AC_CONFIG_HEADERS([config.h])
# Checks for programs.
AC_PROG_CC
AC_PROG_CC_STDC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
