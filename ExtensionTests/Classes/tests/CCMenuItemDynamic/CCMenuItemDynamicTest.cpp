//
//  AdvanceSpriteTest.cpp
//  test
//
//  Created by varadharaj on 16/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "CCMenuItemDynamicTest.h"

using namespace cocos2d;


void CCMenuItemDynamicTestScene::runThisTest()
{
    CCLayer* pLayer = new CCMenuItemDynamicTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}

CCMenuItemDynamicTest::CCMenuItemDynamicTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );
   
    m_pMenuItemDynamic = new CCMenuItemDynamic();

	CCSize minSize = CCSize(20,20);

	m_pMenuItemDynamic = CCMenuItemDynamic::dynamicItemWithText("Example Text",  "fonts/futura-48.fnt", minSize, "r1.png", "r2.png", this, menu_selector(CCMenuItemDynamicTest::menuCallback));
    m_pMenuItemDynamic->setPosition(ccp(s.width/2,s.height/2));
    
    addChild(m_pMenuItemDynamic);
    //m_pAdvanceSprite->addFrames("animations/grossini-aliases.plist", "animations/grossini-aliases.png");
    //m_pAdvanceSprite->startAnimation(1, 14, -1, 0, this, 5, false, false);
}

void CCMenuItemDynamicTest::onEnter()
{
    
}

std::string CCMenuItemDynamicTest::title()
{
    return "CCMenuItemDynamic Test";
}

CCMenuItemDynamicTest::~CCMenuItemDynamicTest()
{
    CC_SAFE_RELEASE(m_pMenuItemDynamic);
}

void CCMenuItemDynamicTest::menuCallback(CCObject* pSender)
{
}