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

#ifndef _CCNETWORK_TEST_H
#define _CCNETWORK_TEST_H

#include "CCNetwork/CCNetwork.h"
#include "../testBasic.h"

class CCNetworkTest : public cocos2d::CCLayer
{  
protected:
	bool isThreadRunning;
	CCNetwork * network;
public: 
    CCNetworkTest();  

	virtual std::string title();
	virtual void update( cocos2d::ccTime dt );
	void menuCallback(CCObject* pSender);
	void dataArrived();
	void onEnter();
};

class CCNetworkTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif