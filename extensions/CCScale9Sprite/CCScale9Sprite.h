//
//  CCScale9Sprite.h
//  PlantCaring
//
//  Created by Jung Sang-Taik on 12. 3. 16..
//  Copyright (c) 2012년 Neofect. All rights reserved.
//

#ifndef __CCScale9Sprite_H__
#define __CCScale9Sprite_H__


#include "cocos2d.h"
using namespace cocos2d;

enum positions
{
	pCentre = 0,
	pTop,
	pLeft,
	pRight,
	pBottom,
	pTopRight,
	pTopLeft,
	pBottomRight,
	pBottomLeft
};

class CCScale9Sprite : public CCNode, public CCRGBAProtocol
{
public:
	CCScale9Sprite();
	virtual ~CCScale9Sprite();

public:
	/** Original sprite's size. */
	CC_SYNTHESIZE(CCSize, m_originalSize, OriginalSize);
	/** Prefered sprite's size. By default the prefered size is the original size. */

	//if the preferredSize component is given as -1, it is ignored
	CC_SYNTHESIZE(CCSize, m_preferredSize, PreferredSize); 
	/** 
	 * The end-cap insets. 
	 * On a non-resizeable sprite, this property is set to CGRectZero; the sprite 
	 * does not use end caps and the entire sprite is subject to stretching. 
	 */
	
	/** Opacity: conforms to CCRGBAProtocol protocol */
	CC_PROPERTY(GLubyte, m_cOpacity, Opacity)
	/** Color: conforms to CCRGBAProtocol protocol */
	CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color)
	CC_PROPERTY(CCRect, m_capInsets, CapInsets);
	
	
protected:
	CCRect m_spriteRect;
    
    CCSpriteBatchNode* scale9Image;
    CCSprite* topLeft;
    CCSprite* top;
    CCSprite* topRight;
    CCSprite* left;
    CCSprite* centre;
    CCSprite* right;
    CCSprite* bottomLeft;
    CCSprite* bottom;
    CCSprite* bottomRight;
	
	/** Conforms to CocosNodeRGBA protocol. */
	ccColor3B m_sColorUnmodified;
	bool m_bIsOpacityModifyRGB;
	
//	virtual void setOpacityModifyRGB(bool bValue)
//	{
//		ccColor3B oldColor    = this->m_tColor;
//		m_bIsOpacityModifyRGB = bValue;
//		this->m_tColor        = oldColor;
//	}
//	virtual bool isOpacityModifyRGB()
//	{
//		return m_bIsOpacityModifyRGB;
//	}
	
