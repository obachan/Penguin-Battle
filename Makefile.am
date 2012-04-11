noinst_HEADERS = Network.hpp AppState.hpp AppStateManager.hpp MenuState.hpp MultiplayerMenuState.hpp ClientMenuState.hpp ServerMenuState.hpp PauseState.hpp HUD.hpp SoundWrapper.hpp Controller.hpp WorldObjects.hpp Physics.hpp OgreFramework.hpp OgreDemo.hpp OgreApp.hpp GameState.hpp
#noinst_HEADERS= Network.hpp

bin_PROGRAMS= Project1
Project1_CPPFLAGS= -I$(top_srcdir)
Project1_SOURCES= Network.cpp AppStateManager.cpp MenuState.cpp PauseState.cpp MultiplayerMenuState.cpp ClientMenuState.cpp ServerMenuState.cpp HUD.cpp SoundWrapper.cpp Controller.cpp WorldObjects.cpp Physics.cpp OgreFramework.cpp OgreDemo.cpp OgreApp.cpp GameState.cpp main.cpp
#Project1_SOURCES= Network.cpp test.cpp
Project1_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(sdl_CFLAGS) $(SDL_mixer_CFLAGS) $(SDL_net_CFLAGS)
Project1_LDADD= $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(sdl_LIBS) $(SDL_mixer_LIBS) $(SDL_net_LIBS)
EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
