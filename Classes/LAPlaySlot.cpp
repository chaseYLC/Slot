//
//  LASlot.cpp
//  gameTest
//
//  Created by Chase on 12. 10. 22..
//  Copyright (c) 2012년 넥스테일. All rights reserved.
//

#include "LAPlaySlot.h"
#include "SystemConfig.h"
#include "SimpleAudioEngine.h"
#include "SlotResult.h"
#include "Diagnose.h"
#include "SCBonusHalf.h"
#include "SCPlay.h"
#include "PlayerData.h"
#include "SCUpDownGame.h"


using namespace cocos2d;

int const BOX_IMAGE_HEIGHTS = 140;
int const BOX_IMAGE_WIDTH = 140;
int const BOX_START_YPOS = -40;
int const OFFSET_FACTOR = 2; // sprite가 한 프레임에 boxHeight/value 값 만큼 이동합니다
int const BIG_NUMBER = 5000;
int const HOW_BIG_NUMBER = 10000;
int const DRAW_COUNT = 60;
int const LINE_SPIN_DELAY_FRAMES = 10;

//int offsetArray[] = {-3,-3,-3,-3
//    , -2,-2,-2,-2
//    , -1,-1,-1,-1
//    , 0,0
//    , 1,1,1,1
//    , 2,2,2,2
//    , 3,3,3,3
//    , 4,4
//    , 8,8
//    , 16,16};

int offsetArray[] = {-3,-3,-3,-3
    , -2,-2,-2,-2
    , -1,-1,-1,-1
    , 0,0
    , 1,1,1,1
    , 2,2,2,2
    , 3,3,3,3
    , 4,4
    , 8,8};



namespace PLAY_BUTTONS
{
    int SPIN = 1;
    int BET = 2;
    int UPDOWNGAME = 4;
    int BACK = 8;
    int HOLD1 = 16;
    int HOLD2 = 32;
    int HOLD3 = 64;
    int MAX_BET = 128;
    int FORTUNE = 256;
    
    int enableAll()
    {
        int retVal = 0;
        
        retVal |= PLAY_BUTTONS::SPIN;
        retVal |= PLAY_BUTTONS::BET;
        retVal |= PLAY_BUTTONS::UPDOWNGAME;
        retVal |= PLAY_BUTTONS::BACK;
        retVal |= PLAY_BUTTONS::HOLD1;
        retVal |= PLAY_BUTTONS::HOLD2;
        retVal |= PLAY_BUTTONS::HOLD3;
        retVal |= PLAY_BUTTONS::MAX_BET;
        retVal |= PLAY_BUTTONS::FORTUNE;
        
        return retVal;
    }
    
    int disableAll()
    {
        return 0;
    }
};


using namespace SlotSpace;

static int clno = 0;

bool LAPlaySlot::init()
{
    boxWidth = SystemConfig::relativePixel(BOX_IMAGE_WIDTH);
	boxHeight = SystemConfig::relativePixel(BOX_IMAGE_HEIGHTS);
    
    int i=0;
    int sum=0;
    int const arrCnt = sizeof(offsetArray)/sizeof(int);
    
    for(; i< arrCnt; ++i)
    {
        sum += offsetArray[i];
    }
    
    _arrMoveResult = sum % boxHeight;
    
    CocosDenshion::SimpleAudioEngine *m_Sae;
    m_Sae = CocosDenshion::SimpleAudioEngine::sharedEngine();
    
	if ( CCLayerColor::initWithColor( ccc4(0,255,0,255
                                           ) ) )
	{
        loadBoxes();
        arrangeBoxes();
                
        _bonusBox = SlotInfo::EFF_NONE;
        _bonusSpinRemains = 0;
        
        this->schedule(schedule_selector(LAPlaySlot::frameAction));
        
        return true;
	}
	else
	{
		return false;
	}
}

LAPlaySlot::LAPlaySlot()
{
    gPlaySlot = this;
    
    assert( 0 == SlotInfo::BOX_SEVEN );
    
    assert(6 == LOAD_ROWS);
    assert(3 == SLOT_COLS);
    assert(-40 == BOX_START_YPOS);
    
    _sprName = new CCArray;
    _sprNameM = new CCArray;
    
    _effectAnimationOn = false;
    _missionEffectOn = false;
    _effectLayer = false;
    
    _betMin = GameData::BET_MIN[PlayerData::currentGirlNo];
    _betMax = GameData::BET_MAX[PlayerData::currentGirlNo];
    
    _betCurrent = _betMin;
    
    _bonusStage = false;
    
    
    PlayerData::gameCnt = 0;
    
    _pauseFrame = false;
}

