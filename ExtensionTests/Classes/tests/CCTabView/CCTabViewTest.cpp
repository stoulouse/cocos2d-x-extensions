//
//  CCTabViewTest.cpp
//  test
//
//  Created by Jose Antonio Andujar Clavell on 10/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//

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
