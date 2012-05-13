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

#include "CCMenuItemDynamicTest.h"

using namespace cocos2d;


void CCMenuItemDynamicTestScene::runThisTest()
{
    CCLayer* pLayer = new CCMenuItemDynamicTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}

CCMenuItemDynamicTest::CCMenuItemDynamicTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );
   
    m_pMenuItemDynamic = new CCMenuItemDynamic();

	CCSize minSize = CCSize(20,20);

	m_pMenuItemDynamic = CCMenuItemDynamic::dynamicItemWithText("Example Text",  "fonts/futura-48.fnt", minSize, "greenButton.png", "greenButtonSel.png", this, menu_selector(CCMenuItemDynamicTest::menuCallback));
    m_pMenuItemDynamic->setPosition(ccp(s.width/2,s.height/2));
    
    addChild(m_pMenuItemDynamic);
}

void CCMenuItemDynamicTest::onEnter()
{
    
}

std::string CCMenuItemDynamicTest::title()
{
    return "CCMenuItemDynamic Test";
}

CCMenuItemDynamicTest::~CCMenuItemDynamicTest()
{
    //CC_SAFE_RELEASE(m_pMenuItemDynamic);
}

void CCMenuItemDynamicTest::menuCallback(CCObject* pSender)
{
}