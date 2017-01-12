#ifndef gameTest_LASlot_h
#define gameTest_LASlot_h

#include "cocos2d.h"
#include "SpriteSetInfo.h"
#include "SlotResult.h"
#include "Effect_Line.h"
#include "SlotInfo.h"
#include "FamilyMaker.h"

//class BoxSprite : public cocos2d::CCSprite
//{
//public:
//    //int _shapeID;
//    cocos2d::CCSprite *_spriteM;
//    
//};
namespace PLAY_BUTTONS
{
    extern int SPIN;
    extern int BET;
    extern int UPDOWNGAME;
    extern int BACK;
    extern int HOLD1;
    extern int HOLD2;
    extern int HOLD3;
    extern int MAX_BET;
    extern int FORTUNE;
    
    int enableAll();
    int disableAll();
};


class LAPlaySlot : public cocos2d::CCLayerColor
{        
public:
    LAPlaySlot();
    
    virtual ~LAPlaySlot();
    bool init();
    CREATE_FUNC(LAPlaySlot);
    
    void visit();
    int spin();
    void bet();
    void betMax();
    void closeEffectLayer();
    
    void updownGame();
    
    void setMissionEffect(const bool on);
    bool isBonusGame()const{return _bonusStage;}
        void pauseFrame(const bool pause);
    
private:
    void loadBoxes();
    void arrangeBoxes();
    
    void frameAction(float dt);
    void frameAction_Slots();
    void frameActoin_Effect();
    
    void SlotMoveProcess(int const lineNo);
    void SlotMove(int const offsetSize, SpriteSetInfo &sprSetInfo);
    void SwapSlots(SpriteSetInfo &sprSetInfo);
    
    void rearrangeBox(SpriteSetInfo& sprSet, int const index, bool const useShakingImage);
    void shakingImageToNormalImage(SpriteSetInfo &sprSet, int const index);
    
    cocos2d::CCArray * getSpriteSet(int const setNo);

    void showResult_combinations();

    virtual void draw();
    
    void drawRect(const float x, const float y);
    void drawRectSolid(const float x, const float y);
    
    void checkBonusGame(const bool popEffect);
    void startBonusGame();

    
private:
    cocos2d::CCArray *_sprName;
    cocos2d::CCArray *_sprNameM;
    
    SpriteSetInfo   _sprSet1;
    SpriteSetInfo   _sprSet2;
    SpriteSetInfo   _sprSet3;
    
    int _arrMoveResult;
    
    bool _effectAnimationOn;
    bool _missionEffectOn;
    
    FamilyTree _familyTree;
    Effect_Line     _effLine;
    bool _effectLayer;
    int _currentSpecialEffectIndexForFamilyTree;
    
    int _betMin;
    int _betMax;
    int _betCurrent;
    
    
    int boxHeight;
    int boxWidth;
    
    bool _bonusStage;
    bool _bonusStageEnd;
    
    int _bonusBox;
    int _bonusSpinRemains;
    std::vector< SlotInfo::EFFECT_TYPE > _bonusGames;
    
    int _shownEffectFrames;
    
    bool _changedShakingImg;
    
    FamilyMaker _fm;
    
    bool _pauseFrame;
};

#endif