LAPlaySlot::~LAPlaySlot()
{
    gPlaySlot = NULL;
    
    class Releaser
    {
    public:
        Releaser(CCObject **obj)
        {
            (*obj)->release();
            (*obj) = NULL;
        }
    };
    
    Releaser a( (CCObject**)(&_sprName) );
    Releaser b( (CCObject**)(&_sprNameM) );
}

void LAPlaySlot::visit()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
#else
    CCSize screenSize = cocos2d::CCDirector::sharedDirector()->getWinSizeInPixels();
#endif
    
    
	glEnable(GL_SCISSOR_TEST);
    //	glScissor(cocos2dFrame.origin.x, cocos2dFrame.origin.y, cocos2dFrame.size.width, cocos2dFrame.size.height);
    glScissor(0, screenSize.height/8, screenSize.width, screenSize.height/2 );
    
    CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);
}


void LAPlaySlot::loadBoxes()
{
    // 스프라이트 캐시를 생성해 둡니다.
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // Box Y 좌표를 구합니다.
    VisableBoxYPos1 = BOX_START_YPOS + BOX_IMAGE_HEIGHTS * 2;
    VisableBoxYPos2 = BOX_START_YPOS + BOX_IMAGE_HEIGHTS * 3;
    VisableBoxYPos3 = BOX_START_YPOS + BOX_IMAGE_HEIGHTS * 4;
    
    //    VisableBoxYPos1 = SystemConfig::relativePixel(BOX_START_YPOS) + boxHeight * 2;
    //    VisableBoxYPos2 = SystemConfig::relativePixel(BOX_START_YPOS) + boxHeight * 3;
    //    VisableBoxYPos3 = SystemConfig::relativePixel(BOX_START_YPOS) + boxHeight * 4;
    
    
    
    _effLine.init(this);
    
    
    //83*70
    
    struct imageLoader
    {
        imageLoader(cocos2d::CCArray* array, cocos2d::CCArray* arrayM, const char *name )
        {
            char nameSpr[255];
            sprintf(nameSpr, "slots/%s.png", name);
            CCSprite *spr = CCSprite::create(nameSpr);
            assert(spr);
            array->addObject( CCString::create(nameSpr) );
            
            sprintf(nameSpr, "slots/%s_m.png", name);
            CCSprite *spr2 = CCSprite::create(nameSpr);
            assert(spr2);
            arrayM->addObject( CCString::create(nameSpr) );
        }
        //cocos2d::CCArray *_array;
    };
    
    
    // !!로딩 순서 바꾸지 마세요!!
    //    BOX_SEVEN = 0,   // 배열 인덱스로 사용합니다. 값을 변경하지 마세요.
    //    BOX_BANANA,
    //    BOX_CHERRY,
    //    BOX_GRAPE,
    //    BOX_LEMON,
    //    BOX_POCKETBLUE,
    //    BOX_POCKETRED,
    //    BOX_POCKETYELLOW,
    //    BOX_HEART,
    //    BOX_NORMALBELL,
    //    BOX_SUPERBELL,
    
    imageLoader i0(_sprName, _sprNameM, "7");
    imageLoader i1(_sprName, _sprNameM, "banana");
    imageLoader i3(_sprName, _sprNameM, "cherry");
    imageLoader i4(_sprName, _sprNameM, "grape");
    imageLoader i5(_sprName, _sprNameM, "lemon");
    imageLoader i9(_sprName, _sprNameM, "pocketBlue");
    imageLoader i10(_sprName, _sprNameM, "pocketRed");
    imageLoader i11(_sprName, _sprNameM, "pocketYellow");
    imageLoader i6(_sprName, _sprNameM, "heart");
    imageLoader i7(_sprName, _sprNameM, "normal_bell");
    imageLoader i8(_sprName, _sprNameM, "super_bell");
    // !!로딩 순서 바꾸지 마세요!!
    // 총 11개
    
    
    // 그림자 이미지 씌우기
    CCSprite *shadowSpr = CCSprite::create("inGame/shadow_cover.png");
    assert(shadowSpr);
    SystemConfig::setPosition(320, 379, shadowSpr);
    this->addChild(shadowSpr, 2);
}


void LAPlaySlot::arrangeBoxes()
{
    _sprSet1.Clear();
    _sprSet2.Clear();
    _sprSet3.Clear();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    int i=0;
    int j=0;
    
    for( ; i<LOAD_ROWS; ++i)
    {
        for( j=0; j<SLOT_COLS; ++j)
        {
            int const index = arc4random() % _sprName->count();
            
            CCString *imgName = (CCString*) _sprName->objectAtIndex(index);
            CCString *imgNameM = (CCString*) _sprNameM->objectAtIndex(index);
            
            //            BoxSprite *spr = (BoxSprite*)CCSprite::create(imgName->getCString() );
            //            spr->_spriteM = CCSprite::create(imgNameM->getCString() );
            //            assert(spr);
            //            assert(spr->_spriteM);
            CCSprite *spr = (CCSprite*)CCSprite::create(imgName->getCString() );
            assert(spr);
            
            
            const int lineNo = j % SLOT_COLS;
            int yPos = BOX_START_YPOS + i*BOX_IMAGE_HEIGHTS;
            //            int yPos = SystemConfig::relativePixel(BOX_START_YPOS) + i*boxHeight;
            if(0 == lineNo)
            {
                SystemConfig::setPosition(BaseBoxXPos1, yPos, spr);
                _sprSet1.sprSet->addObject(spr);
                _sprSet1.slots[i] = index;
            }
            else if( 1 == lineNo)
            {
                SystemConfig::setPosition(BaseBoxXPos2, yPos, spr);
                _sprSet2.sprSet->addObject(spr);
                _sprSet2.slots[i] = index;
            }
            else
            {
                SystemConfig::setPosition(BaseBoxXPos3, yPos, spr);
                _sprSet3.sprSet->addObject(spr);
                _sprSet3.slots[i] = index;
            }
            this->addChild(spr);
        }
    }
}

void LAPlaySlot::rearrangeBox(SpriteSetInfo &sprSet, int const index, bool const useShakingImage)
{
    CCSprite *spr = (CCSprite*)sprSet.sprSet->objectAtIndex(index);
    CCPoint pt = spr->getPosition();
    
    this->removeChild(spr, true);
    sprSet.sprSet->removeObjectAtIndex(index);
    
    int indexNew = 0;
    
    if( -1 != PlayerData::slotBox )
    {
        indexNew = arc4random() % _sprName->count();
        
        if( (PlayerData::gameCnt%3) == 0 )
        {
            if( 1 == index || 4 == index)
            {
                indexNew = PlayerData::slotBox;
            }
        }
    }
    else
    {
        indexNew = _fm.getBox(clno, index);
    }
    
    
    if( true == _bonusStage)
    {
        CCSprite *sprNew = NULL;
        
        if( 0 == arc4random() % 2 )
        {
            sprNew = CCSprite::create("slots/empty.png");
            sprNew->setPosition(pt);
            
            sprSet.sprSet->insertObject(sprNew, index);
            sprSet.slots[index] = -1;
            this->addChild(sprNew);
            
            return; //
        }
        else
        {
            if( SlotInfo::EFF_POCKET3 == _bonusBox ){
                indexNew = SlotInfo::BOX_POCKETYELLOW;
            }
            else if( SlotInfo::EFF_POCKET4 == _bonusBox ){
                indexNew = SlotInfo::BOX_POCKETRED;
            }
            else if( SlotInfo::EFF_POCKET5 == _bonusBox ){
                indexNew = SlotInfo::BOX_POCKETBLUE;
            }
            else
            {
                assert(0);
            }
        }
    }
    
    CCString *imgName = (CCString*) _sprName->objectAtIndex(indexNew);
    CCString *imgNameM = (CCString*) _sprNameM->objectAtIndex(indexNew);
    
    //    BoxSprite *sprNew = (BoxSprite*)CCSprite::create(imgName->getCString() );
    //    sprNew->_spriteM = CCSprite::create(imgNameM->getCString() );
    
    CCSprite *sprNew = NULL;
    if( useShakingImage){
        sprNew = (CCSprite*)CCSprite::create(imgNameM->getCString() );
    }
    else{
        sprNew = (CCSprite*)CCSprite::create(imgName->getCString() );
    }
    
    sprNew->setPosition(pt);
    
    sprSet.sprSet->insertObject(sprNew, index);
    sprSet.slots[index] = indexNew;
    this->addChild(sprNew);
    
    
    CCLog("=====Line No:%d == Index : %d / index-New : %d", clno+1, index, indexNew);
}

void LAPlaySlot::shakingImageToNormalImage(SpriteSetInfo &sprSet, int const index)
{
    if( true == _bonusStage)
    {
        if( -1 == sprSet.slots[index] )
        {
            return;
        }
    }
    
    CCSprite *spr = (CCSprite*)sprSet.sprSet->objectAtIndex(index);
    CCPoint pt = spr->getPosition();
    
    this->removeChild(spr, true);
    sprSet.sprSet->removeObjectAtIndex(index);
    
    CCString *imgName = (CCString*) _sprName->objectAtIndex( sprSet.slots[index] );
    CCSprite *sprNew = (CCSprite*)CCSprite::create(imgName->getCString() );
    
    sprNew->setPosition(pt);
    
    sprSet.sprSet->insertObject(sprNew, index);
    this->addChild(sprNew);
}

void LAPlaySlot::frameAction_Slots()
{
    if( true == _sprSet1.spining)
    {
        SlotMoveProcess(0);
    }
    
    if( true == _sprSet2.spining)
    {
        SlotMoveProcess(1);
    }
    else
    {
        if( true == _sprSet1.spining)
        {
            if( _sprSet2.waitFrameCnt++ > LINE_SPIN_DELAY_FRAMES ){
                
                // 2번 라인 시작
                SND()->playEffect(SoundPath::path(SoundPath::ST_SPIN_LINESTART));

                _sprSet2.spining = true;
                _sprSet2.waitFrameCnt = 0;
            }
        }
    }
    
    if( true == _sprSet3.spining)
    {
        SlotMoveProcess(2);
    }
    else
    {
        if( true == _sprSet2.spining)
        {
            if( _sprSet3.waitFrameCnt++ > LINE_SPIN_DELAY_FRAMES ){
                
                // snd
                SND()->playEffect(SoundPath::path(SoundPath::ST_SPIN_LINESTART));
                // 3번 라인 시작
                _sprSet3.spining = true;
                _sprSet3.waitFrameCnt = 0;
            }
        }
    }
}
void LAPlaySlot::frameActoin_Effect()
{
    if( true == _effectAnimationOn)
    {
        if( SlotInfo::WHOLE_MADE_NONE == _familyTree.wholeMade ){
            
            // 전체 메이드류가 아닐경우(라인 메이드 일 경우)에만 라인 그린다.
            _effLine.process(_sprSet1, _sprSet2, _sprSet3);
        }
    }
    
    if( true == _bonusStage
       || true == _bonusStageEnd)
    {
        return;
    }
    
    if( false == _effectLayer){
        
        if( true == _missionEffectOn )
        {
            if( _currentSpecialEffectIndexForFamilyTree < FamilyTree::MAX_COMBINATIONS )
            {
                _currentSpecialEffectIndexForFamilyTree = FamilyTree::MAX_COMBINATIONS;
                
                gPlayScene->addEffectLayer(SlotInfo::EFF_MISSION);
                _effectLayer = true;
                return;
            }
        }
        else
        {
            if( _currentSpecialEffectIndexForFamilyTree < FamilyTree::MAX_COMBINATIONS
               && _familyTree.wholeMade != SlotInfo::WHOLE_MADE_NONE )
            {
                gPlayScene->addEffectLayer(SlotInfo::EFF_NONE, _familyTree.wholeMade);
                
                // 전체 메이드가 되면 부분 메이드는 무시합니다.
                _currentSpecialEffectIndexForFamilyTree = FamilyTree::MAX_COMBINATIONS;
                _effectLayer = true;
                
                return;
            }
            
            for(; _currentSpecialEffectIndexForFamilyTree < FamilyTree::MAX_COMBINATIONS;
                ++_currentSpecialEffectIndexForFamilyTree)
            {
                SlotInfo::EFFECT_TYPE effectType;
                if( true == _familyTree.isSpecialEffect(_currentSpecialEffectIndexForFamilyTree, effectType) )
                {
                    if( SlotInfo::EFF_POCKET3 == effectType
                       || SlotInfo::EFF_POCKET4 == effectType
                       || SlotInfo::EFF_POCKET5 == effectType )
                    {
                        _bonusGames.push_back(effectType);
                        continue;
                    }
                    else
                    {
                        gPlayScene->addEffectLayer(effectType, _familyTree.wholeMade);
                        _effectLayer = true;
                        
                        return;
                    }
                }
            }//for
            
            checkBonusGame(false);
        }
        
    }//if( false == _effectLayer)
    
//    if( _shownEffectFrames++ > 120)
//    {
//        if( false == _bonusStage){
//            gPlayLayer->enableButtonAll();
//        }
//        
//        _shownEffectFrames = 0;
//    }
}

void LAPlaySlot::frameAction(float dt)
{
    if( true == _pauseFrame ) { return; }
    
    
    frameAction_Slots();
    
    if( true == _effectAnimationOn
       || true == _missionEffectOn )
    {
        frameActoin_Effect();
    }
}



void LAPlaySlot::SlotMoveProcess(int const lineNo)
{
    clno = lineNo;
    
    
    
    int const arrCnt = sizeof(offsetArray)/sizeof(int);
    
    SpriteSetInfo &sprSetInfo = (lineNo == 0) ?  _sprSet1
    : ( (lineNo == 1) ? _sprSet2 : _sprSet3 );
    
    if( true == gPlayLayer->isHold(lineNo) ){
        return;
    }
    
    if( arrCnt <= sprSetInfo.currentOffsetIndex ){
        
        if( BIG_NUMBER > sprSetInfo.currentOffsetIndex )
        {
            sprSetInfo.currentOffsetIndex = BIG_NUMBER;
        }
        else
        {
            if( (sprSetInfo.currentOffsetIndex - BIG_NUMBER) > DRAW_COUNT )
            {
                if( false == sprSetInfo.adjustedBox )
                {
                    // 박스들을 정위치로.
                    sprSetInfo.adjustedBox = true;
                    
                    SlotMove( (-2 * _arrMoveResult ) + boxHeight, sprSetInfo );
                }
                
                // 스핀 속도를 줄입니다.
                if( HOW_BIG_NUMBER > sprSetInfo.currentOffsetIndex )
                {
                    sprSetInfo.currentOffsetIndex = HOW_BIG_NUMBER;
                    
                    // 흔들리는 이미지를 원래의 이미지로 바꿉니다.
                    if( true == _changedShakingImg){
                        int i=0;
                        for( ; i<sprSetInfo.sprSet->count(); ++i)
                        {
                            shakingImageToNormalImage(sprSetInfo, i);
                        }
                    }
                }
                
                const int reverseIndex = sprSetInfo.currentOffsetIndex - HOW_BIG_NUMBER;
                if( arrCnt > reverseIndex ){
                    SlotMove( offsetArray[ arrCnt - 1 - reverseIndex], sprSetInfo);
                }
                else{
                    // 슬롯이 다 돌았습니다.
                    sprSetInfo.Clear();
                    
                    if( false == _bonusStage){
                        SND()->stopBackgroundMusic();
                    }
                    
                    // snd
                    if( 0 == lineNo )
                    {
                    }
                    
                    SND()->playEffect(SoundPath::path(SoundPath::ST_SPIN_LINESTOP) );
                    
                    
                    bool finished = false;
                    
                    if (0 == lineNo) {
                        if( true == (gPlayLayer->isHold(1) && gPlayLayer->isHold(2)) ){
                            finished = true;
                        }
                    }
                    else if(1 == lineNo){
                        if( true == gPlayLayer->isHold(2) ){
                            finished = true;
                        }
                    }
                    else if( 2 == lineNo){
                        finished = true;
                    }
                    
                    if( true == finished)
                    {// 슬롯이 전부 스핀을 마쳤습니다.
                        
                        _sprSet1.Clear();
                        _sprSet2.Clear();
                        _sprSet3.Clear();
                        
                        // 결과 판독
                        SlotResult slotResult(_sprSet1, _sprSet2, _sprSet3, _betCurrent);
                        Diagnose::evaluate(slotResult, _bonusStage );
                        
                        _familyTree = slotResult.getFamilyTree();
                        showResult_combinations();
                    }
                    
                    //
                    return;
                }
            }
            else
            {
                SlotMove( boxHeight / OFFSET_FACTOR, sprSetInfo);
            }
        }
    }
    else{
        SlotMove( offsetArray[sprSetInfo.currentOffsetIndex], sprSetInfo);
    }
    
    sprSetInfo.currentOffsetIndex++;
}


void LAPlaySlot::SlotMove(int const offsetSize, SpriteSetInfo &sprSetInfo)
{
    if( 0 == offsetSize){ return;}
    
    int i=0;
    
    for( i=0; i<LOAD_ROWS; ++i)
    {
        CCSprite *spr = (CCSprite*) sprSetInfo.sprSet->objectAtIndex(i);
        
        CCPoint pt;
        pt.x = spr->getPositionX();
        pt.y = spr->getPositionY() - offsetSize;
        spr->setPosition(pt);
    }
    sprSetInfo.accMove += offsetSize;
    
    if( sprSetInfo.accMove >= (boxHeight) )
    {
        sprSetInfo.accMove = 0;
        SwapSlots(sprSetInfo);
    }
}

void LAPlaySlot::SwapSlots(SpriteSetInfo &sprSetInfo)
{
    int i;
    for( i=0; i<LOAD_ROWS; ++i)
    {
        if( i == sprSetInfo.currentBottomIndex)
        {
            CCSprite *spr = (CCSprite*)sprSetInfo.sprSet->objectAtIndex(i);
            
            CCPoint pt = spr->getPosition();
            
            CCPoint ptPlace;
            ptPlace.x = pt.x;
            ptPlace.y = pt.y + boxHeight * LOAD_ROWS;
            
            spr->setPosition(ptPlace);
        }
    }
    
    sprSetInfo.currentBottomIndex = ++sprSetInfo.currentBottomIndex % LOAD_ROWS;
    
    
    if( LOAD_ROWS > sprSetInfo.shuffleCnt++ )
    {
        // 슬롯이 빠르게 돌아갈때 슬롯을 바꿉니다.
        _changedShakingImg = true;
        rearrangeBox(sprSetInfo, sprSetInfo.currentBottomIndex, true);
    }
}


void LAPlaySlot::bet()
{
    _betCurrent *= 2;
    if( _betMax < _betCurrent){
        _betCurrent = _betMin;
    }
    
    gPlayLayer->setBet(_betCurrent);
}

void LAPlaySlot::betMax()
{
    _betCurrent = _betMax;
    gPlayLayer->setBet(_betCurrent);
}



int LAPlaySlot::spin()
{
    if( true == _sprSet1.spining ) { return 0; }
    if( true == _sprSet2.spining ) { return 0; }
    if( true == _sprSet3.spining ) { return 0; }
    
    if( NULL != getActionByTag(3389) ){ return 0;}

    if( false == _bonusStage){
        SND()->playBackgroundMusic(SoundPath::path(SoundPath::ST_SPIN_BG), true);
    }

    //
    PlayerData::isMade = false;
    _changedShakingImg = false;
    
    //
    _fm.setMaker(_sprSet1, _sprSet2, _sprSet3
                 , gPlayLayer->isHold(0), gPlayLayer->isHold(1), gPlayLayer->isHold(2) );
    
    // 이전스핀 결과 청소
    _familyTree.Clear();
    
    // 업다운 게임 비활성
    gPlayLayer->closeMiniGame();
    
    gPlayLayer->stopNeonSign();
    
    
    if( true == _bonusStage){
        if( 0 >= _bonusSpinRemains){
            checkBonusGame(true);
        }
    }
    
    if( false == _bonusStage)
    {
        _bonusStageEnd = false;
        
        PlayerData::gameCnt++;
        gPlayLayer->setCoin( -_betCurrent);
    }else
    {
        gPlayLayer->setCoin(0);
    }
    
    _effectAnimationOn = false;
    
    // 미션 이펙트가 열려있다면 닫고 포인트를 초기화합니다.
    if( true == _missionEffectOn)
    {
        gPlayLayer->incExp(0.0f);
        
    }
    _missionEffectOn = false;
    
    _currentSpecialEffectIndexForFamilyTree = 0;
    _effLine.stop();
    
    
    // snd
    //  1번 라인 스핀 시작
    SND()->playEffect(SoundPath::path(SoundPath::ST_SPIN_LINESTART));
    _sprSet1.spining = true;
    
    return 1;
}

