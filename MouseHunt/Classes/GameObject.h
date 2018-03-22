#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class GameObject : public cocos2d::CCSprite
{
public:
    GameObject(cocos2d::Vec2 pos );
    GameObject();
    cocos2d::Vec2 position;

    cocos2d::Sprite *objectSpirit;
    cocos2d::CCTexture2D* spriteTexture;

    b2World *myWorld;
    b2Body *objectBody;
    void createPhysicsBody();
    void createObject();
    void setSprite(cocos2d::CCTexture2D* spriteTex );

};

#endif
