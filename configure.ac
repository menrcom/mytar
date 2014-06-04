#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT([mytar], [0.1], [StFedorov.gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_ARG_ENABLE([debug],
		[AS_HELP_STRING([--enable-debug],
				[Enable debug symbols and output])],
		[AC_DEFINE([DEBUG],[1],[Enable debugging])],[])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
#PKG_CHECK_MODULES([LIBCONFIG], [libconfig >= 1.4],,
#AC_MSG_ERROR([libconfig 1.4 or newer not found.])
#)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
