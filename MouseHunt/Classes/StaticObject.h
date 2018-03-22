#ifndef __STATICOBJECT_H__
#define __STATICOBJECT_H__

#include "cocos2d.h"

class StaticObject : public cocos2d::CCSprite
{
public:

	void createObject(const char *wallSpirit, cocos2d::CCPoint pos, cocos2d::Layer *layer,float scaleFactor);
	void destroyObject(cocos2d::Layer *layer);

	cocos2d::CCSprite *myObjectSprite;

};
#endif
