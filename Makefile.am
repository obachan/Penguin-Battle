noinst_HEADERS= Controller.hpp WorldObjects.hpp Physics.hpp OgreFramework.hpp OgreDemo.hpp

bin_PROGRAMS= Project1
Project1_CPPFLAGS= -I$(top_srcdir)
#Project1_SOURCES= HelloWorld.cpp
Project1_SOURCES= Controller.cpp WorldObjects.cpp Physics.cpp OgreDemo.cpp OgreFramework.cpp main.cpp
Project1_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS)
Project1_LDADD= $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS)
EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
