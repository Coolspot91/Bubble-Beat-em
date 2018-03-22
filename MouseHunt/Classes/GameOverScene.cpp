#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
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

    __String *tempScore = __String::createWithFormat( "Score: %i", HelloWorld::score );
    auto scoreLabel = LabelTTF::create( tempScore->getCString(), "fonts/Marker Felt.ttf", 32 );
    scoreLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x,  visibleSize.height / 2 + origin.y ));
    this->addChild(scoreLabel);


/*    pTextField = CCTextFieldTTF::textFieldWithPlaceHolder("click here for input", "Thonburi", 20);
    pTextField->setPosition(ccp(visibleSize.width/2,200));
    addChild(pTextField);*/


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

    //__String *tempHighScore = __String::createWithFormat(  "High Score %i", highScore );
    //std::string strHighScore = highScore.str();
    auto tempHighScore = "High Score " + highScoreName + " : " + stringHighScore;

    auto highScoreLabel = LabelTTF::create( tempHighScore, "fonts/Marker Felt.ttf", 32 );

    highScoreLabel->setColor( Color3B::YELLOW );
    highScoreLabel->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height *.40 + origin.y ) );
    this->addChild( highScoreLabel );

    cocos2d::Label * gameOverLabel = Label::createWithTTF("Game Over ","fonts/Marker Felt.ttf",32);
    gameOverLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x,  visibleSize.height *.80 + origin.y ));
    this->addChild(gameOverLabel);

    cocos2d::Label * yourRankLabel = Label::createWithTTF("Emmm..","fonts/Marker Felt.ttf",32);
    yourRankLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x,  visibleSize.height *.65 + origin.y ));
    if( HelloWorld::score <= 5)
    {
    	yourRankLabel->setString("You're a terrible person");
    }
    else if(HelloWorld::score <= 10)
    {
    	yourRankLabel->setString("Not bad but its a simple game..");
    }
    else if(HelloWorld::score <= 15)
    {
    	yourRankLabel->setString("A grand score");
    }
    else if(HelloWorld::score <= 20)
    {
    	yourRankLabel->setString("Finally you achieved something");
    }
    else if(HelloWorld::score <= 30)
    {
    	yourRankLabel->setString("Aren't you great");
    }
    else
    {
    	yourRankLabel->setString("Captain MY CAPTAIN");
    }
    this->addChild(yourRankLabel);

    auto closeItem = MenuItemImage::create("ShootButton.png","ShootButton.png",CC_CALLBACK_1(GameOverScene::menuCloseCallback, this));
        closeItem->setPosition(Vec2(origin.x + visibleSize.width/2 ,
                               origin.y + visibleSize.height *.20));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void GameOverScene::menuCloseCallback(Ref* pSender)
{
	//Director::getInstance()->end();
	auto scene = MainMenuScene::createScene();
	Director::getInstance( )->replaceScene( TransitionFade::create( 0.5, scene ) );

}
