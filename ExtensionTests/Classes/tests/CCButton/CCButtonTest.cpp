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

#include "CCButtonTest.h"

using namespace cocos2d;


void CCButtonTestScene::runThisTest()
{
    CCLayer* pLayer = new CCButtonTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}

CCButtonTest::CCButtonTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );
   
	m_pCCButton = CCButton::buttonWithFiles(this,menu_selector(CCButtonTest::menuCallback), "r1.png", "r2.png", NULL);
	m_pCCButton->setTitleForState("Show", CCControlStateNormal);
    m_pCCButton->setPosition(ccp(s.width/2,s.height/2));
    
	//Other uses
	/*
	2:
	CCSprite * tmpBgSprite = CCSprite::spriteWithFile("r1.png");
    CCSprite * tmpBgSprite2 = CCSprite::spriteWithFile("r2.png");

    m_pCCButton = CCButton::buttonWithFiles(this,menu_selector(CCButtonTest::menuCallback), NULL,NULL, NULL);
    tmpBtn->setBackgroundImageForState(tmpBgSprite, CCControlStateNormal);
    tmpBtn->setBackgroundImageForState(tmpBgSprite2, CCControlStateSelected);

    tmpBtn->setTitleForState("Show", CCControlStateNormal);
    3:
    m_pCCButton = CCButton::buttonWithFiles(this,menu_selector(CCButtonTest::menuCallback), NULL,NULL, NULL);
    tmpBtn->setTitleForState("Show", CCControlStateNormal);

    4:
	m_pCCButton = CCButton::buttonWithFiles(this,menu_selector(CCButtonTest::menuCallback), "r1.png", "r2.png", NULL);
	*/

    addChild(m_pCCButton);
	setIsTouchEnabled(true);
}

void CCButtonTest::onEnter()
{
    
}

std::string CCButtonTest::title()
{
    return "CCButton Test";
}

CCButtonTest::~CCButtonTest()
{
    //CC_SAFE_RELEASE(m_pDecoratedBox);
}

void CCButtonTest::menuCallback(CCObject* pSender)
{
	CCLog("Button pushed");
}
