//
//  SlidingMenuTest.h
//  test
//
//  Created by Jose Antonio Andujar Clavell on 12/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//
#ifndef _SLIDINGMENU_TEST_H
#define _SLIDINGMENU_TEST_H

#include "SlidingMenu/SlidingMenu.h"
#include "../testBasic.h"

class SlidingMenuTest : public cocos2d::CCLayer
{
protected:
    SlidingMenuGrid *m_pSlidingMenu;
    
public:
    SlidingMenuTest();
    ~SlidingMenuTest();
    
    virtual void onEnter(void);
	virtual std::string title();
};

class SlidingMenuTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif