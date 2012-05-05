#include "WorldObjectPenguin.hpp"

int Penguin::scene_node_counter = 0;


Penguin::Penguin(Ogre::SceneManager* m_pSceneMgr, PhysicsWrapper* physics, bool do_physics)
{
	createPenguin(m_pSceneMgr);
	if(do_physics)
		attachToDynamicWorld(physics);
	third_person_camera = true;
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

	//--------------------
	// Physics - Penguin
	//--------------------	

	const float penguin_half_length = penguin_length / 2;

	penguin_position = new btTransform(btQuaternion(0,0,0,1),btVector3(0, -room_width/2, room_length/4));
	penguin_velocity = Ogre::Vector3(0, 0, 0);
	in_air = false;

	penguinMotionState = new btDefaultMotionState(*penguin_position);

    btScalar mass = 0;
    btVector3 penguinInertia(0,0,0);
	penguin_collision_shape = new btSphereShape(penguin_half_length);
    penguin_collision_shape->calculateLocalInertia(mass,penguinInertia);

    btRigidBody::btRigidBodyConstructionInfo penguinRigidBodyCI(mass,penguinMotionState,penguin_collision_shape,penguinInertia);
	penguinRigidBodyCI.m_restitution = 1;
    penguinRigidBody = new btRigidBody(penguinRigidBodyCI);

    // Disable Gravity because this object will be controlled by the player
    penguinRigidBody->setGravity(btVector3(0,0,0));
	penguinRigidBody->setCollisionFlags( penguinRigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	penguinRigidBody->setActivationState(DISABLE_DEACTIVATION);


	//--------------------
	// Visuals - Penguin
	//--------------------

	float penguin_scale = penguin_length / 50.0;
	btTransform trans;
    penguinRigidBody->getMotionState()->getWorldTransform(trans);
	Ogre::Vector3 vec = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

	// Convert static scene_node_counter to string
	// to give each instance a unique string name
 	std::string scene_node_counter_string;
 	std::stringstream out;
 	out << scene_node_counter;
 	scene_node_counter_string = out.str();
	std::string penguin_name = "penguin" + scene_node_counter_string;
	scene_node_counter++;

	//std::cout << penguin_name << std::endl;

	penguinEntity = m_pSceneMgr->createEntity(penguin_name, "penguin.mesh");
	penguinNode = m_pSceneMgr->getRootSceneNode()->createChildSceneNode(penguin_name);
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


void Penguin::attachToDynamicWorld(PhysicsWrapper* physics)
{
	physics->add_object_to_dynamicWorld(penguinRigidBody);
}

void Penguin::toggleThirdPersonCamera()
{
	third_person_camera = !third_person_camera;
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
    penguinRigidBody->getMotionState()->getWorldTransform(trans);
	Ogre::Vector3 pos = Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());

	// Factor in Gravity
	// new penguin position is put in pos
	handleGravity(timeSinceLastFrame, &pos);

	// Handle Wall and Ceiling Collisions
	// new penguin position is put in pos
	handleCollisions(&pos);

	// Process User Input to move player
	// new penguin position is put in pos
	processController(timeSinceLastFrame, controller, &pos);

	// Animate Penguin
	animate(timeSinceLastFrame, controller);	


	// Sync Visuals	
	trans.setOrigin(btVector3(pos[0], pos[1], pos[2]));
	penguinMotionState->setWorldTransform(trans);
	penguinNode->setPosition(pos[0], pos[1], pos[2]);

	// Modify Camera
	if(third_person_camera && camera != NULL){
		Ogre::Vector3 cameraPosition;
		Ogre::Vector3 cameraDirection;

		cameraDirection = penguin_direction;
		camera->setDirection(cameraDirection);
		cameraPosition = pos - (20*penguin_direction);
		cameraPosition.y += 7;
		camera->setPosition(cameraPosition);
	}


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

void Penguin::updateAsClient(Ogre::Vector3 pos, Ogre::Quaternion rot)
{
	penguinNode->setPosition(pos[0], pos[1], pos[2]);
	//Ogre::Vector3 dest = rot*Ogre::Vector3(0,0,1);
	//Ogre::Vector3 src = penguinNode->getOrientation()*Ogre::Vector3(0,0,1);
	//Ogre::Quaternion quat = src.getRotationTo(dest);
	penguinNode->setOrientation(rot[0], rot[1], rot[2], rot[3]);
	//penguinNode->rotate(quat);
}

void Penguin::updateCamera(Ogre::Camera* camera)
{
/*
	// Modify Camera
	if(third_person_camera && camera != NULL){
		Ogre::Vector3 cameraPosition;
		Ogre::Vector3 cameraDirection;

		cameraDirection = penguin_direction;
		camera->setDirection(cameraDirection);
		cameraPosition = getPenguinPosition() - (20*penguin_direction);
		cameraPosition.y += 7;
		camera->setPosition(cameraPosition);
	}
*/
}

Ogre::Vector3 Penguin::getPenguinPosition()
{
	return penguinNode->getPosition();
}

Ogre::Quaternion Penguin::getPenguinOrientation()
{
	return penguinNode->getOrientation();
}

void Penguin::processController(double timeSinceLastFrame, MyController* controller, Ogre::Vector3* pos)
{
	Ogre::Quaternion quat = Ogre::Quaternion(1, 0, 0, 0);


	// A boost modifier of 1.0 is default normal speed
	// > 1 will cause Player to move faster
	// < 1 will cause Player to move slower
	float boost_modifier = 1.0;

	// Z causes the player to move faster
	if(controller->boost_control_down == true){
		boost_modifier = 2.0;
	}

	// Left and Right on the keyboard will rotate the Penguin
	if(controller->left_control_down == true){
		quat = Ogre::Quaternion(Ogre::Radian(Ogre::Degree(rotation_speed*timeSinceLastFrame)), Ogre::Vector3::UNIT_Y);
		penguinNode->rotate(quat);
		penguin_direction = penguinNode->getOrientation() * Ogre::Vector3(0,0,1);
		penguin_direction.y = 0;
		penguin_direction.normalise();
		previous_direction = penguin_direction;
	}

	if(controller->right_control_down == true){
		quat = Ogre::Quaternion(Ogre::Radian(Ogre::Degree(rotation_speed*-timeSinceLastFrame)), Ogre::Vector3::UNIT_Y);
		penguinNode->rotate(quat);
		penguin_direction = penguinNode->getOrientation() * Ogre::Vector3(0,0,1);
		penguin_direction.y = 0;
		penguin_direction.normalise();
		previous_direction = penguin_direction;
	}

	// Up and Down on the keyboard will move Penguin forwards and backwards
	if(controller->forward_control_down == true){
		*pos = *pos + (penguin_direction * move_vel * timeSinceLastFrame) * (boost_modifier);
	}

	if(controller->backward_control_down == true){
		*pos = *pos + (penguin_direction * -move_vel * timeSinceLastFrame) * (boost_modifier);
	}

	// Space on the keyboard will cause the penguin to jump
	if(controller->jump_control_down == true){
		controller->jump_control_down = false;
		if(!in_air){
			in_air = true;
			penguin_velocity[1] = jump_vel;
		}
	}


	// Mouse controls
	
	if(controller->mouse_x_movement != 0.0000 ) {
		quat = Ogre::Quaternion(Ogre::Radian(Ogre::Degree( 0.15f*controller->mouse_x_movement)), Ogre::Vector3::UNIT_Y);
		penguinNode->rotate(quat);
		penguin_direction = penguinNode->getOrientation() * Ogre::Vector3(0,0,1);
		penguin_direction.y = 0;
		penguin_direction.normalise();
		previous_direction = penguin_direction;
		controller->mouse_x_movement = 0.0;
	
	}

/*	if(controller->mouse_y_movement != 0.0000 ) {
		quat = Ogre::Quaternion(Ogre::Radian(Ogre::Degree( 0.15f*controller->mouse_y_movement)), Ogre::Vector3::UNIT_X);
		penguinNode->rotate(quat);
		penguin_direction = penguinNode->getOrientation() * Ogre::Vector3(0,0,1);
		penguin_direction.x = 0;
		penguin_direction.normalise();
		previous_direction = penguin_direction;
		controller->mouse_y_movement = 0.0;
	
	}*/

}

void Penguin::handleGravity(double timeSinceLastFrame, Ogre::Vector3* pos)
{
	if(in_air){
		penguin_velocity[1] = penguin_velocity[1] + world_grav * timeSinceLastFrame;
		// if penguin is falling too fast
		if(penguin_velocity[1] < max_fall_vel)
			penguin_velocity[1] = max_fall_vel;
		(*pos)[1] =  (*pos)[1] + penguin_velocity[1] * timeSinceLastFrame + (0.5) * world_grav * timeSinceLastFrame * timeSinceLastFrame;
	}
}

void Penguin::handleCollisions(Ogre::Vector3* pos)
{
	if((*pos)[0] < -room_width/2 + penguin_length/2)
		(*pos)[0] = -room_width/2 + penguin_length/2;

	if((*pos)[0] > room_width/2 - penguin_length/2)
		(*pos)[0] = room_width/2 - penguin_length/2;


	if((*pos)[1] > room_width/2 - penguin_length/2)
		(*pos)[1] = room_width/2 - penguin_length/2;


	if((*pos)[2] < -room_length/2 + penguin_length/2)
		(*pos)[2] = -room_length/2 + penguin_length/2;


	if((*pos)[2] > room_length/2 - penguin_length/2)
		(*pos)[2] = room_length/2 - penguin_length/2;


	// If penguin touches the ground, change the penguin to ground state
	if((*pos)[1] < -room_width/2 + penguin_length/2){
		in_air = false;
		(*pos)[1] = -room_width/2 + penguin_length/2;
		float tolerance = abs((*pos)[1] - (-room_width/2 + penguin_length/2));
		if(tolerance < 0.01f){
			penguin_velocity[1]  = 0;
		}	
	}
}

void Penguin::animate(double timeSinceLastFrame, MyController* controller)
{
	// Animation
	if(controller->boost_control_down == true)
	{
		mAnimationState = penguinEntity->getAnimationState("amuse");
        mAnimationState->setLoop(true);
        mAnimationState->setEnabled(true);

        float time_scale = timeSinceLastFrame; // Scale the time back so it doesn't animate as fast
		mAnimationState->addTime(time_scale);
	}
	else if(controller->left_control_down == true ||
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
}