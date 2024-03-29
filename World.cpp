#include "World.hpp"


World::World(Ogre::SceneManager* sceneMgr, PhysicsWrapper* physics, MyController* controller, int numberOfClients)
//World::World(Ogre::SceneManager* sceneMgr, PhysicsWrapper* physics, MyController* controller)
{
	mSceneMgr = sceneMgr;
	mPhysics = physics;
	i_callbackAddBall.SetCallback(this, &World::CallbackAddBall);
	i_callbackRightClick.SetCallback(this, &World::CallbackRightClick);

	worldObjectFactory = new WorldObjectFactory(mSceneMgr, mPhysics);

	room = worldObjectFactory->createNewRoom();
	penguin =  worldObjectFactory->createNewPenguin(controller, &i_callbackAddBall, &i_callbackRightClick);
	penguin->resetPosition(Ogre::Vector3(0, -95, -800), Ogre::Quaternion(Ogre::Degree(180), Ogre::Vector3::UNIT_Y));
	goal = worldObjectFactory->createNewGoal();


	igloos.push_back(worldObjectFactory->createNewIgloo(40, -room_width/2, 0));
	igloos.push_back(worldObjectFactory->createNewIgloo(-30, -room_width/2, 300));
	igloos.push_back(worldObjectFactory->createNewIgloo(10, -room_width/2, -200));
	//igloos.push_back(worldObjectFactory->createNewIgloo(40, -room_width/2, 0));

	//pSys4 = mSceneMgr->createParticleSystem("Jet", "Examples/JetEngine1");
	//rNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//rNode->attachObject(pSys4);
	world_objects.push_back(worldObjectFactory->createNewBall(0, 10, 0));
	
	clientNum = numberOfClients;

	for (int i = 0;i<clientNum; i++)
	{
		client_controllers.push_back(new MyController());
    		clientPenguins.push_back(worldObjectFactory->createNewPenguin(client_controllers[i], &i_callbackAddBall, &i_callbackRightClick));	// Create Player 2's Penguin
		
	}
}

World::~World()
{
	
}

void World::update(double timeSinceLastFrame, MyController* controller, Ogre::Camera* camera)
{
	/* Update Physics Engine */
	if (timeSinceLastFrame!=0){
		mPhysics->stepPhysics(timeSinceLastFrame, 5);
	}

	/* Update Players */
	penguin->update(timeSinceLastFrame, controller, camera);

	for (int i = 0;i<clientNum; i++)
	{
		clientPenguins[i]->update(timeSinceLastFrame, client_controllers[i], NULL);
	}

	// /* Update World Objects */
	for(int i=0; i<world_objects.size(); ++i)		world_objects[i]->update();

	for(int i=0; i<icecubes.size(); ++i)			icecubes[i]->update();
	for(int i=0; i<igloos.size(); ++i)				igloos[i]->update();



/*	int numManifolds = mPhysics->dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold =  mPhysics->dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
	
		int numContacts = contactManifold->getNumContacts();
		for (int j=0;j<numContacts;j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance()<0.f)
			{
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				const btVector3& normalOnB = pt.m_normalWorldOnB;

				btTransform trans = obA->getWorldTransform();
				btVector3 loc = trans.getOrigin();
				rNode->translate(loc.getX(),loc.getY(),loc.getZ());
				
			}
		}
	}*/

}


/* Callback Function */
bool World::CallbackAddBall(void *Param)
{
	Penguin* pen = static_cast<Penguin*>(Param);
	world_objects.push_back(worldObjectFactory->createNewBall(pen));
	return true;
}

/* Callback Function */
bool World::CallbackRightClick(void *Param)
{
	Penguin* pen = static_cast<Penguin*>(Param);
	icecubes.push_back(worldObjectFactory->createNewIcecube(pen));
	return true;
}
