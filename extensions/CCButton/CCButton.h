//
//  CCButton.h
//  test
//
//  Created by  小 苏 http://www.cocos2d-x.org/boards/6/topics/7963
//

#include "cocos2d.h" 
#define TAP_MAX_DRAG 10

using namespace cocos2d;

enum {
    CCControlStateNormal       = 0,
    CCControlStateSelected     = 1 << 0,                  // flag usable by app (see below)
    CCControlStateDisabled     = 1 << 1,
    CCControlStateHighlighted  = 1 << 2                 // todo
};
typedef unsigned int CCControlState;

class CCButton : public CCNode, public CCTargetedTouchDelegate
{
private:
    bool initWithFile(const char* filename, CCObject* target, SEL_MenuHandler selector);
    CCObject* target;
    SEL_MenuHandler selector;
    bool touched;
    CCPoint touchPoint;

    bool isDisabled;

    CCControlState curState;

    CCMutableDictionary<int,CCNode*> * backgroundNodes; //zOrder is 0
    CCMutableDictionary<int,CCNode*> * touchNodes;        //zOrder is 1
    CCMutableDictionary<int,CCString*> * titleCCStrings;  //zOrder is 2

    void setState(CCControlState mState);

public:
    CCButton();
    ~CCButton();

    void initWithFile(CCObject* target, SEL_MenuHandler selector,const char * mNormal,const char * mSelected,const char * mDisabled=NULL);
    static CCButton * buttonWithFiles(CCObject* target, SEL_MenuHandler selector,const char * mNormal,const char * mSelected,const char * mDisabled=NULL);

    void setTitleForState(const char * mTitle,CCControlState mState);
    const char* titleForState(CCControlState mState);

    void setDisable(bool mIsDisabled);

    //todo
    virtual void setTitleColorForState(ccColor3B mColor,CCControlState mState){CC_UNUSED_PARAM(mColor);CC_UNUSED_PARAM(mState);};
    virtual ccColor3B titleColorForState(CCControlState mState){CC_UNUSED_PARAM(mState);return ccYELLOW;};

    void setImageForState(CCNode* mNode,CCControlState mState);
    CCNode * imageForState(CCControlState mState);
    void setBackgroundImageForState(CCNode *mNode,CCControlState mState);// default is NULL
    CCNode * backgroundImageForState(CCControlState mState);

    // touch events
    CCRect rect();
    bool containsTouchLocation(CCTouch* touch);
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    virtual void touchDelegateRetain();
    virtual void touchDelegateRelease();
};
