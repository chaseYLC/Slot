#ifndef gameTest_SystemConfig_h
#define gameTest_SystemConfig_h

#include "cocos2d.h"

#define SND CocosDenshion::SimpleAudioEngine::sharedEngine
#define _rp SystemConfig::relativePixel

#define NXLog cocos2d::CCLog


#define TOUCH_MOVED_ACCEPTABLE  (8)

class SystemConfig
{
public:
    static void setPosition(const float x, const float y, cocos2d::Node *node);
    static void setPositionY(const float y, cocos2d::Node *node);
    static void setOffset(const float heightOffset);
    static float getYPos(const float y);
    static float getXPos(const float x);
    static cocos2d::Size getWinSize(void);
    static float relativePixel(const float p);
    static int getTTFSize(const int iosSize);
public:
    static int SCWIDTHS;
    static int SCHEIGHTS;
    
    static float gScaleX;
    static float gScaleY;
    static cocos2d::Size winSize;
    static float offset;
    static int isHd;
    
    static float MESSAGE_BOX_APPEAR_WAIT;
    static float MESSAGE_BOX_APPEAR_WAIT_STAND;
};

namespace SlotSpace {
    extern int BaseBoxXPos1;
    extern int BaseBoxXPos2;
    extern int BaseBoxXPos3;
    
    extern int VisableBoxYPos1;
    extern int VisableBoxYPos2;
    extern int VisableBoxYPos3;
    
    extern int const LOAD_ROWS;
    extern int const SLOT_COLS;

};



#endif
