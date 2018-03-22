#include "StaticObject.h"
USING_NS_CC;

void StaticObject::createObject(const char *wallSpirit, cocos2d::CCPoint pos, cocos2d::Layer *layer, float scaleFactor)
{
	myObjectSprite = Sprite::create(wallSpirit);
	myObjectSprite->setPosition(pos);
	myObjectSprite->setScale(scaleFactor);
	auto body = PhysicsBody::createCircle(myObjectSprite->getContentSize().width*scaleFactor/2);;//createCircle(myPlayer->getContentSize().width / 2);
	//body->setMass(mass);
	body->setContactTestBitmask(true);
	body->setDynamic(false);
	myObjectSprite->setPhysicsBody(body);
	layer->addChild(myObjectSprite);
}
void  StaticObject::destroyObject(cocos2d::Layer *layer)
{
	layer->removeChild(myObjectSprite, true);
	myObjectSprite->getPhysicsBody()->removeFromWorld();
}
