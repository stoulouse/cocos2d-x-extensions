//
//  CCButtonTest.h
//  test
//
//  Created by Jose Antonio Andujar Clavell on 09/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//
#ifndef _CCBUTTON_TEST_H
#define _CCBUTTON_TEST_H

#include "CCButton/CCButton.h"
#include "../testBasic.h"

class CCButtonTest : public cocos2d::CCLayer
{
protected:
    CCButton *m_pCCButton;
    
public:
    CCButtonTest();
    ~CCButtonTest();
    
    virtual void onEnter(void);
	virtual std::string title();

	void menuCallback(CCObject* pSender);
};

class CCButtonTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif