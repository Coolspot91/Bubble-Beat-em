#ifndef __BALL_H__
#define __BALL_H__

#include "cocos2d.h"

class Ball : public cocos2d::CCSprite
{
public:

	//Ball(cocos2d::Vec2 pos );
	void createOBject(const char *ballSpirit, cocos2d::CCPoint pos, int ballType, float mass,float damping, cocos2d::Layer *layer);
	void destroyBall(cocos2d::Layer *layer);
	Ball* getBall();

	bool hit;
	bool stickToCannon;
	bool AddBallImpulse;
	cocos2d::CCSprite *mySprite;
	static Ball* create(cocos2d::CCSpriteFrame *pSpriteFrame, int color);

};
#endif
