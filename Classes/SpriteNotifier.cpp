#include "SpriteNotifier.h"

void SpriteNotifier::onEnter()
{
	Node::onEnter();

	// 터치 활성화
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(SpriteNotifier::onTouchBegan, this);
	//touchListener->onTouchMoved = CC_CALLBACK_2(GameTitleLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SpriteNotifier::onTouchEnded, this);
	//touchListener->onTouchCancelled = CC_CALLBACK_2(GameTitleLayer::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void SpriteNotifier::onExit()
{
	Node::onExit();
}

bool SpriteNotifier::onTouchBegan(Touch* touch, Event* event)
{    
	touch->getLocation();
	Point pt = Director::getInstance()->convertToGL(touch->getLocationInView());

	return rect().containsPoint( pt);
}

void SpriteNotifier::onTouchEnded(Touch* touch, Event* event){
    //    CCLOG(“Fish ccTouchEnded”);
    /* do your stuff here */
	_callback(this);
}

CCRect SpriteNotifier::rect(){
    const float x = (_sprite->getPositionX()) - ((_sprite->getTextureRect().size.width/2) * _sprite->getScaleX());
    const float y = _sprite->getPositionY() - _sprite->getTextureRect().size.height/2 * _sprite->getScaleY();
    const float w = _sprite->getTextureRect().size.width * _sprite->getScaleX();
    const float h = _sprite->getTextureRect().size.height * _sprite->getScaleY();
    
    return Rect(x, y, w, h);
}
