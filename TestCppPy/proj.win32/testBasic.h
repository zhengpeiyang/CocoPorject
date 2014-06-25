#ifndef _TEST_BASIC_H_
#define _TEST_BASIC_H_

#include "cocos2d.h"
#include "VisibleRect.h"

USING_NS_CC;
using namespace std;

class TestScene : public CCScene
{
public:
	TestScene(bool bPortrait = false);
	virtual void onEnter();
	virtual void runThisTest()=0;
	virtual void MainMenuCallback(CCObject* pSender);

};


#endif