//|||||||||||||||||||||||||||||||||||||||||||||||
 
#ifndef WORLD_OBJECT_GOAL_HPP
#define WORLD_OBJECT_GOAL_HPP
 
//|||||||||||||||||||||||||||||||||||||||||||||||


#include "WorldObjectAbstract.hpp"

class Goal
{
public:
	Goal(Ogre::SceneManager*, PhysicsWrapper*, bool do_physics = true);
	~Goal();

	Ogre::SceneNode* 	goalLeftNode;
	Ogre::Entity* 		goalLeftEntity;
	btRigidBody* 		goalLeftBody;

	Ogre::SceneNode* 	goalRightNode;
	Ogre::Entity* 		goalRightEntity;
	btRigidBody* 		goalRightBody;

	Ogre::SceneNode* 	goalBackNode;
	Ogre::Entity* 		goalBackEntity;
	btRigidBody* 		goalBackBody;

	Ogre::SceneNode* 	goalTopNode;
	Ogre::Entity* 		goalTopEntity;
	btRigidBody* 		goalTopBody;

	// The front panel should be open
	Ogre::SceneNode* 	goalFrontNode;
	Ogre::Entity* 		goalFrontEntity;

private:
	void createGoal(Ogre::SceneManager*, double);
	void attachToDynamicWorld(PhysicsWrapper*);

	btCollisionShape* goalLeftShape;
	btCollisionShape* goalRightShape;
	btCollisionShape* goalBackShape;
	btCollisionShape* goalTopShape;

	static int 				scene_node_counter;
};

//|||||||||||||||||||||||||||||||||||||||||||||||
 
#endif
 
//|||||||||||||||||||||||||||||||||||||||||||||||