#ifndef gameTest_SCTitle_h
#define gameTest_SCTitle_h

#include "cocos2d.h"

class GameTitleLayer : public cocos2d::LayerColor
{
public:
	GameTitleLayer() = default;
    ~GameTitleLayer();

    bool init();
    
    CREATE_FUNC(GameTitleLayer);
    
    void loadTitle();    
    
    virtual void TouchesBegan(cocos2d::Set *pTouches, cocos2d::Event *pEvent);
    virtual void TouchesMoved(cocos2d::Set *pTouches, cocos2d::Event *pEvent);
    
private:
    static void loadedTitleCharacter(cocos2d::Node* pSender);
    static void loadedTitle(cocos2d::Node* pSender);
};

class GameTitleScene : public cocos2d::Scene
{
public:
    GameTitleScene():_layer(NULL) {};
    ~GameTitleScene();

    bool init();
    CREATE_FUNC(GameTitleScene);
    
    CC_SYNTHESIZE_READONLY(GameTitleLayer*, _layer, Layer);
};

#endif