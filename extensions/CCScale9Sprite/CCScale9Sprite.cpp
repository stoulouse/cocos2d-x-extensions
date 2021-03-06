//
//  CCScale9Sprite.cpp
//  PlantCaring
//
//  Created by Jung Sang-Taik on 12. 3. 16..
//  Copyright (c) 2012년 Neofect. All rights reserved.
//

#include "CCScale9Sprite.h"

CCScale9Sprite::CCScale9Sprite()
{
	
}

CCScale9Sprite::~CCScale9Sprite()
{

}

bool CCScale9Sprite::initWithBatchNode(CCSpriteBatchNode* batchnode, const CCRect& inRect, const CCRect& capInsets)
{
	
	CCAssert(batchnode != NULL, "The batchnode must be not nil.");
	
	scale9Image = batchnode;
	
	CCRect rect = inRect;
	
	// If there is no given rect
	if ( rect.equals(CCRectZero) )
	{
		// Get the texture size as original
		CCSize textureSize = scale9Image->getTextureAtlas()->getTexture()->getContentSize();
		
		rect = CCRectMake(0, 0, textureSize.width, textureSize.height);
	}
	
	// Set the given rect's size as original size
	m_spriteRect = rect;
	m_originalSize = rect.size;
	m_preferredSize = m_originalSize;
	m_capInsets = capInsets;
	this->setAnchorPoint(ccp(0.5f, 0.5f));
	
	// If there is no specified center region
	if ( m_capInsets.equals(CCRectZero) )
	{
		// Apply the 3x3 grid format
		m_capInsets = CCRectMake(
								rect.origin.x + m_originalSize.width / 3, 
								rect.origin.y + m_originalSize.height / 3, 
								m_originalSize.width / 3,
								m_originalSize.height / 3);
	}
	
	// Get the image edges
	float l = rect.origin.x;
	float t = rect.origin.y;
	float h = rect.size.height;
	float w = rect.size.width;

	//
	// Set up the image
	//
	
	// Centre
	centre = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(m_capInsets.origin.x + l, m_capInsets.origin.y + t, m_capInsets.size.width, m_capInsets.size.height));
	scale9Image->addChild(centre ,0 ,pCentre);
	
	// Top
	top = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(l + m_capInsets.origin.x,
																t,
																m_capInsets.size.width,
																m_capInsets.origin.y));
	scale9Image->addChild(top, 1, pTop);
	
	// Bottom
	bottom = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake( l + m_capInsets.origin.x,
																   t + m_capInsets.origin.y + m_capInsets.size.height,
																   m_capInsets.size.width,
																   h - (m_capInsets.origin.y + m_capInsets.size.height) ));
	scale9Image->addChild(bottom, 1, pBottom);
	
	// Left
	left = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(
																 l,
																 t + m_capInsets.origin.y,
																 m_capInsets.origin.x,
																 m_capInsets.size.height) );
	scale9Image->addChild(left, 1, pLeft);
	
	// Right
	right = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(
																  l + m_capInsets.origin.x + m_capInsets.size.width,
																  t + m_capInsets.origin.y,
																  w - (m_capInsets.origin.x + m_capInsets.size.width),
																  m_capInsets.size.height));
	scale9Image->addChild(right, 1, pRight);
	
	// Top left
	topLeft = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(
																	l,
																	t,
																	m_capInsets.origin.x,
																	m_capInsets.origin.y));

	scale9Image->addChild(topLeft, 2, pTopLeft);

	// Top right
	topRight = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(
																				 l + m_capInsets.origin.x + m_capInsets.size.width,
																				 t,
																				 w - (m_capInsets.origin.x + m_capInsets.size.width),
																				 m_capInsets.origin.y));
	
	scale9Image->addChild(topRight, 2, pTopRight);
	
	// Bottom left
	bottomLeft = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(
																	   l,
																	   t + m_capInsets.origin.y + m_capInsets.size.height,
																	   m_capInsets.origin.x,
																	   h - (m_capInsets.origin.y + m_capInsets.size.height)) );
	scale9Image->addChild(bottomLeft, 2, pBottomLeft);
	
	// Bottom right
	bottomRight = CCSprite::createWithTexture(scale9Image->getTexture(), CCRectMake(
																		l + m_capInsets.origin.x + m_capInsets.size.width,
																		t + m_capInsets.origin.y + m_capInsets.size.height,
																		w - (m_capInsets.origin.x + m_capInsets.size.width),
																		h - (m_capInsets.origin.y + m_capInsets.size.height)) );
	scale9Image->addChild(bottomRight, 2, pBottomRight);
	
	this->setContentSize(rect.size);
	this->addChild(scale9Image);
	
	return true;
}

void CCScale9Sprite::setContentSize(const CCSize &size)
{
	
	CCNode::setContentSize(size);
	setAnchorPoint(ccp(0.5f,0.5f));
	
//	CCLOG("scale9 set content size %0.2f %0.2f",size.width,size.height);
//	CCLOG("leftCap %0.2f rightCap %0.2f",topLeft->getContentSize().width,topRight->getContentSize().width);
	
	float sizableWidth = size.width - topLeft->getContentSize().width - topRight->getContentSize().width;
	float sizableHeight = size.height - topLeft->getContentSize().height - bottomRight->getContentSize().height;
	float horizontalScale = sizableWidth/centre->getContentSize().width;
	float verticalScale = sizableHeight/centre->getContentSize().height;
	centre->setScaleX(horizontalScale);
	centre->setScaleY(verticalScale);
	float rescaledWidth = centre->getContentSize().width * horizontalScale;
	float rescaledHeight = centre->getContentSize().height * verticalScale;
	
	float despx = size.width*0.5f;
	float despy = size.height*0.5f;

	//Position corners
	topLeft->setPosition(ccp(-rescaledWidth/2 - topLeft->getContentSize().width/2 +despx, rescaledHeight/2 + topLeft->getContentSize().height*0.5f +despy) );
	topRight->setPosition(ccp(rescaledWidth/2 + topRight->getContentSize().width/2 +despx, rescaledHeight/2 + topRight->getContentSize().height*0.5f +despy));
	bottomLeft->setPosition(ccp(-rescaledWidth/2 - bottomLeft->getContentSize().width/2 +despx, -rescaledHeight/2 - bottomLeft->getContentSize().height*0.5f +despy));
	bottomRight->setPosition(ccp(rescaledWidth/2 + bottomRight->getContentSize().width/2 +despx, -rescaledHeight/2 + -bottomRight->getContentSize().height*0.5f +despy));

	top->setScaleX(horizontalScale);
	top->setPosition(ccp(0+despx,rescaledHeight/2 + topLeft->getContentSize().height*0.5f +despy));
	bottom->setScaleX (horizontalScale);
	bottom->setPosition(ccp(0+despx,-rescaledHeight/2 - bottomLeft->getContentSize().height*0.5f +despy));
	left->setScaleY (verticalScale);
	left->setPosition(ccp(-rescaledWidth/2 - topLeft->getContentSize().width/2 +despx, 0+despy));
	right->setScaleY (verticalScale);
	right->setPosition(ccp(rescaledWidth/2 + topRight->getContentSize().width/2 +despx, 0+despy));
	
	centre->setPosition(ccp(despx, despy));
	
//	CCLOG("Scale9 setContentSize %02.f x %02.f <%0.2f x %0.2f>",sizableWidth,sizableHeight,horizontalScale,verticalScale);
}

bool CCScale9Sprite::initWithFile(const char* file, const CCRect& rect,  const CCRect& capInsets)
{
	CCAssert(file != NULL, "Invalid file for sprite");
    
    CCSpriteBatchNode *batchnode = CCSpriteBatchNode::create(file, 9);
    bool pReturn = this->initWithBatchNode(batchnode, rect, capInsets);
    return pReturn;
}

bool CCScale9Sprite::initWithTexture(CCTexture2D* tex, const CCRect& rect,  const CCRect& capInsets)
{
	CCAssert(tex != NULL, "Invalid file for sprite");
    
    CCSpriteBatchNode *batchnode = CCSpriteBatchNode::createWithTexture(tex, 9);
    bool pReturn = this->initWithBatchNode(batchnode, rect, capInsets);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::spriteWithFile(const char* file, const CCRect& rect,  const CCRect& capInsets)
{
	CCScale9Sprite* pReturn = new CCScale9Sprite();
	if ( pReturn && pReturn->initWithFile(file, rect, capInsets) )
	{
		pReturn->autorelease();
		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	return NULL;
}

bool CCScale9Sprite::initWithFile(const char* file, const CCRect& rect)
{
    bool pReturn = this->initWithFile(file, rect, CCRectZero);
    return pReturn;
}

bool CCScale9Sprite::initWithTexture(CCTexture2D* file, const CCRect& rect)
{
    bool pReturn = this->initWithTexture(file, rect, CCRectZero);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::spriteWithFile(const char* file, const CCRect& rect)
{
	CCScale9Sprite* pReturn = new CCScale9Sprite();
	if ( pReturn && pReturn->initWithFile(file, rect) )
	{
		pReturn->autorelease();
		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	return NULL;
}


bool CCScale9Sprite::initWithFile(const CCRect& capInsets, const char* file)
{
    bool pReturn = this->initWithFile(file, CCRectZero, capInsets);
    return pReturn;
}

bool CCScale9Sprite::initWithTexture(const CCRect& capInsets, CCTexture2D* file)
{
    bool pReturn = this->initWithTexture(file, CCRectZero, capInsets);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::spriteWithFile(const CCRect& capInsets, const char* file)
{
	CCScale9Sprite* pReturn = new CCScale9Sprite();
	if ( pReturn && pReturn->initWithFile(file, capInsets) )
	{
		pReturn->autorelease();
		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	return NULL;
}

bool CCScale9Sprite::initWithFile(const char* file)
{
    bool pReturn = this->initWithFile(file, CCRectZero);
    return pReturn;
	
}

bool CCScale9Sprite::initWithTexture(CCTexture2D* file)
{
    bool pReturn = this->initWithTexture(file, CCRectZero);
    return pReturn;
	
}

CCScale9Sprite* CCScale9Sprite::spriteWithFile(const char* file)
{
	CCScale9Sprite* pReturn = new CCScale9Sprite();
	if ( pReturn && pReturn->initWithFile(file) )
	{
		pReturn->autorelease();
		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	return NULL;
}

bool CCScale9Sprite::initWithSpriteFrame(CCSpriteFrame* spriteFrame, const CCRect& capInsets)
{
	CCAssert(spriteFrame != NULL, "Sprite frame must be not nil");
    
    CCSpriteBatchNode *batchnode = CCSpriteBatchNode::createWithTexture(spriteFrame->getTexture(), 9);
    bool pReturn = this->initWithBatchNode(batchnode, spriteFrame->getRect(), capInsets);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::spriteWithSpriteFrame(CCSpriteFrame* spriteFrame, const CCRect& capInsets)
{
	CCScale9Sprite* pReturn = new CCScale9Sprite();
	if ( pReturn && pReturn->initWithSpriteFrame(spriteFrame, capInsets) )
	{
		pReturn->autorelease();
		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	return NULL;
}
bool CCScale9Sprite::initWithSpriteFrame(CCSpriteFrame* spriteFrame)
{
	bool pReturn = this->initWithSpriteFrame(spriteFrame, CCRectZero);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::spriteWithSpriteFrame(CCSpriteFrame* spriteFrame)
{
	CCScale9Sprite* pReturn = new CCScale9Sprite();
	if ( pReturn && pReturn->initWithSpriteFrame(spriteFrame) )
	{
		pReturn->autorelease();
		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	return NULL;
}

bool CCScale9Sprite::initWithSpriteFrameName(const char* spriteFrameName, const CCRect& capInsets)
{
	CCAssert(spriteFrameName != NULL, "Invalid spriteFrameName for sprite");
    
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName);
    bool pReturn = this->initWithSpriteFrame(frame, capInsets);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::spriteWithSpriteFrameName(const char* spriteFrameName, const CCRect& capInsets)
{
	CCScale9Sprite* pReturn = new CCScale9Sprite();
	if ( pReturn && pReturn->initWithSpriteFrameName(spriteFrameName, capInsets) )
	{
		pReturn->autorelease();
		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	return NULL;
	
}

bool CCScale9Sprite::initWithSpriteFrameName(const char* spriteFrameName)
{
	bool pReturn = this->initWithSpriteFrameName(spriteFrameName, CCRectZero);
    return pReturn;
}

CCScale9Sprite* CCScale9Sprite::spriteWithSpriteFrameName(const char* spriteFrameName)
{
	CCScale9Sprite* pReturn = new CCScale9Sprite();
	if ( pReturn && pReturn->initWithSpriteFrameName(spriteFrameName) )
	{
		pReturn->autorelease();
		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	return NULL;
	
}

CCScale9Sprite* CCScale9Sprite::resizableSpriteWithCapInsets(const CCRect& capInsets)
{
	CCScale9Sprite* pReturn = new CCScale9Sprite();
	if ( pReturn && pReturn->initWithBatchNode(scale9Image, m_spriteRect, capInsets) )
	{
		pReturn->autorelease();
		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	return NULL;
}

bool CCScale9Sprite::initWithName(const char* name, const CCRect& rect, const CCRect& capInsets)
{
	CCAssert(name != NULL, "Invalid name for sprite");
    
	bool pReturn = false;
	
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
	if (frame) {
		pReturn = this->initWithSpriteFrame(frame, capInsets);
	} else {
		pReturn = this->initWithFile(name, rect, capInsets);
	}

	return pReturn;
}

CCScale9Sprite* CCScale9Sprite::spriteWithName(const char* name, const CCRect& rect, const CCRect& capInsets)
{
	CCScale9Sprite* pReturn = new CCScale9Sprite();
	if ( pReturn && pReturn->initWithName(name, rect, capInsets) )
	{
		pReturn->autorelease();
		return pReturn;
	}
	CC_SAFE_DELETE(pReturn);
	return NULL;
	
}



//LabelBMFont - CCRGBAProtocol protocol
void CCScale9Sprite::setColor(const ccColor3B& color3)
{
	m_tColor = color3;
	if (scale9Image->getChildren() && scale9Image->getChildren()->count() != 0)
	{
		CCObject* child;
		CCARRAY_FOREACH(scale9Image->getChildren(), child)
		{
			CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);		
			if (pNode)
			{
				pNode->setColor(m_tColor);
			}
		}
	}
}
const ccColor3B& CCScale9Sprite::getColor(void)
{
	return m_tColor;
}

void CCScale9Sprite::setOpacity(GLubyte var)
{
	m_cOpacity = var;
	
	if (scale9Image->getChildren() && scale9Image->getChildren()->count() != 0)
	{
		CCObject* child;
		CCARRAY_FOREACH(scale9Image->getChildren(), child)
		{
			CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);
			if (pNode)
			{
				pNode->setOpacity(m_cOpacity);
			}
			//CCNode* pNode = (CCNode*) child;
			//if (pNode)
			//{
			//	CCRGBAProtocol *pRGBAProtocol = (CCRGBAProtocol *)pNode;
			//	if (pRGBAProtocol)
			//	{
			//		pRGBAProtocol->setOpacity(m_cOpacity);
			//	}
			//}
		}
	}
}

/** sets the opacity.
 @warning If the the texture has premultiplied alpha then, the R, G and B channels will be modifed.
 Values goes from 0 to 255, where 255 means fully opaque.
 */
GLubyte CCScale9Sprite::getOpacity()
{
	return m_cOpacity;
}


void CCScale9Sprite::setCapInsets(CCRect capInsets)
{
	m_capInsets = capInsets;
}

CCRect CCScale9Sprite::getCapInsets()
{
	return m_capInsets;
}

void CCScale9Sprite::setOpacityModifyRGB(bool var)
{
	m_bIsOpacityModifyRGB = var;
	if (scale9Image->getChildren() && scale9Image->getChildren()->count() != 0)
	{
		CCObject* child;
		CCARRAY_FOREACH(scale9Image->getChildren(), child)
		{
			CCRGBAProtocol* pNode = dynamic_cast<CCRGBAProtocol*>(child);
			if (pNode)
			{
				pNode->setOpacityModifyRGB(m_bIsOpacityModifyRGB);
			}
			//CCNode* pNode = (CCNode*) child;
			//if (pNode)
			//{
			//	CCRGBAProtocol *pRGBAProtocol = (CCRGBAProtocol *)pNode;
			//	if (pRGBAProtocol)
			//	{
			//		pRGBAProtocol->setIsOpacityModifyRGB(m_bIsOpacityModifyRGB);
			//	}
			//}
		}
	}
}
bool CCScale9Sprite::isOpacityModifyRGB()
{
	return m_bIsOpacityModifyRGB;
}

