#include "WorldObjectBall.hpp"

Ball::Ball() : WorldObjectAbstract()
{
}

Ball::Ball(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics, 
	double start_pos_x, double start_pos_y, double start_pos_z) : WorldObjectAbstract()
{
	createSphere(m_pSceneMgr, start_pos_x, start_pos_y, start_pos_z, ball_radius);
	if(physics != NULL)
		attachToDynamicWorld(physics);
	
}

Ball::~Ball()
{
}

// ==========================
// Class Methods
// ==========================

void Ball::createSphere(Ogre::SceneManager* m_pSceneMgr, Ogre::Real start_pos_x, Ogre::Real start_pos_y, Ogre::Real start_pos_z, Ogre::Real rScaleFactor)
{

	//-------------------- I switched it to a cube so textures would work correctly. The original sphere has bad UV mapping
	// Physics - Ball
	//--------------------

	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(start_pos_x, start_pos_y, start_pos_z)));

    btScalar mass = ball_mass;
    btVector3 ballInertia(0,0,0);

	btCollisionShape* ball_collision_shape = new btSphereShape(ball_radius);
    ball_collision_shape->calculateLocalInertia(mass,ballInertia);

    btRigidBody::btRigidBodyConstructionInfo worldObjectRigidBodyCI(mass,ballMotionState,ball_collision_shape,ballInertia);
	worldObjectRigidBodyCI.m_restitution = 0.765f;
    worldObjectRigidBody = new btRigidBody(worldObjectRigidBodyCI);
	worldObjectRigidBody->setLinearVelocity(btVector3(0,0,0));

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
	Ogre::Vector3 v3SphereScaleFactor = Ogre::Vector3(rScaleFactor, rScaleFactor, rScaleFactor);

	//Ogre::Entity* objSphereEntity = m_pSceneMgr->createEntity(ball_name, "sphereCheck.mesh");
	Ogre::Entity* objSphereEntity = m_pSceneMgr->createEntity(ball_name, "igloo.mesh");
	worldObjectSceneNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(ball_name);
	worldObjectSceneNode->attachObject(objSphereEntity);

	worldObjectSceneNode->setPosition(v3SpherePosition);
	worldObjectSceneNode->setScale(v3SphereScaleFactor);
	objSphereEntity->setMaterialName("Ball/Snow");

}

// Checks whether the ball is contained
// in the Goal Object which is passed in
bool Ball::inGoal(Goal* goal)
{
	Ogre::Vector3 ball_pos = getRigidBodyPosition();

	Ogre::Vector3 left_goal_pos = goal->goalLeftNode->getPosition();
	Ogre::Vector3 right_goal_pos = goal->goalRightNode->getPosition();

	Ogre::Vector3 back_goal_pos = goal->goalBackNode->getPosition();
	Ogre::Vector3 front_goal_pos = goal->goalFrontNode->getPosition();

	Ogre::Vector3 top_goal_pos = goal->goalTopNode->getPosition();

	if(ball_pos[0] > left_goal_pos[0] + ball_radius &&
		ball_pos[0] < right_goal_pos[0] - ball_radius &&
		ball_pos[1] < top_goal_pos[1] - ball_radius &&
		ball_pos[2] < front_goal_pos[2] - ball_radius &&
		ball_pos[2] > back_goal_pos[2] + ball_radius)
	{
		return true;
	}
	
	return false;
}

// Physics is passin so the that ball can be removed and readded to the dynamics world
void Ball::reset(PhysicsWrapper* physics)
{

	//----------------------------------
	// Define new position and velocity
	//----------------------------------

	int rand_pos_x = rand() % 50 - 24;
	int rand_pos_y = rand() % 50 - 24;
	int rand_pos_z = rand() % 50 - 24;

	int rand_vel_x = rand() % 10;
	int rand_vel_y = rand() % 10;
	int rand_vel_z = rand() % 10;

	btTransform trans;
    worldObjectRigidBody->getMotionState()->getWorldTransform(trans);
	trans.setOrigin(btVector3(rand_pos_x, rand_pos_y, rand_pos_z));
	worldObjectRigidBody->setLinearVelocity(btVector3(rand_vel_x,-rand_vel_y,rand_vel_z));

	//----------------------------------
	// Set new position and velocity
	//----------------------------------

	btMotionState *motionState = worldObjectRigidBody->getMotionState();
	motionState->setWorldTransform(trans);
	worldObjectRigidBody->setMotionState (motionState);
}

void Ball::createRigidBody(PhysicsWrapper* physics)
{
	std::cout << "Ball::createRigidBody()" << std::endl;

	//-------------------- I switched it to a cube so textures would work correctly. The original sphere has bad UV mapping
	// Physics - Ball
	//--------------------

	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0, 0, 0)));

    btScalar mass = ball_mass;
    btVector3 ballInertia(0,0,0);

	btCollisionShape* ball_collision_shape = new btSphereShape(ball_radius);
    ball_collision_shape->calculateLocalInertia(mass,ballInertia);

    btRigidBody::btRigidBodyConstructionInfo worldObjectRigidBodyCI(mass,ballMotionState,ball_collision_shape,ballInertia);
	worldObjectRigidBodyCI.m_restitution = 0.765f;
    worldObjectRigidBody = new btRigidBody(worldObjectRigidBodyCI);
	worldObjectRigidBody->setLinearVelocity(btVector3(0,0,0));
}

void Ball::createSceneNode(Ogre::SceneManager* m_pSceneMgr)
{
	std::cout << "Ball::createSceneNode()" << std::endl;

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
	Ogre::Vector3 v3SphereScaleFactor = Ogre::Vector3(ball_radius, ball_radius, ball_radius);

	Ogre::Entity* objSphereEntity = m_pSceneMgr->createEntity(ball_name, "sphere.mesh");
	worldObjectSceneNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(ball_name);
	worldObjectSceneNode->attachObject(objSphereEntity);

	worldObjectSceneNode->setPosition(v3SpherePosition);
	worldObjectSceneNode->setScale(v3SphereScaleFactor);
	objSphereEntity->setMaterialName("Ball/Snow");

}


// ========================================
// Static Classes
// ========================================

Ball* Ball::createNewBall(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics, Ogre::Vector3 pos)
{
	Ball* ball = new Ball();
	ball->initWorldObject(m_pSceneMgr, physics);
	ball->resetPosition(Ogre::Vector3(pos[0], pos[1], pos[2]));
	return ball;
}

Ball* Ball::createNewBall(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics, Penguin* penguin)
{
	Ogre::Vector3 penguin_pos = penguin->getVisualPosition();
	Ogre::Vector3 penguin_dir = penguin->getPenguinDirection();

	Ogre::Vector3 ball_start_pos = penguin_pos + 8*penguin_dir;
	Ogre::Vector3 ball_start_dir = penguin_dir.midPoint(Ogre::Vector3(0, 1, 0));
	ball_start_dir.normalise();

	Ball* ball = new Ball();
	ball->initWorldObject(m_pSceneMgr, physics);
	ball->resetPosition(ball_start_pos);
	ball->resetVelocity(ball_start_dir, ball_launch_vel);
	return ball;
}
