#include "WorldObjectGoal.hpp"

Goal::Goal(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics, bool do_physics)
{
	float goal_to_edge_wall_offset = 50.0;

	createGoal(m_pSceneMgr, -room_length/2 + goal_to_edge_wall_offset);

	if(do_physics)
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
	goalLeftRigidBodyCI.m_restitution = 1;
	
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
	goalRightRigidBodyCI.m_restitution = 1;
	
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
	goalBackRigidBodyCI.m_restitution = 1;
	
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
	goalTopRigidBodyCI.m_restitution = 1;
	
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
	delete goalLeftBody->getMotionState();
    delete goalLeftBody;
	
	
    delete goalRightBody->getMotionState();
    delete goalRightBody;
	
    delete goalBackBody->getMotionState();
    delete goalBackBody;
	
    delete goalTopBody->getMotionState();
    delete goalTopBody;
 
	delete goalLeftShape;
	delete goalRightShape;
	delete goalBackShape;
	delete goalTopShape;
}