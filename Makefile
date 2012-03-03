# Makefile.in generated by automake 1.11.1 from Makefile.am.
# Makefile.  Generated from Makefile.in by configure.

# Copyright (C) 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002,
# 2003, 2004, 2005, 2006, 2007, 2008, 2009  Free Software Foundation,
# Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.





pkgdatadir = $(datadir)/SampleApp
pkgincludedir = $(includedir)/SampleApp
pkglibdir = $(libdir)/SampleApp
pkglibexecdir = $(libexecdir)/SampleApp
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_triplet = x86_64-unknown-linux-gnu
host_triplet = x86_64-unknown-linux-gnu
bin_PROGRAMS = Project1$(EXEEXT)
subdir = .
DIST_COMMON = README $(am__configure_deps) $(noinst_HEADERS) \
	$(srcdir)/Makefile.am $(srcdir)/Makefile.in \
	$(srcdir)/config.h.in $(top_srcdir)/configure config.guess \
	config.sub depcomp install-sh ltmain.sh missing
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/configure.ac
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
am__CONFIG_DISTCLEAN_FILES = config.status config.cache config.log \
 configure.lineno config.status.lineno
mkinstalldirs = $(install_sh) -d
CONFIG_HEADER = config.h
CONFIG_CLEAN_FILES =
CONFIG_CLEAN_VPATH_FILES =
am__installdirs = "$(DESTDIR)$(bindir)"
PROGRAMS = $(bin_PROGRAMS)
am_Project1_OBJECTS = Project1-Controller.$(OBJEXT) \
	Project1-WorldObjects.$(OBJEXT) Project1-Physics.$(OBJEXT) \
	Project1-OgreDemo.$(OBJEXT) Project1-OgreFramework.$(OBJEXT) \
	Project1-main.$(OBJEXT)
Project1_OBJECTS = $(am_Project1_OBJECTS)
am__DEPENDENCIES_1 =
Project1_DEPENDENCIES = $(am__DEPENDENCIES_1) $(am__DEPENDENCIES_1) \
	$(am__DEPENDENCIES_1) $(am__DEPENDENCIES_1)
Project1_LINK = $(LIBTOOL) --tag=CXX $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CXXLD) $(Project1_CXXFLAGS) \
	$(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
DEFAULT_INCLUDES = -I.
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__depfiles_maybe = depfiles
am__mv = mv -f
CXXCOMPILE = $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)
LTCXXCOMPILE = $(LIBTOOL) --tag=CXX $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
	--mode=compile $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)
CXXLD = $(CXX)
CXXLINK = $(LIBTOOL) --tag=CXX $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) \
	--mode=link $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) \
	$(LDFLAGS) -o $@
SOURCES = $(Project1_SOURCES)
DIST_SOURCES = $(Project1_SOURCES)
HEADERS = $(noinst_HEADERS)
ETAGS = etags
CTAGS = ctags
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
distdir = $(PACKAGE)-$(VERSION)
top_distdir = $(distdir)
am__remove_distdir = \
  { test ! -d "$(distdir)" \
    || { find "$(distdir)" -type d ! -perm -200 -exec chmod u+w {} ';' \
         && rm -fr "$(distdir)"; }; }
DIST_ARCHIVES = $(distdir).tar.gz
GZIP_ENV = --best
distuninstallcheck_listfiles = find . -type f -print
distcleancheck_listfiles = find . -type f -print
ACLOCAL = ${SHELL} /v/filer4b/v38q001/ruoyi/GameTech/Assignment-2/missing --run aclocal-1.11
AMTAR = ${SHELL} /v/filer4b/v38q001/ruoyi/GameTech/Assignment-2/missing --run tar
AR = ar
AUTOCONF = ${SHELL} /v/filer4b/v38q001/ruoyi/GameTech/Assignment-2/missing --run autoconf
AUTOHEADER = ${SHELL} /v/filer4b/v38q001/ruoyi/GameTech/Assignment-2/missing --run autoheader
AUTOMAKE = ${SHELL} /v/filer4b/v38q001/ruoyi/GameTech/Assignment-2/missing --run automake-1.11
AWK = gawk
CC = gcc
CCDEPMODE = depmode=gcc3
CEGUI_CFLAGS = -I/lusr/opt/cegui-0.7.6/include -I/lusr/opt/cegui-0.7.6/include/CEGUI  
CEGUI_LIBS = -L/lusr/opt/cegui-0.7.6/lib -lCEGUIBase  
CFLAGS = -g -O2
CPP = gcc -E
CPPFLAGS = 
CXX = g++
CXXCPP = g++ -E
CXXDEPMODE = depmode=gcc3
CXXFLAGS = -g -O2
CYGPATH_W = echo
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
DSYMUTIL = 
DUMPBIN = 
ECHO_C = 
ECHO_N = -n
ECHO_T = 
EGREP = /bin/grep -E
EXEEXT = 
FGREP = /bin/grep -F
GREP = /bin/grep
INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = $(install_sh) -c -s
LD = /usr/bin/ld -m elf_x86_64
LDFLAGS = 
LIBOBJS = 
LIBS = 
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LIPO = 
LN_S = ln -s
LTLIBOBJS = 
MAKEINFO = ${SHELL} /v/filer4b/v38q001/ruoyi/GameTech/Assignment-2/missing --run makeinfo
MKDIR_P = /bin/mkdir -p
NM = /usr/bin/nm -B
NMEDIT = 
OBJDUMP = objdump
OBJEXT = o
OGRE_CFLAGS = -pthread -I/lusr/opt/ogre-1.7.4/include -I/lusr/opt/ogre-1.7.4/include/OGRE  
OGRE_LIBS = -L/lusr/opt/ogre-1.7.4/lib -lOgreMain -lpthread  
OIS_CFLAGS = -I/usr/include/OIS  
OIS_LIBS = -lOIS  
OTOOL = 
OTOOL64 = 
PACKAGE = SampleApp
PACKAGE_BUGREPORT = 
PACKAGE_NAME = 
PACKAGE_STRING = 
PACKAGE_TARNAME = 
PACKAGE_URL = 
PACKAGE_VERSION = 
PATH_SEPARATOR = :
PKG_CONFIG = /usr/bin/pkg-config
RANLIB = ranlib
SED = /bin/sed
SET_MAKE = 
SHELL = /bin/bash
STRIP = strip
VERSION = 0.1
abs_builddir = /v/filer4b/v38q001/ruoyi/GameTech/Assignment-2
abs_srcdir = /v/filer4b/v38q001/ruoyi/GameTech/Assignment-2
abs_top_builddir = /v/filer4b/v38q001/ruoyi/GameTech/Assignment-2
abs_top_srcdir = /v/filer4b/v38q001/ruoyi/GameTech/Assignment-2
ac_ct_CC = gcc
ac_ct_CXX = g++
ac_ct_DUMPBIN = 
am__include = include
am__leading_dot = .
am__quote = 
am__tar = ${AMTAR} chof - "$$tardir"
am__untar = ${AMTAR} xf -
bindir = ${exec_prefix}/bin
build = x86_64-unknown-linux-gnu
build_alias = 
build_cpu = x86_64
build_os = linux-gnu
build_vendor = unknown
builddir = .
bullet_CFLAGS = -I/usr/local/include/bullet  
bullet_LIBS = -L/usr/local/lib -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath  
datadir = ${datarootdir}
datarootdir = ${prefix}/share
docdir = ${datarootdir}/doc/${PACKAGE}
dvidir = ${docdir}
exec_prefix = ${prefix}
host = x86_64-unknown-linux-gnu
host_alias = 
host_cpu = x86_64
host_os = linux-gnu
host_vendor = unknown
htmldir = ${docdir}
includedir = ${prefix}/include
infodir = ${datarootdir}/info
install_sh = ${SHELL} /v/filer4b/v38q001/ruoyi/GameTech/Assignment-2/install-sh
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localedir = ${datarootdir}/locale
localstatedir = ${prefix}/var
lt_ECHO = echo
mandir = ${datarootdir}/man
mkdir_p = /bin/mkdir -p
oldincludedir = /usr/include
pdfdir = ${docdir}
prefix = /usr/local
program_transform_name = s,x,x,
psdir = ${docdir}
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
srcdir = .
sysconfdir = ${prefix}/etc
target_alias = 
top_build_prefix = 
top_builddir = .
top_srcdir = .
noinst_HEADERS = Controller.hpp WorldObjects.hpp Physics.hpp OgreFramework.hpp OgreDemo.hpp
Project1_CPPFLAGS = -I$(top_srcdir)
#Project1_SOURCES= HelloWorld.cpp
Project1_SOURCES = Controller.cpp WorldObjects.cpp Physics.cpp OgreDemo.cpp OgreFramework.cpp main.cpp
Project1_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(CEGUI_CFLAGS)
Project1_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(CEGUI_LIBS)
EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
all: config.h
	$(MAKE) $(AM_MAKEFLAGS) all-am

.SUFFIXES:
.SUFFIXES: .cpp .lo .o .obj
am--refresh:
	@:
$(srcdir)/Makefile.in:  $(srcdir)/Makefile.am  $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      echo ' cd $(srcdir) && $(AUTOMAKE) --foreign'; \
	      $(am__cd) $(srcdir) && $(AUTOMAKE) --foreign \
		&& exit 0; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --foreign Makefile'; \
	$(am__cd) $(top_srcdir) && \
	  $(AUTOMAKE) --foreign Makefile
.PRECIOUS: Makefile
Makefile: $(srcdir)/Makefile.in $(top_builddir)/config.status
	@case '$?' in \
	  *config.status*) \
	    echo ' $(SHELL) ./config.status'; \
	    $(SHELL) ./config.status;; \
	  *) \
	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $@ $(am__depfiles_maybe)'; \
	    cd $(top_builddir) && $(SHELL) ./config.status $@ $(am__depfiles_maybe);; \
	esac;

$(top_builddir)/config.status: $(top_srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	$(SHELL) ./config.status --recheck

$(top_srcdir)/configure:  $(am__configure_deps)
	$(am__cd) $(srcdir) && $(AUTOCONF)
$(ACLOCAL_M4):  $(am__aclocal_m4_deps)
	$(am__cd) $(srcdir) && $(ACLOCAL) $(ACLOCAL_AMFLAGS)
$(am__aclocal_m4_deps):

config.h: stamp-h1
	@if test ! -f $@; then \
	  rm -f stamp-h1; \
	  $(MAKE) $(AM_MAKEFLAGS) stamp-h1; \
	else :; fi

stamp-h1: $(srcdir)/config.h.in $(top_builddir)/config.status
	@rm -f stamp-h1
	cd $(top_builddir) && $(SHELL) ./config.status config.h
$(srcdir)/config.h.in:  $(am__configure_deps) 
	($(am__cd) $(top_srcdir) && $(AUTOHEADER))
	rm -f stamp-h1
	touch $@

distclean-hdr:
	-rm -f config.h stamp-h1
install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	test -z "$(bindir)" || $(MKDIR_P) "$(DESTDIR)$(bindir)"
	@list='$(bin_PROGRAMS)'; test -n "$(bindir)" || list=; \
	for p in $$list; do echo "$$p $$p"; done | \
	sed 's/$(EXEEXT)$$//' | \
	while read p p1; do if test -f $$p || test -f $$p1; \
	  then echo "$$p"; echo "$$p"; else :; fi; \
	done | \
	sed -e 'p;s,.*/,,;n;h' -e 's|.*|.|' \
	    -e 'p;x;s,.*/,,;s/$(EXEEXT)$$//;$(transform);s/$$/$(EXEEXT)/' | \
	sed 'N;N;N;s,\n, ,g' | \
	$(AWK) 'BEGIN { files["."] = ""; dirs["."] = 1 } \
	  { d=$$3; if (dirs[d] != 1) { print "d", d; dirs[d] = 1 } \
	    if ($$2 == $$4) files[d] = files[d] " " $$1; \
	    else { print "f", $$3 "/" $$4, $$1; } } \
	  END { for (d in files) print "f", d, files[d] }' | \
	while read type dir files; do \
	    if test "$$dir" = .; then dir=; else dir=/$$dir; fi; \
	    test -z "$$files" || { \
	    echo " $(INSTALL_PROGRAM_ENV) $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL_PROGRAM) $$files '$(DESTDIR)$(bindir)$$dir'"; \
	    $(INSTALL_PROGRAM_ENV) $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL_PROGRAM) $$files "$(DESTDIR)$(bindir)$$dir" || exit $$?; \
	    } \
	; done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	@list='$(bin_PROGRAMS)'; test -n "$(bindir)" || list=; \
	files=`for p in $$list; do echo "$$p"; done | \
	  sed -e 'h;s,^.*/,,;s/$(EXEEXT)$$//;$(transform)' \
	      -e 's/$$/$(EXEEXT)/' `; \
	test -n "$$list" || exit 0; \
	echo " ( cd '$(DESTDIR)$(bindir)' && rm -f" $$files ")"; \
	cd "$(DESTDIR)$(bindir)" && rm -f $$files

clean-binPROGRAMS:
	@list='$(bin_PROGRAMS)'; test -n "$$list" || exit 0; \
	echo " rm -f" $$list; \
	rm -f $$list || exit $$?; \
	test -n "$(EXEEXT)" || exit 0; \
	list=`for p in $$list; do echo "$$p"; done | sed 's/$(EXEEXT)$$//'`; \
	echo " rm -f" $$list; \
	rm -f $$list
Project1$(EXEEXT): $(Project1_OBJECTS) $(Project1_DEPENDENCIES) 
	@rm -f Project1$(EXEEXT)
	$(Project1_LINK) $(Project1_OBJECTS) $(Project1_LDADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT)

distclean-compile:
	-rm -f *.tab.c

include ./$(DEPDIR)/Project1-Controller.Po
include ./$(DEPDIR)/Project1-OgreDemo.Po
include ./$(DEPDIR)/Project1-OgreFramework.Po
include ./$(DEPDIR)/Project1-Physics.Po
include ./$(DEPDIR)/Project1-WorldObjects.Po
include ./$(DEPDIR)/Project1-main.Po

.cpp.o:
	$(CXXCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXXCOMPILE) -c -o $@ $<

.cpp.obj:
	$(CXXCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ `$(CYGPATH_W) '$<'`
	$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXXCOMPILE) -c -o $@ `$(CYGPATH_W) '$<'`

