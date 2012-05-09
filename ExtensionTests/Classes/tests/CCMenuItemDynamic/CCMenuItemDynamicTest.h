//
//  CCMenuItemDynamicTest.h
//  test
//
//  Created by Jose Antonio Andujar Clavell on 09/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//
#ifndef _CCMENUITEMDYNAMIC_TEST_H
#define _CCMENUITEMDYNAMIC_TEST_H

#include "CCMenuItemDynamic/CCMenuItemDynamic.h"
#include "../testBasic.h"

class CCMenuItemDynamicTest : public cocos2d::CCLayer
{
protected:
    cocos2d:: CCMenuItemSprite *m_pMenuItemDynamic;
    
public:
    CCMenuItemDynamicTest();
    ~CCMenuItemDynamicTest();
    
    virtual void onEnter(void);
	virtual std::string title();

	void menuCallback(CCObject* pSender);
};

class CCMenuItemDynamicTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif