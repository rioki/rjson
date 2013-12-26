
AC_INIT([rjson], [0.1.0], [https://github.com/rioki/rjson/issues])
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AM_SILENT_RULES([yes])
AM_PROG_AR

AC_LANG([C++])

AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11

LT_INIT([shared static win32-dll])

AC_CHECK_HEADER([rtest.h], :, AC_MSG_ERROR([rtest.h not found!]))
AC_CHECK_LIB([rtest], [main], TEST_LIBS="-lrtest", AC_MSG_ERROR([rtest not found!]))
AC_SUBST(TEST_LIBS)

AC_CHECK_PROG(BISON, [bison], [bison], AC_MSG_WARN([No bison found.]))
AC_SUBST(BISON)
AC_CHECK_PROG(FLEX, [flex], [flex], AC_MSG_WARN([No flex found.]))
AC_SUBST(FLEX)

AC_CONFIG_FILES([Makefile rjson.pc])

AC_OUTPUT