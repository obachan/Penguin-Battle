noinst_HEADERS = AppState.hpp AppStateManager.hpp MenuState.hpp PauseState.hpp HUD.hpp SoundWrapper.hpp Controller.hpp WorldObjects.hpp Physics.hpp OgreFramework.hpp OgreDemo.hpp OgreApp.hpp

bin_PROGRAMS= Project1
Project1_CPPFLAGS= -I$(top_srcdir)
Project1_SOURCES= AppStateManager.cpp MenuState.cpp PauseState.cpp HUD.cpp SoundWrapper.cpp Controller.cpp WorldObjects.cpp Physics.cpp OgreFramework.cpp OgreDemo.cpp OgreApp.cpp main.cpp
Project1_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(CEGUI_CFLAGS) $(sdl_CFLAGS) $(SDL_mixer_CFLAGS) $(SDL_net_CFLAGS)
Project1_LDADD= $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(CEGUI_LIBS) $(sdl_LIBS) $(SDL_mixer_LIBS) $(SDL_net_LIBS)
EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
