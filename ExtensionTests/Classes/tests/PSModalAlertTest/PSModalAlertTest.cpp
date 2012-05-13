/*
 * Created by Jose Antonio Andujar Clavell on 12/05/2012.
 * Copyright 2011 JanduSoft. All rights reserved.
 *
 * Jose Antonio Andujar Clavell, JanduSoft
 * http://www.jandusoft.com 
 * http://www.jandujar.com
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

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
    return "PSModalAlert Test";
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
