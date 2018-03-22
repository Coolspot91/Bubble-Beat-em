#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "cocos2d.h"
#include "MainMenuScene.h"

class TutorialScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(TutorialScene);

private:
    void GoToMainScene( cocos2d::Ref *sender );

};

#endif // __MAIN_MENU_SCENE_H__
