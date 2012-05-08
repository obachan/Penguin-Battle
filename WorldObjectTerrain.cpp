#include "WorldObjectTerrain.hpp"

#include <iostream>

Terrain::Terrain(Ogre::SceneManager* m_pSceneMgr) 
{
	//Ogre::Vector3 tPosition = Ogre::Vector3(start_pos_x, start_pos_y, start_pos_z);
	//Ogre::Vector3 v3SphereScaleFactor = Ogre::Vector3(rScaleFactor, rScaleFactor, rScaleFactor);

	terrainEntity = m_pSceneMgr->createEntity("terrain", "quickterrain.mesh");
	terrainNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("terrain");
	terrainNode->attachObject(terrainEntity);

	terrainNode->setPosition(Ogre::Vector3(0,-140,0));
	terrainNode->setScale(Ogre::Vector3(20,20,20));
	terrainEntity->setMaterialName("lambert3");
	//scene_node_counter++;
}


