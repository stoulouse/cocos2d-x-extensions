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

#ifndef _CCMOSQUITTO_CLIENT_TEST_H
#define _CCMOSQUITTO_CLIENT_TEST_H

#include "CCMosquittoClient/CCMosquittoClient.h"
#include "../testBasic.h"

class CCMosquittoClientTest : public cocos2d::CCLayer, public MosquittoClientDelegate
{  
protected:
	bool isWorking;
	CCMosquittoClient * mosquitto;
public: 
    CCMosquittoClientTest();  

	virtual std::string title();
	void menuCallback(CCObject* pSender);
	void onEnter();

	//MosquittoClientDelegate
	virtual void didConnect(int code);
	virtual void didDisconnect();
	virtual void didPublish(int messageId);

	virtual void didReceiveMessage(std::string message, std::string topic);
	virtual void didSubscribe(int messageID, cocos2d::CCArray* grantedQos);
	virtual void didUnsubscribe(int messageID);
};

class CCMosquittoClientTestScene : public TestScene
{
public:
    virtual void runThisTest();
};

#endif