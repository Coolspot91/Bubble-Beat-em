#include "GameObject.h"

USING_NS_CC;

GameObject::GameObject(cocos2d::Vec2 pos)
{
	position = pos;
	//spriteTexture = spriteTex;
}
//10
GameObject::GameObject()
{
}


void GameObject::createObject()
{
	objectSpirit = Sprite::create("cannon2.png");
	objectSpirit->setTag(1);
/*20*/    auto body2 = PhysicsBody::createBox(objectSpirit->getContentSize());//createCircle(myPlayer->getContentSize().width / 2);
    objectSpirit->setPhysicsBody(body2);
    objectSpirit->setPosition(CCPoint(position.x,position.y));
/*23*/    //this->addChild(objectSpirit);
}
void GameObject::setSprite(cocos2d::CCTexture2D* spriteTex)
{
	//spriteTexture = spriteTex;
}

void GameObject::createPhysicsBody()
{
	 b2BodyDef objectBodyDef;
	 objectBodyDef.type = b2_dynamicBody;
	 objectBodyDef.position.Set(100, 100);
	 objectBodyDef.userData = ( (void*) "object");
	 objectBody = myWorld->CreateBody(&objectBodyDef);

	 b2CircleShape dynamicObjectShape;
	 dynamicObjectShape.m_radius = .5f;

	 b2FixtureDef objectShapeDef;
	 objectShapeDef.shape = &dynamicObjectShape;
	 objectShapeDef.density = 10.0f;
	 objectShapeDef.friction = 0.4f;
	 objectShapeDef.restitution = 0.1f;

	 b2Fixture *objectFixture;
	 objectFixture = objectBody->CreateFixture(&objectShapeDef);

}

