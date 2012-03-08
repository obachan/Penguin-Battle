#include "WorldObjects.hpp"


Ball::Ball(Ogre::SceneManager* m_pSceneMgr)
{

	const double start_pos_x = 10.5f;
	const double start_pos_y = 3.0f;
	const double start_pos_z = -25.0f;

	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(start_pos_x, start_pos_y, start_pos_z)));

    btScalar mass = ball_mass;
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
	_objSphereEntity->setMaterialName("Examples/PinkBall");

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

	// Right Plane
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

Goal::Goal(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics)
{
	float goal_to_edge_wall_offset = 30.0;

	createGoal(m_pSceneMgr, -room_length/2 + goal_to_edge_wall_offset);
	attachToDynamicWorld(physics);
}

void Goal::createGoal(Ogre::SceneManager* m_pSceneMgr, double translate_z)
{
	const float cube_length = 100;

	const float goal_length = 75;
	const float goal_height = 50;

	//dimensions for the side blocks
	const float goal_left_width = 2;
	const float goal_left_height = goal_height;
	const float goal_left_depth = 30;

	float goal_left_width_scale = goal_left_width/cube_length;
	float goal_left_height_scale = goal_left_height/cube_length;
	float goal_left_depth_scale = goal_left_depth/cube_length;

	//dimensions for the back block
	const float goal_back_width = goal_length + 2 * goal_left_width;
	const float goal_back_height = goal_height;
	const float goal_back_depth = goal_left_width;

	float goal_back_width_scale = goal_back_width/cube_length;
	float goal_back_height_scale = goal_back_height/cube_length;
	float goal_back_depth_scale = goal_back_depth/cube_length;

	//dimensions for the top block
	const float goal_top_width = goal_length + 2 * goal_left_width;
	const float goal_top_height = goal_left_width;
	const float goal_top_depth = goal_left_depth + goal_back_depth;

	float goal_top_width_scale = goal_top_width/cube_length;
	float goal_top_height_scale = goal_top_height/cube_length;
	float goal_top_depth_scale = goal_top_depth/cube_length;

	//dimensions for the front block
	const float goal_front_width = goal_length;
	const float goal_front_height = goal_height;
	const float goal_front_depth = 1;

	float goal_front_width_scale = goal_front_width/cube_length;
	float goal_front_height_scale = goal_front_height/cube_length;
	float goal_front_depth_scale = goal_front_depth/cube_length;



	btTransform trans;
	Ogre::Vector3 vec;
	//--------------------
	// Physics - Goal Left
	//--------------------

	btDefaultMotionState* goalLeftMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(-goal_length/2, -room_width/2 + goal_left_height/2, 0 + translate_z)));

    btScalar massLeft = 100;
    btVector3 goalLeftInertia(0,0,0);

	goalLeftShape = new btBoxShape(btVector3(goal_left_width/2, goal_left_height/2, goal_left_depth/2));
    goalLeftShape->calculateLocalInertia(massLeft,goalLeftInertia);

    btRigidBody::btRigidBodyConstructionInfo goalLeftRigidBodyCI(massLeft, goalLeftMotionState,goalLeftShape,goalLeftInertia);
	goalLeftRigidBodyCI.m_restitution = 0.712f;
	
    goalLeftBody = new btRigidBody(goalLeftRigidBodyCI);

    goalLeftBody->setLinearFactor(btVector3(0,0,0));
    goalLeftBody->setAngularFactor(btVector3(0,0,0));

    //--------------------
	// Visuals - Goal Right
	//--------------------
    
    // Get the coordinates from the bullet physics model
    goalLeftBody->getMotionState()->getWorldTransform(trans);
	vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

	goalLeftEntity = m_pSceneMgr->createEntity("goalLeftBound", "cube.mesh");
	goalLeftNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("goalLeftBound");
	goalLeftNode->attachObject(goalLeftEntity);
	goalLeftNode->setScale(goal_left_width_scale, goal_left_height_scale, goal_left_depth_scale);
	goalLeftNode->setPosition(vec[0], vec[1], vec[2]);
	goalLeftEntity->setMaterialName("WoodPallet");

	//--------------------
	// Physics - Goal Right
	//--------------------

	btDefaultMotionState* goalRightMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(goal_length/2, -room_width/2 + goal_left_height/2, 0 + translate_z)));

    btScalar massRight = 100;
    btVector3 goalRightInertia(0,0,0);

    //Goal Right is symmetrical to Goal Left
	goalRightShape = new btBoxShape(btVector3(goal_left_width/2, goal_left_height/2, goal_left_depth/2));
    goalRightShape->calculateLocalInertia(massRight,goalRightInertia);

    btRigidBody::btRigidBodyConstructionInfo goalRightRigidBodyCI(massRight, goalRightMotionState,goalRightShape,goalRightInertia);
	goalRightRigidBodyCI.m_restitution = 0.712f;
	
    goalRightBody = new btRigidBody(goalRightRigidBodyCI);

    goalRightBody->setLinearFactor(btVector3(0,0,0));
    goalRightBody->setAngularFactor(btVector3(0,0,0));


    //--------------------
	// Visuals - Goal Right
	//--------------------
    goalRightBody->getMotionState()->getWorldTransform(trans);
	vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

	goalRightEntity = m_pSceneMgr->createEntity("goalRightBound", "cube.mesh");
	goalRightNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("goalRightBound");
	goalRightNode->attachObject(goalRightEntity);
	goalRightNode->setScale(goal_left_width_scale, goal_left_height_scale, goal_left_depth_scale);
	goalRightNode->setPosition(vec[0], vec[1], vec[2]);
	goalRightEntity->setMaterialName("WoodPallet");


	//--------------------
	// Physics - Goal Back
	//--------------------

	btDefaultMotionState* goalBackMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0, -room_width/2 + goal_left_height/2, -(goal_left_depth/2 + goal_back_depth/2)  + translate_z)));

    btScalar massBack = 100;
    btVector3 goalBackInertia(0,0,0);

	goalBackShape = new btBoxShape(btVector3(goal_back_width/2, goal_back_height/2, goal_back_depth/2));
    goalBackShape->calculateLocalInertia(massBack,goalBackInertia);

    btRigidBody::btRigidBodyConstructionInfo goalBackRigidBodyCI(massBack, goalBackMotionState,goalBackShape,goalBackInertia);
	goalBackRigidBodyCI.m_restitution = 0.712f;
	
    goalBackBody = new btRigidBody(goalBackRigidBodyCI);

    goalBackBody->setLinearFactor(btVector3(0,0,0));
    goalBackBody->setAngularFactor(btVector3(0,0,0));

	//--------------------
	// Visuals - Goal Back
	//--------------------

	goalBackBody->getMotionState()->getWorldTransform(trans);
	vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

	goalBackEntity = m_pSceneMgr->createEntity("goalBackBound", "cube.mesh");
	goalBackNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("goalBackBound");
	goalBackNode->attachObject(goalBackEntity);
	goalBackNode->setScale(goal_back_width_scale, goal_back_height_scale, goal_back_depth_scale);
	goalBackNode->setPosition(vec[0], vec[1], vec[2]);
	goalBackEntity->setMaterialName("WoodPallet");


	
	//--------------------
	// Physics - Goal Top
	//--------------------

	btDefaultMotionState* goalTopMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0, -room_width/2 + goal_height + goal_top_height/2, 0 + translate_z)));

    btScalar massTop = 100;
    btVector3 goalTopInertia(0,0,0);

	goalTopShape = new btBoxShape(btVector3(goal_back_width/2, goal_back_height/2, goal_back_depth/2));
    goalTopShape->calculateLocalInertia(massTop,goalTopInertia);

    btRigidBody::btRigidBodyConstructionInfo goalTopRigidBodyCI(massTop, goalTopMotionState,goalTopShape,goalTopInertia);
	goalTopRigidBodyCI.m_restitution = 0.712f;
	
    goalTopBody = new btRigidBody(goalTopRigidBodyCI);

    goalTopBody->setLinearFactor(btVector3(0,0,0));
    goalTopBody->setAngularFactor(btVector3(0,0,0));

    //--------------------
	// Visuals - Goal Top
	//--------------------

	goalTopBody->getMotionState()->getWorldTransform(trans);
	vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

	goalTopEntity = m_pSceneMgr->createEntity("goalTopBound", "cube.mesh");
	goalTopNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("goalTopBound");
	goalTopNode->attachObject(goalTopEntity);
	goalTopNode->setScale(goal_top_width_scale, goal_top_height_scale, goal_top_depth_scale);
	goalTopNode->setPosition(vec[0], vec[1], vec[2]);
	goalTopEntity->setMaterialName("WoodPallet");

	//--------------------
	// Visuals - Goal Front
	//--------------------

	goalFrontEntity = m_pSceneMgr->createEntity("goalFrontBound", "cube.mesh");
	goalFrontNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("goalFrontBound");
	goalFrontNode->attachObject(goalFrontEntity);
	goalFrontNode->setScale(goal_front_width_scale, goal_back_height_scale, goal_back_depth_scale);
	goalFrontNode->setPosition(0, -room_width/2 + goal_back_height/2, goal_left_depth/2 + goal_back_depth/2 + translate_z);
	goalFrontEntity->setMaterialName("Examples/WaterStream");
	
}

void Goal::attachToDynamicWorld(PhysicsWrapper* physics){

	physics->add_object_to_dynamicWorld(goalLeftBody);
	physics->add_object_to_dynamicWorld(goalRightBody);
	physics->add_object_to_dynamicWorld(goalBackBody);
	physics->add_object_to_dynamicWorld(goalTopBody);  
}

Goal::~Goal()
{

}

void Goal::update()
{

	btTransform trans;
	Ogre::Vector3 vec;

    goalLeftBody->getMotionState()->getWorldTransform(trans);
	vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	goalLeftNode->setPosition(vec[0], vec[1], vec[2]);

	goalRightBody->getMotionState()->getWorldTransform(trans);
	vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	goalRightNode->setPosition(vec[0], vec[1], vec[2]);

	goalBackBody->getMotionState()->getWorldTransform(trans);
	vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	goalBackNode->setPosition(vec[0], vec[1], vec[2]);

	goalTopBody->getMotionState()->getWorldTransform(trans);
	vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	goalTopNode->setPosition(vec[0], vec[1], vec[2]);
}

void Goal::translate(double translate_x, double translate_y, double translate_z)
{
	btTransform trans;
	Ogre::Vector3 vec;

	// Translate Back Block
    goalBackBody->getMotionState()->getWorldTransform(trans);
	vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	trans.setOrigin(btVector3(vec[0] + translate_x, vec[1] + translate_y, vec[2] + translate_z));
	goalBackBody->getMotionState()->setWorldTransform(trans);

	// Translate Left Block
    goalLeftBody->getMotionState()->getWorldTransform(trans);
	vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	trans.setOrigin(btVector3(vec[0] + translate_x, vec[1] + translate_y, vec[2] + translate_z));
	goalLeftBody->getMotionState()->setWorldTransform(trans);

	// Translate Right Block
    goalRightBody->getMotionState()->getWorldTransform(trans);
	vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	trans.setOrigin(btVector3(vec[0] + translate_x, vec[1] + translate_y, vec[2] + translate_z));
	goalRightBody->getMotionState()->setWorldTransform(trans);

	// Translate Top Block
    goalTopBody->getMotionState()->getWorldTransform(trans);
	vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
	trans.setOrigin(btVector3(vec[0] + translate_x, vec[1] + translate_y, vec[2] + translate_z));
	goalTopBody->getMotionState()->setWorldTransform(trans);

	// Syncs the Visuals with the Physics
	update();

	// Move the visual goal post
	vec = goalFrontNode->getPosition();
	goalFrontNode->setPosition(vec[0] + translate_x, vec[1] + translate_y, vec[2] + translate_z);




	goalRightBody->getMotionState()->getWorldTransform(trans);
	std::cout << trans.getOrigin().getX() << " " << trans.getOrigin().getY() << " " << trans.getOrigin().getZ() << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << "=================" << std::endl;
	std::cout << "=================" << std::endl;
}

Penguin::Penguin(Ogre::SceneManager* m_pSceneMgr)
{

	penguin_position = new btTransform(btQuaternion(0,0,0,1),btVector3(0, -room_width/2, 0));
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
	// Physics
	//--------------------


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

	//--------------------
	// Visuals
	//--------------------

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

