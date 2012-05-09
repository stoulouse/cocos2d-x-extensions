//
//  DecoratedBox.h
//  DecoratedBox
//
//  Created by Fabio Rodella on 7/8/11.
//  Copyright 2011 Crocodella Software. All rights reserved.
//  
//  Modify by xiaobin zhou on 11/17/11  cocos2d-x version
//

//#import <Foundation/Foundation.h>
//#import "cocos2d.h"
//
//@interface DecoratedBox : CCSpriteBatchNode {
//    CGFloat cellSize;
//    
//    CGFloat boxWidth;
//    CGFloat boxHeight;
//}
//
//@property (readonly, nonatomic) CGFloat cellSize;
//@property (readonly, nonatomic) CGFloat boxWidth;
//@property (readonly, nonatomic) CGFloat boxHeight;
//
//+ (id)decoratedBoxWithFile:(NSString *)filename width:(CGFloat)w height:(CGFloat)h;
//
//- (id)initWithFile:(NSString *)filename width:(CGFloat)w height:(CGFloat)h;
//
//- (void)resizeToWidth:(CGFloat)w height:(CGFloat)h;
//
//@end

#ifndef _DECORATED_BOX_
#define _DECORATED_BOX_

#include "cocos2d.h"

using namespace cocos2d;

class DecoratedBox : public CCSpriteBatchNode ,public CCRGBAProtocol
{
    
public:
    static DecoratedBox *decoratedBoxWithFile(const char *pzsFileName, float width, float height);
    
    bool initWithFile(const char *pzsFileName, float width, float height);
    
    void resizeToWidth(float width, float height);
    
	
	/** Color: conforms with CCRGBAProtocol protocol */
	CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color);
	/** Opacity: conforms with CCRGBAProtocol protocol */
	CC_PROPERTY(GLubyte, m_cOpacity, Opacity);
	
	virtual void setIsOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
	virtual bool getIsOpacityModifyRGB(void) { return false;}
private:
    
    CC_SYNTHESIZE_READONLY(float, cellSizeX, CellSizeX);
	CC_SYNTHESIZE_READONLY(float, cellSizeY, CellSizeY);
    CC_SYNTHESIZE_READONLY(float, boxWidth, BoxWidth);
    CC_SYNTHESIZE_READONLY(float, boxHeight, BoxHeight);
};


#endif
