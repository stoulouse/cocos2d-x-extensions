/*
 * CCControlSwitch.m
 *
 * Copyright 2012 Yannick Loriot. All rights reserved.
 * http://yannickloriot.com
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
 * Converted to c++ / cocos2d-x by starfair
 */

#include "CCControlExtension/CCControlSwitch.h"

CCControlSwitch::~CCControlSwitch()
{
}

bool CCControlSwitch::initWithMaskSprite(CCSprite *maskSprite, CCSprite *onSprite, CCSprite *offSprite,CCSprite * thumbSprite)
{
    return initWithMaskSprite(maskSprite,onSprite,offSprite,thumbSprite,NULL,NULL);
}

CCControlSwitch * CCControlSwitch::switchWithMaskSprite(CCSprite * maskSprite, CCSprite *onSprite, CCSprite *offSprite, CCSprite *thumbSprite)
{
	CCControlSwitch * pRet=new CCControlSwitch();
    pRet->initWithMaskSprite(maskSprite,onSprite,offSprite,thumbSprite);
	pRet->autorelease();
	return pRet;
}

 bool CCControlSwitch::initWithMaskSprite(CCSprite * maskSprite,CCSprite * onSprite,CCSprite *offSprite,CCSprite * thumbSprite,CCNode *onLabel,CCNode *offLabel)
{
	if (CCControl::init())
    {
		setIsTouchEnabled(true);
        CCAssert(maskSprite,"Mask must not be nil.");
		CCAssert(onSprite, "onSprite must not be nil.");
        CCAssert(offSprite,"offSprite must not be nil.");
        CCAssert(thumbSprite,"thumbSprite must not be nil.");        
        on= true;

		addChild(maskSprite);
		addChild(onSprite);
		addChild(offSprite);
		addChild(thumbSprite);
		if(onLabel)
			addChild(onLabel);
		if(offLabel)
			addChild(offLabel);

		switchSprite_  = CCControlSwitchSprite::initWithMaskSprite(maskSprite,onSprite,offSprite,thumbSprite,onLabel,offLabel);
		addChild(switchSprite_);        
       switchSprite_->setPosition(ccp (switchSprite_->getContentSize().width / 2, switchSprite_->getContentSize().height / 2));
        isRelativeAnchorPoint  = true;
        setAnchorPoint(ccp (0.5f, 0.5f));
        setContentSize(switchSprite_->getContentSize());
		return true;
    }
    return false;
}

CCControlSwitch * CCControlSwitch::switchWithMaskSprite(CCSprite *maskSprite, CCSprite *onSprite,CCSprite *offSprite,CCSprite *thumbSprite,CCNode *onLabel, CCNode*offLabel)
{
	CCControlSwitch * pRet=new CCControlSwitch();
	pRet->initWithMaskSprite(maskSprite,onSprite,offSprite,thumbSprite,onLabel,offLabel);
	pRet->autorelease();
	return pRet;
}

void CCControlSwitch::setOn(bool isOn)
{
    setOn(isOn,false);
}

void CCControlSwitch::setOn(bool isOn,bool animated)
{
    on = isOn;
	if(animated)
	{
	//	switchSprite_->runAction(CCActionTween::actionWithDuration(0.2f,"sliderXPosition_",on?switchSprite_->onPosition_ :switchSprite_->offPosition_));        
	}
	else
	{
		if(on)
			switchSprite_->setSliderXPosition(switchSprite_->getContentSize().width);
		else
			switchSprite_->setSliderXPosition(0);
		switchSprite_->needsLayout(); 
	}
	sendActionsForControlEvents(CCControlEventValueChanged);
}

void CCControlSwitch::setIsEnabled(bool enabled)
{
	switchSprite_->setOpacity((enabled) ? 255 : 128);
	CCControl::setIsEnabled(enabled);
}

CCPoint CCControlSwitch::locationFromTouch(CCTouch *touch)
{
    CCPoint touchLocation   = touch->locationInView();                      // Get the touch position
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);  // Convert the position to GL space
    touchLocation = convertToNodeSpace(touchLocation);                  // Convert to the node space of this class    
    return touchLocation;
}

bool CCControlSwitch::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	if (!isTouchInside(touch)||!getIsEnabled())
    {
        return false;
    }    
    moved= false;    
    CCPoint location= locationFromTouch(touch);    
    initialTouchXPosition = location.x - switchSprite_->getSliderXPosition();    
    switchSprite_->setSelectedOn();
    switchSprite_->needsLayout();    
    return true;
}

void CCControlSwitch::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
    CCPoint location    = locationFromTouch(touch);
    location            = ccp (location.x - initialTouchXPosition, 0);    
    moved              = true;    
    switchSprite_->setSliderXPosition(location.x);
}

void CCControlSwitch::ccTouchEnded(CCTouch *touch, CCEvent *event)
{
    CCPoint location   = locationFromTouch(touch);    
	switchSprite_->setSelectedOff();    
    if (moved)
    {
		if(location.x >= switchSprite_->getContentSize().width / 2)
		{			
			setOn(true ,true);
			//switchSprite_->setSliderXPosition(switchSprite_->getContentSize().width);
		}
		else
		{
			setOn(false,true);
			//switchSprite_->setSliderXPosition(0);
		}
    } 
	else
    {
        setOn(on,true);
    }
}

