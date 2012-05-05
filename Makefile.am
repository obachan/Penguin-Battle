
noinst_HEADERS = Network.hpp AppState.hpp AppStateManager.hpp MenuState.hpp MultiplayerMenuState.hpp ClientMenuState.hpp ServerMenuState.hpp PauseState.hpp HUD.hpp SoundWrapper.hpp Controller.hpp WorldObjectAbstract.hpp WorldObjects.hpp WorldObjectGoal.hpp WorldObjectBall.hpp WorldObjectPenguin.hpp WorldObjectRoom.hpp WorldObjectPaddle.hpp Physics.hpp OgreFramework.hpp OgreApp.hpp ServerState.hpp ClientState.hpp GameState.hpp
#noinst_HEADERS= Network.hpp WorldObjectAbstract.hpp

bin_PROGRAMS= Project1
Project1_CPPFLAGS= -I$(top_srcdir)
Project1_SOURCES= Network.cpp AppStateManager.cpp MenuState.cpp PauseState.cpp MultiplayerMenuState.cpp ClientMenuState.cpp ServerMenuState.cpp HUD.cpp SoundWrapper.cpp Controller.cpp WorldObjectAbstract.cpp WorldObjects.cpp WorldObjectGoal.cpp WorldObjectBall.cpp WorldObjectPenguin.cpp WorldObjectRoom.cpp WorldObjectPaddle.cpp Physics.cpp OgreFramework.cpp OgreApp.cpp ServerState.cpp ClientState.cpp GameState.cpp main.cpp
#Project1_SOURCES= Network.cpp test.cpp WorldObjectAbstract.cpp




Project1_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(sdl_CFLAGS) $(SDL_mixer_CFLAGS) $(SDL_net_CFLAGS)
Project1_LDADD= $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(sdl_LIBS) $(SDL_mixer_LIBS) $(SDL_net_LIBS)

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
