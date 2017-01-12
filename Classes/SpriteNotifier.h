#ifndef __gameTest__SpriteNotifier__
#define __gameTest__SpriteNotifier__

#include "cocos2d.h"

using namespace cocos2d;

class SpriteNotifier : public cocos2d::Node
{    
public:
    SpriteNotifier()
    {
        _sprite = NULL;
        _notificationID = 0;
    }
    
private:
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool onTouchBegan(Touch* touch, Event* event);
    virtual void onTouchEnded(Touch* touch, Event* event);
   
    Rect rect();

public:
    Sprite *_sprite;
    int _notificationID;
	std::function< void(SpriteNotifier *) > _callback;
};




#endif /* defined(__gameTest__SpriteNotifier__) */
