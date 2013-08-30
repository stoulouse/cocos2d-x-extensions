/*
 * CCControlPicker.m
 *
 * Copyright 2013 Yannick Loriot. All rights reserved.
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
 */

#import "CCControlPicker.h"

#define CCControlPickerFriction         0.70f   // Between 0 and 1
#define CCControlPickerDefaultRowWidth  35      // px
#define CCControlPickerDefaultRowHeight 35      // px

CCControlPicker::CCControlPicker() {
	background = 0;
	delegate = 0;
	dataSource = 0;
	rowsLayer = 0;
	_foregroundSprite = 0;
	_selectionSprite = 0;
}
CCControlPicker::~CCControlPicker()
{
//    SAFE_ARC_RELEASE(_previousDate);
//	CC_SAFE_RELEASE(rowsLayer);
    CC_SAFE_RELEASE(background);
    
//    SAFE_ARC_SUPER_DEALLOC();
}

CCControlPicker* CCControlPicker::initWithForegroundSprite(CCNode * foregroundSprite)
{
    return initWithForegroundSpriteSelectionSprite(foregroundSprite, 0);
}

CCControlPicker* CCControlPicker::pickerWithForegroundSprite(CCNode * foregroundSprite)
{
	CCControlPicker* picker = new CCControlPicker;
	picker->initWithForegroundSprite(foregroundSprite);
	picker->autorelease();
    return picker;
}

CCControlPicker* CCControlPicker::pickerWithForegroundFile(const std::string& foregroundFile)
{
    // Prepare the foreground for the picker
    CCSprite *foregroundSprite  = CCSprite::create(foregroundFile.c_str());
    
    return pickerWithForegroundSprite(foregroundSprite);
}

CCControlPicker* CCControlPicker::initWithForegroundSpriteSelectionSprite(CCNode *foregroundSprite, CCNode * selectionSprite)
{
    if (init())
    {
		_foregroundSprite = 0;
		_selectionSprite = 0;

        CCAssert(foregroundSprite,   "Foreground sprite must be not nil");
        
        this->decelerating                   = false;
        this->ignoreAnchorPointForPosition( false );
        this->setContentSize( foregroundSprite->getContentSize() );
        
        cachedRowCount                     = 0;
        _selectedRow = -1 ;
        highlightRow                       = -1;
        cacheRowSize                       = CCSizeMake(CCControlPickerDefaultRowWidth,
                                                         CCControlPickerDefaultRowHeight);
        swipeOrientation                   = CCControlPickerOrientationVertical;
        looping                            = false;
        
        CCPoint center                      = ccp (getContentSize().width / 2, getContentSize().height /2);
		foregroundSprite->setContentSize(getContentSize());
        foregroundSprite->setPosition( center );
        addChild(foregroundSprite, 3);
		setForegroundSprite(foregroundSprite);
        
        rowsLayer                      = CCLayer::create();
        addChild(rowsLayer, 1);
        
        if (selectionSprite)
        {
			selectionSprite->setContentSize(CCSizeMake(getContentSize().width, CCControlPickerDefaultRowHeight));
            selectionSprite->setPosition( center );
            addChild(selectionSprite, 2);
        }
		setSelectionSprite(selectionSprite);
    }
    return this;
}

CCControlPicker* CCControlPicker::pickerWithForegroundSpriteSelectionSprite(CCNode * foregroundSprite, CCNode * selectionSprite)
{
	CCControlPicker* picker = new CCControlPicker;
	picker->initWithForegroundSpriteSelectionSprite(foregroundSprite, selectionSprite);
	picker->autorelease();
    return picker;
}

CCControlPicker* CCControlPicker::pickerWithForegroundFileSelectionFile(const std::string &foregroundFile, const std::string & selectionFile)
{
    // Prepare the foreground for the picker
    CCSprite *foregroundSprite  = CCSprite::create(foregroundFile.c_str());
    
    // Prepare the selection for the picker
    CCSprite *selectionSprite   = CCSprite::create(selectionFile.c_str());
    
    return pickerWithForegroundSpriteSelectionSprite(foregroundSprite, selectionSprite);
}

void CCControlPicker::onEnter()
{
	superClass::onEnter();
    
	this->registerWithTouchDispatcher();

	scheduleUpdate();
    
    reloadComponent();
}

void CCControlPicker::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    unscheduleUpdate();
    
	superClass::onExit();
}

