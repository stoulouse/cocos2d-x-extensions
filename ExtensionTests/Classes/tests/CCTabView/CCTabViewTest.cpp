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

#include "CCTabViewTest.h"

using namespace cocos2d;

enum
{
    TEST_ASK = 0,
	TEST_CONFIRM,
	TEST_TELL,
};

void CCTabViewTestScene::runThisTest()
{
    CCLayer* pLayer = new CCTabViewTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}

CCTabViewTest::CCTabViewTest()
{

	CCTabView * myTab = new CCTabView(CCRectMake(50, 20, 380, 300));
	myTab->autorelease();

	CCLayerColor * mylay = CCLayerColor::layerWithColorWidthHeight(ccc4f(255, 0, 0,120),200,100);
    CCLabelTTF * lbl = CCLabelTTF::labelWithString("tab1","Arial",18);
    lbl->setPosition(ccp(50,50));
    mylay->addChild(lbl);

	CCLayerColor * mylay1 = CCLayerColor::layerWithColorWidthHeight(ccc4f(0, 255, 0,120),200,100);
    CCLabelTTF * lbl1 = CCLabelTTF::labelWithString("tab2","Arial",18);
    lbl1->setPosition(ccp(50,50));
    mylay1->addChild(lbl1);

	CCLayerColor * mylay2 = CCLayerColor::layerWithColorWidthHeight(ccc4f(0,50, 220,120),200,100);
    CCLabelTTF * lbl2 = CCLabelTTF::labelWithString("tab3","Arial",18);
    lbl2->setPosition(ccp(50,50));
    mylay2->addChild(lbl2);

	myTab->addTab("tab1", mylay);
    myTab->addTab("tab2", mylay1);
    myTab->addTab("tab3", mylay2);
    this->addChild(myTab);
}

void CCTabViewTest::onEnter()
{
	CCLayer::onEnter();
}

std::string CCTabViewTest::title()
{
    return "CCTabView Test";
}

CCTabViewTest::~CCTabViewTest()
{
}
