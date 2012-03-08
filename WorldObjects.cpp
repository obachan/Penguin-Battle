#include "WorldObjects.hpp"


Ball::Ball(Ogre::SceneManager* m_pSceneMgr)
{

	const double start_pos_x = 10.5f;
	const double start_pos_y = 3.0f;
	const double start_pos_z = -25.0f;

	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(start_pos_x, start_pos_y, start_pos_z)));

    btScalar mass = 1;
    btVector3 ballInertia(0,0,0);

	ball_collision_shape = new btSphereShape(ball_radius);
    ball_collision_shape->calculateLocalInertia(mass,ballInertia);

    /*
	btSphereShape* ball_collision_shape_test = new btSphereShape(1);
    std::cout << "Hello World" << std::endl;
    std::cout << ball_collision_shape_test->getRadius() << std::endl;
	*/

    btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(mass,ballMotionState,ball_collision_shape,ballInertia);
	ballRigidBodyCI.m_restitution = 0.712f;
    ballRigidBody = new btRigidBody(ballRigidBodyCI);
	ballRigidBody->setLinearVelocity(btVector3(10,0,0));
	
	float ball_radius_node_conversion = ball_radius / 100.0f;
	createSphere(m_pSceneMgr, start_pos_x, start_pos_y, start_pos_z, ball_radius_node_conversion, "Awesome_Sphere");

}

Ball::~Ball()
{
	delete _objSphereEntity;
    delete ballMotionState;
    delete ballRigidBody;
    delete ball_collision_shape;


}

void Ball::createSphere(Ogre::SceneManager* m_pSceneMgr, Ogre::Real _rCoordX, Ogre::Real _rCoordY, Ogre::Real _rCoordZ, Ogre::Real _rScaleFactor, Ogre::String _strObjName)
{


	sphere_TranslateVector = Ogre::Vector3(0.02, 0.02, 0.02);

	Ogre::Vector3 _v3SpherePosition = Ogre::Vector3(_rCoordX, _rCoordY, _rCoordZ);
	Ogre::Vector3 _v3SphereScaleFactor = Ogre::Vector3(_rScaleFactor, _rScaleFactor, _rScaleFactor);

	_objSphereEntity = m_pSceneMgr->createEntity(_strObjName, "sphere.mesh");
	_objSphereNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(_strObjName);
	_objSphereNode->attachObject(_objSphereEntity);

	_objSphereNode->setPosition(_v3SpherePosition);
	_objSphereNode->setScale(_v3SphereScaleFactor);
	_objSphereEntity->setMaterialName("Examples/SphereMappedRustySteel");

}

void Ball::update(double timeSinceLastFrame){
	_objSphereNode->setPosition(getBallPosition());
}

Ogre::Vector3 Ball::getBallPosition()
{
	btTransform trans;
    ballRigidBody->getMotionState()->getWorldTransform(trans);
	return Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
}

Room::Room(Ogre::SceneManager* m_pSceneMgr)
{
	createRoom(m_pSceneMgr, room_width, room_length);    
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

void Room::createRoom(Ogre::SceneManager* m_pSceneMgr, int room_width, int room_length)
{

	//lPlane(Ogre::Vector3(1.0f, 0.0f, 0.0f), -300/2.0f),

	// Bottom Plane
	Ogre::Plane bottom_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        bottom_plane, room_width, room_length, 20, 20, true, 1, room_width/20, room_length/20, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_botNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* entGround = m_pSceneMgr->createEntity("GroundEntity", "ground");
    _botNode->attachObject(entGround);
    _botNode->setPosition(0, -room_width/2, 0);
	entGround->setMaterialName("Examples/Rockwall");

	// Top Plane
	Ogre::Plane top_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("top", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        top_plane, room_width, room_length, 20, 20, true, 1, room_width/20, room_length/20, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_topNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entTop = m_pSceneMgr->createEntity("TopEntity", "top");
    _topNode->attachObject(entTop);
	_topNode->rotate(Ogre::Vector3::UNIT_X,Ogre::Degree(180));
	_topNode->setPosition(0, room_width/2, 0);
	entTop->setMaterialName("Examples/Transparent");


	// Left Plane
	Ogre::Plane left_plane(Ogre::Vector3(-1.0f, 0.0f, 0.0f), -room_width/2);
	Ogre::MeshManager::getSingleton().createPlane("left", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, left_plane, room_length, room_width, 20, 20, true, 1, room_length/20, room_width/20, Ogre::Vector3::UNIT_Y);
	Ogre::Entity* entLeft = m_pSceneMgr->createEntity("LeftEntity", "left");
	m_pSceneMgr->getRootSceneNode()->createChildSceneNode("leftWall")->attachObject(entLeft);
	entLeft->setMaterialName("Examples/Transparent");

	/*Ogre::Plane left_plane(Ogre::Vector3(1,0,0), 0);
    Ogre::MeshManager::getSingleton().createPlane("left", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        left_plane, room_width, room_length, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
    Ogre::SceneNode *_leftNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entLeft = m_pSceneMgr->createEntity("LeftEntity", "left");
    _leftNode->attachObject(entLeft);
	//_leftNode->roll(Ogre::Degree(90));
	_leftNode->setPosition(room_width/2, 0, 0);
	entLeft->setMaterialName("Examples/Rockwall");*/

	// Right Plane
	/*Ogre::Plane right_plane(Ogre::Vector3(1,0,0), 0);
    Ogre::MeshManager::getSingleton().createPlane("right", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        right_plane, room_width, room_length, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
    Ogre::SceneNode *_rightNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entRight = m_pSceneMgr->createEntity("RightEntity", "right");
    _rightNode->attachObject(entRight);
	//_rightNode->roll(Ogre::Degree(-90));
	_rightNode->setPosition(-room_width/2, 0, 0);
	entRight->setMaterialName("Examples/Rockwall");*/

	Ogre::Plane right_plane(Ogre::Vector3(1.0f, 0.0f, 0.0f), -room_width/2);
	Ogre::MeshManager::getSingleton().createPlane("right", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, right_plane, room_length, room_width, 20, 20, true, 1, room_length/20, room_width/20, Ogre::Vector3::UNIT_Y);
	Ogre::Entity* entRight = m_pSceneMgr->createEntity("RightEntity", "right");
	m_pSceneMgr->getRootSceneNode()->createChildSceneNode("rightWall")->attachObject(entRight);
	entRight->setMaterialName("Examples/Transparent");

	// Back Plane
	Ogre::Plane back_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("back", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        back_plane, room_width, room_width, room_width, room_width, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_backNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entBack = m_pSceneMgr->createEntity("BackEntity", "back");
    _backNode->attachObject(entBack);
	_backNode->pitch(Ogre::Degree(90));
	_backNode->setPosition(0, 0, -room_length/2);
	entBack->setMaterialName("Examples/WaterStream");

	// Front Plane
	Ogre::Plane front_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("front", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        front_plane, room_width, room_width, room_width, room_width, true, 1, 1, 1, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_frontNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entFront = m_pSceneMgr->createEntity("FrontEntity", "front");
    _frontNode->attachObject(entFront);
	_frontNode->pitch(Ogre::Degree(-90));
	_frontNode->setPosition(0, 0, room_length/2);
	entFront->setMaterialName("Examples/WaterStream2");

	bottom = new btStaticPlaneShape(btVector3(0,1,0),-room_width/2);
	top = new btStaticPlaneShape(btVector3(0,-1,0),-room_width/2);
	left = new btStaticPlaneShape(btVector3(-1,0,0),-room_width/2);
	right = new btStaticPlaneShape(btVector3(1,0,0),-room_width/2);
	back = new btStaticPlaneShape(btVector3(0,0,-1),-room_length/2);
	front = new btStaticPlaneShape(btVector3(0,0,1),-room_length/2);
 
 
    btDefaultMotionState* bottomMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
    btRigidBody::btRigidBodyConstructionInfo
                bottomRigidBodyCI(0,bottomMotionState,bottom,btVector3(0,0,0));
	bottomRigidBodyCI.m_restitution = 1;
    bottomRigidBody = new btRigidBody(bottomRigidBodyCI);
    
	btDefaultMotionState* topMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));	
	btRigidBody::btRigidBodyConstructionInfo
                topRigidBodyCI(0,topMotionState,top,btVector3(0,0,0));
	topRigidBodyCI.m_restitution = 1;
	topRigidBody = new btRigidBody(topRigidBodyCI);

	btDefaultMotionState* leftMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo
                leftRigidBodyCI(0,leftMotionState,left,btVector3(0,0,0));
	leftRigidBodyCI.m_restitution = 1;
	leftRigidBody = new btRigidBody(leftRigidBodyCI);
    
	btDefaultMotionState* rightMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo
                rightRigidBodyCI(0,rightMotionState,right,btVector3(0,0,0));
	rightRigidBodyCI.m_restitution = 1;
	rightRigidBody = new btRigidBody(rightRigidBodyCI);
    
	btDefaultMotionState* backMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo
                backRigidBodyCI(0,backMotionState,back,btVector3(0,0,0));
	backRigidBodyCI.m_restitution = 1;
	backRigidBody = new btRigidBody(backRigidBodyCI);
    
	btDefaultMotionState* frontMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
	btRigidBody::btRigidBodyConstructionInfo
                frontRigidBodyCI(0,frontMotionState,front,btVector3(0,0,0));
	frontRigidBodyCI.m_restitution = 1;
	frontRigidBody = new btRigidBody(frontRigidBodyCI);
}

Penguin::Penguin(Ogre::SceneManager* m_pSceneMgr)
{

	penguin_position = new btTransform(btQuaternion(0,0,0,1),btVector3(0, 0, 0));
	penguin_velocity = Ogre::Vector3(0, 0, 0);
	in_air = true;

	penguinMotionState = new btDefaultMotionState(*penguin_position);

    btScalar mass = 0;
    btVector3 penguinInertia(0,0,0);

	//penguin_collision_shape = new btBox2dShape(btVector3(10, 10, 0.5));

	const float penguin_half_length = penguin_length / 2;
	//penguin_collision_shape = new btBoxShape(btVector3(penguin_half_length, penguin_half_length, penguin_half_length));
	penguin_collision_shape = new btSphereShape(penguin_half_length);
    penguin_collision_shape->calculateLocalInertia(mass,penguinInertia);
    /*
	btSphereShape* ball_collision_shape_test = new btSphereShape(1);
    std::cout << "Hello World" << std::endl;
    std::cout << ball_collision_shape_test->getRadius() << std::endl;
	*/

    btRigidBody::btRigidBodyConstructionInfo penguinRigidBodyCI(mass,penguinMotionState,penguin_collision_shape,penguinInertia);
	penguinRigidBodyCI.m_restitution = 1;
	
    penguinRigidBody = new btRigidBody(penguinRigidBodyCI);

    // Disable Gravity because this object will be controlled by the player
    penguinRigidBody->setGravity(btVector3(0,0,0));
	penguinRigidBody->setCollisionFlags( penguinRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	penguinRigidBody->setActivationState(DISABLE_DEACTIVATION);
	//penguinRigidBody->setCollisionFlags(2);

	//penguinRigidBody->setLinearVelocity(btVector3(10,0,0));



	createPenguin(m_pSceneMgr);    
}

Penguin::~Penguin()
{
	delete penguinNode;

	delete penguinRigidBody->getMotionState();
	delete penguinRigidBody;

	delete penguin_collision_shape;
}

void Penguin::createPenguin(Ogre::SceneManager* m_pSceneMgr)
{

	btTransform trans;
    penguinRigidBody->getMotionState()->getWorldTransform(trans);
	Ogre::Vector3 vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

	float penguin_scale = penguin_length / 50.0;

	//Ogre::Entity* penguinEntity = m_pSceneMgr->createEntity("penguin", "cube.mesh");
	penguinEntity = m_pSceneMgr->createEntity("penguin", "penguin.mesh");
	penguinNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("penguin");
	penguinNode->attachObject(penguinEntity);
	penguinNode->setScale(penguin_scale, penguin_scale, penguin_scale);
	penguinNode->setPosition(vec[0], vec[1], vec[2]);
	penguinEntity->setMaterialName("Penguin");
	penguinNode->yaw( Ogre::Degree( -180 ) );
	penguin_direction = Ogre::Vector3(0,0,-1);
	previous_direction = Ogre::Vector3(0,0,-1);

	/*Ogre::Camera* camera = m_pSceneMgr->getCamera("Camera");
	camera->setPosition(penguinNode->getPosition());
	camera->setDirection(penguin_direction);*/
}

void Penguin::update(double timeSinceLastFrame, MyController* controller, Ogre::Camera* camera)
{

	if(timeSinceLastFrame > 0.4f)
		timeSinceLastFrame = 0.4f;

	btTransform trans;
    	penguinRigidBody->getMotionState()->getWorldTransform(trans);
	Ogre::Vector3 vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

	Ogre::Quaternion quat = Ogre::Quaternion(1, 0, 0, 0);
	Ogre::Vector3 cameraPosition;
	Ogre::Vector3 cameraDirection;

	// Account for Gravity
	if(in_air){
		penguin_velocity[1] = penguin_velocity[1] + world_grav * timeSinceLastFrame;
		// if penguin is falling too fast
		if(penguin_velocity[1] < max_fall_vel)
			penguin_velocity[1] = max_fall_vel;
		vec[1] =  vec[1] + penguin_velocity[1] * timeSinceLastFrame + (0.5) * world_grav * timeSinceLastFrame * timeSinceLastFrame;
	}

	// Take in user input and handle bounds
	if(controller->left_control_down == true){
		//std::cout << "left" << std::endl;
		//vec[0] = vec[0] + (-move_vel) * timeSinceLastFrame;
		quat = Ogre::Quaternion(Ogre::Radian(Ogre::Degree(rotation_speed*timeSinceLastFrame)), Ogre::Vector3::UNIT_Y);
		penguinNode->rotate(quat);
		penguin_direction = penguinNode->getOrientation() * Ogre::Vector3(0,0,1);
		penguin_direction.y = 0;
		penguin_direction.normalise();
		previous_direction = penguin_direction;
		cameraDirection = penguin_direction;
		//cameraDirection.y = -5;
		camera->setDirection(cameraDirection);
	}

	if(controller->right_control_down == true){
		//std::cout << "right" << std::endl;
		//vec[0] = vec[0] + (move_vel) * timeSinceLastFrame;
		quat = Ogre::Quaternion(Ogre::Radian(Ogre::Degree(rotation_speed*-timeSinceLastFrame)), Ogre::Vector3::UNIT_Y);
		penguinNode->rotate(quat);
		penguin_direction = penguinNode->getOrientation() * Ogre::Vector3(0,0,1);
		penguin_direction.y = 0;
		penguin_direction.normalise();
		previous_direction = penguin_direction;
		cameraDirection = penguin_direction;
		//cameraDirection.y = -5;
		camera->setDirection(cameraDirection);
	}

	if(controller->up_control_down == true){
		vec[1] = vec[1] + (move_vel) * timeSinceLastFrame;
	}

	if(controller->bottom_control_down == true){
		vec[1] = vec[1] + (-move_vel) * timeSinceLastFrame;
	}

	if(controller->forward_control_down == true){
		//std::cout << "forward" << std::endl;
		//vec[2] = vec[2] + (-move_vel) * timeSinceLastFrame;
		vec = vec + (penguin_direction * move_vel * timeSinceLastFrame);
	}

	if(controller->backward_control_down == true){
		//std::cout << "backward" << std::endl;
		//vec[2] = vec[2] + (move_vel) * timeSinceLastFrame;
		vec = vec + (penguin_direction * -move_vel * timeSinceLastFrame);
	}

	if(controller->jump_control_down == true){
		controller->jump_control_down = false;
		if(!in_air){
			in_air = true;
			penguin_velocity[1] = jump_vel;
		}
	}

	// Handle Wall and Ceiling Collisions

	if(vec[0] < -room_width/2 + penguin_length/2)
		vec[0] = -room_width/2 + penguin_length/2;

	if(vec[0] > room_width/2 - penguin_length/2)
		vec[0] = room_width/2 - penguin_length/2;


	if(vec[1] > room_width/2 - penguin_length/2)
		vec[1] = room_width/2 - penguin_length/2;


	if(vec[2] < -room_length/2 + penguin_length/2)
		vec[2] = -room_length/2 + penguin_length/2;


	if(vec[2] > room_length/2 - penguin_length/2)
		vec[2] = room_length/2 - penguin_length/2;


	// If penguin touches the ground, change the penguin to ground state
	if(vec[1] < -room_width/2 + penguin_length/2){
		in_air = false;
		vec[1] = -room_width/2 + penguin_length/2;
		float tolerance = abs(vec[1] - (-room_width/2 + penguin_length/2));
		if(tolerance < 0.01f){
			penguin_velocity[1]  = 0;
		}	
	}
	//std::cout << vec[0] << " " << vec[1] << " " << vec[2] << std::endl;

	
	if(controller->left_control_down == true ||
		controller->right_control_down == true ||
		controller->up_control_down == true ||
		controller->bottom_control_down == true ||
		controller->forward_control_down == true ||
		controller->backward_control_down == true ||
		in_air)
	{
		mAnimationState = penguinEntity->getAnimationState("amuse");
        mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true);

        float time_scale = timeSinceLastFrame / 4.0f; // Scale the time back so it doesn't animate as fast
		mAnimationState->addTime(time_scale);
	}
	

	//penguin_direction = Ogre::Vector3(vec[0], vec[1], vec[2]) - penguinNode->getPosition();
	//penguin_direction.y = 0;
	//penguin_direction.normalise();

	
	trans.setOrigin(btVector3(vec[0], vec[1], vec[2]));
	penguinMotionState->setWorldTransform(trans);
	penguinNode->setPosition(vec[0], vec[1], vec[2]);

	cameraPosition= vec - (20*penguin_direction);
	cameraPosition.y += 7;
	camera->setPosition(cameraPosition);
	
	/*if(penguin_direction != previous_direction)
	{
	std::cout << penguin_direction << std::endl;
	std::cout << previous_direction << std::endl;
	}
	
        if ((1.0f + previous_direction.dotProduct(penguin_direction)) < 0.0001f) 
        {
            penguinNode->yaw(Ogre::Degree(180));
        }
        else
        {
            //quat = previous_direction.getRotationTo(penguin_direction);
		//std::cout << quat << std::endl;
            penguinNode->rotate(quat);
        }

	if (penguin_direction != Ogre::Vector3::ZERO)
	{
		previous_direction = Ogre::Vector3(penguin_direction.x, 0, penguin_direction.z);
	}*/

	/*Ogre::Vector3 cameraPosition = vec-(15*penguin_direction);
	cameraPosition.y += 10;
	camera->setPosition(cameraPosition);
	camera->setDirection(penguin_direction);*/

	/*
	penguin_direction.normalise();
	Ogre::Vector3 src = penguinNode->getOrientation()*penguin_direction;

	
	
	penguin_direction.normalise();
        Ogre::Quaternion quat = src.getRotationTo(penguin_direction);
        camera->setPosition(vec[0], vec[1], vec[2]);
	camera->rotate(quat);*/
}


Paddle::Paddle(Ogre::SceneManager* m_pSceneMgr)
{

	paddle_position = new btTransform(btQuaternion(0,0,0,1),btVector3(10, 0, -25));
	paddle_velocity = Ogre::Vector3(0, 0, 0);
	in_air = true;

	paddleMotionState = new btDefaultMotionState(*paddle_position);

    btScalar mass = 0;
    btVector3 paddleInertia(0,0,0);

	//paddle_collision_shape = new btBox2dShape(btVector3(10, 10, 0.5));

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
	//paddleRigidBody->setCollisionFlags(2);

	//paddleRigidBody->setLinearVelocity(btVector3(10,0,0));

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
	btTransform trans;
    paddleRigidBody->getMotionState()->getWorldTransform(trans);
	Ogre::Vector3 vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());


	float paddle_scale = paddle_length / 100.0;

	paddleEntity = m_pSceneMgr->createEntity("paddle", "cube.mesh");
	//paddleEntity = m_pSceneMgr->createEntity("paddle", "penguin.mesh");
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

	
	if(controller->left_control_down == true ||
		controller->right_control_down == true ||
		controller->up_control_down == true ||
		controller->bottom_control_down == true ||
		controller->forward_control_down == true ||
		controller->backward_control_down == true)
	{
		mAnimationState = paddleEntity->getAnimationState("amuse");
        mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true);

        float time_scale = timeSinceLastFrame / 4.0f; // Scale the time back so it doesn't animate as fast
		mAnimationState->addTime(time_scale);
	}
	

	trans.setOrigin(btVector3(vec[0], vec[1], vec[2]));
	paddleMotionState->setWorldTransform(trans);
	paddleNode->setPosition(vec[0], vec[1], vec[2]);
}

