//
//  JACModalAlertTest.cpp
//  test
//
//  Created by Jose Antonio Andujar Clavell on 10/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//

#include "JACModalAlertTest.h"

using namespace cocos2d;

enum
{
    TEST_ASK = 0,
	TEST_CONFIRM,
	TEST_TELL,
};

void JACModalAlertTestScene::runThisTest()
{
    CCLayer* pLayer = new JACModalAlertTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}

JACModalAlertTest::JACModalAlertTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );
   
	currentTest = TEST_ASK;

	menuCallback();
}

void JACModalAlertTest::onEnter()
{
	CCLayer::onEnter();
}

std::string JACModalAlertTest::title()
{
    return "JACModalAlert Test";
}

JACModalAlertTest::~JACModalAlertTest()
{
}

void JACModalAlertTest::menuCallback()
{
	switch(currentTest){
		case TEST_ASK:
			//JACModalAlert::AskQuestionOnLayer("bla,bla,bla,question",this,this,callfunc_selector(JACModalAlertTest::menuCallback),this,callfunc_selector(JACModalAlertTest::menuCallback));
			//currentTest++;
		//break;
		case TEST_CONFIRM:
			//JACModalAlert::ConfirmQuestionOnLayer("bla,bla,bla,confirm",this,this,callfunc_selector(JACModalAlertTest::menuCallback),this,callfunc_selector(JACModalAlertTest::menuCallback));
			//currentTest++;
		//break;
		case TEST_TELL:
			JACModalAlert::PopupOnLayer(this,"Hello", "ok",this,callfunc_selector(JACModalAlertTest::menuCallback));
			currentTest++;
		break;
		default:
			CCLog("Done");
			break;
	}
}
