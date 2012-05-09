//
//  DecoratedBox.m
//  DecoratedBox
//
//  Created by Fabio Rodella on 7/8/11.
//  Copyright 2011 Crocodella Software. All rights reserved.
//

#include "DecoratedBox.h"

//
//@implementation DecoratedBox
//
//@synthesize cellSize;
//@synthesize boxWidth;
//@synthesize boxHeight;
//
//+ (id)decoratedBoxWithFile:(NSString *)filename width:(CGFloat)w height:(CGFloat)h {
//    return [[[self alloc] initWithFile:filename width:w height:h] autorelease];
//}
//
//- (id)initWithFile:(NSString *)filename width:(CGFloat)w height:(CGFloat)h {
//    if ((self = [super initWithFile:filename capacity:9])) {
//        
//        cellSize = [self.textureAtlas.texture contentSize].width / 3;
//        
//        self.anchorPoint = ccp(0.5, 0.5);
//        
//        [self resizeToWidth:w height:h];        
//    }
//    return self;
//}

DecoratedBox *DecoratedBox::decoratedBoxWithFile(const char *pzsFileName, float width, float height){
    DecoratedBox *pRet = new DecoratedBox();
    if (pRet && pRet->initWithFile(pzsFileName, width, height))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool DecoratedBox::initWithFile(const char *pzsFileName, float width, float height){
    
//    CCSpriteFrame *sprFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
    
//    CCSprite *sprite = CCSprite::spriteWithSpriteFrame(sprFrame);
    
    if (!CCSpriteBatchNode::initWithFile(pzsFileName,9)) {
        return false;
    }
    
	cellSizeX = this->getTextureAtlas()->getTexture()->getContentSize().width / 3;
	cellSizeY = this->getTextureAtlas()->getTexture()->getContentSize().height / 3;
    
	this->setIsRelativeAnchorPoint(true);
    this->setAnchorPoint(ccp(0.5,0.5));
    
    this->resizeToWidth(width, height);
    
    return true;
}

void DecoratedBox::resizeToWidth(float width, float height){
	
    this->removeAllChildrenWithCleanup(true);
    
    boxWidth = width;
    boxHeight = height;
    
    int uw = floor(width / cellSizeX);
    int uh = floor(height / cellSizeY);
    
	float realW = 0;
	float realH = 0;
	
    this->setContentSize(CCSizeMake(uw * cellSizeX, uh * cellSizeY));
    
    for (int j = 0; j < uh; j++) {
        for (int i = 0; i < uw; i++) {
            
            CCRect rect;
            
            if (i == 0) {
                
                if (j == (uh - 1)) {
                    // Top left cap
                    rect = CCRectMake(0, 0, cellSizeX, cellSizeY);
                } else if (j == 0) {
                    // Bottom left cap
                    rect = CCRectMake(0, cellSizeY * 2, cellSizeX, cellSizeY);
                } else {
                    // Left border
                    rect = CCRectMake(0, cellSizeY, cellSizeX, cellSizeY);
                }
                
            } else if (i == (uw - 1)) {
                
                if (j == (uh - 1)) {
                    // Top right cap
                    rect = CCRectMake(cellSizeX * 2, 0, cellSizeX, cellSizeY);
                } else if (j == 0) {
                    // Bottom right cap
                    rect = CCRectMake(cellSizeX * 2, cellSizeY * 2, cellSizeX, cellSizeY);
                } else {
                    // Right border
                    rect = CCRectMake(cellSizeX * 2, cellSizeY, cellSizeX, cellSizeY);
                }
                
            } else if (j == (uh - 1)) {
                
                // Top border
                rect = CCRectMake(cellSizeX, 0, cellSizeX, cellSizeY);
                
            } else if (j == 0) {
                
                // Bottom border
                rect = CCRectMake(cellSizeX, cellSizeY * 2, cellSizeX, cellSizeY);
                
            } else {
                
                // Middle
                rect = CCRectMake(cellSizeX, cellSizeY, cellSizeX, cellSizeY);
                
            }

            CCSprite *b = CCSprite::spriteWithBatchNode(this, rect);
            b->setPosition(ccp(i*cellSizeX,j*cellSizeY));
            b->setTag(j * cellSizeX + i);
            this->addChild(b);
			
			if (i == (uw - 1) && realW ==0)
				realW = realW + b->getPosition().x;
			if (j == (uh - 1) && realH ==0)
				realH = realH + b->getPosition().y;
        }
    }
	
	boxWidth = realW;
    boxHeight = realH;
	this->setContentSize(CCSizeMake(realW,realH));
}

// Opacity Protocol

/** Override synthesized setOpacity to recurse items */
void DecoratedBox::setOpacity(GLubyte var)
{
	m_cOpacity = var;
	
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pChild);
				if (pRGBAProtocol)
				{
					pRGBAProtocol->setOpacity(m_cOpacity);
				}
			}
		}
	}
}

GLubyte DecoratedBox::getOpacity(void)
{
	return m_cOpacity;
}

void DecoratedBox::setColor(const ccColor3B& var)
{
	m_tColor = var;
	
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pChild);
				if (pRGBAProtocol)
				{
					pRGBAProtocol->setColor(m_tColor);
				}
			}
		}
	}
}

const ccColor3B& DecoratedBox::getColor(void)
{
	return m_tColor;
}

