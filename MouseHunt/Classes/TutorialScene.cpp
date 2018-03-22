#include "TutorialScene.h"

USING_NS_CC;

Scene* TutorialScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = TutorialScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TutorialScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create( "HelpScreen.png" );
    backgroundSprite->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );

    this->addChild( backgroundSprite );

/*    auto label = Text::create();
    auto label2 = Text::create();
    auto label3 = Text::create();
    label->setText("The aim of the game is to pop the matching colour balls");
    label2->setText("For each Popped you get +1 score and another ball");
    label3->setText("Use your finger to direct the cannon, and the shhot button to fire");
    label->setFontName("Marker Felt");
    label->setFontSize(30);
    //label->setColor(Color3B(159, 168, 176));
    label->setPosition(Point(size.width / 2, size.height / 2));

    addChild(label);*/

    cocos2d::MenuItem* pCloseItem = cocos2d::MenuItemFont::create("MainMenu",this,menu_selector(TutorialScene::GoToMainScene));
    pCloseItem->setScale(visibleSize.height * .003 );
    pCloseItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height *.20 + origin.y ) );

    auto menu = Menu::create( pCloseItem, NULL );
    menu->setPosition( Point::ZERO );

    this->addChild( menu );

    return true;
}

void TutorialScene::GoToMainScene( cocos2d::Ref *sender )
{
    auto scene = MainMenuScene::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( 0.5, scene ) );
}
