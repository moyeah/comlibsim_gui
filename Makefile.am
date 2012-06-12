#
#  Makefile.am
#
#  Copyright (C) 2011-2012 Daniel Sousa  <da.arada@gmail.com>
#  Copyright (C) 2011-2012 Jorge Estrela <jes@isep.ipp.pt>
#
#  Autor:
#    Daniel Sousa <da.arada@gmail.com>
#
#  Orientador:
#    Jorge Estrela <jes@isep.ipp.pt>
#

AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
AM_CPPFLAGS = $(COMLIBSIM_CFLAGS)

bin_PROGRAMS = comlibsim
comlibsim_SOURCES = src/main.cpp \
                    src/modelcolumns.h \
                    src/mainwindow.h src/mainwindow.cpp \
                    src/sensorsmap.h src/sensorsmap.cpp \
                    src/sensorsettings.h \
                    src/clustersettings.h src/clustersettings.cpp \
                    src/sensor.h src/sensor.cpp

comlibsim_LDADD = $(COMLIBSIM_LIBS)

# TODO
# dist_noinst_SCRIPTS = autogen.sh
