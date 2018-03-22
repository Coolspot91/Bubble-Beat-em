#include "Ball.h"
USING_NS_CC;

/*Ball* Ball::create(CCSpriteFrame *pSpriteFrame, int color)
{
   Ball *pSprite = new Ball();
   if (pSprite && pSprite->initWithSpriteFrame(pSpriteFrame))
   {
      // Set to autorelease
      pSprite->autorelease();

      // assign color value
      //this->mColor = color;

      pSprite->setPosition(200,200);
	  auto body2 = PhysicsBody::createCircle(pSprite->getTexture()->getPixelsWide()/2);//createCircle(myPlayer->getContentSize().width / 2);
      pSprite->setPhysicsBody(body2);
      return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}*/

void Ball::createOBject(const char *ballSpirit, cocos2d::CCPoint pos, int ballType, float mass, float damping, cocos2d::Layer *layer)
{
	mySprite = Sprite::create(ballSpirit);
	mySprite->setTag(ballType);
	mySprite->setPosition(pos);
	//mySprite->autorelease();
	//mySprite->setUserData("ball");
	hit = false;
	stickToCannon = true;
	AddBallImpulse = false;
	auto body = PhysicsBody::createCircle(mySprite->getContentSize().width/2);//createCircle(myPlayer->getContentSize().width / 2);
	body->setMass(mass);
	body->setCollisionBitmask(ballType);
	body->setContactTestBitmask(true);
	body->setAngularDamping(damping);
	body->setLinearDamping(damping);
	mySprite->setPhysicsBody(body);
	layer->addChild(mySprite);
}
void Ball::destroyBall(cocos2d::Layer *layer)
{
	layer->removeChild(mySprite, true);
	mySprite->getPhysicsBody()->removeFromWorld();
}
Ball *Ball::getBall()
{
	Ball *pSprite = new Ball();
	return pSprite;
}