.cpp.lo:
	$(LTCXXCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Plo
#	source='$<' object='$@' libtool=yes \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(LTCXXCOMPILE) -c -o $@ $<

Project1-Controller.o: Controller.cpp
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -MT Project1-Controller.o -MD -MP -MF $(DEPDIR)/Project1-Controller.Tpo -c -o Project1-Controller.o `test -f 'Controller.cpp' || echo '$(srcdir)/'`Controller.cpp
	$(am__mv) $(DEPDIR)/Project1-Controller.Tpo $(DEPDIR)/Project1-Controller.Po
#	source='Controller.cpp' object='Project1-Controller.o' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -c -o Project1-Controller.o `test -f 'Controller.cpp' || echo '$(srcdir)/'`Controller.cpp

Project1-Controller.obj: Controller.cpp
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -MT Project1-Controller.obj -MD -MP -MF $(DEPDIR)/Project1-Controller.Tpo -c -o Project1-Controller.obj `if test -f 'Controller.cpp'; then $(CYGPATH_W) 'Controller.cpp'; else $(CYGPATH_W) '$(srcdir)/Controller.cpp'; fi`
	$(am__mv) $(DEPDIR)/Project1-Controller.Tpo $(DEPDIR)/Project1-Controller.Po
#	source='Controller.cpp' object='Project1-Controller.obj' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -c -o Project1-Controller.obj `if test -f 'Controller.cpp'; then $(CYGPATH_W) 'Controller.cpp'; else $(CYGPATH_W) '$(srcdir)/Controller.cpp'; fi`

Project1-WorldObjects.o: WorldObjects.cpp
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -MT Project1-WorldObjects.o -MD -MP -MF $(DEPDIR)/Project1-WorldObjects.Tpo -c -o Project1-WorldObjects.o `test -f 'WorldObjects.cpp' || echo '$(srcdir)/'`WorldObjects.cpp
	$(am__mv) $(DEPDIR)/Project1-WorldObjects.Tpo $(DEPDIR)/Project1-WorldObjects.Po
#	source='WorldObjects.cpp' object='Project1-WorldObjects.o' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -c -o Project1-WorldObjects.o `test -f 'WorldObjects.cpp' || echo '$(srcdir)/'`WorldObjects.cpp

Project1-WorldObjects.obj: WorldObjects.cpp
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -MT Project1-WorldObjects.obj -MD -MP -MF $(DEPDIR)/Project1-WorldObjects.Tpo -c -o Project1-WorldObjects.obj `if test -f 'WorldObjects.cpp'; then $(CYGPATH_W) 'WorldObjects.cpp'; else $(CYGPATH_W) '$(srcdir)/WorldObjects.cpp'; fi`
	$(am__mv) $(DEPDIR)/Project1-WorldObjects.Tpo $(DEPDIR)/Project1-WorldObjects.Po
#	source='WorldObjects.cpp' object='Project1-WorldObjects.obj' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -c -o Project1-WorldObjects.obj `if test -f 'WorldObjects.cpp'; then $(CYGPATH_W) 'WorldObjects.cpp'; else $(CYGPATH_W) '$(srcdir)/WorldObjects.cpp'; fi`

Project1-Physics.o: Physics.cpp
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -MT Project1-Physics.o -MD -MP -MF $(DEPDIR)/Project1-Physics.Tpo -c -o Project1-Physics.o `test -f 'Physics.cpp' || echo '$(srcdir)/'`Physics.cpp
	$(am__mv) $(DEPDIR)/Project1-Physics.Tpo $(DEPDIR)/Project1-Physics.Po
#	source='Physics.cpp' object='Project1-Physics.o' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -c -o Project1-Physics.o `test -f 'Physics.cpp' || echo '$(srcdir)/'`Physics.cpp

Project1-Physics.obj: Physics.cpp
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -MT Project1-Physics.obj -MD -MP -MF $(DEPDIR)/Project1-Physics.Tpo -c -o Project1-Physics.obj `if test -f 'Physics.cpp'; then $(CYGPATH_W) 'Physics.cpp'; else $(CYGPATH_W) '$(srcdir)/Physics.cpp'; fi`
	$(am__mv) $(DEPDIR)/Project1-Physics.Tpo $(DEPDIR)/Project1-Physics.Po
#	source='Physics.cpp' object='Project1-Physics.obj' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -c -o Project1-Physics.obj `if test -f 'Physics.cpp'; then $(CYGPATH_W) 'Physics.cpp'; else $(CYGPATH_W) '$(srcdir)/Physics.cpp'; fi`

Project1-OgreDemo.o: OgreDemo.cpp
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -MT Project1-OgreDemo.o -MD -MP -MF $(DEPDIR)/Project1-OgreDemo.Tpo -c -o Project1-OgreDemo.o `test -f 'OgreDemo.cpp' || echo '$(srcdir)/'`OgreDemo.cpp
	$(am__mv) $(DEPDIR)/Project1-OgreDemo.Tpo $(DEPDIR)/Project1-OgreDemo.Po
#	source='OgreDemo.cpp' object='Project1-OgreDemo.o' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -c -o Project1-OgreDemo.o `test -f 'OgreDemo.cpp' || echo '$(srcdir)/'`OgreDemo.cpp

Project1-OgreDemo.obj: OgreDemo.cpp
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -MT Project1-OgreDemo.obj -MD -MP -MF $(DEPDIR)/Project1-OgreDemo.Tpo -c -o Project1-OgreDemo.obj `if test -f 'OgreDemo.cpp'; then $(CYGPATH_W) 'OgreDemo.cpp'; else $(CYGPATH_W) '$(srcdir)/OgreDemo.cpp'; fi`
	$(am__mv) $(DEPDIR)/Project1-OgreDemo.Tpo $(DEPDIR)/Project1-OgreDemo.Po
#	source='OgreDemo.cpp' object='Project1-OgreDemo.obj' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -c -o Project1-OgreDemo.obj `if test -f 'OgreDemo.cpp'; then $(CYGPATH_W) 'OgreDemo.cpp'; else $(CYGPATH_W) '$(srcdir)/OgreDemo.cpp'; fi`

Project1-OgreFramework.o: OgreFramework.cpp
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -MT Project1-OgreFramework.o -MD -MP -MF $(DEPDIR)/Project1-OgreFramework.Tpo -c -o Project1-OgreFramework.o `test -f 'OgreFramework.cpp' || echo '$(srcdir)/'`OgreFramework.cpp
	$(am__mv) $(DEPDIR)/Project1-OgreFramework.Tpo $(DEPDIR)/Project1-OgreFramework.Po
#	source='OgreFramework.cpp' object='Project1-OgreFramework.o' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -c -o Project1-OgreFramework.o `test -f 'OgreFramework.cpp' || echo '$(srcdir)/'`OgreFramework.cpp

Project1-OgreFramework.obj: OgreFramework.cpp
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -MT Project1-OgreFramework.obj -MD -MP -MF $(DEPDIR)/Project1-OgreFramework.Tpo -c -o Project1-OgreFramework.obj `if test -f 'OgreFramework.cpp'; then $(CYGPATH_W) 'OgreFramework.cpp'; else $(CYGPATH_W) '$(srcdir)/OgreFramework.cpp'; fi`
	$(am__mv) $(DEPDIR)/Project1-OgreFramework.Tpo $(DEPDIR)/Project1-OgreFramework.Po
#	source='OgreFramework.cpp' object='Project1-OgreFramework.obj' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -c -o Project1-OgreFramework.obj `if test -f 'OgreFramework.cpp'; then $(CYGPATH_W) 'OgreFramework.cpp'; else $(CYGPATH_W) '$(srcdir)/OgreFramework.cpp'; fi`

Project1-main.o: main.cpp
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -MT Project1-main.o -MD -MP -MF $(DEPDIR)/Project1-main.Tpo -c -o Project1-main.o `test -f 'main.cpp' || echo '$(srcdir)/'`main.cpp
	$(am__mv) $(DEPDIR)/Project1-main.Tpo $(DEPDIR)/Project1-main.Po
#	source='main.cpp' object='Project1-main.o' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -c -o Project1-main.o `test -f 'main.cpp' || echo '$(srcdir)/'`main.cpp

Project1-main.obj: main.cpp
	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -MT Project1-main.obj -MD -MP -MF $(DEPDIR)/Project1-main.Tpo -c -o Project1-main.obj `if test -f 'main.cpp'; then $(CYGPATH_W) 'main.cpp'; else $(CYGPATH_W) '$(srcdir)/main.cpp'; fi`
	$(am__mv) $(DEPDIR)/Project1-main.Tpo $(DEPDIR)/Project1-main.Po
#	source='main.cpp' object='Project1-main.obj' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(Project1_CPPFLAGS) $(CPPFLAGS) $(Project1_CXXFLAGS) $(CXXFLAGS) -c -o Project1-main.obj `if test -f 'main.cpp'; then $(CYGPATH_W) 'main.cpp'; else $(CYGPATH_W) '$(srcdir)/main.cpp'; fi`

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:
	-rm -f libtool config.lt

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '{ files[$$0] = 1; nonempty = 1; } \
	      END { if (nonempty) { for (i in files) print i; }; }'`; \
	mkid -fID $$unique
tags: TAGS

TAGS:  $(HEADERS) $(SOURCES) config.h.in $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	set x; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS) config.h.in $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '{ files[$$0] = 1; nonempty = 1; } \
	      END { if (nonempty) { for (i in files) print i; }; }'`; \
	shift; \
	if test -z "$(ETAGS_ARGS)$$*$$unique"; then :; else \
	  test -n "$$unique" || unique=$$empty_fix; \
	  if test $$# -gt 0; then \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      "$$@" $$unique; \
	  else \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      $$unique; \
	  fi; \
	fi
ctags: CTAGS
CTAGS:  $(HEADERS) $(SOURCES) config.h.in $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	list='$(SOURCES) $(HEADERS) config.h.in $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '{ files[$$0] = 1; nonempty = 1; } \
	      END { if (nonempty) { for (i in files) print i; }; }'`; \
	test -z "$(CTAGS_ARGS)$$unique" \
	  || $(CTAGS) $(CTAGSFLAGS) $(AM_CTAGSFLAGS) $(CTAGS_ARGS) \
	     $$unique

GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && $(am__cd) $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) "$$here"

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH tags

