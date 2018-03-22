#include "HighScoreScene.h"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

std::string Name;

Scene* HighScoreScene::createScene(std::string str)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HighScoreScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    Name = str;

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HighScoreScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create( "Background.png" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    this->addChild( backgroundSprite );

    UserDefault *def = UserDefault::getInstance( );
       auto highScore = def->getIntegerForKey( "HIGHSCORE", 0 );

       UserDefault *defName = UserDefault::getInstance( );
       auto highScoreName = defName->getStringForKey( "NAME", "" );

       if ( HelloWorld::score > highScore )
       {
           highScore = HelloWorld::score;
           highScoreName = MainMenuScene::name;
           def->setIntegerForKey( "HIGHSCORE", highScore );
           defName->setStringForKey("NAME", highScoreName);
       }
       def->flush( );
       defName->flush();

       std::string stringHighScore(std::to_string(highScore));
       auto tempHighScore = "High Score " + highScoreName + " : " + stringHighScore;

       auto highScoreLabel = LabelTTF::create( tempHighScore, "fonts/Marker Felt.ttf", 32 );
       highScoreLabel->setScale(visibleSize.height * .003 );
       highScoreLabel->setColor( Color3B::YELLOW );
       highScoreLabel->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height *.40 + origin.y ) );
       this->addChild( highScoreLabel );



    cocos2d::MenuItem* pCloseItem = cocos2d::MenuItemFont::create("MainMenu",this,menu_selector(HighScoreScene::GoToMainScene));
    //pCloseItem->setFontSize(visibleSize.height * .1 );
    pCloseItem->setScale(visibleSize.height * .003 );
    pCloseItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height *.20 + origin.y ) );

    auto menu = Menu::create( pCloseItem, NULL );
    menu->setPosition( Point::ZERO );
    this->addChild( menu );

    return true;
}

void HighScoreScene::GoToMainScene( cocos2d::Ref *sender )
{
    auto scene = MainMenuScene::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( 0.5, scene ) );
}