void Paddle::moveLeft(double timeSinceLastFrame)
{
	//std::cout << "Left" << std::endl;
	//btVector3 vec = paddleRigidBody->getLinearVelocity();
	//paddleRigidBody->setLinearVelocity(btVector3(-move_vel,vec[1],vec[2]));
}

void Paddle::moveRight(double timeSinceLastFrame)
{
	//btVector3 vec = paddleRigidBody->getLinearVelocity();
	//paddleRigidBody->setLinearVelocity(btVector3(move_vel,vec[1],vec[2]));
}

void Paddle::moveUp(double timeSinceLastFrame)
{
	//btVector3 vec = paddleRigidBody->getLinearVelocity();
	//paddleRigidBody->setLinearVelocity(btVector3(vec[0],move_vel,vec[2]));
}

void Paddle::moveDown(double timeSinceLastFrame)
{
	//btVector3 vec = paddleRigidBody->getLinearVelocity();
	//paddleRigidBody->setLinearVelocity(btVector3(vec[0],-move_vel,vec[2]));
}

void Paddle::moveForward(double timeSinceLastFrame)
{
	//btVector3 vec = paddleRigidBody->getLinearVelocity();
	//paddleRigidBody->setLinearVelocity(btVector3(vec[0], vec[1], -move_vel));
}

void Paddle::moveBackward(double timeSinceLastFrame)
{
	//btVector3 vec = paddleRigidBody->getLinearVelocity();
	//paddleRigidBody->setLinearVelocity(btVector3(vec[0], vec[1], move_vel));
}

void Paddle::moveStop(double timeSinceLastFrame)
{
	//paddleRigidBody->setLinearVelocity(btVector3(0,0,0));
}

