#include "WorldObjects.hpp"


Ball::Ball(Ogre::SceneManager* m_pSceneMgr)
{

	const double start_pos_x = 10.5f;
	const double start_pos_y = 3.0f;
	const double start_pos_z = -25.0f;

	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(start_pos_x, start_pos_y, start_pos_z)));

    btScalar mass = 1;
    btVector3 ballInertia(0,0,0);

	ball_collision_shape = new btSphereShape(1);
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
	
	createSphere(m_pSceneMgr, start_pos_x, start_pos_y, start_pos_z, 0.01f, "Awesome_Sphere");

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
	int room_width = 100; // represents width/height or room
	int room_length = 300; // represents the length of the prism

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

	// Bottom Plane
	Ogre::Plane bottom_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        bottom_plane, room_width, room_length, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_botNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::Entity* entGround = m_pSceneMgr->createEntity("GroundEntity", "ground");
    _botNode->attachObject(entGround);
    _botNode->setPosition(0, -room_width/2, 0);
	entGround->setMaterialName("Examples/Rockwall");

	// Top Plane
	Ogre::Plane top_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("top", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        top_plane, room_width, room_length, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_topNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entTop = m_pSceneMgr->createEntity("TopEntity", "top");
    _topNode->attachObject(entTop);
	_topNode->rotate(Ogre::Vector3::UNIT_X,Ogre::Degree(180));
	_topNode->setPosition(0, room_width/2, 0);
	entTop->setMaterialName("Examples/Rockwall");


	// Left Plane
	Ogre::Plane left_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("left", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        left_plane, room_width, room_length, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_leftNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entLeft = m_pSceneMgr->createEntity("LeftEntity", "left");
    _leftNode->attachObject(entLeft);
	_leftNode->roll(Ogre::Degree(90));
	_leftNode->setPosition(room_width/2, 0, 0);
	entLeft->setMaterialName("Examples/Rockwall");

	// Right Plane
	Ogre::Plane right_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("right", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        right_plane, room_width, room_length, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_rightNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entRight = m_pSceneMgr->createEntity("RightEntity", "right");
    _rightNode->attachObject(entRight);
	_rightNode->roll(Ogre::Degree(-90));
	_rightNode->setPosition(-room_width/2, 0, 0);
	entRight->setMaterialName("Examples/Rockwall");

	// Back Plane
	Ogre::Plane back_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("back", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        back_plane, room_width, room_width, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    Ogre::SceneNode *_backNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* entBack = m_pSceneMgr->createEntity("BackEntity", "back");
    _backNode->attachObject(entBack);
	_backNode->pitch(Ogre::Degree(90));
	_backNode->setPosition(0, 0, -room_length/2);
	entBack->setMaterialName("Examples/WaterStream");

	// Front Plane
	Ogre::Plane front_plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("front", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        front_plane, room_width, room_width, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
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

Paddle::Paddle(Ogre::SceneManager* m_pSceneMgr)
{
	createPaddle(m_pSceneMgr);    
}

Paddle::~Paddle()
{
	delete paddleRigidBody->getMotionState();
	delete paddleRigidBody;

	delete paddle_collision_shape;
}

void Paddle::createPaddle(Ogre::SceneManager* m_pSceneMgr)
{
	Ogre::Entity* paddleEntity = m_pSceneMgr->createEntity("paddle", "cube.mesh");
	Ogre::SceneNode *paddleNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("paddle");
	paddleNode->attachObject(paddleEntity);
	paddleNode->setScale(0.1f, 0.1f, 0.005f);
	paddleNode->setPosition(0,0,25);
	paddleEntity->setMaterialName("WoodPallet");
}

void Paddle::update(double timeSinceLastFrame){
}