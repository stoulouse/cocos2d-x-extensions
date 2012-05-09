//
//  DecoratedBoxTest.h
//  test
//
//  Created by Jose Antonio Andujar Clavell on 09/05/2012.
//  Copyright 2011 JanduSoft. All rights reserved.
//
#ifndef _DECORATEDBOX_TEST_H
#define _DECORATEDBOX_TEST_H

#include "DecoratedBox/DecoratedBox.h"
#include "../testBasic.h"

class DecoratedBoxTest : public cocos2d::CCLayer
{
protected:
    DecoratedBox *m_pDecoratedBox;
    
public:
    DecoratedBoxTest();
    ~DecoratedBoxTest();
    
    virtual void onEnter(void);
	virtual std::string title();
};

class DecoratedBoxTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif