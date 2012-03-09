noinst_HEADERS= HUD.hpp SoundWrapper.hpp Controller.hpp WorldObjects.hpp Physics.hpp OgreFramework.hpp OgreDemo.hpp

bin_PROGRAMS= Project1
Project1_CPPFLAGS= -I$(top_srcdir)
#Project1_SOURCES= HelloWorld.cpp
Project1_SOURCES= HUD.cpp SoundWrapper.cpp Controller.cpp WorldObjects.cpp Physics.cpp OgreDemo.cpp OgreFramework.cpp main.cpp
Project1_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(CEGUI_CFLAGS) $(sdl_CFLAGS) $(SDL_mixer_CFLAGS)
Project1_LDADD= $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(CEGUI_LIBS) $(sdl_LIBS) $(SDL_mixer_LIBS)
EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
