#include "WorldObjects.hpp"

#include <iostream>

Room::Room(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics, bool do_physics)
{
	createRoom(m_pSceneMgr, room_width, room_length);
	if(do_physics)
		attachToDynamicWorld(physics);
}

void Room::createRoom(Ogre::SceneManager* m_pSceneMgr, int room_width, int room_length)
{

	const float wall_restitution = 1.0;

	//---------------
	// Bottom Plane
	//---------------

	// Visuals
	Ogre::Plane bottom_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        bottom_plane, room_width, room_length, 20, 20, true, 1, room_width/20, room_length/20, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *botNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* entGround = m_pSceneMgr->createEntity("GroundEntity", "ground");
    botNode->attachObject(entGround);
    botNode->setPosition(0, -room_width/2, 0);
	entGround->setMaterialName("Examples/Rockwall");

	// Physics
	bottom = new btStaticPlaneShape(btVector3(0,1,0),-room_width/2);
	btDefaultMotionState* bottomMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
    btRigidBody::btRigidBodyConstructionInfo bottomRigidBodyCI(0,bottomMotionState,bottom,btVector3(0,0,0));
	bottomRigidBodyCI.m_restitution = wall_restitution;
    bottomRigidBody = new btRigidBody(bottomRigidBodyCI);

	//---------------
	// Top Plane
	//---------------

	// Visuals
	Ogre::Plane top_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("top", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        top_plane, room_width, room_length, 20, 20, true, 1, room_width/20, room_length/20, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *topNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entTop = m_pSceneMgr->createEntity("TopEntity", "top");
    topNode->attachObject(entTop);
	topNode->rotate(Ogre::Vector3::UNIT_X,Ogre::Degree(180));
	topNode->setPosition(0, room_width/2, 0);
	entTop->setMaterialName("Examples/Transparent");

	// Physics
	top = new btStaticPlaneShape(btVector3(0,-1,0),-room_width/2);
	btDefaultMotionState* topMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));	
	btRigidBody::btRigidBodyConstructionInfo topRigidBodyCI(0,topMotionState,top,btVector3(0,0,0));
	topRigidBodyCI.m_restitution = wall_restitution;
	topRigidBody = new btRigidBody(topRigidBodyCI);

	//---------------
	// Left Plane
	//---------------

	// Visuals
	Ogre::Plane left_plane(Ogre::Vector3(-1.0f, 0.0f, 0.0f), -room_width/2);
	Ogre::MeshManager::getSingleton().createPlane("left", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, left_plane, room_length, room_width, 20, 20, true, 1, room_length/20, room_width/20, Ogre::Vector3::UNIT_Y);
	Ogre::Entity* entLeft = m_pSceneMgr->createEntity("LeftEntity", "left");
	m_pSceneMgr->getRootSceneNode()->createChildSceneNode("leftWall")->attachObject(entLeft);
	entLeft->setMaterialName("Examples/Transparent");

	// Physics
	left = new btStaticPlaneShape(btVector3(-1,0,0),-room_width/2);
	btDefaultMotionState* leftMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo leftRigidBodyCI(0,leftMotionState,left,btVector3(0,0,0));
	leftRigidBodyCI.m_restitution = wall_restitution;
	leftRigidBody = new btRigidBody(leftRigidBodyCI);

	//---------------
	// Right Plane
	//---------------

	// Visuals
	Ogre::Plane right_plane(Ogre::Vector3(1.0f, 0.0f, 0.0f), -room_width/2);
	Ogre::MeshManager::getSingleton().createPlane("right", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, right_plane, room_length, room_width, 20, 20, true, 1, room_length/20, room_width/20, Ogre::Vector3::UNIT_Y);
	Ogre::Entity* entRight = m_pSceneMgr->createEntity("RightEntity", "right");
	m_pSceneMgr->getRootSceneNode()->createChildSceneNode("rightWall")->attachObject(entRight);
	entRight->setMaterialName("Examples/Transparent");

	// Physics
	right = new btStaticPlaneShape(btVector3(1,0,0),-room_width/2);
	btDefaultMotionState* rightMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo rightRigidBodyCI(0,rightMotionState,right,btVector3(0,0,0));
	rightRigidBodyCI.m_restitution = wall_restitution;
	rightRigidBody = new btRigidBody(rightRigidBodyCI);

	//---------------
	// Back Plane
	//---------------

	// Visuals
	Ogre::Plane back_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("back", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        back_plane, room_width, room_width, room_width, room_width, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *backNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entBack = m_pSceneMgr->createEntity("BackEntity", "back");
    backNode->attachObject(entBack);
	backNode->pitch(Ogre::Degree(90));
	backNode->setPosition(0, 0, -room_length/2);
	entBack->setMaterialName("Examples/Transparent");
	//entBack->setMaterialName("Examples/WaterStream");

	// Physics
	back = new btStaticPlaneShape(btVector3(0,0,-1),-room_length/2);
	btDefaultMotionState* backMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo backRigidBodyCI(0,backMotionState,back,btVector3(0,0,0));
	backRigidBodyCI.m_restitution = wall_restitution;
	backRigidBody = new btRigidBody(backRigidBodyCI);

	//---------------
	// Front Plane
	//---------------

	// Visuals
	Ogre::Plane front_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("front", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        front_plane, room_width, room_width, room_width, room_width, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *frontNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entFront = m_pSceneMgr->createEntity("FrontEntity", "front");
    frontNode->attachObject(entFront);
	frontNode->pitch(Ogre::Degree(-90));
	frontNode->setPosition(0, 0, room_length/2);
	entFront->setMaterialName("Examples/WaterStream2");

	// Physics
	front = new btStaticPlaneShape(btVector3(0,0,1),-room_length/2);
	btDefaultMotionState* frontMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo frontRigidBodyCI(0,frontMotionState,front,btVector3(0,0,0));
	frontRigidBodyCI.m_restitution = wall_restitution;
	frontRigidBody = new btRigidBody(frontRigidBodyCI);
}

void Room::attachToDynamicWorld(PhysicsWrapper* physics)
{
	physics->add_object_to_dynamicWorld(frontRigidBody);
	physics->add_object_to_dynamicWorld(backRigidBody);
	physics->add_object_to_dynamicWorld(rightRigidBody);
	physics->add_object_to_dynamicWorld(leftRigidBody);
	physics->add_object_to_dynamicWorld(topRigidBody);
	physics->add_object_to_dynamicWorld(bottomRigidBody);    

}

Room::~Room()
{
	delete bottomRigidBody->getMotionState();
    delete bottomRigidBody;
	
    delete topRigidBody->getMotionState();
    delete topRigidBody;
	
    delete leftRigidBody->getMotionState();
    delete leftRigidBody;
	
    delete rightRigidBody->getMotionState();
    delete rightRigidBody;
	
    delete backRigidBody->getMotionState();
    delete backRigidBody;
	
    delete frontRigidBody->getMotionState();
    delete frontRigidBody;
 
	delete bottom;
	delete top;
	delete left;
	delete right;
	delete back;
	delete front;
}

Paddle::Paddle(Ogre::SceneManager* m_pSceneMgr)
{
	createPaddle(m_pSceneMgr);    
}

Paddle::~Paddle()
{
	delete paddleNode;

	delete paddleRigidBody->getMotionState();
	delete paddleRigidBody;

	delete paddle_collision_shape;
}

void Paddle::createPaddle(Ogre::SceneManager* m_pSceneMgr)
{
	//--------------------
	// Physics - Paddle
	//--------------------

	paddle_position = new btTransform(btQuaternion(0,0,0,1),btVector3(10, 0, -25));
	paddle_velocity = Ogre::Vector3(0, 0, 0);
	in_air = true;

	paddleMotionState = new btDefaultMotionState(*paddle_position);

    btScalar mass = 0;
    btVector3 paddleInertia(0,0,0);
    float paddle_half_length = paddle_length / 2;

	paddle_collision_shape = new btBoxShape(btVector3(paddle_half_length, paddle_half_length, paddle_half_length));
    paddle_collision_shape->calculateLocalInertia(mass,paddleInertia);
    
    btRigidBody::btRigidBodyConstructionInfo paddleRigidBodyCI(mass,paddleMotionState,paddle_collision_shape,paddleInertia);
	paddleRigidBodyCI.m_restitution = 0.712f;
    paddleRigidBody = new btRigidBody(paddleRigidBodyCI);

    // Disable Gravity because this object will be controlled by the player
    paddleRigidBody->setGravity(btVector3(0,0,0));
	paddleRigidBody->setCollisionFlags( paddleRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	paddleRigidBody->setActivationState(DISABLE_DEACTIVATION);


	//--------------------
	// Visuals - Paddle
	//--------------------

	btTransform trans;
    paddleRigidBody->getMotionState()->getWorldTransform(trans);
	Ogre::Vector3 vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());


	float paddle_scale = paddle_length / 100.0;

	paddleEntity = m_pSceneMgr->createEntity("paddle", "cube.mesh");
	paddleNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("paddle");
	paddleNode->attachObject(paddleEntity);
	paddleNode->setScale(paddle_scale, paddle_scale, paddle_scale);
	paddleNode->setPosition(vec[0] ,vec[1], vec[2]);
	paddleEntity->setMaterialName("WoodPallet");
}

void Paddle::update(double timeSinceLastFrame, MyController* controller)
{

	if(timeSinceLastFrame > 0.4f)
		timeSinceLastFrame = 0.4f;

	btTransform trans;
    paddleRigidBody->getMotionState()->getWorldTransform(trans);
	Ogre::Vector3 vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

	// Account for Gravity
	if(in_air){
		paddle_velocity[1] = paddle_velocity[1] + world_grav * timeSinceLastFrame;
		// if paddle is falling too fast
		if(paddle_velocity[1] < max_fall_vel)
			paddle_velocity[1] = max_fall_vel;
		vec[1] =  vec[1] + paddle_velocity[1] * timeSinceLastFrame + (0.5) * world_grav * timeSinceLastFrame * timeSinceLastFrame;
	}

	// Take in user input and handle bounds
	if(controller->left_control_down == true){
		//std::cout << "left" << std::endl;
		vec[0] = vec[0] + (-move_vel) * timeSinceLastFrame;
		if(vec[0] < -room_width/2 + paddle_length/2)
			vec[0] = -room_width/2 + paddle_length/2;
	}

	if(controller->right_control_down == true){
		//std::cout << "right" << std::endl;
		vec[0] = vec[0] + (move_vel) * timeSinceLastFrame;
		if(vec[0] > room_width/2 - paddle_length/2)
			vec[0] = room_width/2 - paddle_length/2;
	}

	if(controller->up_control_down == true){
		vec[1] = vec[1] + (move_vel) * timeSinceLastFrame;
		if(vec[1] > room_width/2 - paddle_length/2)
			vec[1] = room_width/2 - paddle_length/2;
	}

	if(controller->bottom_control_down == true){
		vec[1] = vec[1] + (-move_vel) * timeSinceLastFrame;
		if(vec[1] < -room_width/2 + paddle_length/2)
			vec[1] = -room_width/2 + paddle_length/2;
	}

	if(controller->forward_control_down == true){
		//std::cout << "forward" << std::endl;
		vec[2] = vec[2] + (-move_vel) * timeSinceLastFrame;
		if(vec[2] < -room_length/2 + paddle_length/2)
			vec[2] = -room_length/2 + paddle_length/2;
	}

	if(controller->backward_control_down == true){
		//std::cout << "backward" << std::endl;
		vec[2] = vec[2] + (move_vel) * timeSinceLastFrame;
		if(vec[2] > room_length/2 - paddle_length/2)
			vec[2] = room_length/2 - paddle_length/2;
	}

	if(controller->jump_control_down == true){
		controller->jump_control_down = false;
		if(!in_air){
			in_air = true;
			paddle_velocity[1] = jump_vel;
		}
	}

	// If paddle touches the ground, change the paddle to ground state
	if(vec[1] < -room_width/2 + paddle_length/2){
		vec[1] = -room_width/2 + paddle_length/2;
		float tolerance = abs(vec[1] - (-room_width/2 + paddle_length/2));
		if(tolerance < 0.01f){

			in_air = false;
			paddle_velocity[1]  = 0;
		}	
	}
	//std::cout << vec[0] << " " << vec[1] << " " << vec[2] << std::endl;

	trans.setOrigin(btVector3(vec[0], vec[1], vec[2]));
	paddleMotionState->setWorldTransform(trans);
	paddleNode->setPosition(vec[0], vec[1], vec[2]);
}


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


