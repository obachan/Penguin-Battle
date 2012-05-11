#===========================================
# Awesome Comments by Tom Yu
#===========================================
#-------------------------------------------
# noinst_HEADERS: OgreFramework classes .hpp
#-------------------------------------------
noinst_HEADERS = AppState.hpp AppStateManager.hpp MenuState.hpp MultiplayerMenuState.hpp ClientMenuState.hpp ServerMenuState.hpp PauseState.hpp ServerState.hpp ClientState.hpp GameState.hpp Network.hpp Physics.hpp HUD.hpp SoundWrapper.hpp Controller.hpp OgreFramework.hpp 
#-------------------------------------------
# noinst_HEADERS: WorldObject classes .hpp
#-------------------------------------------
noinst_HEADERS = WorldObjectAbstract.hpp WorldObjectFactory.hpp WorldObjectGoal.hpp WorldObjectBall.hpp WorldObjectPenguin.hpp WorldObjectRoom.hpp WorldObjectTerrain.hpp  WorldObjectPaddle.hpp World.hpp WorldServer.hpp OgreApp.hpp

#-------------------------------------------
# Name of Executable file
#-------------------------------------------
bin_PROGRAMS= Project1
Project1_CPPFLAGS= -I$(top_srcdir)

#-------------------------------------------
# Project1_SOURCES: .cpp
#-------------------------------------------
Project1_SOURCES = AppStateManager.cpp MenuState.cpp MultiplayerMenuState.cpp ClientMenuState.cpp ServerMenuState.cpp PauseState.cpp ServerState.cpp ClientState.cpp GameState.cpp Network.cpp Physics.cpp HUD.cpp SoundWrapper.cpp Controller.cpp OgreFramework.cpp WorldObjectAbstract.cpp WorldObjectFactory.cpp WorldObjectGoal.cpp WorldObjectBall.cpp WorldObjectPenguin.cpp WorldObjectRoom.cpp WorldObjectTerrain.cpp WorldObjectPaddle.cpp World.cpp WorldServer.cpp OgreApp.cpp main.cpp

Project1_CXXFLAGS= $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(sdl_CFLAGS) $(SDL_mixer_CFLAGS) $(SDL_net_CFLAGS)
Project1_LDADD= $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(sdl_LIBS) $(SDL_mixer_LIBS) $(SDL_net_LIBS)

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign
