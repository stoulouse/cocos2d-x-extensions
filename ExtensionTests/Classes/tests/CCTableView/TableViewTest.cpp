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

#include "TableViewTest.h"
#include "CustomCCTableViewCell.h"

using namespace cocos2d;


void CCTableViewTestScene::runThisTest()
{
    CCLayer* pLayer = new CCTableViewTest();
    addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(this);
    pLayer->release();
}

CCTableViewTest::CCTableViewTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 28);
	addChild(label, 0);
	label->setPosition( ccp(s.width/2, s.height-50) );
   
    m_pTableView = new CCTableView(CCRectMake(0, 0, 200, 200));

    m_pTableView->setDelegate(this);
	m_pTableView->setDataSource(this);
    m_pTableView->setPosition( 0, 0 );
    
    rowCount = 15;

    
    addChild(m_pTableView);
}

void CCTableViewTest::onEnter()
{
    
}

std::string CCTableViewTest::title()
{
    return "CCTableView Test";
}

CCTableViewTest::~CCTableViewTest()
{
}

void CCTableViewTest::ccTableViewWillDisplayCellForRowAtIndexPath(CCIndexPath &mIndexPath,CCTableViewCell * mTableViewCell,CCTableView * mTableView)
{
    
}

void CCTableViewTest::ccTableViewWillReloadCellForRowAtIndexPath(CCIndexPath &mIndexPath,CCTableViewCell * mTableViewCell,CCTableView * mTableView)
{
	char labelStr[60];
	sprintf(labelStr, "%d",mIndexPath.row);
	
	CCLabelTTF * label = (CCLabelTTF * ) mTableViewCell->getChildByTag(20);
	if (label) {
		label->setString(labelStr);
	}
}


float CCTableViewTest::cellHeightForRowAtIndexPath(CCIndexPath & mIndexPath,CCTableView * mTableView)
{
    //	if (mIndexPath.row == 2) {
    //		return 120;
    //	}else if (mIndexPath.row == 4) {
    //		return 160;
    //	}
	return 60;
}

void CCTableViewTest::didSelectRowAtIndexPath(CCIndexPath & mIndexPath,CCTableView * mTableView)
{
	if (mIndexPath.row == rowCount -1) {
		rowCount += 2;
		mTableView->reloadData();
	}
}

unsigned int CCTableViewTest::numberOfRowsInSection(unsigned int mSection,CCTableView * mTableView)
{
	return rowCount;
}

unsigned int CCTableViewTest::numberOfSectionsInCCTableView(CCTableView * mTableView)
{
	return 1;
}

/*cell was set to anchor point(0.5,0.5)*/
CCTableViewCell * CCTableViewTest::cellForRowAtIndexPath(CCIndexPath &mIndexPath,CCTableView * mTableView)
{
	static const char * cellIdentifier = "cell-identifier";
	
	char labelStr[60];
	sprintf(labelStr, "%d",mIndexPath.row);
	
	CustomCCTableViewCell * cell = (CustomCCTableViewCell *) mTableView->dequeueReusableCellWithIdentifier(cellIdentifier);
	if (cell == NULL) {
		printf("cell alloc row =%d\n",mIndexPath.row);
		cell = new CustomCCTableViewCell(cellIdentifier);
		cell->autorelease();
		
        //		DecoratedBox * box = DecoratedBox::decoratedBoxWithFile("Icon.png", mTableView->getContentSize().width,60);
        //		box->setTag(200);
        //		box->setPosition(CCPointMake(mTableView->getContentSize().width/2.0,60/2.0));
        //		cell->addChild(box);
		
		CCLabelTTF * label = CCLabelTTF::labelWithString(labelStr, "Arial", 16);
		label->setColor(ccc3(0, 0, 0));
		label->setPosition(ccp(40,60/2.0));
		label->setColor(ccc3(255,255,255));
		label->setTag(20);
		cell->addChild(label);
		cell->parentView = m_pTableView;
		//cell->setColor(ccc3(128, 128, 128)); 
	}
	else{
		CCLabelTTF * label = (CCLabelTTF * ) cell->getChildByTag(20);
		if (label) {
			label->setString(labelStr);
		}
	}
	return cell;
}

void CCTableViewTest::ccTableViewCommitCellEditingStyleForRowAtIndexPath(CCTableView * mTableView,CCTableViewCellEditingStyle mCellEditStyle,CCIndexPath &mIndexPath)
{
	if (mCellEditStyle == CCTableViewCellEditingStyleDelete) {
		rowCount--;
		mTableView->reloadData();
	}
}
