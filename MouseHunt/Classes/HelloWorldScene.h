#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Cannon.h"
#include "Ball.h"
#include "StaticObject.h"
#include "GameOverScene.h"
#include "MainMenuScene.h"
//#include "GUI/CCEditBox/CCEditBox.h"
//#include " ../extensions/GUI/CCEditBox/CCEditBox.h"
//#include "sqlite3/include/sqlite3.h"


class HelloWorld : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();
    int getScore();

    virtual bool init();  
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void returnToMenu(cocos2d::Ref* pSender);
    void update(float dt);
    int getRandomNumber(int from ,int to);
    
    void onAcceleration(cocos2d::Acceleration *acc,cocos2d::Event *event);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    bool onContactBegin( cocos2d::PhysicsContact &contact );

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Sprite *mySprite;
    cocos2d::Sprite *myBallSprite;
    cocos2d::CCPoint touchPosition;
    cocos2d::CCPoint direction;
    cocos2d::CCPoint cannonOffset;
    cocos2d::CCPoint cannonBallDir;

    Ball myBall;
    Cannon myCannon;
    StaticObject myWall;
    cocos2d::Vector<Ball*> cannonBallz;
    cocos2d::Vector<StaticObject*> wallObjects;
    cocos2d::Label *scoreLabel;
    cocos2d::Label *ballsRemainingLabel;
    cocos2d::Label *flashInformationLabel;
    cocos2d::Label *lastBallLabel;
    cocos2d::LabelTTF *lvlLabel;

    //cocos2d::CCTextFieldTTF * pTextField;

    int ballsRemaing;
    float delay = 0;
    float hitcounter = 1;
    static int score;
    int lvl;
    bool createBall = false;
    bool bonusBallz = false;
    bool flashflashInformation = false;
    float visibleCounter=0;

    //cocos2d::extension::CCEditBox *m_pEditName;

};

#endif // __HELLOWORLD_SCENE_H__
