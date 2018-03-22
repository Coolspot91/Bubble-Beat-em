#ifndef __CANNON_H__
#define __CANNON_H__

#include "GameObject.h"

class Cannon : public cocos2d::CCSprite
{
public:

	cocos2d::Vec2 cannonPosition;
	cocos2d::Vec2 cannonDirection;
	cocos2d::CCSprite *mySprite;

	void createCannon(cocos2d::Vec2 pos,  cocos2d::Layer *layer );

	void shootBall(cocos2d::Vec2 dir );
};
#endif