void LAPlaySlot::showResult_combinations()
{
    // 한 게임슬롯 종료.
    //
    
    // 홀드버튼 해제
    gPlayLayer->holdOffAll();
    
    
    if( true == _bonusStage )   // 현재 보너스 스테이지를 진행중이면
    {
        if( 0 < _familyTree._totalPoint )
        {
            SND()->playEffect(SoundPath::path(SoundPath::ST_LINE_MADE));
            
            PlayerData::isMade = true;
            

//            if( false == _familyTree.isContainSpecialEffect() )
            {
                gPlayLayer->enableButtonAll();
            }
            
            
            PlayerData::winsFinal = PlayerData::winsFirst = _familyTree.getTotalPoint();
            
            // win 이미지 출력
            PlayerData::waitWins = true;
            gPlayLayer->showWinsLabel(_familyTree.getTotalPoint() * _betCurrent );
            
            
            
            _effLine.setResult(&_familyTree);
            
            _shownEffectFrames = 0;
            _effectAnimationOn = true;
        }
        
        _bonusSpinRemains--;
        
        if( 0 >= _bonusSpinRemains ){
            // 보너스 스핀을 전부 소모했습니다.
            _bonusStage = false;
            _bonusStageEnd = true;
            
            _bonusGames.clear();
            
            SND()->stopBackgroundMusic();
        }
        gPlayLayer->enableButtonAll();
        
        return;
    }
    
    
    
    if( 0 < _familyTree.getTotalPoint() )
    {
        // 메이드!!!
        
        gPlayLayer->runNeonSign();

        
        // SND
        SND()->playEffect(SoundPath::path(SoundPath::ST_LINE_MADE));
        
        //
        if( false == _familyTree.isContainSpecialEffect() )
        {
            gPlayLayer->enableButtonAll();
        }
        
        
        PlayerData::isMade = true;
        
        PlayerData::winsFinal = PlayerData::winsFirst = _familyTree.getTotalPoint();
        
        // win 이미지 출력
        PlayerData::waitWins = true;
        gPlayLayer->showWinsLabel(_familyTree.getTotalPoint() );
        
        _effLine.setResult(&_familyTree);
        
        _shownEffectFrames = 0;
        _effectAnimationOn = true;
        
        
        if( true == _familyTree.isMadeBonusSpin() ){
            // 보너스 게임에 진입합니다. 다음 스핀부터 적용됩니다.
        }else{
            if( (_betMax * 2 ) < PlayerData::winsFinal )
            {
                gPlayLayer->readyMiniGame();
            }
        }
    }
    else
    {
        // 아무 패도 나오지 않았음.
        //
        //
        // 미션 포인트를 증가
        //
        if( false == gPlayLayer->incExp(10) )  // 값 사용 주의 : 
        {
            // 게임을 재개할 수 있습니다.
            gPlayLayer->enableButtonAll();
        }
    }
}

void LAPlaySlot::setMissionEffect(const bool on)
{
    SND()->playEffect(SoundPath::path(SoundPath::ST_MISSION_START));
    
    _missionEffectOn = true;
}

void LAPlaySlot::closeEffectLayer()
{
    _currentSpecialEffectIndexForFamilyTree++;
    gPlayScene->removeEffectLayer();
    _effectLayer = false;
    
    
    gPlayLayer->enableButtonAll();
}


void LAPlaySlot::drawRect(const float x, const float y)
{
    // 사각 영역 그리기는 하지 않습니다.
    return;
    
    ccDrawRect(CCPoint( SystemConfig::relativePixel(x-BOX_IMAGE_WIDTH/2)
                       ,SystemConfig::relativePixel(y+BOX_IMAGE_HEIGHTS))
               , CCPoint( SystemConfig::relativePixel(x+BOX_IMAGE_WIDTH/2)
                         , SystemConfig::relativePixel(y) )
               );
}

void LAPlaySlot::drawRectSolid(const float x, const float y)
{
    ccDrawSolidRect(CCPoint( SystemConfig::relativePixel(x-BOX_IMAGE_WIDTH/2)
                            ,SystemConfig::relativePixel(y+BOX_IMAGE_HEIGHTS))
                    , CCPoint( SystemConfig::relativePixel(x+BOX_IMAGE_WIDTH/2)
                              , SystemConfig::relativePixel(y) )
                    , ccc4f(1.0f, 0.0f, 0.0f, 1.0f) );
}


void LAPlaySlot::draw()
{
    // 배경을 흰색으로 칠합니다.
    ccColor4F bgColor = ccc4f(255.0f, 255.0f, 255.0f, 255.0f);
    if( true == _bonusStage)
    {// 보너스 게임중에는 배경을 파랑색으로
        bgColor = ccc4f(0.0f, 0.0f, 255.0f, 255.0f);
    }
    
    ccDrawSolidRect(ccp(SystemConfig::getXPos(0),SystemConfig::getYPos(0))
                    , ccp(SystemConfig::getXPos(640), SystemConfig::getYPos(960))
                    , bgColor );
    
    if( false == _effectAnimationOn )return;
    if( false == _effLine.isActiveCurrentFamily() ) return;
    
    
    ccDrawColor4F(1.0f, 0.0f, 0.0f, 1.0f);
    
    CCPoint pt;
    CCPoint pt2;
    
    switch( _effLine.getCurrentFamilyNo() )
    {
        case 0:
        {
            drawRect(BaseBoxXPos1, VisableBoxYPos3);
            drawRect(BaseBoxXPos2, VisableBoxYPos3);
            drawRect(BaseBoxXPos3, VisableBoxYPos3);
        }break;
        case 1:
        {
            drawRect(BaseBoxXPos1, VisableBoxYPos2);
            drawRect(BaseBoxXPos2, VisableBoxYPos2);
            drawRect(BaseBoxXPos3, VisableBoxYPos2);
        }break;
        case 2:
        {
            drawRect(BaseBoxXPos1, VisableBoxYPos1);
            drawRect(BaseBoxXPos2, VisableBoxYPos1);
            drawRect(BaseBoxXPos3, VisableBoxYPos1);
        }break;
        case 3:
        {
            drawRect(BaseBoxXPos1, VisableBoxYPos3);
            drawRect(BaseBoxXPos1, VisableBoxYPos2);
            drawRect(BaseBoxXPos1, VisableBoxYPos1);
        }break;
        case 4:
        {
            drawRect(BaseBoxXPos2, VisableBoxYPos3);
            drawRect(BaseBoxXPos2, VisableBoxYPos2);
            drawRect(BaseBoxXPos2, VisableBoxYPos1);
        }break;
        case 5:
        {
            drawRect(BaseBoxXPos3, VisableBoxYPos3);
            drawRect(BaseBoxXPos3, VisableBoxYPos2);
            drawRect(BaseBoxXPos3, VisableBoxYPos1);
        }break;
        case 6:
        {
            drawRect(BaseBoxXPos1, VisableBoxYPos3);
            drawRect(BaseBoxXPos2, VisableBoxYPos2);
            drawRect(BaseBoxXPos3, VisableBoxYPos1);
        }break;
        case 7:
        {
            drawRect(BaseBoxXPos1, VisableBoxYPos1);
            drawRect(BaseBoxXPos2, VisableBoxYPos2);
            drawRect(BaseBoxXPos3, VisableBoxYPos3);
        }break;
        default:
            assert(0);
            break;
    }
}

void LAPlaySlot::checkBonusGame(const bool popEffect)
{
    if( true == popEffect){
        _bonusGames.pop_back();
    }
    
    if( false == _bonusGames.empty() )
    {// 보너스 게임 진행.
        SlotInfo::EFFECT_TYPE const effectType = _bonusGames.at(_bonusGames.size()-1);
        
        // bonus stage~~~
        SND()->playEffect(SoundPath::path(SoundPath::ST_BONUSGAME_START));
        
        _bonusStage = true;
        _bonusStageEnd = false;
        
        _bonusBox = effectType;
        if( _bonusBox == SlotInfo::EFF_POCKET3 ){
            _bonusSpinRemains = 3;
        }else if( _bonusBox == SlotInfo::EFF_POCKET4){
            _bonusSpinRemains = 4;
        }else if( _bonusBox == SlotInfo::EFF_POCKET5){
            _bonusSpinRemains = 5;
        }else{
            assert(0);
        }
        
        _effectLayer = true;
        gPlayScene->addEffectLayer(effectType);
        
        scheduleOnce(schedule_selector(LAPlaySlot::startBonusGame), 2.0f); // alert.m4a 길이보다 길게 지연
    }
    else
    {
        _bonusBox = SlotInfo::EFF_NONE;
        _bonusStage = false;
    }
}

void LAPlaySlot::startBonusGame()
{
    //    gPlayLayer->enableButtonAll();
    SND()->playBackgroundMusic(SoundPath::path(SoundPath::ST_BG_BONUS), true);
}

void LAPlaySlot::updownGame()
{
    SCUpDownGame *s = SCUpDownGame::create();
    CCDirector::sharedDirector()->pushScene(s);
}


void LAPlaySlot::pauseFrame(const bool pause)
{
    _pauseFrame = pause;
}