void CCControlPicker::visit()
{
	if (!isVisible())
        return;
    
    glEnable(GL_SCISSOR_TEST);
    
    CCPoint worldOrg    = convertToWorldSpace(ccp(0, 0));
    CCPoint dest        = convertToWorldSpace(ccp(getContentSize().width, getContentSize().height));
    CCPoint dims        = ccpSub(dest, worldOrg);
    
    CCRect scissorRect  = CCRectMake(worldOrg.x, worldOrg.y, dims.x, dims.y);
    scissorRect         = CC_RECT_POINTS_TO_PIXELS(scissorRect);
    
    glScissor(scissorRect.origin.x, scissorRect.origin.y,
              scissorRect.size.width, scissorRect.size.height);
    
	superClass::visit();
    
	glDisable(GL_SCISSOR_TEST);
}

void CCControlPicker::update(float delta)
{
    if (!decelerating)
        return;
    
    if (velocity.y <= 30.0f && velocity.y >= -30.0f)
    {
        decelerating           = false;
        
        unsigned int rowNumber    = rowNumberAtLocation(rowsLayer->getPosition());
        selectRow(rowNumber, true);
        return;
    }
    
    CCPoint tranlation      = ccp (velocity.x * delta, velocity.y * delta);
    rowsLayer->setPosition(     positionWithTranslationForLayerPosition(tranlation, rowsLayer->getPosition()) );
    
    sendPickerRowEventForPosition(rowsLayer->getPosition());
    
    // Update the new velocity
    velocity               = ccp(velocity.x * CCControlPickerFriction,
                                  velocity.y * CCControlPickerFriction);
}

#pragma mark Properties

void CCControlPicker::setBackground(CCNode *nbackground)
{
    if (background)
    {
        removeChild(background,true);
        CC_SAFE_RELEASE(background);
    }
    
    if (nbackground) {
		nbackground->retain();
		background = nbackground;
		
        addChild(background, 0);
	}
}

#pragma mark - CCControlPicker Public Methods

CCSize CCControlPicker::rowSize()
{
    return cacheRowSize;
}

unsigned int CCControlPicker::numberOfRows()
{
    return 0;
}

void CCControlPicker::reloadComponent()
{
	if (!rowsLayer)
		return;

	cachedRowCount        = 0;
    
    if (dataSource)
        cachedRowCount     = dataSource->numberOfRowsInControlPicker(this);
    
//	rowsLayer->removeAllChildrenWithCleanup(true);
    needsLayoutWithRowCount(cachedRowCount);
}

void CCControlPicker::selectRow(unsigned int row, bool animated)
{
	if (!rowsLayer)
		return;
	
    CCPoint dest = rowsLayer->getPosition();
    
    if (swipeOrientation == CCControlPickerOrientationVertical)
        dest.y  = cacheRowSize.height * row;
    else
        dest.x  = cacheRowSize.width * row;

    _selectedRow = row;
    
    // Send events
    if (highlightRow != _selectedRow && highlightRow != -1)
    {
        CCControlPickerRowDelegate* rowNode  = dynamic_cast<CCControlPickerRowDelegate*>(rowsLayer->getChildByTag(_selectedRow));
        rowNode->rowDidDownplayed();
    }
    CCControlPickerRowDelegate* rowNode  = dynamic_cast<CCControlPickerRowDelegate*>(rowsLayer->getChildByTag(_selectedRow));
    rowNode->rowWillBeSelected();
    highlightRow   = -1;
    
    if (animated)
    {
        rowsLayer->runAction(CCSequence::create(
												CCEaseInOut::create(
																	
																							 CCMoveTo::create(0.2f, dest), 1.0f),
												CCCallFunc::create(this, callfunc_selector(CCControlPicker::sendSelectedRowCallback)),0));
    } else
    {
        sendSelectedRowCallback();
    }
}

int CCControlPicker::selectedRow()
{
    return _selectedRow;
}

#pragma mark - CCControlPicker Private Methods

