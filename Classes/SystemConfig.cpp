#include "SystemConfig.h"
#include "TargetDeviceUtils.h"

float SystemConfig::gScaleX;
float SystemConfig::gScaleY;
float SystemConfig::offset;
int SystemConfig::isHd = 0;
cocos2d::Size SystemConfig::winSize;


float SystemConfig::MESSAGE_BOX_APPEAR_WAIT_STAND = 2.0f;
float SystemConfig::MESSAGE_BOX_APPEAR_WAIT = SystemConfig::MESSAGE_BOX_APPEAR_WAIT_STAND;



void SystemConfig::setPosition(const float x, const float y, cocos2d::Node *node)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if( isHd == true )
		node->setPosition( cocos2d::Vec2(x, y + offset) );
	else
		node->setPosition( cocos2d::Vec2(x/2, y/2 + offset) );
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	node->setPosition(cocos2d::Vec2(x / 2, y / 2 + offset));
#else
    node->setPosition( cocos2d::Vec2(x/2, y/2 + offset) );
#endif
}

void SystemConfig::setPositionY(const float y, cocos2d::Node *node)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    node->setPosition( cocos2d::Vec2( node->getPositionX(), y + offset) );
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	node->setPosition(cocos2d::Vec2(node->getPositionX(), y / 2 + offset));
#else
    node->setPosition( cocos2d::Vec2(node->getPositionX(), y/2 + offset) );
#endif
}



float SystemConfig::relativePixel(const float p)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if( isHd = true )
		return p;

	return p/2.0;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return p / 2.0;
#else
	return p/2.0;
#endif
}

float SystemConfig::getYPos(const float y)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if( isHd == true )
		return (y + offset);
	return (y/2 + offset);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)	
	return (y / 2 + offset);
#else
    return (y/2 + offset);
#endif
    
}

float SystemConfig::getXPos(const float x)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if( isHd == true )
		return x;
	return x / 2;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)	
	return x / 2;
#else
    return x / 2;
#endif
}

cocos2d::Size SystemConfig::getWinSize(void)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	if( isHd == true )
//		return x;
//	return x / 2;
	return winSize;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)	
	return winSize;
#else
    return winSize;|
#endif
}

void SystemConfig::setOffset(const float heightOffset)
{
    offset = heightOffset;
}

int SystemConfig::getTTFSize(const int iosSize)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if( isHd == true ){ return iosSize * 2; }

    return iosSize;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)	
	return iosSize;
#else
    return iosSize;
#endif
}


namespace SlotSpace {
    int BaseBoxXPos1;
    int BaseBoxXPos2;
    int BaseBoxXPos3;
    
    int VisableBoxYPos1;
    int VisableBoxYPos2;
    int VisableBoxYPos3;
    
    int const LOAD_ROWS = 6;
    int const SLOT_COLS = 3;
}



