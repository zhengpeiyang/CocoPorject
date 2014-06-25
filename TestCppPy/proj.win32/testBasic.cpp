#include "testBasic.h"
#include "controller.h"

TestScene::TestScene(bool bPortrait)
{
	CCScene::init();
}

void TestScene::onEnter()
{
	CCScene::onEnter();
	
	CCLabelTTF* label = CCLabelTTF::create("MainMenu","Arial",20);
	CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label,this,menu_selector(TestScene::MainMenuCallback));
	CCMenu* pMenu = CCMenu::create(pMenuItem,NULL);

	pMenu->setPosition(CCPointZero);
	pMenuItem->setPosition(ccp(VisibleRect::right().x - 50,VisibleRect::top().y + 25));
	addChild(pMenu,1);
}

void TestScene::MainMenuCallback(CCObject* pSender)
{
	CCScene* pScene = CCScene::create();
	CCLayer* pLayer = new TestController();
	pLayer->autorelease();

	pScene->addChild(pLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}