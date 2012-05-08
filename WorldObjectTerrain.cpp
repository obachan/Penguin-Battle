#include "WorldObjectTerrain.hpp"

#include <iostream>

using namespace std;

Terrain::Terrain(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics) 
{
	//Ogre::Vector3 tPosition = Ogre::Vector3(start_pos_x, start_pos_y, start_pos_z);
	//Ogre::Vector3 v3SphereScaleFactor = Ogre::Vector3(rScaleFactor, rScaleFactor, rScaleFactor);

/*	terrainEntity = m_pSceneMgr->createEntity("terrain", "quickterrain.mesh");
	terrainNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("terrain");
	terrainNode->attachObject(terrainEntity);

	terrainNode->setPosition(Ogre::Vector3(0,-140,0));
	terrainNode->setScale(Ogre::Vector3(20,20,20));
	terrainEntity->setMaterialName("lambert3");*/
	//scene_node_counter++;

	ifstream myfile;
	myfile.open("heightInfo.data");

	if(!myfile) {
		cerr << "Couldn't open height data file" << endl;
	}

	char temp;

	int index = 0;
	while(!myfile.eof()) {
		myfile >> temp;
		heightdata[index] = ((int) temp) / 255.0;
		//cerr << ((int) temp) << endl;
	}
	
/*	for(int i = 0; i < 256*256; i++) {
		heightdata[i] = 0.0;
	}*/
	terrainShape = new btHeightfieldTerrainShape(256, 256, heightdata, 0.001f, -100, 100, 1, PHY_FLOAT, false);
	
	btDefaultMotionState* terrainMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo terrainRigidBodyCI(0,terrainMotionState,terrainShape,btVector3(0,0,0));
	//bottomRigidBodyCI.m_restitution = wall_restitution;
    	terrainRigidBody = new btRigidBody(terrainRigidBodyCI);
	physics->add_object_to_dynamicWorld(terrainRigidBody);
}

void Terrain::attachToDynamicWorld(PhysicsWrapper* physics)
{
	physics->add_object_to_dynamicWorld(terrainRigidBody);
}

