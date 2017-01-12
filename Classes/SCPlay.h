#ifndef gameTest_SCGame_h
#define gameTest_SCGame_h

#include "cocos2d.h"
#include "LAPlaySlot.h"
#include "LAPlayEffect.h"
#include "SlotInfo.h"
#include "AsyncResourceLoader.h"
#include "SpriteNotifier.h"

USING_NS_CC;

struct HoldButton
{
    CCSprite *led;
    bool holdOn;
    SpriteNotifier area;
    
    HoldButton()
    {
        led = NULL;
        holdOn = false;
    }
};

class PlayLayer
    : public cocos2d::LayerColor
{
public:
    enum
    {
        BTN_SPIN = 0,
        BTN_BACK,
        BTN_BET,
        BTN_MAXBET,
        BTN_HOLD1,
        BTN_HOLD2,
        BTN_HOLD3,
        BTN_MINIGAME,
        BTN_FORTUNE,
    };
    
    
    PlayLayer();
    
    virtual ~PlayLayer();
    bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    void touchSpin(CCObject* pSender);
    
    void setSlotLayer(LAPlaySlot * slotLayer){_slotLayer = slotLayer;}
    
    void showWinsLabel(int const wins);
    
    void finishedCoinAction(CCObject* pSender);
    void finishedCoinActionOffset(CCObject* pSender);
    void finishedExpAction(CCObject* pSender);
    
    void setCoin(int const offset);
    void setBet(int const bet);
    void setWinLabel(int const win);
    void setRemain(int const remain);
    void enableButtonAll();
    
    virtual void receiveNotification(int const notificationNo);
    bool isHold(int const lineNo) const;
    
    bool incExp(float const incPt);
    
    void closeWinLabel();
    
    void readyMiniGame();
    void closeMiniGame();
    void holdOffAll();
    void updateEnableButtons();
    void runNeonSign();
    void stopNeonSign();
    void continueSelectedNo();
    void continueSelectedYes();

   
    CREATE_FUNC(PlayLayer);
    
private:
    
    void setExp(float const exp, float const offset);
    
    void initPosCoinSprite();
    void initPosLabelOffsetMoney();
    void initPosLabelExp();
    
    bool moveWinSpin();
    void holdOff(HoldButton &hold, const char *imgPath);
    void pauseFrame(const bool pause);
    void exitGame();
    void frameAction(float dt);
    void frameNotice(float dt);
    void finishedNoticeMove();
    void updateMoneyLabel();
    void showMissionAnimation();
    void hideMissionAnimation();
    
private:
    LAPlaySlot *_slotLayer;
    CCSprite *_coinSprite;
    int _coinAnimating; // 0:동작 않음. 1:윈 라벨 움직임. 2:코인 회전 움직임
    CCLabelBMFont *_moneyLabel;
    CCLabelBMFont *_diamondLabel;
    CCLabelBMFont *_betLabel;
    CCLabelBMFont *_lvLabel;
    CCLabelBMFont *_remainLabel;
    CCLabelBMFont *_winLabel;
    
    
    CCLabelBMFont *_offsetMoneyLabelPlus;
    CCLabelBMFont *_offsetMoneyLabelMinus;
    CCLabelBMFont *_offsetExpLabel;

    HoldButton  _hold1;
    HoldButton  _hold2;
    HoldButton  _hold3;
    

    CCMenu          *_menu;
    CCMenuItemImage *_backItem;
    CCMenuItemImage *_spinItem;
    CCMenuItemImage *_miniGameItem;
    CCMenuItemImage *_betItem;
    CCMenuItemImage *_betMaxItem;
    CCMenuItemImage *_fortuneItem;
    
    
    CCSprite        *_expGauge;
    CCSprite        *_minigameDisableSpr;
    CCSprite        *_winSpin[5][4];
    int _winsSpriteCnt;
    
    int _enableButtons;
    
    float _coinScaleCurrent;
    float _coinScaleNext;
    
    int _scaleOffsetIndex;
    int _scalePauseCnt;
    
    int _currentWinSpinSprite;
    int _winSpinFrames;
    int _currentWinSpinIndex[5];
    float _currentWinSpinPosY[5];
    
    CCLabelTTF *_notice;
    CCLayerColor *_noticeBack;
    
    int _writtenMoney;
    int _writtenDiamond;
    
    float _exp; // 미션 포인트
    
    CCSprite *_neonLeft;
    CCSprite *_neonRight;
    CCFiniteTimeAction *_actionsNeonLeft;
    CCFiniteTimeAction *_actionsNeonRight;
    
    CCSprite *_bg1, *_bg2;
    int _frameCnt;
    
    bool _holdPrev;
    bool _pauseFrame;
    
    CCSprite *_missionBird[8];
    bool _missionAnimating;
    int _currentMissinBird;
};

class LAPlayUserOption;

class PlayScene : public cocos2d::CCScene
{
    friend class PlayLayer;
    friend class LAPlayUserOption;
    
public:
    PlayScene();
    ~PlayScene();
    bool init();
    CREATE_FUNC(PlayScene);
    
    CC_SYNTHESIZE_READONLY(PlayLayer*, _layer, Layer);
    CC_SYNTHESIZE_READONLY(LAPlaySlot*, _slotLayer, SlotLayer);
    CC_SYNTHESIZE_READONLY(LAPlayEffect*, _effectLayer, EffectLayer);
    CC_SYNTHESIZE_READONLY(LAPlayUserOption*, _layerOption, LayerOption);

public:
    void addEffectLayer(const SlotInfo::EFFECT_TYPE effectType
                        , const SlotInfo::WHOLE_MADE wholeEffect = SlotInfo::WHOLE_MADE_NONE);
    void removeEffectLayer();
    
    AsyncResourceLoader* pAsyncLoader;
    void addSprite(CCObject* pSender);
    void asyncResourceCallback(cocos2d::CCObject *obj);    
};


class LAPlayUserOption : public cocos2d::CCLayerColor
{
public:
    LAPlayUserOption();
    virtual ~LAPlayUserOption();
    bool init();
    
    CREATE_FUNC(LAPlayUserOption);
    
    void menuCallback(CCObject* pSender);
    
    void setOption(int const option);
    
private:
    void hideAll();
private:
    
    CCMenu *_pMenu;
    CCMenuItemImage *_btnYes, *_btnNo;
    
    CCSprite *_msgBox;
    
    CCLabelTTF *_contents;
};



#endif
