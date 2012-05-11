#include "WorldObjectPenguin.hpp"
#include "WorldObjectBall.hpp"

Penguin::Penguin(MyController* controller, cCallback* callbackAddBall){
	mController = controller;
	mCallbackAddBall = callbackAddBall;
}

Penguin::Penguin(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics, MyController* controller) : WorldObjectAbstract()
{
	mController = controller;
	createPenguin(m_pSceneMgr);

	if(physics != NULL)
		attachToDynamicWorld(physics);
}

Penguin::Penguin(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics) : WorldObjectAbstract()
{

	createPenguin(m_pSceneMgr);

	if(physics != NULL)
		attachToDynamicWorld(physics);
}

Penguin::~Penguin()
{
}

void Penguin::createPenguin(Ogre::SceneManager* m_pSceneMgr)
{
	//--------------------
	// Physics - Penguin
	//--------------------	

	const float penguin_half_length = penguin_length / 2;

	penguin_position = new btTransform(btQuaternion(0,0,0,1),btVector3(0, -room_width/2, room_length/4));
	penguin_velocity = Ogre::Vector3(0, 0, 0);
	
	penguinMotionState = new btDefaultMotionState(*penguin_position);

    btScalar mass = 0;
    btVector3 penguinInertia(0,0,0);
	penguin_collision_shape = new btSphereShape(penguin_half_length);
    penguin_collision_shape->calculateLocalInertia(mass,penguinInertia);

    btRigidBody::btRigidBodyConstructionInfo penguinRigidBodyCI(mass,penguinMotionState,penguin_collision_shape,penguinInertia);
	penguinRigidBodyCI.m_restitution = 1;
    worldObjectRigidBody = new btRigidBody(penguinRigidBodyCI);

    // Disable Gravity because this object will be controlled by the player
    worldObjectRigidBody->setGravity(btVector3(0,0,0));
	worldObjectRigidBody->setCollisionFlags( worldObjectRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	worldObjectRigidBody->setActivationState(DISABLE_DEACTIVATION);


	//--------------------
	// Visuals - Penguin
	//--------------------

	float penguin_scale = penguin_length / 50.0;
	btTransform trans;
    worldObjectRigidBody->getMotionState()->getWorldTransform(trans);
	Ogre::Vector3 vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

	// Convert static scene_node_counter to string
	// to give each instance a unique string name
 	std::string unique_id_string;
 	std::stringstream out;
 	out << getUniqueId();
 	unique_id_string = out.str();
	std::string penguin_name = "penguin" + unique_id_string;

	//std::cout << penguin_name << std::endl;

	penguinEntity = m_pSceneMgr->createEntity(penguin_name, "penguin.mesh");
	worldObjectSceneNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(penguin_name);
	worldObjectSceneNode->attachObject(penguinEntity);
	worldObjectSceneNode->setScale(penguin_scale, penguin_scale, penguin_scale);
	worldObjectSceneNode->setPosition(vec[0], vec[1], vec[2]);
	penguinEntity->setMaterialName("Penguin");
	worldObjectSceneNode->yaw( Ogre::Degree( -180 ) );
	penguin_direction = Ogre::Vector3(0,0,-1);
	previous_direction = Ogre::Vector3(0,0,-1);

	/*Ogre::Camera* camera = m_pSceneMgr->getCamera("Camera");
	camera->setPosition(worldObjectSceneNode->getPosition());
	camera->setDirection(penguin_direction);*/

}

void Penguin::update(double timeSinceLastFrame, MyController* controller, Ogre::Camera* camera)
{
	// We cap the timeSinceLastFrame to avoid
	// huge time steps
	if(timeSinceLastFrame > 0.4f)
		timeSinceLastFrame = 0.4f;

	// 'vec' is passed around to different functions to be modified
	// At the end of update, 'pos' is put back into the btTransform
	btTransform trans;
    worldObjectRigidBody->getMotionState()->getWorldTransform(trans);
	Ogre::Vector3 pos = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

	// Factor in Gravity
	// new penguin position is put in pos
	handleGravity(timeSinceLastFrame, &pos);

	// Handle Wall and Ceiling Collisions
	// new penguin position is put in pos
	handleCollisions(&pos);

	// Process User Input to move player
	// new penguin position is put in pos
	processController(timeSinceLastFrame, &pos);

	// Animate Penguin
	animate(timeSinceLastFrame);	

	// Sync Visuals: We don't use the parent's updateWorldObjectVisual
	// to sync because that method is for objects not under user control
	trans.setOrigin(btVector3(pos[0], pos[1], pos[2]));
	penguinMotionState->setWorldTransform(trans);
	worldObjectSceneNode->setPosition(pos[0], pos[1], pos[2]);

	// Modify Camera
	if(mController->thirdPersonCameraOn() && camera != NULL){
		Ogre::Vector3 cameraPosition;
		Ogre::Vector3 cameraDirection;

		cameraDirection = penguin_direction;
		camera->setDirection(cameraDirection);
		cameraPosition = pos - (20*penguin_direction);
		cameraPosition.y += 7;
		camera->setPosition(cameraPosition);
	}

}

void Penguin::processController(double timeSinceLastFrame, Ogre::Vector3* pos)
{
	Ogre::Quaternion quat = Ogre::Quaternion(1, 0, 0, 0);


	// A boost modifier of 1.0 is default normal speed
	// > 1 will cause Player to move faster
	// < 1 will cause Player to move slower
	float boost_modifier = 1.0;

	// Z causes the player to move faster
	if(mController->boost_control_down == true){
		boost_modifier = 2.0;
	}

	// Left and Right on the keyboard will rotate the Penguin
	if(mController->left_control_down == true){
		quat = Ogre::Quaternion(Ogre::Radian(Ogre::Degree(rotation_speed*timeSinceLastFrame)), Ogre::Vector3::UNIT_Y);
		worldObjectSceneNode->rotate(quat);
		penguin_direction = worldObjectSceneNode->getOrientation() * Ogre::Vector3(0,0,1);
		penguin_direction.y = 0;
		penguin_direction.normalise();
		previous_direction = penguin_direction;
	}

	if(mController->right_control_down == true){
		quat = Ogre::Quaternion(Ogre::Radian(Ogre::Degree(rotation_speed*-timeSinceLastFrame)), Ogre::Vector3::UNIT_Y);
		worldObjectSceneNode->rotate(quat);
		penguin_direction = worldObjectSceneNode->getOrientation() * Ogre::Vector3(0,0,1);
		penguin_direction.y = 0;
		penguin_direction.normalise();
		previous_direction = penguin_direction;
	}

	// Up and Down on the keyboard will move Penguin forwards and backwards

	if(mController->forward_control_down == true){
		*pos = *pos + (penguin_direction * move_vel * timeSinceLastFrame) * (boost_modifier);
		//worldObjectRigidBody->setLinearVelocity(btVector3(100,100, 100));
		
	} else if(mController->backward_control_down == true){
		*pos = *pos + (penguin_direction * -move_vel * timeSinceLastFrame) * (boost_modifier);
		//worldObjectRigidBody->setLinearVelocity(btVector3(-100*penguin_direction.x,-100*penguin_direction.y, -100*penguin_direction.z));
	} else {
	//	worldObjectRigidBody->setLinearVelocity(btVector3(0, 0, 0));
	}

	// Space on the keyboard will cause the penguin to jump
	if(mController->jump_control_down == true){
		mController->jump_control_down = false;
		penguin_velocity[1] = jump_vel;
	}

	//cout << worldObjectRigidBody->getLinearVelocity().getX() << endl;
	// Mouse controls
	
	if(mController->mouse_x_movement != 0.0000 ) {
		quat = Ogre::Quaternion(Ogre::Radian(Ogre::Degree( 0.15f*mController->mouse_x_movement)), Ogre::Vector3::UNIT_Y);
		worldObjectSceneNode->rotate(quat);
		penguin_direction = worldObjectSceneNode->getOrientation() * Ogre::Vector3(0,0,1);
		penguin_direction.y = 0;
		penguin_direction.normalise();
		previous_direction = penguin_direction;
		mController->mouse_x_movement = 0.0;
	
	}
	
	if( mController->left_mouse_button_down == true) {
		mController->left_mouse_button_down = false;
		fireWeapon();
	}
}


void Penguin::fireWeapon() {

	char s8_Out[50];
	mCallbackAddBall->Execute((void*)s8_Out);
}

void Penguin::handleGravity(double timeSinceLastFrame, Ogre::Vector3* pos)
{
		penguin_velocity[1] = penguin_velocity[1] + world_grav * timeSinceLastFrame;
		// if penguin is falling too fast
		if(penguin_velocity[1] < max_fall_vel)
			penguin_velocity[1] = max_fall_vel;
		(*pos)[1] =  (*pos)[1] + penguin_velocity[1] * timeSinceLastFrame + (0.5) * world_grav * timeSinceLastFrame * timeSinceLastFrame;
}

void Penguin::handleCollisions(Ogre::Vector3* pos)
{
	// if((*pos)[0] < -room_width/2 + penguin_length/2)
	// 	(*pos)[0] = -room_width/2 + penguin_length/2;

	// if((*pos)[0] > room_width/2 - penguin_length/2)
	// 	(*pos)[0] = room_width/2 - penguin_length/2;


	// if((*pos)[1] > room_width/2 - penguin_length/2)
	// 	(*pos)[1] = room_width/2 - penguin_length/2;


	// if((*pos)[2] < -room_length/2 + penguin_length/2)
	// 	(*pos)[2] = -room_length/2 + penguin_length/2;


	// if((*pos)[2] > room_length/2 - penguin_length/2)
	// 	(*pos)[2] = room_length/2 - penguin_length/2;


	// If penguin touches the ground, change the penguin to ground state
	if((*pos)[1] < -room_width/2 + penguin_length/2){
		(*pos)[1] = -room_width/2 + penguin_length/2;
		float tolerance = abs((*pos)[1] - (-room_width/2 + penguin_length/2));
		if(tolerance < 0.01f){
			penguin_velocity[1]  = 0;
		}	
	}
}

void Penguin::animate(double timeSinceLastFrame)
{
	// Animation
	if(mController->boost_control_down == true)
	{
		mAnimationState = penguinEntity->getAnimationState("amuse");
        mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true);

        float time_scale = timeSinceLastFrame; // Scale the time back so it doesn't animate as fast
		mAnimationState->addTime(time_scale);
	}
	else if(mController->left_control_down == true ||
		mController->right_control_down == true ||
		mController->up_control_down == true ||
		mController->bottom_control_down == true ||
		mController->forward_control_down == true ||
		mController->backward_control_down == true
		)
	{
		mAnimationState = penguinEntity->getAnimationState("amuse");
        mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true);

        float time_scale = timeSinceLastFrame / 4.0f; // Scale the time back so it doesn't animate as fast
		mAnimationState->addTime(time_scale);
	}
}

Ogre::Vector3 Penguin::getPenguinDirection()
{
	return Ogre::Vector3(penguin_direction[0], penguin_direction[1], penguin_direction[2]);
}



// =========================================
// From Parent Class, WorldObjectAbstract
// ========================================
void Penguin::createSceneNode(Ogre::SceneManager* m_pSceneMgr)
{
	//--------------------
	// Visuals - Penguin
	//--------------------

	float penguin_scale = penguin_length / 50.0;
	btTransform trans;
    worldObjectRigidBody->getMotionState()->getWorldTransform(trans);
	Ogre::Vector3 vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

	// Convert static scene_node_counter to string
	// to give each instance a unique string name
 	std::string unique_id_string;
 	std::stringstream out;
 	out << getUniqueId();
 	unique_id_string = out.str();
	std::string penguin_name = "penguin" + unique_id_string;

	//std::cout << penguin_name << std::endl;

	penguinEntity = m_pSceneMgr->createEntity(penguin_name, "penguin.mesh");
	worldObjectSceneNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(penguin_name);
	worldObjectSceneNode->attachObject(penguinEntity);
	worldObjectSceneNode->setScale(penguin_scale, penguin_scale, penguin_scale);
	worldObjectSceneNode->setPosition(vec[0], vec[1], vec[2]);
	penguinEntity->setMaterialName("Penguin");
	worldObjectSceneNode->yaw( Ogre::Degree( -180 ) );
	penguin_direction = Ogre::Vector3(0,0,-1);
	previous_direction = Ogre::Vector3(0,0,-1);
}

