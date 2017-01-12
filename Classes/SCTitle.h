#ifndef gameTest_SCTitle_h
#define gameTest_SCTitle_h

#include "cocos2d.h"

class GameTitleLayer : public cocos2d::LayerColor
{
public:
	GameTitleLayer() = default;
    ~GameTitleLayer();

    bool init();

	virtual void onEnter() override;
	virtual void onExit() override;
    
    CREATE_FUNC(GameTitleLayer);
    
    void loadTitle();    
    
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) override;
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    
private:
    void loadedTitleCharacter();
    void loadedTitle();

private:
	cocos2d::Sprite * m_touchLabel;
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