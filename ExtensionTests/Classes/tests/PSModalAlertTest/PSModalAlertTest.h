//
//  PSModalAlertTest.h
//  test
//
//  Created by Jose Antonio Andujar Clavell on 09/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//
#ifndef _PSMODAL_ALERT_TEST_H
#define _PSMODAL_ALERT_TEST_H

#include "PSModalAlert/PSModalAlert.h"
#include "../testBasic.h"

class PSModalAlertTest : public cocos2d::CCLayer
{  
public:
    PSModalAlertTest();
    ~PSModalAlertTest();
    
    virtual void onEnter(void);
	virtual std::string title();

	void menuCallback();
};

class PSModalAlertTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif