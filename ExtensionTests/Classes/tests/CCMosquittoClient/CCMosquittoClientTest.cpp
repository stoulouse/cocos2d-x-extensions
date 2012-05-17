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

#include "CCMosquittoClientTest.h"

using namespace cocos2d;

void CCMosquittoClientTestScene::runThisTest()
{
    CCLayer* pLayer = new CCMosquittoClientTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();

	
}

CCMosquittoClientTest::CCMosquittoClientTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );
   
	// Create a "close" menu item with close icon, it's an auto release object.
    CCMenuItemImage * pCloseItem = CCMenuItemImage::itemFromNormalImage(
        "CloseNormal.png",
        "CloseSelected.png",
        this,
        menu_selector(CCMosquittoClientTest::menuCallback));

    // Place the menu item in the center
    pCloseItem->setPosition(ccp(s.width/2, s.height/2));

	CCMenu *menu = CCMenu::menuWithItems(pCloseItem, NULL);	
	menu->setPosition( CCPointZero );

	addChild(menu);

	isWorking = false;
	mosquitto = CCMosquittoClient::initWithClientId("ID_CLIENT", this);
	addChild(mosquitto); //for scheduling
}

std::string CCMosquittoClientTest::title()
{
    return "CCNetwork Test";
}

void CCMosquittoClientTest::onEnter()
{
	CCLayer::onEnter();
}


void CCMosquittoClientTest::menuCallback(CCObject* pSender)
{
	std::string topic("yourtopic");
	std::string host("yourserver");	

	if(!isWorking){
		mosquitto->connectToHost(host);
		mosquitto->subscribe(topic);
		isWorking = true;
	}else{
		mosquitto->loop(0);
		//mosquitto->unsubscribe(topic);
		//mosquitto->disconnect();
		//isWorking = false;
	}
	
}

void CCMosquittoClientTest::didConnect(int code){
	CCLog("Connected");
}

void CCMosquittoClientTest::didDisconnect(){
	CCLog("Disconnected");
}

void CCMosquittoClientTest::didPublish(int messageId){
	CCLog("Published");
}

void CCMosquittoClientTest::didReceiveMessage(std::string message, std::string topic){
	CCLog("Received message %s from topic %s",message.c_str(), topic.c_str());
}
void CCMosquittoClientTest::didSubscribe(int messageID, cocos2d::CCArray* grantedQos){
	CCLog("Subscribed with id %d", messageID);
}

void CCMosquittoClientTest::didUnsubscribe(int messageID){
	CCLog("Unsubscribe with id %id", messageID);
}