public:
	
	void virtual setContentSize(const CCSize &size);
	
	virtual bool initWithBatchNode(CCSpriteBatchNode* batchnode, CCRect rect, CCRect capInsets);
	/**
	 * Initializes a 9-slice sprite with a texture file, a delimitation zone and
	 * with the specified cap insets.
	 * Once the sprite is created, you can then call its "setContentSize:" method
	 * to resize the sprite will all it's 9-slice goodness intract.
	 * It respects the anchorPoint too.
	 *
	 * @param file The name of the texture file.
	 * @param rect The rectangle that describes the sub-part of the texture that
	 * is the whole image. If the shape is the whole texture, set this to the 
	 * texture's full rect.
	 * @param capInsets The values to use for the cap insets.
	 */
	virtual bool initWithFile(const char* file, CCRect rect,  CCRect capInsets);
	
	/** 
	 * Creates a 9-slice sprite with a texture file, a delimitation zone and
	 * with the specified cap insets.
	 *
	 * @see initWithFile:rect:centerRegion:
	 */
	static CCScale9Sprite* spriteWithFile(const char* file, CCRect rect,  CCRect capInsets);
	
	/**
	 * Initializes a 9-slice sprite with a texture file and a delimitation zone. The
	 * texture will be broken down into a 3×3 grid of equal blocks.
	 * Once the sprite is created, you can then call its "setContentSize:" method
	 * to resize the sprite will all it's 9-slice goodness intract.
	 * It respects the anchorPoint too.
	 *
	 * @param file The name of the texture file.
	 * @param rect The rectangle that describes the sub-part of the texture that
	 * is the whole image. If the shape is the whole texture, set this to the 
	 * texture's full rect.
	 */
	virtual bool initWithFile(const char* file, CCRect rect);
	
	/** 
	 * Creates a 9-slice sprite with a texture file and a delimitation zone. The
	 * texture will be broken down into a 3×3 grid of equal blocks.
	 *
	 * @see initWithFile:rect:
	 */
	static CCScale9Sprite* spriteWithFile(const char* file, CCRect rect);
	
	/**
	 * Initializes a 9-slice sprite with a texture file and with the specified cap
	 * insets.
	 * Once the sprite is created, you can then call its "setContentSize:" method
	 * to resize the sprite will all it's 9-slice goodness intract.
	 * It respects the anchorPoint too.
	 *
	 * @param file The name of the texture file.
	 * @param capInsets The values to use for the cap insets.
	 */
	virtual bool initWithFile(CCRect capInsets, const char* file);
	
	/** 
	 * Creates a 9-slice sprite with a texture file. The whole texture will be
	 * broken down into a 3×3 grid of equal blocks.
	 *
	 * @see initWithFile:capInsets:
	 */
	static CCScale9Sprite* spriteWithFile(CCRect capInsets, const char* file);
	
	/**
	 * Initializes a 9-slice sprite with a texture file. The whole texture will be
	 * broken down into a 3×3 grid of equal blocks.
	 * Once the sprite is created, you can then call its "setContentSize:" method
	 * to resize the sprite will all it's 9-slice goodness intract.
	 * It respects the anchorPoint too.
	 *
	 * @param file The name of the texture file.
	 */
	virtual bool initWithFile(const char* file);
	
	/** 
	 * Creates a 9-slice sprite with a texture file. The whole texture will be
	 * broken down into a 3×3 grid of equal blocks.
	 *
	 * @see initWithFile:
	 */
	static CCScale9Sprite* spriteWithFile(const char* file);
	
	/**
	 * Initializes a 9-slice sprite with an sprite frame and with the specified 
	 * cap insets.
	 * Once the sprite is created, you can then call its "setContentSize:" method
	 * to resize the sprite will all it's 9-slice goodness intract.
	 * It respects the anchorPoint too.
	 *
	 * @param spriteFrame The sprite frame object.
	 * @param capInsets The values to use for the cap insets.
	 */
	virtual bool initWithSpriteFrame(CCSpriteFrame* spriteFrame, CCRect capInsets);
	
	/**
	 * Creates a 9-slice sprite with an sprite frame and the centre of its zone.
	 * Once the sprite is created, you can then call its "setContentSize:" method
	 * to resize the sprite will all it's 9-slice goodness intract.
	 * It respects the anchorPoint too.
	 *
	 * @see initWithSpriteFrame:centerRegion:
	 */
	static CCScale9Sprite* spriteWithSpriteFrame(CCSpriteFrame* spriteFrame, CCRect capInsets);	
	/**
	 * Initializes a 9-slice sprite with an sprite frame.
	 * Once the sprite is created, you can then call its "setContentSize:" method
	 * to resize the sprite will all it's 9-slice goodness intract.
	 * It respects the anchorPoint too.
	 *
	 * @param spriteFrame The sprite frame object.
	 */
	virtual bool initWithSpriteFrame(CCSpriteFrame* spriteFrame);
	
	/**
	 * Creates a 9-slice sprite with an sprite frame.
	 * Once the sprite is created, you can then call its "setContentSize:" method
	 * to resize the sprite will all it's 9-slice goodness intract.
	 * It respects the anchorPoint too.
	 *
	 * @see initWithSpriteFrame:
	 */
	static CCScale9Sprite* spriteWithSpriteFrame(CCSpriteFrame* spriteFrame);	
	/**
	 * Initializes a 9-slice sprite with an sprite frame name and with the specified 
	 * cap insets.
	 * Once the sprite is created, you can then call its "setContentSize:" method
	 * to resize the sprite will all it's 9-slice goodness intract.
	 * It respects the anchorPoint too.
	 *
	 * @param spriteFrameName The sprite frame name.
	 * @param capInsets The values to use for the cap insets.
	 */
	virtual bool initWithSpriteFrameName(const char*spriteFrameName, CCRect capInsets);
	/**
	 * Creates a 9-slice sprite with an sprite frame name and the centre of its
	 * zone.
	 * Once the sprite is created, you can then call its "setContentSize:" method
	 * to resize the sprite will all it's 9-slice goodness intract.
	 * It respects the anchorPoint too.
	 *
	 * @see initWithSpriteFrameName:centerRegion:
	 */
	static CCScale9Sprite* spriteWithSpriteFrameName(const char*spriteFrameName, CCRect capInsets);	
	/**
	 * Initializes a 9-slice sprite with an sprite frame name.
	 * Once the sprite is created, you can then call its "setContentSize:" method
	 * to resize the sprite will all it's 9-slice goodness intract.
	 * It respects the anchorPoint too.
	 *
	 * @param spriteFrameName The sprite frame name.
	 */
	virtual bool initWithSpriteFrameName(const char*spriteFrameName);
	
	/**
	 * Creates a 9-slice sprite with an sprite frame name.
	 * Once the sprite is created, you can then call its "setContentSize:" method
	 * to resize the sprite will all it's 9-slice goodness intract.
	 * It respects the anchorPoint too.
	 *
	 * @see initWithSpriteFrameName:
	 */
	static CCScale9Sprite* spriteWithSpriteFrameName(const char*spriteFrameName);
	
	/**
	 * Creates and returns a new sprite object with the specified cap insets.
	 * You use this method to add cap insets to a sprite or to change the existing
	 * cap insets of a sprite. In both cases, you get back a new image and the 
	 * original sprite remains untouched.
	 *
	 * @param capInsets The values to use for the cap insets.
	 */
	CCScale9Sprite* resizableSpriteWithCapInsets(CCRect capInsets);
	
	
	

	
	// optional
	
	/** sets the premultipliedAlphaOpacity property.
	 If set to NO then opacity will be applied as: glColor(R,G,B,opacity);
	 If set to YES then oapcity will be applied as: glColor(opacity, opacity, opacity, opacity );
	 Textures with premultiplied alpha will have this property by default on YES. Otherwise the default value is NO
	 @since v0.8
	 */
	virtual void setOpacityModifyRGB(bool bValue);
	
	/** returns whether or not the opacity will be applied using glColor(R,G,B,opacity) or glColor(opacity, opacity, opacity, opacity);
	 @since v0.8
	 */
	virtual bool isOpacityModifyRGB(void);
	
};

#endif // __CCScale9Sprite_H__
