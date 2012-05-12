#include "WorldObjectIgloo.hpp"

Igloo::Igloo(): WorldObjectAbstract()
{
}

Igloo::~Igloo()
{
}

void Igloo::createRigidBody(PhysicsWrapper* physics)
{
	std::cout << "Igloo::createRigidBody()" << std::endl;

	//-------------------- I switched it to a cube so textures would work correctly. The original sphere has bad UV mapping
	// Physics - Ball
	//--------------------

	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0, 0, 0)));

    btScalar mass = ball_mass;
    btVector3 ballInertia(0,0,0);

	btCollisionShape* ball_collision_shape = new btBoxShape(btVector3(igloo_length, igloo_height, igloo_length));
    ball_collision_shape->calculateLocalInertia(mass,ballInertia);

    btRigidBody::btRigidBodyConstructionInfo worldObjectRigidBodyCI(mass,ballMotionState,ball_collision_shape,ballInertia);
	worldObjectRigidBodyCI.m_restitution = 0.765f;
    worldObjectRigidBody = new btRigidBody(worldObjectRigidBodyCI);
	worldObjectRigidBody->setLinearVelocity(btVector3(0,0,0));

	worldObjectRigidBody->setAngularFactor(btVector3(0,1,0));
}

void Igloo::createSceneNode(Ogre::SceneManager* m_pSceneMgr)
{
	std::cout << "Igloo::createSceneNode()" << std::endl;

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

	float igloo_length_scale_factor = igloo_length/2;

	Ogre::Vector3 v3SpherePosition = Ogre::Vector3(1000, 1000, 1000);
	Ogre::Vector3 v3SphereScaleFactor = 
		Ogre::Vector3(igloo_length_scale_factor, igloo_length_scale_factor, igloo_length_scale_factor);

	Ogre::Entity* objSphereEntity = m_pSceneMgr->createEntity(ball_name, "igloo.mesh");
	worldObjectSceneNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(ball_name);
	worldObjectSceneNode->attachObject(objSphereEntity);

	worldObjectSceneNode->setPosition(v3SpherePosition);
	worldObjectSceneNode->setScale(v3SphereScaleFactor);
	objSphereEntity->setMaterialName("Ball/Snow");

}
// ========================================
// Static Classes
// ========================================

Igloo* Igloo::createNewIgloo(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics, Ogre::Vector3 pos)
{
	Igloo* igloo = new Igloo();
	igloo->initWorldObject(m_pSceneMgr, physics);
	igloo->resetPosition(Ogre::Vector3(pos[0], pos[1], pos[2]));
	return igloo;
}
