#include "WorldObjectIcecube.hpp"

Icecube::Icecube(): WorldObjectAbstract()
{
}

Icecube::~Icecube()
{
}

void Icecube::createRigidBody(PhysicsWrapper* physics)
{
	std::cout << "Icecube::createRigidBody()" << std::endl;

	//-------------------- I switched it to a cube so textures would work correctly. The original sphere has bad UV mapping
	// Physics - Ball
	//--------------------

	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0, 0, 0)));

    btScalar mass = ice_mass;
    btVector3 ballInertia(0,0,0);

	btCollisionShape* ball_collision_shape = new btBoxShape(btVector3(paddle_length, paddle_length, paddle_length));
    ball_collision_shape->calculateLocalInertia(mass,ballInertia);

    btRigidBody::btRigidBodyConstructionInfo worldObjectRigidBodyCI(mass,ballMotionState,ball_collision_shape,ballInertia);
	worldObjectRigidBodyCI.m_restitution = 0.765f;
	worldObjectRigidBodyCI.m_friction = 0.0f;
    worldObjectRigidBody = new btRigidBody(worldObjectRigidBodyCI);
	worldObjectRigidBody->setLinearVelocity(btVector3(0,0,0));
	worldObjectRigidBody->setLinearFactor(btVector3(1,0,1));
	worldObjectRigidBody->setAngularFactor(btVector3(0,1,0));
}

void Icecube::createSceneNode(Ogre::SceneManager* m_pSceneMgr)
{
	std::cout << "Icecube::createSceneNode()" << std::endl;

	// Convert static scene_node_counter to string
	// to give each instance a unique string name
 	std::string unique_id_string;
 	std::stringstream out;
 	out << getUniqueId();
 	unique_id_string = out.str();

	std::string ball_name = "ball" + unique_id_string;

	//--------------------
	// Visual - Ball
	//--------------------

	Ogre::Vector3 v3SpherePosition = Ogre::Vector3(1000, 1000, 1000);
	Ogre::Vector3 v3SphereScaleFactor = Ogre::Vector3(0.1f, 0.1f, 0.1f);

	Ogre::Entity* objSphereEntity = m_pSceneMgr->createEntity(ball_name, "cube.mesh");
	worldObjectSceneNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(ball_name);
	worldObjectSceneNode->attachObject(objSphereEntity);

	worldObjectSceneNode->setPosition(v3SpherePosition);
	worldObjectSceneNode->setScale(v3SphereScaleFactor);
	objSphereEntity->setMaterialName("Icecube");

}
// ========================================
// Static Classes
// ========================================

Icecube* Icecube::createNewIcecube(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics, Ogre::Vector3 pos)
{
	Icecube* icecube = new Icecube();
	icecube->initWorldObject(m_pSceneMgr, physics);
	icecube->resetPosition(Ogre::Vector3(pos[0], pos[1], pos[2]));
	return icecube;
}

Icecube* Icecube::createNewIcecube(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics, Penguin* penguin)
{
	const float launch_vel = 20.0f;

	Ogre::Vector3 penguin_pos = penguin->getVisualPosition();
	Ogre::Vector3 penguin_dir = penguin->getPenguinDirection();

	Ogre::Vector3 start_pos = penguin_pos + 8*penguin_dir;
	Ogre::Vector3 start_dir = penguin_dir;
	start_dir.normalise();

	Icecube* icecube = new Icecube();
	icecube->initWorldObject(m_pSceneMgr, physics);
	icecube->resetPosition(start_pos);
	icecube->resetVelocity(start_dir, launch_vel);
	return icecube;
}
