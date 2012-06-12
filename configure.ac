#
#  configure.ac
#
#  Copyright (C) 2011-2012 Daniel Sousa  <da.arad@gmail.com>
#  Copyright (C) 2011-2012 Jorge Estrela <jes@isep.ipp.pt>
#
#  Autor:
#    Daniel Sousa <da.arada@gmail.com>
#
#  Orientador:
#    Jorge Estrela <jes@isep.ipp.pt>
#

AC_INIT([Communication Library Simulator], [0.0],
        [da.arada@gmail.com], [comlibsim])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 -Wall no-define])

AC_CONFIG_HEADERS([config.h])
AC_PROG_CXX

PKG_CHECK_MODULES([COMLIBSIM], [gtkmm-3.0 >= 3.0.0 libxml++-2.6 >= 2.10.0])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
