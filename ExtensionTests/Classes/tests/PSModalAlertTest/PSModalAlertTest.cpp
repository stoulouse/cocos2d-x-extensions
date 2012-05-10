//
//  PSModalAlertTest.cpp
//  test
//
//  Created by Jose Antonio Andujar Clavell on 09/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//

#include "PSModalAlertTest.h"

using namespace cocos2d;

enum
{
    TEST_ASK = 0,
	TEST_CONFIRM,
	TEST_TELL,
};

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
   
	currentTest = TEST_ASK;

	menuCallback();
}

void PSModalAlertTest::onEnter()
{
	CCLayer::onEnter();
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
	switch(currentTest){
		case TEST_ASK:
			PSModalAlert::AskQuestionOnLayer("bla,bla,bla,question",this,this,callfunc_selector(PSModalAlertTest::menuCallback),this,callfunc_selector(PSModalAlertTest::menuCallback));
			currentTest++;
		break;
		case TEST_CONFIRM:
			PSModalAlert::ConfirmQuestionOnLayer("bla,bla,bla,confirm",this,this,callfunc_selector(PSModalAlertTest::menuCallback),this,callfunc_selector(PSModalAlertTest::menuCallback));
			currentTest++;
		break;
		case TEST_TELL:
			PSModalAlert::TellStatementOnLayer("bla,bla,bla,Tell",this,this,callfunc_selector(PSModalAlertTest::menuCallback));
			currentTest++;
		break;
		default:
			CCLog("Done");
			break;
	}
}
