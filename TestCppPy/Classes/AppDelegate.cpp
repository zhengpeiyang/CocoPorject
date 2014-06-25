#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "controller.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	CCSize designSize = CCSizeMake(480,320);

	if(screenSize.height > 320)
	{

		CCSize resourceSize = CCSizeMake(960,540);
		CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");
		pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
	}

	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width,designSize.height,kResolutionNoBorder);
	pDirector->setDisplayStats(true);
	pDirector->setAnimationInterval(1.0/60);

	CCScene *pScene = CCScene::create();
	CCLayer *pLayer = new TestController();
	pLayer->autorelease();

	pScene->addChild(pLayer);
	pDirector->runWithScene(pScene);
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
