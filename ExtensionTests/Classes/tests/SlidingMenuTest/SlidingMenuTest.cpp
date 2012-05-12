//
//  SlidingMenuTest.cpp
//  test
//
//  Created by Jose Antonio Andujar Clavell on 12/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//

#include "SlidingMenuTest.h"

using namespace cocos2d;


void SlidingMenuTestScene::runThisTest()
{
    CCLayer* pLayer = new SlidingMenuTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}

SlidingMenuTest::SlidingMenuTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );
   
    //objc_selector* selector = @selector(LaunchLevel:);
    int iMaxLevels = 45;
    
    CCMutableArray<CCMenuItemSprite *> *allItems = new CCMutableArray<CCMenuItemSprite*>();
    for (int i = 1; i <= iMaxLevels; ++i)
    {
        CCSprite* normalSprite = CCSprite::spriteWithFile("LevelButton.png");
        CCSprite* selectedSprite = CCSprite::spriteWithFile("LevelButton.png");
        CCMenuItemSprite* item = CCMenuItemSprite::itemFromNormalSprite(normalSprite, selectedSprite);
        allItems->addObject(item);
    }
    
    m_pSlidingMenu = SlidingMenuGrid::menuWithArray(allItems, 5, 4, ccp(s.width/2,s.height/2), CCPointMake(90, 80));
    //m_pSlidingMenu->setPosition(ccp(s.width/2,s.height/2));
    
    addChild(m_pSlidingMenu);
}

void SlidingMenuTest::onEnter()
{
    
}

std::string SlidingMenuTest::title()
{
    return "SlidingMenu Test";
}

SlidingMenuTest::~SlidingMenuTest()
{
    //CC_SAFE_RELEASE(m_pDecoratedBox);
}