void CCControlPicker::needsLayoutWithRowCount(unsigned int rowCount)
{
    CCPoint center      = ccp (getContentSize().width / 2, getContentSize().height /2);
    
    if (delegate)
    {
        cacheRowSize   = delegate->rowSizeForControlPicker(this);
    }
    
    for (unsigned int i = 0; i < rowCount; i++)
    {
        CCControlPickerRow *row     = dataSource->controlPickerNodeForRow(this, i);
        row->fitRowInSize(cacheRowSize);
        row->setAnchorPoint( ccp(0.5f, 0.5f) );
//		row->ignoreAnchorPointForPosition(true);
        rowsLayer->addChild(row, 1, i);
        
        CCPoint position        = center;
        if (swipeOrientation == CCControlPickerOrientationVertical)
            position.y          += -cacheRowSize.height * i;
        else
            position.x          += cacheRowSize.width * i;
        row->setPosition( position );
    }
    
    if (looping)
    {
        CCSize pickerSize = getContentSize();
        int numberOfRowToLoop = 0;
        
        if (swipeOrientation == CCControlPickerOrientationVertical)
            numberOfRowToLoop = pickerSize.height / rowSize().height;
        else
            numberOfRowToLoop = pickerSize.width / rowSize().width;
        
        for (int i = 1; i <= numberOfRowToLoop; i++)
        {
            CCControlPickerRow *row_sub = dataSource->controlPickerNodeForRow(this, rowCount - i);
            row_sub->fitRowInSize(cacheRowSize);
            row_sub->setAnchorPoint( ccp(0.5f, 0.5f) );
            rowsLayer->addChild(row_sub, 1);
            
            CCControlPickerRow *row_over = dataSource->controlPickerNodeForRow(this, (i - 1) % rowCount);
            row_over->fitRowInSize(cacheRowSize);
            row_over->setAnchorPoint( ccp(0.5f, 0.5f) );
            rowsLayer->addChild(row_over, 1);
            
            if (swipeOrientation == CCControlPickerOrientationVertical)
            {
                row_sub->setPosition( ccpAdd(center, ccp(0, cacheRowSize.height * i)) );
                row_over->setPosition( ccpAdd(center, ccp(0, -cacheRowSize.height * (rowCount + i - 1))) );
            } else
            {
                row_sub->setPosition( ccpAdd(center, ccp(-cacheRowSize.width * i, 0)) );
                row_over->setPosition( ccpAdd(center, ccp(cacheRowSize.height * (rowCount + i - 1), 0)) );
            }
        }
    }
    
    // Defines the limit bounds for non-circular picker
    limitBounds    = CCRectMake(-cacheRowSize.width * (cachedRowCount - 1),
                                 0,
                                 0,
                                 cacheRowSize.height * (cachedRowCount - 1));
    
    selectRow(0, false);
}

bool CCControlPicker::isValueOutOfMinBoundMaxBound(double value, double min, double max)
{
    return  (value <= min || max <= value);
}

unsigned int CCControlPicker::rowNumberAtLocation(CCPoint location)
{
    if (swipeOrientation == CCControlPickerOrientationVertical)
    {
        if (location.y < limitBounds.origin.y)
            return 0;
        else if (location.y >= limitBounds.size.height)
            return cachedRowCount - 1;
        else
        {
            unsigned int row  = round(location.y / cacheRowSize.height);
            if (row == cachedRowCount)
                row         = 0;
            
            return row;
        }
    } else
    {
        if (location.x < limitBounds.origin.x)
            return cachedRowCount - 1;
        else if (location.x >= limitBounds.size.width)
            return 0;
        else
        {
            unsigned int row  = round(fabsf(location.x) / cacheRowSize.width);
            if (row == cachedRowCount)
                row         = 0;
            
            return row;
        }
    }
}

CCPoint CCControlPicker::positionWithTranslationForLayerPosition(CCPoint translation, CCPoint position)
{
    if (swipeOrientation == CCControlPickerOrientationVertical)
    {
        position.y      -= adjustTranslationForAxisValueUsingMinBoundMaxBound(translation.y,
																			  position.y,
																			  limitBounds.origin.y,
																			  limitBounds.size.height);
        
        if (looping)
        {
            if (position.y < limitBounds.origin.y)
            {
                double diff = limitBounds.origin.y - position.y;
                position.y  = limitBounds.size.height + cacheRowSize.height - diff;
            } else if ((limitBounds.size.height + cacheRowSize.height) < position.y)
            {
                double diff = position.y - (limitBounds.size.height + cacheRowSize.height);
                position.y  = limitBounds.origin.y + diff;
            }
        }
    } else
    {
        position.x      -= adjustTranslationForAxisValueUsingMinBoundMaxBound(translation.x,
																			  position.x,
																			  limitBounds.origin.x,
																			  limitBounds.size.width);
        
        if (looping)
        {
            if (position.x < limitBounds.origin.x)
            {
                double diff = limitBounds.origin.x - position.x;
                position.x  = limitBounds.size.width + cacheRowSize.width - diff;
            } else if ((limitBounds.size.width + cacheRowSize.width) < position.x)
            {
                double diff = position.x - (limitBounds.size.width + cacheRowSize.width);
                position.x  = limitBounds.origin.x + diff;
            }
        }
    }
    
    return position;
}

double CCControlPicker::adjustTranslationForAxisValueUsingMinBoundMaxBound(double tranlation, double axis, double min, double max)
{
    // If the picker is not circular we check if we have reached an edge
    if (!looping && isValueOutOfMinBoundMaxBound(axis, min, max))
    {
        double d1       = fabsf(min - axis);
        double d2       = fabsf(max - axis);
        
        double friction = exp(std::min(d1, d2) / 30.0f) + 1.0f;
        
        return tranlation / friction;
    } else
    {
        return tranlation;
    }
}

void CCControlPicker::setContentSize(const CCSize & size)
{
	superClass::setContentSize(size);

	CCPoint center                      = ccp (getContentSize().width / 2, getContentSize().height /2);

	if (_foregroundSprite) {
		_foregroundSprite->setContentSize(size);
        _foregroundSprite->setPosition( center );
	}
	if (_selectionSprite) {
		CCSize selectionSize = CCSizeMake(getContentSize().width, rowSize().height);
		if (delegate) {
			selectionSize = delegate->rowSizeForControlPicker(this);
		}
		_selectionSprite->setContentSize(selectionSize);
		_selectionSprite->setPosition( center );
	}
	reloadComponent();
	if (_selectedRow != -1)
		selectRow(selectedRow(), false);
}

void CCControlPicker::sendSelectedRowCallback()
{    
    if (delegate)
    {
        delegate->controlPickerDidSelectRow(this, _selectedRow);
    }
    
    // Notifie the row
    CCControlPickerRowDelegate* rowNode  = dynamic_cast<CCControlPickerRowDelegate*>(rowsLayer->getChildByTag(_selectedRow));
    rowNode->rowDidSelected();
}

void CCControlPicker::sendPickerRowEventForPosition(CCPoint location)
{
    unsigned int nhighlightRow = rowNumberAtLocation(rowsLayer->getPosition());
    
    if (highlightRow != nhighlightRow)
    {
        CCControlPickerRowDelegate* rowNode = 0;
        if (highlightRow != -1)
        {
            rowNode     = dynamic_cast<CCControlPickerRowDelegate*>(rowsLayer->getChildByTag(highlightRow));
            rowNode->rowDidDownplayed();
        }
        
        highlightRow               = nhighlightRow;
		rowNode     = dynamic_cast<CCControlPickerRowDelegate*>(rowsLayer->getChildByTag(highlightRow));
        rowNode->rowDidHighlighted();
    }
}

void CCControlPicker::initMoveWithActionLocation(CCPoint location)
{
    setIsSelected( false );
    
    rowsLayer->stopAllActions();
    
    decelerating       = false;
    previousLocation   = location;

    struct cc_timeval now;
	
    if (CCTime::gettimeofdayCocos2d(&now, NULL) != 0)
    {
        CCLOG("error in gettimeofday");
    }

    previousDate   = now.tv_usec;
    
    // Update the cell layer position
    CCPoint translation = ccpSub(previousLocation, location);
    rowsLayer->setPosition( positionWithTranslationForLayerPosition(translation, rowsLayer->getPosition() ) );
}

void CCControlPicker::updateMoveWithActionLocation(CCPoint location)
{
    // Update the cell layer position
    CCPoint translation     = ccpSub(location, previousLocation);
    rowsLayer->setPosition(     positionWithTranslationForLayerPosition(translation, rowsLayer->getPosition() ) );
    
    // Sends the picker's row event
    sendPickerRowEventForPosition(rowsLayer->getPosition());
    
    // Compute the current velocity
    struct cc_timeval now;
	
    if (CCTime::gettimeofdayCocos2d(&now, NULL) != 0)
    {
        CCLOG("error in gettimeofday");
    }

    double delta_time       = (now.tv_usec - previousDate) / 10000000.0f;
    CCPoint delta_position  = ccpSub(location, previousLocation);
    velocity               = ccp(delta_position.x / delta_time, delta_position.y / delta_time);
    
    // Update the previous location and date
    previousLocation       = location;
    previousDate       = now.tv_usec;
}

