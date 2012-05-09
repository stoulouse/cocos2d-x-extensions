//
//  PSModalAlertTest.cpp
//  test
//
//  Created by Jose Antonio Andujar Clavell on 09/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//

#include "PSModalAlertTest.h"

using namespace cocos2d;


void PSModalAlertTestScene::runThisTest()
{
    CCLayer* pLayer = new PSModalAlertTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}

PSModalAlertTest::PSModalAlertTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );
   
	PSModalAlert::TellStatementOnLayer("bla,bla,bla,",this,this,callfunc_selector(PSModalAlertTest::menuCallback));
}

void PSModalAlertTest::onEnter()
{
    
}

std::string PSModalAlertTest::title()
{
    return "CCButton Test";
}

PSModalAlertTest::~PSModalAlertTest()
{
    //CC_SAFE_RELEASE(m_pDecoratedBox);
}

void PSModalAlertTest::menuCallback()
{
	CCLog("Modal pushed");
}
