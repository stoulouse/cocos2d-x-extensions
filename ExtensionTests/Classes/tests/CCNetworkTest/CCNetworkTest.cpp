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

#include "CCNetworkTest.h"

using namespace cocos2d;

void CCNetworkTestScene::runThisTest()
{
    CCLayer* pLayer = new CCNetworkTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();

	
}

CCNetworkTest::CCNetworkTest()
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
        menu_selector(CCNetworkTest::menuCallback));

    // Place the menu item in the center
    pCloseItem->setPosition(ccp(s.width/2, s.height/2));

	CCMenu *menu = CCMenu::menuWithItems(pCloseItem, NULL);	
	menu->setPosition( CCPointZero );

	addChild(menu);

	isThreadRunning = false;
}

std::string CCNetworkTest::title()
{
    return "CCNetwork Test";
}

void CCNetworkTest::onEnter()
{
	CCLayer::onEnter();
}


void CCNetworkTest::menuCallback(CCObject* pSender)
{
	if(!isThreadRunning){
		std::string url(http://www.google.com/calendar/feeds/developer-calendar@google.com/public/full?alt=json);
		isThreadRunning = true;
		scheduleUpdate();
		network = CCNetwork::loadJSON( url.c_str(), this, callfunc_selector( CCNetworkTest::dataArrived ) );
		network->retain();
	}
}

void CCNetworkTest::update( ccTime dt )
{
    if( !isThreadRunning )
    {
        if( network != NULL )
        {
            cJSON *result = network->getResultJSON();

			char *text = cJSON_Print(result);
			CCLog("JSON Readed \n%s",text);
			free(text);

			network->release();
        }

        unscheduleUpdate();
    }
}

void CCNetworkTest::dataArrived() { isThreadRunning = false; }