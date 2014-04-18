#include "GameObject.h"

GameObject::GameObject(	Ogre::String entityName,   // contrutor para esfera
						char * mesh, 
						Ogre::String nodeName, 
						Ogre::SceneNode* parentNode, 
						Ogre::Vector3 relativePosition,//posicao do no da mesh						
						btScalar mass, 
						Ogre::SceneManager * sceneMgr,
						btDynamicsWorld * dWld,
						btVector3 * iPos,
						int radius) //posicao da figura fisica

{
	sceneManager = sceneMgr;
	dWorld = dWld;
	initGraphics(	entityName, 
					mesh, 
					nodeName, 
					parentNode, 
					relativePosition,
					radius
					);
	
	initPhysics(mass,iPos,radius);
}


GameObject::GameObject(	Ogre::String entityName,  //construtor para boxes
						char * mesh, 
						Ogre::String nodeName, 
						Ogre::SceneNode* parentNode, 
						Ogre::Vector3 relativePosition,//posicao do no da mesh
						btScalar mass, 
						Ogre::SceneManager * sceneMgr,
						btDynamicsWorld * dWld,
						btVector3 * iPos,
						float x, float y, float z) //posicao da figura fisica

{
	sceneManager = sceneMgr;
	dWorld = dWld;
	initGraphicsBox(	entityName, 
					mesh, 
					nodeName, 
					parentNode, 
					relativePosition,
					x, y, z
					);
	
	initPhysicsBox(mass,iPos,x, y, z);
}


void GameObject::initGraphics(	Ogre::String entityName, 
								char* mesh,
								Ogre::String nodeName, 
								Ogre::SceneNode* parentNode, 
								Ogre::Vector3 relativePosition,
								float radius
								)
{
	//Ogre::Entity *sphere = mSceneMgr->createEntity("sphere", "sphere.mesh");//Sinbad
	sceneEntity = sceneManager->createEntity(entityName, mesh);//createEntity(entityName, "sinbad.mesh");//criando entidade no gerenciador de cena
	sceneNode = sceneManager->createSceneNode(nodeName); //criando node no gerenciador de cena
	parentNode->addChild(sceneNode); // adiciona o n� na arvore de cena como filho de parent node
	sceneNode->attachObject(sceneEntity); // associa n� � entidade
	sceneNode->setPosition(relativePosition); // define a posicao do n� em rela��o a seu parentNode
	sceneNode->scale(radius/100, radius/100, radius/100); //pois a mesh tem dimensao 100	
}


void GameObject::initPhysics(btScalar mass, btVector3 * iPos, int radius)
{

	collisionShape = new btSphereShape(radius); // cria uma esfera de colisao

	motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),*iPos));
	bodyMass = mass;
	btVector3 bodyInertia = btVector3(0,0,0);

	collisionShape->calculateLocalInertia(mass,bodyInertia);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,collisionShape,bodyInertia);
	rigidBody = new btRigidBody(rigidBodyCI);
	dWorld->addRigidBody(rigidBody);
}


void GameObject::initPhysicsBox(btScalar mass, btVector3 * iPos, float x, float y, float z)
{
    collisionShape = new btBoxShape(btVector3(x / 2, y / 2, z / 2));
	motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),*iPos));
    bodyMass = mass;
	btVector3 bodyInertia = btVector3(0,0,0);
	collisionShape->calculateLocalInertia(mass,bodyInertia);
	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass,motionState,collisionShape,bodyInertia);
	rigidBody = new btRigidBody(rigidBodyCI);
	dWorld->addRigidBody(rigidBody);

}


void GameObject::initGraphicsBox(	Ogre::String entityName, 
								char* mesh,
								Ogre::String nodeName, 
								Ogre::SceneNode* parentNode, 
								Ogre::Vector3 relativePosition,
								float x, float y, float z
								)
{
	//Ogre::Entity *sphere = mSceneMgr->createEntity("sphere", "sphere.mesh");//Sinbad
	sceneEntity = sceneManager->createEntity(entityName, mesh);//createEntity(entityName, "sinbad.mesh");//criando entidade no gerenciador de cena
	sceneNode = sceneManager->createSceneNode(nodeName); //criando node no gerenciador de cena
	parentNode->addChild(sceneNode); // adiciona o n� na arvore de cena como filho de parent node
	sceneNode->attachObject(sceneEntity); // associa n� � entidade
	sceneNode->setPosition(relativePosition); // define a posicao do n� em rela��o a seu parentNode
	sceneNode->scale(x/100, y/100, z/100);
	
}



GameObject::~GameObject(void)
{


}