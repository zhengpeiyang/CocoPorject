#include "controller.h"
#include "testResource.h"
#include "tests.h"
#include "VisibleRect.h"

#define LINE_SPACE  40
static CCPoint s_tCurPos = CCPointZero;

static TestScene* CreateTestScene(int nIdx)
{
	CCDirector::sharedDirector()->purgeCachedData();
	TestScene* pScene = NULL;

	switch (nIdx)
	{
	case TEST_ACTIONS:
		pScene = new ActionsTestScene();
		break;
	default:
		break;
	}
	return pScene;
}

TestController::TestController()
	:m_tBeginPos(CCPointZero)
{
	CCMenuItemImage* pcloseItem = CCMenuItemImage::create(s_pPathClose,s_pPathClose,this,menu_selector(TestController::closeCallback));
	CCMenu* pMenu = CCMenu::create(pcloseItem,NULL);
	pMenu->setPosition(CCPointZero);
	pcloseItem->setPosition(ccp(VisibleRect::right().x - 30,VisibleRect::top().y - 30));

	m_pItemMenu = CCMenu::create();
	for(int i = 0 ;i < TESTS_COUNT; i++)
	{
		CCLabelTTF* label = CCLabelTTF::create(g_aTestNames[i].c_str(),"Arial",24);
		CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label,this,menu_selector(TestController::menuCallback));
		m_pItemMenu->addChild(pMenuItem,i+10000);
		pMenuItem->setPosition(ccp(VisibleRect::center().x,(VisibleRect::top().y - (i + 1) * LINE_SPACE)));
	}

	m_pItemMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width,(TESTS_COUNT + 1) * (LINE_SPACE)));
	m_pItemMenu->setPosition(s_tCurPos);
	
	addChild(m_pItemMenu);
	setTouchEnabled(true);
	addChild(pMenu,1);

}


TestController::~TestController()
{

}

void TestController::menuCallback(CCObject * pSender)
{
	CCMenuItem* pMenuItem = (CCMenuItem*)pSender;
	int nIdx = pMenuItem->getZOrder() - 10000;
	

	TestScene* pScene = CreateTestScene(nIdx);
	if(pScene)
	{
		pScene->runThisTest();
		pScene->release();
	}
}

void TestController::closeCallback(CCObject * pSender)
{
	CCDirector::sharedDirector()->end();

}

void TestController::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{

	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	m_tBeginPos = touch->getLocation();
}

void TestController::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint touchLocation = touch->getLocation();
	float nMoveY = touchLocation.y - m_tBeginPos.y;

	CCPoint curPos = m_pItemMenu->getPosition();
	CCPoint nextPos = ccp(curPos.x,curPos.y + nMoveY);

	if(nextPos.y < 0.0f)
	{
		m_pItemMenu->setPosition(CCPointZero);
		return;
	}

	if(nextPos.y > ((TESTS_COUNT + 1) * LINE_SPACE - VisibleRect::getVisibleRect().size.height))
	{
		m_pItemMenu->setPosition(ccp(0,((TESTS_COUNT + 1) * LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
		return;
	}

	m_pItemMenu->setPosition(nextPos);
	m_tBeginPos = touchLocation;
	s_tCurPos = nextPos;
}