void CCControlSwitch::ccTouchCancelled(CCTouch *touch, CCEvent *event)
{
	CCPoint location   = locationFromTouch(touch); 
	switchSprite_->setSelectedOff();    
	if (moved)
	{
		if(location.x >= switchSprite_->getContentSize().width / 2)
		{			
			setOn(true ,true);
			//switchSprite_->setSliderXPosition(switchSprite_->getContentSize().width);
		}
		else
		{
			//switchSprite_->setSliderXPosition(0);
			setOn(false,true);			
		}
	} 
	else
	{
		setOn(on,true);
	}
}


CCControlSwitchSprite::~CCControlSwitchSprite()
{
}

CCControlSwitchSprite *CCControlSwitchSprite::initWithMaskSprite(CCSprite *maskSprite,CCSprite *onSprite,CCSprite *offSprite,CCSprite *thumbSprite,CCNode *onLabel,CCNode *offLabel)
{
	CCControlSwitchSprite * self=new CCControlSwitchSprite();		
    if (self)
    {
		self->initWithTexture(maskSprite->getTexture());
        // Sets the default values
        self->onPosition_ = maskSprite->getContentSize().width - thumbSprite->getContentSize().width;
        self->offPosition_= 0;
        self->sliderXPosition_ = self->onPosition_; 
        
        self->maskSprite_= maskSprite;
        self->maskSprite_->setPosition(ccp(maskSprite->getContentSize().width / 2, maskSprite->getContentSize().height / 2));
        
        self->onSprite_= onSprite;
        self->offSprite_= offSprite;
        self->thumbSprite_= thumbSprite;
        self->onLabel_= onLabel;
        self->offLabel_= offLabel;        
        self->needsLayout();
    }
    return self;
}

void CCControlSwitchSprite::needsLayout()
{
    onSprite_->setPosition( ccp(-onSprite_->getContentSize().width/2+ thumbSprite_->getContentSize().width/2+ sliderXPosition_, onSprite_->getContentSize().height / 2));
    offSprite_->setPosition(ccp(thumbSprite_->getContentSize().width/2+sliderXPosition_+offSprite_->getContentSize().width/2,offSprite_->getContentSize().height / 2));
    thumbSprite_->setPosition(ccp(thumbSprite_->getContentSize().width/2 + sliderXPosition_,  maskSprite_->getContentSize().height / 2));
    
    if (onLabel_)
    {
        onLabel_->setPosition(ccp(onSprite_->getPosition().x - thumbSprite_->getContentSize().width / 6, onSprite_->getContentSize().height / 2));
    }
    if (offLabel_)
    {
        offLabel_->setPosition(ccp(offSprite_->getPosition().x + thumbSprite_->getContentSize().width / 6, offSprite_->getContentSize().height / 2));
    }

	CCRenderTexture *inRT   =  CCRenderTexture::renderTextureWithWidthAndHeight(maskSprite_->getContentSize().width,maskSprite_->getContentSize().height);
    
	onSprite_->setIsVisible(true);
	offSprite_->setIsVisible(true);
	onLabel_->setIsVisible(true);
	offLabel_->setIsVisible(true);
	inRT->begin();
	onSprite_->visit();
	offSprite_->visit();
	if(onLabel_)
		onLabel_->visit();
	if(offLabel_)
		offLabel_->visit();
	inRT->end();
	onSprite_->setIsVisible(false);
	offSprite_->setIsVisible(false);
	onLabel_->setIsVisible(false);
	offLabel_->setIsVisible(false);

    CCSprite *inSprite = inRT->getSprite();
    inSprite->setPosition(maskSprite_->getPosition());
	ccBlendFunc fn={GL_DST_ALPHA, GL_ZERO};
    inSprite->setBlendFunc(fn);

	CCRenderTexture *rt     = CCRenderTexture::renderTextureWithWidthAndHeight(maskSprite_->getContentSize().width,maskSprite_->getContentSize().height);
	maskSprite_->setIsVisible(true);
	thumbSprite_->setIsVisible(true);
	rt->begin();
	maskSprite_->visit();
	inSprite->visit();
	thumbSprite_->visit();
	rt->end();
	maskSprite_->setIsVisible(false);
	thumbSprite_->setIsVisible(false);
    setTexture(rt->getSprite()->getTexture());
	setFlipY(true);
    flipY= true;
}

void CCControlSwitchSprite::setSliderXPosition(float sliderXPosition)
{
    if (sliderXPosition <= offPosition_)
    {        // Off
        sliderXPosition = offPosition_;
    } 
	else if (sliderXPosition >= onPosition_)
    {        // On
        sliderXPosition = onPosition_;
    }    
    sliderXPosition_  = sliderXPosition;    
    needsLayout();
}

float CCControlSwitchSprite::onSideWidth()
{
    return onSprite_->getContentSize().width;
}

float CCControlSwitchSprite::offSideWidth()
{
    return offSprite_->getContentSize().height;
}

void CCControlSwitchSprite::setSelectedOn()
{
	if(thumbSprite_)
	{
		thumbSprite_->setColor(ccGRAY);
	}
}

void CCControlSwitchSprite::setSelectedOff()
{
	if(thumbSprite_)
	{
		thumbSprite_->setColor(ccWHITE);
	}
}

