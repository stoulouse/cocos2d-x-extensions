//
//  CCTabViewTest.h
//  test
//
//  Created by Jose Antonio Andujar Clavell on 10/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//
#ifndef _CCTAB_VIEW_TEST_H
#define _CCTAB_VIEW_TEST_H

#include "CCTabView/CCTabView.h"
#include "../testBasic.h"

class CCTabViewTest : public cocos2d::CCLayer
{  
protected:
	int currentTest;
public:
    CCTabViewTest();
    ~CCTabViewTest();
    
    virtual void onEnter(void);
	virtual std::string title();
};

class CCTabViewTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif