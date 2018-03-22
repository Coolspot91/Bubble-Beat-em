#include "Cannon.h"
USING_NS_CC;
void Cannon::createCannon(cocos2d::Vec2 pos,  cocos2d::Layer *layer) //: GameObject(pos)
{
	mySprite = Sprite::create("BubbleCannon.png");
	mySprite->setTag(1);
	mySprite->setPosition(pos);
	//mySprite->setAnchorPoint(CCPoint(.5,0));
	mySprite->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
	mySprite->setRotation(180);
	auto cannonBody = PhysicsBody::createBox(mySprite->getContentSize());
	cannonBody->setCollisionBitmask(1);
	cannonBody->setContactTestBitmask(true);
	cannonBody->setMass(10000000);
	mySprite->setPhysicsBody(cannonBody);
	layer->addChild(mySprite);
}

void Cannon::shootBall(cocos2d::Vec2 dir)
{

}
