#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

typedef struct tagResource
 {
     cocos2d::CCSize size;
     char directory[100];
 }Resource;

 static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "iphone" };
 static Resource smallHDResource  =  { cocos2d::CCSizeMake(960, 640), "iphonehd" };
 static Resource mediumHDResource  =  { cocos2d::CCSizeMake(1136, 640), "iphone5hd" };
 static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "ipad"   };
 static Resource largeResource  =  { cocos2d::CCSizeMake(1920, 1200), "ipadhd" };

 static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);


bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    //auto fileUtils = FileUtils::getInstance();
    //auto screenSize = glview->getFrameSize();
    //std::vector<std::string> resDirOrders;

/*    if (2048 == screenSize.width || 2048 == screenSize.height)
    {
        resDirOrders.push_back("ipadhd");
        resDirOrders.push_back("ipad");
        resDirOrders.push_back("iphonehd5");
        resDirOrders.push_back("iphonehd");
        resDirOrders.push_back("iphone");

        glview->setDesignResolutionSize(2048, 1536, ResolutionPolicy::NO_BORDER);
    }
    else if (1024 == screenSize.width || 1024 == screenSize.height)
    {
        resDirOrders.push_back("ipad");
        resDirOrders.push_back("iphonehd5");
        resDirOrders.push_back("iphonehd");
        resDirOrders.push_back("iphone");

        glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::NO_BORDER);
    }
    else if (1136 == screenSize.width || 1136 == screenSize.height)
    {
        resDirOrders.push_back("iphonehd5");
        resDirOrders.push_back("iphonehd");
        resDirOrders.push_back("iphone");

        glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::NO_BORDER);
    }
    else if (960 == screenSize.width || 960 == screenSize.height)
    {
        resDirOrders.push_back("iphonehd");
        resDirOrders.push_back("iphone");

        glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
    }
    else
    {
        if (screenSize.width > 1080)
        {
            resDirOrders.push_back("iphonehd");
            resDirOrders.push_back("iphone");

            glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
        }
        else
        {
            resDirOrders.push_back("iphone");

            glview->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);
        }
    }
    fileUtils->setSearchPaths(resDirOrders);*/

    auto fileUtils = FileUtils::getInstance();
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionExactFit);

    CCSize frameSize = glview->getFrameSize();
    std::vector<std::string> searchPath;

    // In this demo, we select resource according to the frame's height.
    // If the resource size is different from design resolution size, you need to set contentScaleFactor.
    // We use the ratio of resource's height to the height of design resolution,
    // this can make sure that the resource's height could fit for the height of design resolution.

    // if the frame's height is larger than the height of medium resource size, select large resource.
    if (frameSize.height > mediumResource.size.height)
    {
        searchPath.push_back(largeResource.directory);
        director->setContentScaleFactor(largeResource.size.height/designResolutionSize.height);
    }
    // if the frame's height is larger than the height of small resource size, select medium resource.
    else if (frameSize.height > mediumHDResource.size.height)
    {
        searchPath.push_back(mediumResource.directory);
        director->setContentScaleFactor(mediumResource.size.height/designResolutionSize.height);
    }

    else if (frameSize.height > smallHDResource.size.height)
    {
        searchPath.push_back(mediumHDResource.directory);
        director->setContentScaleFactor(mediumHDResource.size.height/designResolutionSize.height);
    }

    else if (frameSize.height > smallResource.size.height)
    {
        searchPath.push_back(smallHDResource.directory);
        director->setContentScaleFactor(smallHDResource.size.height/designResolutionSize.height);
    }
    // if the frame's height is smaller than the height of medium resource size, select small resource.
    else
    {
        searchPath.push_back(smallResource.directory);
        director->setContentScaleFactor(smallResource.size.height/designResolutionSize.height);
    }

    fileUtils->setSearchPaths(searchPath);

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    //director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MainMenuScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