void Penguin::createRigidBody(PhysicsWrapper* physics)
{
		//--------------------
	// Physics - Penguin
	//--------------------	

	const float penguin_half_length = penguin_length / 2;

	penguin_position = new btTransform(btQuaternion(0,0,0,1),btVector3(0, -room_width/2, room_length/4));
	penguin_velocity = Ogre::Vector3(0, 0, 0);
	
	penguinMotionState = new btDefaultMotionState(*penguin_position);

    btScalar mass = 0;
    btVector3 penguinInertia(0,0,0);
	penguin_collision_shape = new btSphereShape(penguin_half_length);
    penguin_collision_shape->calculateLocalInertia(mass,penguinInertia);

    btRigidBody::btRigidBodyConstructionInfo penguinRigidBodyCI(mass,penguinMotionState,penguin_collision_shape,penguinInertia);
	penguinRigidBodyCI.m_restitution = 1;
    worldObjectRigidBody = new btRigidBody(penguinRigidBodyCI);

    // Disable Gravity because this object will be controlled by the player
    worldObjectRigidBody->setGravity(btVector3(0,0,0));
	worldObjectRigidBody->setCollisionFlags( worldObjectRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	worldObjectRigidBody->setActivationState(DISABLE_DEACTIVATION);
}

// ========================================
// Static Classes
// ========================================


Penguin* Penguin::createNewPenguin(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics, MyController* controller, cCallback* callbackAddBall)
{
	Penguin* penguin = new Penguin(controller, callbackAddBall);
	penguin->initWorldObject(m_pSceneMgr, physics);
	return penguin;
}