distdir: $(DISTFILES)
	$(am__remove_distdir)
	test -d "$(distdir)" || mkdir "$(distdir)"
	@srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	list='$(DISTFILES)'; \
	  dist_files=`for file in $$list; do echo $$file; done | \
	  sed -e "s|^$$srcdirstrip/||;t" \
	      -e "s|^$$topsrcdirstrip/|$(top_builddir)/|;t"`; \
	case $$dist_files in \
	  */*) $(MKDIR_P) `echo "$$dist_files" | \
			   sed '/\//!d;s|^|$(distdir)/|;s,/[^/]*$$,,' | \
			   sort -u` ;; \
	esac; \
	for file in $$dist_files; do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  if test -d $$d/$$file; then \
	    dir=`echo "/$$file" | sed -e 's,/[^/]*$$,,'`; \
	    if test -d "$(distdir)/$$file"; then \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -fpR $(srcdir)/$$file "$(distdir)$$dir" || exit 1; \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    cp -fpR $$d/$$file "$(distdir)$$dir" || exit 1; \
	  else \
	    test -f "$(distdir)/$$file" \
	    || cp -p $$d/$$file "$(distdir)/$$file" \
	    || exit 1; \
	  fi; \
	done
	-test -n "$(am__skip_mode_fix)" \
	|| find "$(distdir)" -type d ! -perm -755 \
		-exec chmod u+rwx,go+rx {} \; -o \
	  ! -type d ! -perm -444 -links 1 -exec chmod a+r {} \; -o \
	  ! -type d ! -perm -400 -exec chmod a+r {} \; -o \
	  ! -type d ! -perm -444 -exec $(install_sh) -c -m a+r {} {} \; \
	|| chmod -R a+r "$(distdir)"
dist-gzip: distdir
	tardir=$(distdir) && $(am__tar) | GZIP=$(GZIP_ENV) gzip -c >$(distdir).tar.gz
	$(am__remove_distdir)

dist-bzip2: distdir
	tardir=$(distdir) && $(am__tar) | bzip2 -9 -c >$(distdir).tar.bz2
	$(am__remove_distdir)

dist-lzma: distdir
	tardir=$(distdir) && $(am__tar) | lzma -9 -c >$(distdir).tar.lzma
	$(am__remove_distdir)

dist-xz: distdir
	tardir=$(distdir) && $(am__tar) | xz -c >$(distdir).tar.xz
	$(am__remove_distdir)

dist-tarZ: distdir
	tardir=$(distdir) && $(am__tar) | compress -c >$(distdir).tar.Z
	$(am__remove_distdir)

dist-shar: distdir
	shar $(distdir) | GZIP=$(GZIP_ENV) gzip -c >$(distdir).shar.gz
	$(am__remove_distdir)

dist-zip: distdir
	-rm -f $(distdir).zip
	zip -rq $(distdir).zip $(distdir)
	$(am__remove_distdir)

dist dist-all: distdir
	tardir=$(distdir) && $(am__tar) | GZIP=$(GZIP_ENV) gzip -c >$(distdir).tar.gz
	$(am__remove_distdir)

# This target untars the dist file and tries a VPATH configuration.  Then
# it guarantees that the distribution is self-contained by making another
# tarfile.
distcheck: dist
	case '$(DIST_ARCHIVES)' in \
	*.tar.gz*) \
	  GZIP=$(GZIP_ENV) gzip -dc $(distdir).tar.gz | $(am__untar) ;;\
	*.tar.bz2*) \
	  bzip2 -dc $(distdir).tar.bz2 | $(am__untar) ;;\
	*.tar.lzma*) \
	  lzma -dc $(distdir).tar.lzma | $(am__untar) ;;\
	*.tar.xz*) \
	  xz -dc $(distdir).tar.xz | $(am__untar) ;;\
	*.tar.Z*) \
	  uncompress -c $(distdir).tar.Z | $(am__untar) ;;\
	*.shar.gz*) \
	  GZIP=$(GZIP_ENV) gzip -dc $(distdir).shar.gz | unshar ;;\
	*.zip*) \
	  unzip $(distdir).zip ;;\
	esac
	chmod -R a-w $(distdir); chmod a+w $(distdir)
	mkdir $(distdir)/_build
	mkdir $(distdir)/_inst
	chmod a-w $(distdir)
	test -d $(distdir)/_build || exit 0; \
	dc_install_base=`$(am__cd) $(distdir)/_inst && pwd | sed -e 's,^[^:\\/]:[\\/],/,'` \
	  && dc_destdir="$${TMPDIR-/tmp}/am-dc-$$$$/" \
	  && am__cwd=`pwd` \
	  && $(am__cd) $(distdir)/_build \
	  && ../configure --srcdir=.. --prefix="$$dc_install_base" \
	    $(DISTCHECK_CONFIGURE_FLAGS) \
	  && $(MAKE) $(AM_MAKEFLAGS) \
	  && $(MAKE) $(AM_MAKEFLAGS) dvi \
	  && $(MAKE) $(AM_MAKEFLAGS) check \
	  && $(MAKE) $(AM_MAKEFLAGS) install \
	  && $(MAKE) $(AM_MAKEFLAGS) installcheck \
	  && $(MAKE) $(AM_MAKEFLAGS) uninstall \
	  && $(MAKE) $(AM_MAKEFLAGS) distuninstallcheck_dir="$$dc_install_base" \
	        distuninstallcheck \
	  && chmod -R a-w "$$dc_install_base" \
	  && ({ \
	       (cd ../.. && umask 077 && mkdir "$$dc_destdir") \
	       && $(MAKE) $(AM_MAKEFLAGS) DESTDIR="$$dc_destdir" install \
	       && $(MAKE) $(AM_MAKEFLAGS) DESTDIR="$$dc_destdir" uninstall \
	       && $(MAKE) $(AM_MAKEFLAGS) DESTDIR="$$dc_destdir" \
	            distuninstallcheck_dir="$$dc_destdir" distuninstallcheck; \
	      } || { rm -rf "$$dc_destdir"; exit 1; }) \
	  && rm -rf "$$dc_destdir" \
	  && $(MAKE) $(AM_MAKEFLAGS) dist \
	  && rm -rf $(DIST_ARCHIVES) \
	  && $(MAKE) $(AM_MAKEFLAGS) distcleancheck \
	  && cd "$$am__cwd" \
	  || exit 1
	$(am__remove_distdir)
	@(echo "$(distdir) archives ready for distribution: "; \
	  list='$(DIST_ARCHIVES)'; for i in $$list; do echo $$i; done) | \
	  sed -e 1h -e 1s/./=/g -e 1p -e 1x -e '$$p' -e '$$x'
distuninstallcheck:
	@$(am__cd) '$(distuninstallcheck_dir)' \
	&& test `$(distuninstallcheck_listfiles) | wc -l` -le 1 \
	   || { echo "ERROR: files left after uninstall:" ; \
	        if test -n "$(DESTDIR)"; then \
	          echo "  (check DESTDIR support)"; \
	        fi ; \
	        $(distuninstallcheck_listfiles) ; \
	        exit 1; } >&2
distcleancheck: distclean
	@if test '$(srcdir)' = . ; then \
	  echo "ERROR: distcleancheck can only run from a VPATH build" ; \
	  exit 1 ; \
	fi
	@test `$(distcleancheck_listfiles) | wc -l` -eq 0 \
	  || { echo "ERROR: files left in build directory after distclean:" ; \
	       $(distcleancheck_listfiles) ; \
	       exit 1; } >&2
check-am: all-am
check: check-am
all-am: Makefile $(PROGRAMS) $(HEADERS) config.h
installdirs:
	for dir in "$(DESTDIR)$(bindir)"; do \
	  test -z "$$dir" || $(MKDIR_P) "$$dir"; \
	done
install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:

distclean-generic:
	-test -z "$(CONFIG_CLEAN_FILES)" || rm -f $(CONFIG_CLEAN_FILES)
	-test . = "$(srcdir)" || test -z "$(CONFIG_CLEAN_VPATH_FILES)" || rm -f $(CONFIG_CLEAN_VPATH_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-binPROGRAMS clean-generic clean-libtool mostlyclean-am

distclean: distclean-am
	-rm -f $(am__CONFIG_DISTCLEAN_FILES)
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
distclean-am: clean-am distclean-compile distclean-generic \
	distclean-hdr distclean-libtool distclean-tags

dvi: dvi-am

dvi-am:

html: html-am

html-am:

info: info-am

info-am:

install-data-am:

install-dvi: install-dvi-am

install-dvi-am:

install-exec-am: install-binPROGRAMS

install-html: install-html-am

install-html-am:

install-info: install-info-am

install-info-am:

install-man:

install-pdf: install-pdf-am

install-pdf-am:

install-ps: install-ps-am

install-ps-am:

installcheck-am:

maintainer-clean: maintainer-clean-am
	-rm -f $(am__CONFIG_DISTCLEAN_FILES)
	-rm -rf $(top_srcdir)/autom4te.cache
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic \
	mostlyclean-libtool

pdf: pdf-am

pdf-am:

ps: ps-am

ps-am:

uninstall-am: uninstall-binPROGRAMS

.MAKE: all install-am install-strip

.PHONY: CTAGS GTAGS all all-am am--refresh check check-am clean \
	clean-binPROGRAMS clean-generic clean-libtool ctags dist \
	dist-all dist-bzip2 dist-gzip dist-lzma dist-shar dist-tarZ \
	dist-xz dist-zip distcheck distclean distclean-compile \
	distclean-generic distclean-hdr distclean-libtool \
	distclean-tags distcleancheck distdir distuninstallcheck dvi \
	dvi-am html html-am info info-am install install-am \
	install-binPROGRAMS install-data install-data-am install-dvi \
	install-dvi-am install-exec install-exec-am install-html \
	install-html-am install-info install-info-am install-man \
	install-pdf install-pdf-am install-ps install-ps-am \
	install-strip installcheck installcheck-am installdirs \
	maintainer-clean maintainer-clean-generic mostlyclean \
	mostlyclean-compile mostlyclean-generic mostlyclean-libtool \
	pdf pdf-am ps ps-am tags uninstall uninstall-am \
	uninstall-binPROGRAMS


# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
