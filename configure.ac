#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libmorse], [1.0])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([autotools])

AC_CHECK_PROG(XXD,[xxd],[xxd],[no])
AC_CHECK_PROG(UNIFDEF,[unifdef],[unifdef],[no])
test "$XXD" == "no" && AC_MSG_ERROR([Required program 'xxd' not found.])
test "$UNIFDEF" == "no" && AC_MSG_ERROR([Required program 'unifdef' not found.])

CFLAGS=${CFLAGS="--std=c99 -O3 -Wall -Wextra -Werror -Wpedantic"} 

AM_INIT_AUTOMAKE([subdir-objects serial-tests foreign -Wall -Werror])
AM_PROG_AR

LT_INIT

AC_CONFIG_SRCDIR([src/morse.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC_C99

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