void CCControlPicker::endMoveWithActionLocation(CCPoint location)
{
    setIsSelected(false);
    decelerating   = true;
}

#pragma mark -
#pragma mark CCTargetedTouch Delegate Methods

bool CCControlPicker::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!isTouchInside(pTouch)
        || !getIsEnabled()
        || !isVisible()
        || !hasVisibleParents())
        return false;

    CCPoint touchLocation   = pTouch->getLocation();
    touchLocation           = CCDirector::sharedDirector()->convertToGL(touchLocation);
    touchLocation           = getParent()->convertToNodeSpace(touchLocation);
    
    initMoveWithActionLocation(touchLocation);
    
    return true;
}

void CCControlPicker::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchLocation   = pTouch->getLocation();
    touchLocation           = CCDirector::sharedDirector()->convertToGL(touchLocation);
    touchLocation           = getParent()->convertToNodeSpace(touchLocation);
    
    updateMoveWithActionLocation(touchLocation);
}

void CCControlPicker::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchLocation   = pTouch->getLocation();
    touchLocation           = CCDirector::sharedDirector()->convertToGL(touchLocation);
    touchLocation           = getParent()->convertToNodeSpace(touchLocation);
    
	if (pTouch->getTapCount() == 1) {
		CCPoint center      = ccp (0.0f, getContentSize().height + cacheRowSize.height / 2.0f);
		unsigned int nhighlightRow = rowNumberAtLocation(ccpAdd(rowsLayer->getPosition(), ccpSub(touchLocation, center)));
		selectRow(nhighlightRow, true);
	} else {
		endMoveWithActionLocation(touchLocation);		
	}
}

void CCControlPicker::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    ccTouchEnded(pTouch, pEvent);
}


#pragma mark - CCControlPickerRow

CCControlPickerRow::CCControlPickerRow() {
	textLabel = 0;
}
CCControlPickerRow::~CCControlPickerRow()
{
//    CC_SAFE_RELEASE(textLabel);
}

bool CCControlPickerRow::init()
{
//    if (superClass::init())
    {
        CCSize defaultSize              = CCSizeMake(CCControlPickerDefaultRowWidth, CCControlPickerDefaultRowHeight);

        textLabel                      = CCLabelTTF::create("",
															 "HelveticaNeue-Bold",
															 18,
															 CCSizeMake(CCControlPickerDefaultRowWidth,
																		CCControlPickerDefaultRowHeight),
															 kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
		
        textLabel->setVerticalAlignment( kCCVerticalTextAlignmentCenter );
        textLabel->setColor(                ccc3(0, 0, 0));
        textLabel->setAnchorPoint( ccp(0.5f, 0.5f) );
		textLabel->ignoreAnchorPointForPosition(true);
        textLabel->setPosition( ccp (CCControlPickerDefaultRowWidth / 2, CCControlPickerDefaultRowHeight / 2) );

        addChild(textLabel, 1);
        
        setContentSize( defaultSize );
    }
	return true;
}

CCControlPickerRow* CCControlPickerRow::initWithTitle(const std::string& title)
{
    if (init())
    {
        textLabel->setString( title.c_str() );
    }
    return this;
}

CCControlPickerRow* CCControlPickerRow::rowWithTitle(const std::string &title)
{
	CCControlPickerRow* row = new CCControlPickerRow;
	row->initWithTitle(title);
	row->autorelease();
    return row;
}

#pragma mark Properties

#pragma mark - Public Methods

void CCControlPickerRow::fitRowInSize(CCSize size)
{
    CCPoint center          = ccp(size.width / 2, size.height / 2);

    setContentSize( size );
	
    textLabel->setDimensions( size );
    textLabel->setContentSize( size );
    textLabel->setPosition( CCPointMake(0, -center.y / 2) );
}

#pragma mark - CCControlPickerRow Delegate Methods

void CCControlPickerRow::rowDidHighlighted()
{
//    textLabel->setFontSize( 24.0f );
//    textLabel->setColor( ccc3(201, 62, 119) );
}

void CCControlPickerRow::rowDidDownplayed()
{
//    textLabel->setFontSize( 18.0f );
//    textLabel->setColor( ccc3(86, 86, 86) );
}

void CCControlPickerRow::rowWillBeSelected()
{
//    textLabel->setFontSize( 29.0f );
//    textLabel->setColor( ccc3(201, 62, 119) );
}

void CCControlPickerRow::rowDidSelected()
{
    
}

