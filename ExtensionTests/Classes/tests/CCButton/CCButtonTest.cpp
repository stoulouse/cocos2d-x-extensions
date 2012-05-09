//
//  CCButtonTest.cpp
//  test
//
//  Created by Jose Antonio Andujar Clavell on 09/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//

#include "CCButtonTest.h"

using namespace cocos2d;


void CCButtonTestScene::runThisTest()
{
    CCLayer* pLayer = new CCButtonTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}

CCButtonTest::CCButtonTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );
   
	m_pCCButton = CCButton::buttonWithFiles(this,menu_selector(CCButtonTest::menuCallback), "r1.png", "r2.png", NULL);
	m_pCCButton->setTitleForState("Show", CCControlStateNormal);
    m_pCCButton->setPosition(ccp(s.width/2,s.height/2));
    
	//Other uses
	/*
	2:
	CCSprite * tmpBgSprite = CCSprite::spriteWithFile("r1.png");
    CCSprite * tmpBgSprite2 = CCSprite::spriteWithFile("r2.png");

    m_pCCButton = CCButton::buttonWithFiles(this,menu_selector(CCButtonTest::menuCallback), NULL,NULL, NULL);
    tmpBtn->setBackgroundImageForState(tmpBgSprite, CCControlStateNormal);
    tmpBtn->setBackgroundImageForState(tmpBgSprite2, CCControlStateSelected);

    tmpBtn->setTitleForState("Show", CCControlStateNormal);
    3:
    m_pCCButton = CCButton::buttonWithFiles(this,menu_selector(CCButtonTest::menuCallback), NULL,NULL, NULL);
    tmpBtn->setTitleForState("Show", CCControlStateNormal);

    4:
	m_pCCButton = CCButton::buttonWithFiles(this,menu_selector(CCButtonTest::menuCallback), "r1.png", "r2.png", NULL);
	*/

    addChild(m_pCCButton);
	setIsTouchEnabled(true);
}

void CCButtonTest::onEnter()
{
    
}

std::string CCButtonTest::title()
{
    return "CCButton Test";
}

CCButtonTest::~CCButtonTest()
{
    //CC_SAFE_RELEASE(m_pDecoratedBox);
}

void CCButtonTest::menuCallback(CCObject* pSender)
{
	CCLog("Button pushed");
}
