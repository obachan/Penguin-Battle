#include "WorldObjects.hpp"


Ball::Ball(Ogre::SceneManager* m_pSceneMgr)
{

	const double start_pos_x = 10.5f;
	const double start_pos_y = 3.0f;
	const double start_pos_z = -25.0f;

	btDefaultMotionState* ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(start_pos_x, start_pos_y, start_pos_z)));

        btScalar mass = 1;
        btVector3 ballInertia(0,0,0);

	ball = new btSphereShape(1);
        ball->calculateLocalInertia(mass,ballInertia);


        btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(mass,ballMotionState,ball,ballInertia);
	ballRigidBodyCI.m_restitution = 0.712f;
        ballRigidBody = new btRigidBody(ballRigidBodyCI);
	ballRigidBody->setLinearVelocity(btVector3(10,0,0));
	
	createSphere(m_pSceneMgr, start_pos_x, start_pos_y, start_pos_z, 0.01f, "Awesome_Sphere");

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
