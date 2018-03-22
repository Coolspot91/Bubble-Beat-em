#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "TutorialScene.h"
#include "HighScoreScene.h"

USING_NS_CC;

std::string MainMenuScene::name;// = "";

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
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

    auto titleSprite = Sprite::create( "BubbleLogo2.png" );
    titleSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height *.80 ) );

    this->addChild( titleSprite );

    /*auto playItem = MenuItemImage::create( "Play Button.png", "Play Button Clicked.png", CC_CALLBACK_1( MainMenuScene::GoToGameScene, this ) );
    playItem->setScaleX((visibleSize.width / playItem->getContentSize().width) * .2);
    playItem->setScaleY((visibleSize.height / playItem->getContentSize().height) * .12);
    playItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height *.35 + origin.y ) );*/


    cocos2d::MenuItem* playItem = cocos2d::MenuItemFont::create( "Start Game", CC_CALLBACK_1( MainMenuScene::GoToGameScene, this ) );
    playItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height *.45 + origin.y ) );
    playItem->setColor(Color3B::YELLOW);
    playItem->setScale(visibleSize.height * .003 );
    cocos2d::MenuItem* pHelpItem = cocos2d::MenuItemFont::create("Help Screen",CC_CALLBACK_1(MainMenuScene::GoToHelpScene,this));
    pHelpItem->setScale(visibleSize.height * .003 );
    pHelpItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height *.30 + origin.y ) );
    pHelpItem->setColor(Color3B::YELLOW);
    cocos2d::MenuItem* pScoreItem = cocos2d::MenuItemFont::create("High Score",CC_CALLBACK_1(MainMenuScene::GoToHighScoreScene,this));
    pScoreItem->setScale(visibleSize.height * .003 );
    pScoreItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height *.15 + origin.y ) );
    pScoreItem->setColor(Color3B::YELLOW);


    pTextField = CCTextFieldTTF::textFieldWithPlaceHolder(name, "Thonburi", 20);
    pTextField->setPosition(Point(visibleSize.width *.85, visibleSize.height *.90 + origin.y ));
    pTextField->setScale(visibleSize.height*.003);
    pTextField->setString(name);
    addChild(pTextField);

    cocos2d::MenuItem* nameItem = cocos2d::MenuItemFont::create( "Enter Name", CC_CALLBACK_1( MainMenuScene::SetUserName, this ) );
    nameItem->setPosition( Point( visibleSize.width *.85 + origin.x, visibleSize.height *.80 + origin.y ) );
    nameItem->setColor(Color3B::YELLOW);
    nameItem->setScale(visibleSize.height*.0015);

    auto menu = Menu::create( playItem, pHelpItem, pScoreItem, nameItem, NULL );
    menu->setPosition( Point::ZERO );

    this->addChild( menu );

    return true;
}

void MainMenuScene::GoToGameScene( cocos2d::Ref *sender )
{
	name = pTextField->getString();
    auto scene = HelloWorld::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( 0.5, scene ) );
}
void MainMenuScene::GoToHelpScene( cocos2d::Ref *sender)
{
	name = pTextField->getString();
	auto scene = TutorialScene::createScene();
	Director::getInstance( )->replaceScene( TransitionFade::create( 0.5, scene ) );
}

void MainMenuScene::SetUserName( cocos2d::Ref *sender )
{
	pTextField->attachWithIME();
	name = pTextField->getString();
	//name = "jay";
}

void MainMenuScene::GoToHighScoreScene( cocos2d::Ref *sender )
{
	name = pTextField->getString();
	auto scene = HighScoreScene::createScene(name);
	Director::getInstance( )->replaceScene( TransitionFade::create( 0.5, scene ) );
}
