#include "WorldObjectBall.hpp"

int Ball::scene_node_counter = 0;

Ball::Ball(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics, 
	double start_pos_x, double start_pos_y, double start_pos_z) : WorldObjectAbstract(physics)
{
	//const double start_pos_x = 0.0f;
	//const double start_pos_y = -(room_width/2) + ball_radius;
	//const double start_pos_z = 0.0f;

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

	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0, 0, 0)));

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
 	std::string scene_node_counter_string;
 	std::stringstream out;
 	out << scene_node_counter;
 	scene_node_counter_string = out.str();

	std::string ball_name = "ball" + scene_node_counter_string;
	scene_node_counter++;


	//--------------------
	// Visual - Ball
	//--------------------

	Ogre::Vector3 v3SpherePosition = Ogre::Vector3(1000, 1000, 1000);
	Ogre::Vector3 v3SphereScaleFactor = Ogre::Vector3(rScaleFactor, rScaleFactor, rScaleFactor);

	Ogre::Entity* objSphereEntity = m_pSceneMgr->createEntity(ball_name, "sphereCheck.mesh");
	worldObjectSceneNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(ball_name);
	worldObjectSceneNode->attachObject(objSphereEntity);

	worldObjectSceneNode->setPosition(v3SpherePosition);
	worldObjectSceneNode->setScale(v3SphereScaleFactor);
	objSphereEntity->setMaterialName("Ball/Snow");

	createRigidBody();

}

void Ball::update(double timeSinceLastFrame)
{
	updateWorldObjectVisual();
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

// ========================================
// From Parent Class, WorldObjectAbstract
// ========================================

void Ball::update()
{

}

void Ball::createSceneNode()
{
	std::cout << "Ball::createSceneNode()" << std::endl;
}

void Ball::createRigidBody()
{
	std::cout << "Ball::createRigidBody()" << std::endl;
}