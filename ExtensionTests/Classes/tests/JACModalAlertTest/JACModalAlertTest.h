//
//  JACModalAlertTest.h
//  test
//
//  Created by Jose Antonio Andujar Clavell on 10/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//
#ifndef _JACMODAL_ALERT_TEST_H
#define _JACMODAL_ALERT_TEST_H

#include "JACModalAlert/JACModalAlert.h"
#include "../testBasic.h"

class JACModalAlertTest : public cocos2d::CCLayer
{  
protected:
	int currentTest;
public:
    JACModalAlertTest();
    ~JACModalAlertTest();
    
    virtual void onEnter(void);
	virtual std::string title();

	void menuCallback();
};

class JACModalAlertTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif