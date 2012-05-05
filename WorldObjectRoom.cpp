#include "WorldObjectRoom.hpp"

Room::Room(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics)
{
	createRoom(m_pSceneMgr, room_width, room_length);
	if(physics != NULL)
		attachToDynamicWorld(physics);
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
