//
//  DecoratedBoxTest.cpp
//  test
//
//  Created by Jose Antonio Andujar Clavell on 09/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//

#include "DecoratedBoxTest.h"

using namespace cocos2d;


void DecoratedBoxTestScene::runThisTest()
{
    CCLayer* pLayer = new DecoratedBoxTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}

DecoratedBoxTest::DecoratedBoxTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );
   
    m_pDecoratedBox = DecoratedBox::decoratedBoxWithFile("box.png",200,100);
    m_pDecoratedBox->setPosition(ccp(s.width/2,s.height/2));
    
    addChild(m_pDecoratedBox);
}

void DecoratedBoxTest::onEnter()
{
    
}

std::string DecoratedBoxTest::title()
{
    return "DecoratedBox Test";
}

DecoratedBoxTest::~DecoratedBoxTest()
{
    //CC_SAFE_RELEASE(m_pDecoratedBox);
}
