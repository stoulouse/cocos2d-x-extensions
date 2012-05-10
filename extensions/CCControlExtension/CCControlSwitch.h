

/*
 * CCControlSwitch.h
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
 Converted to c++ / cocos2d-x by starfair
 */

#ifndef __CCCONTROL_SWITCH_H__
#define __CCCONTROL_SWITCH_H__

#include "cocos2d.h"
#include "CCControl.h"

class CCControlSwitchSprite :public CCSprite
{
protected:
	float sliderXPosition_;
	float onPosition_;
	float offPosition_;
	CCSprite *maskSprite_;
	CCSprite *onSprite_;
	CCSprite *offSprite_;
	CCSprite *thumbSprite_;
	CCNode *onLabel_;
	CCNode *offLabel_;
	bool flipY;
	float onSideWidth();
	float offSideWidth();
public:
	CCControlSwitchSprite():maskSprite_(NULL),onSprite_(NULL),offSprite_(NULL),thumbSprite_(NULL),onLabel_(NULL),offLabel_(NULL){};
	~CCControlSwitchSprite();
	static CCControlSwitchSprite * initWithMaskSprite(CCSprite *maskSprite,CCSprite *onSprite,CCSprite *offSprite,CCSprite *thumbSprite,CCNode*onLabel,CCNode*offLabel);
	void setSliderXPosition(float sliderXPosition);
	float getSliderXPosition(){return sliderXPosition_;}
	void setSelectedOn();
	void setSelectedOff();
	void needsLayout();

};

/** class CCControlSwitch Switch control for Cocos2D. */
class CCControlSwitch :public CCControl
{
protected:
	CCControlSwitchSprite   *switchSprite_;
	float initialTouchXPosition;
	bool  moved;
	bool isRelativeAnchorPoint; 
	bool on;
public:
	/** A Boolean value that determines the off/on state of the switch. */
	CCControlSwitch():switchSprite_(NULL),moved(false),on(true),initialTouchXPosition(0),isRelativeAnchorPoint(false){};
	virtual ~CCControlSwitch();
	/** Initializes a switch with a mask sprite, on/off sprites for on/off states and a thumb sprite. */
	virtual bool initWithMaskSprite(CCSprite *maskSprite, CCSprite * onSprite , CCSprite * offSprite,CCSprite *thumbSprite);

	/** Creates a switch with a mask sprite, on/off sprites for on/off states and a thumb sprite. */
	static CCControlSwitch* switchWithMaskSprite(CCSprite *maskSprite, CCSprite * onSprite,CCSprite * offSprite, CCSprite *thumbSprite);

	/** Initializes a switch with a mask sprite, on/off sprites for on/off states, a thumb sprite and an on/off labels. */
	virtual bool initWithMaskSprite(CCSprite * maskSprite, CCSprite * onSprite, CCSprite * offSprite,CCSprite *thumbSprite,CCNode *onLabel, CCNode *offLabel);

	/** Creates a switch with a mask sprite, on/off sprites for on/off states, a thumb sprite and an on/off labels. */
	static CCControlSwitch * switchWithMaskSprite(CCSprite *maskSprite,CCSprite * onSprite, CCSprite *offSprite, CCSprite * thumbSprite,CCNode *onLabel, CCNode *offLabel);
	/**
	* Set the state of the switch to On or Off, optionally animating the transition.
	*
	* @param isOn YES if the switch should be turned to the On position; NO if it 
	* should be turned to the Off position. If the switch is already in the 
	* designated position, nothing happens.
	* @param animated YES to animate the “flipping” of the switch; otherwise NO.
	*/
	void setOn( bool isOn, bool  animated);
	void setOn( bool isOn);
	bool getIsOn(){return on;}
	virtual void setIsEnabled(bool enabled);
	virtual bool ccTouchBegan(CCTouch *, CCEvent *);
	virtual void ccTouchMoved(CCTouch *, CCEvent *);
	virtual void ccTouchEnded(CCTouch *, CCEvent *);
	virtual void ccTouchCancelled(CCTouch *, CCEvent *);
	CCPoint locationFromTouch(CCTouch *);
};

#endif
