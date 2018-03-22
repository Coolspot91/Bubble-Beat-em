#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "NativeUtils.h"
#include "PlayGameConstants.h"
//#include "GUI/CCEditBox/CCEditBox.h"
//#include "GUI/CCEditBox/CCEditBox.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    //layer->setPhyWorld(scene->getPhysicsWorld());
    //scene->getPhysicsWorld()->setGravity(CCPoint(0,-9.81));

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//////BUG LOG
//1. Balls shoot fast the further u swipe away.					****FIXED
//2. Balls shooting through bounding box.						****FIXED
//3. Balls not deleting properly.( from vector, and spirits).	****NotreallyFIXED
//4. Score adding up wrong. 									****FIXED
//5. Crashs sometimes when deleting balls.
//6. Shooting quick adds impulse to same ball twice.			****FIXED
//7. If a ball hits the cannon, cannon spins out of control
/////////

int HelloWorld::score = 0;

bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    //NativeUtils::signIn();

	/*sqlite3 *pdb=NULL;
	//std::string path=CCFileUtils::sharedFileUtils()->getWriteablePath()+"save.db3";
	std::string path=CCFileUtils::sharedFileUtils()->getWritablePath();

	std::string sql;
	int result;
	result=sqlite3_open(path.c_str(),&pdb);
	if(result!=SQLITE_OK)
		CCLog("open database failed,  number%d",result);


	std::string dbPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("save.db3");

	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	        dbPath  = CCFileUtils::sharedFileUtils()->getWritablePath();
	        dbPath  += "/save.db3";

	        FILE* file = fopen(dbPath.c_str(), "r");
	        if (file == nullptr)
	        {
	            unsigned long size;
	            const char* data = (char*) CCFileUtils::sharedFileUtils()->getFileData("dict.db", "rb", &size);
	            //unsigned char *readData = CCFileUtils::getFileData(“db.sqlite”,“r”,&readSize);
	            file = fopen(dbPath.c_str(), "wb");
	            fwrite(data, size, 1, file);
	            CC_SAFE_DELETE_ARRAY(data);
	        }
	        fclose(file);
	#endif

	result=sqlite3_exec(pdb,"create table student(ID integer primary key autoincrement,name text,sex text)",NULL,NULL,NULL);
	if(result!=SQLITE_OK)
		CCLog("create table failed");

	sql="insert into student  values(1,'zhycheng','male')";
	result=sqlite3_exec(pdb,sql.c_str(),NULL,NULL,NULL);
	if(result!=SQLITE_OK)
		CCLog("insert data failed!");


	sql="insert into student  values(2,'liuyali','female')";
	result=sqlite3_exec(pdb,sql.c_str(),NULL,NULL,NULL);
	if(result!=SQLITE_OK)
		CCLog("insert data failed!");

	sql="insert into student  values(3,'zhy_cheng','male')";
	result=sqlite3_exec(pdb,sql.c_str(),NULL,NULL,NULL);
	if(result!=SQLITE_OK)
		CCLog("insert data failed!");

	//sql="delete from student where ID=1";
	//result=sqlite3_exec(pdb,sql.c_str(), ,NULL,NULL);
	//if(result!=SQLITE_OK)
	//	CCLog("delete data failed!");



	char **re;

	int r,c;

	sqlite3_get_table(pdb,"select * from student",&re,&r,&c,NULL);

	CCLog("row is %d,column is %d",r,c);

	CCLabelTTF *liu=CCLabelTTF::create(re[2*c+1],"Arial",24);
	liu->setPosition(ccp(200,200));
	addChild(liu,1);
	//CCLog(re[2*c+1]);


	sqlite3_free_table(re);

	sqlite3_close(pdb);*/



    score =0;
    lvl = 1;
    ballsRemaing=4;//4
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("popsound.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("howitzer_cannon_single_shot.mp3");//cannonShot
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("buying_power.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("buying_power.mp3",true);

    cocos2d::CCSprite * backroundSp = Sprite::create("Sprite_background_effects_0015.png");
    backroundSp->setScaleX((visibleSize.width / backroundSp->getContentSize().width) * 1);
    backroundSp->setScaleY((visibleSize.height / backroundSp->getContentSize().height) * 1);
    backroundSp->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    this->addChild(backroundSp);

    cocos2d::CCSprite * borderSp = Sprite::create("Border.png");
    auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    //auto edgeNode = Node::create();
    borderSp->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    borderSp->setPhysicsBody(body);
    this->addChild(borderSp);

    myCannon.createCannon(CCPoint(visibleSize.width/2,origin.y + visibleSize.height *.94), this);
    myCannon.mySprite->getPhysicsBody()->setGravityEnable(false);
   // this->addChild(&myCannon);

    cannonOffset = CCPoint(myCannon.mySprite->getPositionX(), myCannon.mySprite->getPositionY() +myCannon.mySprite->getContentSize().height/2);

    myBall.createOBject("CloseNormal.png",cannonBallDir, 2, 150 , .25, this);
    myBall.mySprite->getPhysicsBody()->setGravityEnable(false);
    myBall.mySprite->getPhysicsBody()->setVelocityLimit(250);
    cannonBallz.pushBack(&myBall);
    myBall.AddBallImpulse = true;
    //this->addChild(myBall.mySprite);
    //this->addChild(&myBall);
    //createBall = true;

    myWall.createObject("boulder.png",CCPoint(origin.x +visibleSize.width/2,origin.y + visibleSize.height*.30), this ,1);
    wallObjects.pushBack(&myWall);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    Device::setAccelerometerEnabled(true);
    auto listener2 = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration,this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2,this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    this->schedule( schedule_selector(HelloWorld::update), 0.01 );


    auto closeItem = MenuItemImage::create("ShootButton.png","ShootButton.png",CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                           origin.y + visibleSize.height/2));

    cocos2d::MenuItem* addBallItem = cocos2d::MenuItemFont::create( "Main Menu", CC_CALLBACK_1( HelloWorld::returnToMenu, this ) );
    //auto addBallItem = MenuItemImage::create("CloseSelected.png","CloseSelected.png",CC_CALLBACK_1(HelloWorld::addBallsCallback, this));
    addBallItem->setPosition(Vec2(origin.x + visibleSize.width *.9 ,
                              origin.y + visibleSize.height *.95));
    addBallItem->setScale(visibleSize.height * .0016 );
    addBallItem->setColor(Color3B::YELLOW);

    auto menu = Menu::create(closeItem,addBallItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    scoreLabel = Label::createWithTTF("Score : ","fonts/Marker Felt.ttf",visibleSize.height * .05);
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width *.065,  origin.y + visibleSize.height *.95 ));
    this->addChild(scoreLabel);

    ballsRemainingLabel = Label::createWithTTF("Balls Remaining : ","fonts/Marker Felt.ttf",visibleSize.height * .05);
    ballsRemainingLabel->setPosition(Vec2(origin.x + visibleSize.width *.13,  origin.y + visibleSize.height *.90 ));
    this->addChild(ballsRemainingLabel);

    //lvlLabel = Label::createWithTTF("Level : ","fonts/Marker Felt.ttf",32);
    lvlLabel = LabelTTF::create( "Level : ", "fonts/Marker Felt.ttf", visibleSize.height * .05 );
    lvlLabel->setPosition(Vec2(origin.x + visibleSize.width *.065,  origin.y + visibleSize.height *.85 ));
    this->addChild(lvlLabel);


    flashInformationLabel = Label::createWithTTF("Lvl up .New Ball Added ! ","fonts/Marker Felt.ttf",visibleSize.height * .05);
    flashInformationLabel->setPosition(Vec2(origin.x + visibleSize.width/2,  origin.y + visibleSize.height/2  ));
    this->addChild(flashInformationLabel);
    flashInformationLabel->setVisible(false);

    lastBallLabel = Label::createWithTTF("Last ball.. ","fonts/Marker Felt.ttf",visibleSize.height * .05);
    lastBallLabel->setPosition(Vec2(origin.x + visibleSize.width/2,  origin.y + visibleSize.height*.6  ));
    this->addChild(lastBallLabel);
    lastBallLabel->setColor(Color3B::RED);
    lastBallLabel->setVisible(false);


    return true;
}
int HelloWorld::getScore()
{
	return HelloWorld::score;
}
int HelloWorld::getRandomNumber(int from ,int to)
{
    return (int)from + arc4random() % (to-from+1);
}
void HelloWorld::update(float  dt)
{
	if( score > 1 && score <= 4 && bonusBallz == false)
	{lvl=2; ballsRemaing+=1; bonusBallz= true;
	flashflashInformation = true;}

	else if ( score > 4 && score <= 9 && bonusBallz == true)
	{
		lvl = 3;ballsRemaing+=1; bonusBallz= false;
		myWall.createObject("boulder.png",CCPoint(origin.x +visibleSize.width*.15,origin.y + visibleSize.height*.35), this, .7);
		wallObjects.pushBack(&myWall);
		myWall.createObject("boulder.png",CCPoint(origin.x +visibleSize.width*.85,origin.y + visibleSize.height*.35), this, .7);
		wallObjects.pushBack(&myWall);
		flashflashInformation = true;
	}

	else if ( score > 9 && score <= 15 && bonusBallz == false)
	{
		lvl = 4;ballsRemaing+=2; bonusBallz= true;
		myWall.createObject("boulder.png",CCPoint(origin.x +visibleSize.width*.30,origin.y + visibleSize.height*.30), this, .7);
		wallObjects.pushBack(&myWall);
		myWall.createObject("boulder.png",CCPoint(origin.x +visibleSize.width*.70,origin.y + visibleSize.height*.30), this, .7);
		wallObjects.pushBack(&myWall);
		flashflashInformation = true;
	}

	else if ( score > 15 && bonusBallz == true)
	{
		lvl = 5;ballsRemaing+=2; bonusBallz= false;
		flashflashInformation = true;
	}

	if(createBall==true)
	{
		delay+=1;
	}

	if(flashflashInformation == true)
	{
		flashInformationLabel->setVisible(true);
		visibleCounter += dt;
	}
	if(visibleCounter> 2)
	{
		flashInformationLabel->setVisible(false);
		flashflashInformation= false;
		visibleCounter=0;
	}

    if(delay > 50 && createBall==true && ballsRemaing > 0)
    {
    	int randomNumber = getRandomNumber(1 ,lvl);
    	if (randomNumber==1)
		{
    		myBall.createOBject("CloseNormal.png",cannonBallDir, 2, 150, .4,this );
    		myBall.mySprite->getPhysicsBody()->setVelocityLimit(250);
		}
    	else if (randomNumber==2)
    	{
    		myBall.createOBject("CloseRedNormal.png",cannonBallDir, 3, 250,.25,this );
    		myBall.mySprite->getPhysicsBody()->setVelocityLimit(200);
    	}
    	else if (randomNumber==3)
    	{
    		myBall.createOBject("CloseGreenNormal.png",cannonBallDir, 4, 120, .3, this );
    		myBall.mySprite->getPhysicsBody()->setVelocityLimit(350);
    	}
    	else if (randomNumber==4)
    	{
    	    myBall.createOBject("ClosePurpleNormal.png",cannonBallDir, 5, 150, .4, this );
    	    myBall.mySprite->setScale(.7);
    	    myBall.mySprite->getPhysicsBody()->setVelocityLimit(300);

    	}
    	else if (randomNumber==5)
    	{
    	    myBall.createOBject("CloseGoldNormal.png",cannonBallDir, 6, 300, .5, this );
    	    myBall.mySprite->setScale(1.3);
    	    myBall.mySprite->getPhysicsBody()->setVelocityLimit(400);

    	}
    	myBall.mySprite->getPhysicsBody()->setGravityEnable(false);
    	myBall.AddBallImpulse = true;
		cannonBallz.pushBack(&myBall);
		//this->addChild(myBall.mySprite);
		createBall=false;
		delay = 0;
    }

	Ball* endBall = cannonBallz.back();
	if (ballsRemaing <= 0 && (endBall->mySprite->getPhysicsBody()->getVelocity().x <= 2.5 && endBall->mySprite->getPhysicsBody()->getVelocity().x >= -2.5
			&& endBall->mySprite->getPhysicsBody()->getVelocity().y <= 2 && endBall->mySprite->getPhysicsBody()->getVelocity().y >= -2))
	{
		auto scene = GameOverScene::createScene();
		Director::getInstance( )->replaceScene( TransitionFade::create( 1.0, scene ) );
	}

    //  loop through Balls
/*    for (Ball* numberOfBalls: this->cannonBallz)
    {
        if (numberOfBalls->hit == true )
        {
        	//numberOfBalls
        	//numberOfBalls->getPhysicsBody()->removeFromWorld();
        	score++;
        	numberOfBalls->hit = false;
        	this->removeChild(numberOfBalls,true);
        	this->cannonBallz.eraseObject(numberOfBalls);
        }
    }*/

    for (Ball* numberOfBalls: this->cannonBallz)
    {
    	if(numberOfBalls->mySprite->getPhysicsBody()->getTag() == 10)
    	{
    		//numberOfBalls->destroyBall();
    		//numberOfBalls->getPhysicsBody()->removeFromWorld();

    		//numberOfBalls->mySprite->setScale(.5);

    		//this->removeChild(numberOfBalls,true);
    		//this->cannonBallz.eraseObject(numberOfBalls);
    		//score++;
    	}
    }

    const int labelLength = 32;
    char scoreLabelText[labelLength];
    char ballsRemaingLabelText[labelLength];
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    snprintf(scoreLabelText, labelLength, "Score: %i", score);
    scoreLabel->setString(scoreLabelText);

    snprintf(ballsRemaingLabelText, labelLength, "Balls Remaining: %i", ballsRemaing);
    ballsRemainingLabel->setString(ballsRemaingLabelText);

    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width *.065,  origin.y + visibleSize.height *.95));
    ballsRemainingLabel->setPosition(Vec2(origin.x + visibleSize.width *.13,  origin.y + visibleSize.height *.90 ));
    //CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);

    __String *tempLvl = __String::createWithFormat( "Level: %i", lvl );
    auto strLvl = tempLvl->getCString();
    lvlLabel->setString(strLvl);

    if( ballsRemaing <= 1)
    {
    	lastBallLabel->setVisible(true);
    }
    else
    {
    	lastBallLabel->setVisible(false);
    }


    //CCLog("%i",MainMenuScene::name);
    CCLog("%i", visibleSize.width);
}
void HelloWorld::onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event)
{
	//CCLog("%f", acc->z);
	//cube->myPlayer->setPosition(CCPointMake((acc->x *6) + cube->myPlayer->getPosition().x,(acc->y*6) + cube->myPlayer->getPosition().y));
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
	myBall.mySprite->getPhysicsBody()->resetForces();
	myCannon.mySprite->getPhysicsBody()->resetForces();
	myCannon.mySprite->getPhysicsBody()->setAngularVelocity(0);

	touchPosition = touch->getLocationInView();
	touchPosition = CCDirector::sharedDirector()->convertToGL(touchPosition);
	touchPosition = this->convertToNodeSpace(touchPosition);

	direction.x = touchPosition.x - myCannon.mySprite->getPosition().x;
	direction.y = touchPosition.y - myCannon.mySprite->getPosition().y;
	float angleRadians = atan2f(direction.x,direction.y);

	float angleInDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	myCannon.mySprite->setRotation(angleInDegrees);

	float radiansAngle = myCannon.mySprite->getRotation() * M_PI / 180;
	cannonOffset.x = (myCannon.mySprite->getContentSize().width ) * sin(radiansAngle);
	cannonOffset.y = (myCannon.mySprite->getContentSize().width ) * cos(radiansAngle);
	cannonBallDir = ccpAdd(cannonOffset, myCannon.mySprite->getPosition());
	if(myBall.stickToCannon == true){
	myBall.mySprite->setPosition(cannonBallDir);
	}
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
	createBall = true;
	myBall.stickToCannon = false;
	myBall.mySprite->getPhysicsBody()->setGravityEnable(true);
    myBall.mySprite->getPhysicsBody()->resetForces();
    myCannon.mySprite->getPhysicsBody()->resetForces();
    myCannon.mySprite->getPhysicsBody()->setAngularVelocity(0);

    if(myBall.AddBallImpulse == true)
    {
    	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("howitzer_cannon_single_shot.mp3");
    	myBall.mySprite->getPhysicsBody()->applyImpulse(250*direction);
    	ballsRemaing--;
    	myBall.AddBallImpulse = false;
    }
    //NativeUtils::submitScore("CgkItPOI3oUdEAIQAQ", HelloWorld::score);
/*    if(NativeUtils::isSignedIn())
    {

    }*/

    //cocos2d::JniMethodInfo methodInfo;


    /*if ( cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com\Ngames\MouseHunt", "gameServicesSignIn", "()V"))
    {


    //jint retV =
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }*/


    /*if ( cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com\Ngames\MouseHunt", "updateTopScoreLeaderboard", "(I;)Ljava/lang/String;"))
    {


    //jint retV =
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,HelloWorld::score);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }*/
/*    if (! cocos2d::JniHelper::getStaticMethodInfo(methodInfo, "com\Ngames\MouseHunt", "showLeaderboards", "()V"))
    {
    	return;
    }
    methodInfo.env->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
    methodInfo.env->DeleteLocalRef(methodInfo.classID);*/

}
void HelloWorld::returnToMenu(Ref* pSender)
{
	//Director::getInstance()->end();
	auto scene = MainMenuScene::createScene();
	Director::getInstance( )->replaceScene( TransitionFade::create( 0.5, scene ) );
}

bool HelloWorld::onContactBegin(cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    // check if the bodies have collided
    if ( ( 2 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) || ( 2 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) )
    {
        //CCLOG( "COLLISION HAS OCCURED" );
        this->removeChild(a->getNode(),true);
		//this->removeChild(b->getNode(),true);
		//this->cannonBallz.getIndex(numberOfBalls+1);
    	//this->removeChild(numberOfBalls->mySprite,true);
    	//this->cannonBallz.eraseObject(numberOfBalls);
		//int bTag1 = a->getNode()->getTag();
		//int bTag2 = b->getNode()->getTag();
		a->removeFromWorld();
		//b->removeFromWorld();
		a->setTag(10);
		b->setTag(10);
		this->cannonBallz.popBack();
		//this->cannonBallz.popBack();
		score++;
		ballsRemaing = ballsRemaing+1;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("popsound.wav");

    }

    if ( ( 3 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ) || ( 3 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ) )
        {
            this->removeChild(a->getNode(),true);
    		a->removeFromWorld();
    		score++;
    		this->cannonBallz.popBack();
    		ballsRemaing = ballsRemaing+1;
    		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("popsound.wav");
        }

    if ( ( 4 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask() ) || ( 4 == a->getCollisionBitmask() && 4 == b->getCollisionBitmask() ) )
        {
            this->removeChild(a->getNode(),true);
    		//this->removeChild(b->getNode(),true);
    		a->removeFromWorld();
    		//b->removeFromWorld();
    		a->setTag(10);
    		b->setTag(10);
    		this->cannonBallz.popBack();
    		//this->cannonBallz.popBack();
    		score++;
    		ballsRemaing = ballsRemaing+1;
    		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("popsound.wav");
        }

    if ( ( 5 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask() ) || ( 5 == a->getCollisionBitmask() && 5 == b->getCollisionBitmask() ) )
        {
            this->removeChild(a->getNode(),true);
    		//this->removeChild(b->getNode(),true);
    		a->removeFromWorld();
    		//b->removeFromWorld();
    		a->setTag(10);
    		b->setTag(10);
    		this->cannonBallz.popBack();
    		//this->cannonBallz.popBack();
    		HelloWorld::score++;
    		ballsRemaing = ballsRemaing+1;
    		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("popsound.wav");
        }

    if ( ( 6 == a->getCollisionBitmask() && 6 == b->getCollisionBitmask() ) || ( 6 == a->getCollisionBitmask() && 6 == b->getCollisionBitmask() ) )
        {
            this->removeChild(a->getNode(),true);
    		//this->removeChild(b->getNode(),true);
    		a->removeFromWorld();
    		//b->removeFromWorld();
    		a->setTag(10);
    		//b->setTag(10);
    		this->cannonBallz.popBack();
    		//this->cannonBallz.popBack();
    		HelloWorld::score++;
    		ballsRemaing = ballsRemaing+1;
    		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("popsound.wav");
        }

    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	return true;
}
