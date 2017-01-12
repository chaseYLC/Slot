#include "SCPlay.h"
//#include "SCClearClothes.h"

#include "SystemConfig.h"
//#include "PlayerData.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace SlotSpace;

float const EXP_LABEL_X = 320.0f;
float const EXP_LABEL_Y = 674.0f;

float const COIN_SCALE_OFFSET = 0.005f;
float const COIN_SCALE_MIN = 0.8f;
int const SCALE_PAUSE_CNT = 30;
int const FRAME_PER_WINSPIN_CHANGE = 2;    // 스프라이트 채인지에 필요함 프레임
int const CNT_WINSPIN_DELAY = 4;
int const MISSION_BIRD_OFFSET = 4;
int const FRAME_FOR_MISSION_MOVE = 6;


#define COIN_FACTOR     (COIN_SCALE_OFFSET * COIN_SCALES[_scaleOffsetIndex])

//float const COIN_SCALES[] = {10,8,8,6,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
float const COIN_SCALES[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};


int const WINS_SPIN_OFFSET[13] = {20, 20, 20, 20,
    12,
    4, 4, 4,
    12,
    20, 20, 20, 20 };


const int NOTICE_CNT_TOTAL = 10;
char NOTICES[NOTICE_CNT_TOTAL][200] = {
    {"Up & Down 에서 '하트'를 획득하면 Gallery에서 달라진 여성을 만날 수 있습니다."},
    {"미션이 발동되면 여러가지 혜택을 받습니다."},
    {"노란 돈주머니로 한 라인을 만들면 3번의 보너스타임을 진행합니다."},
    {"빨간 돈주머니로 한 라인을 만들면 4번의 보너스타임을 진행합니다."},
    {"파란 돈주머니로 한 라인을 만들면 5번의 보너스타임을 진행합니다."},
    {"하트로 한 라인을 만들면 주사위 게임이 진행됩니다."},
    {"7분마다 무료로 골드를 충전할 수 있습니다."},
    {"올세븐으로 대박을 노려보세요."},
    {"매일 20:00 ~ 20:30 까지 미션포인트가 2배."},
    {"일정금액이상 획득 시 하이로우 게임 버튼이 활성화됩니다."},
};

const float WINS_COIN_START_X[5] = {320, 360, 410, 260, 220};
const float WINS_COIN_START_Y[5] = {800, 850, 760, 830, 770};



PlayScene::PlayScene()
{
    gPlayScene = this;
    pAsyncLoader = NULL;
}

void PlayScene::addSprite(CCObject* pSender)
{
    this->addChild(_slotLayer);
    this->addChild(_layer);
    this->addChild(_effectLayer);
    this->addChild(_layerOption);
    
    if( pAsyncLoader )
    {
        pAsyncLoader->removeFromParentAndCleanup(true);
        CC_SAFE_RELEASE_NULL(pAsyncLoader);
    }
}
void PlayScene::asyncResourceCallback(cocos2d::CCObject *obj)
{
    // 슬롯 레이어 올리기
    this->_slotLayer = LAPlaySlot::create();
    this->_slotLayer->retain();
    //    this->addChild(_slotLayer);
    
    
    // 게임 레이어 올리기
    this->_layer = PlayLayer::create();
    this->_layer->retain();
    
    // 게임레이어에 슬롯 레이어 저장
    _layer->setSlotLayer(_slotLayer);
    
    
    // 이펙트 레이어
    this->_effectLayer = LAPlayEffect::create();
    this->_effectLayer->retain();
    _effectLayer->setVisible(false);
    
    
    // 옵션 레이어
    this->_layerOption = LAPlayUserOption::create();
    this->_layerOption->retain();
    _layerOption->setVisible(false);
    
    
    
    CCFiniteTimeAction *actions;
    actions = CCSequence::create(
                                 CCCallFuncN::create(this, callfuncN_selector(PlayScene::addSprite)),
                                 NULL
                                 );
    pAsyncLoader->runAction( actions );
}


bool PlayScene::init()
{
    GameData::currentScene = GameData::SCENE_GAME;
    
	if( CCScene::init() )
	{
        const char* szImageName[] =
        {
            "inGame/bt_spin_off.png",
            "inGame/bt_spin_on.png",
            "effect/eff_coin/coin_1.png",
            "effect/eff_heart/back.png",
            "effect/eff_777/eff_777_1.png",
            "effect/eff_777/eff_777_2.png",
            "effect/eff_777/eff_777_3.png",
            "effect/eff_777/eff_777_4.png",
            "effect/eff_777/eff_777_5.png",
            "effect/eff_777/eff_777_6.png",
            "effect/eff_777/eff_777_7.png",
            "effect/eff_777/eff_777_8.png",
            "effect/eff_bell/eff_bell_1.png",
            "effect/eff_bell/eff_bell_2.png",
            "effect/eff_bell/eff_bell_3.png",
            "effect/eff_bell/eff_bell_4.png",
            "effect/eff_bell/eff_bell_5.png",
            "effect/eff_bell/eff_bell_6.png",
            "effect/eff_heart/ani_1.png",
            "effect/eff_heart/ani_2.png",
            "effect/eff_heart/ani_3.png",
            "effect/eff_heart/ani_4.png",
            "effect/eff_heart/ani_5.png",
            "effect/eff_heart/ani_6.png",
            "effect/eff_heart/ani_7.png",
            "effect/eff_heart/ani_8.png",
            "effect/eff_heart/ani_1.png",
            "effect/eff_heart/mission.png",
            "menu/bt_back_default.png",
            "menu/bt_back_touch.png",
            "effect/eff_line/eff_line_1.png",
            "effect/eff_line/eff_line_2.png",
            "effect/eff_line/eff_line_3.png",
            "effect/eff_line/eff_line_4.png",
            "effect/eff_line/eff_line_5.png",
            "effect/eff_line/eff_line_6.png",
            "effect/eff_line/eff_line_i_1.png",
            "effect/eff_line/eff_line_i_2.png",
            "effect/eff_line/eff_line_i_3.png",
            "effect/eff_line/eff_line_i_4.png",
            "effect/eff_line/eff_line_i_5.png",
            "effect/eff_line/eff_line_x1_1.png",
            "effect/eff_line/eff_line_x1_2.png",
            "effect/eff_line/eff_line_x1_3.png",
            "effect/eff_line/eff_line_x1_4.png",
            "effect/eff_line/eff_line_x1_5.png",
            "effect/eff_line/eff_line_x1_6.png",
            "effect/eff_line/eff_line_x2_1.png",
            "effect/eff_line/eff_line_x2_2.png",
            "effect/eff_line/eff_line_x2_3.png",
            "effect/eff_line/eff_line_x2_4.png",
            "effect/eff_line/eff_line_x2_5.png",
            "effect/eff_line/eff_line_x2_6.png",
            "slots/7.png",
            "slots/7_m.png",
            "slots/banana.png",
            "slots/banana_m.png",
            "slots/cherry.png",
            "slots/cherry_m.png",
            "slots/grape.png",
            "slots/grape_m.png",
            "slots/lemon.png",
            "slots/lemon_m.png",
            "slots/heart.png",
            "slots/heart_m.png",
            "slots/normal_bell.png",
            "slots/normal_bell_m.png",
            "slots/super_bell.png",
            "slots/super_bell_m.png",
            "inGame/sky.png",
            NULL
        };
        
        pAsyncLoader = AsyncResourceLoader::create();
        this->addChild( pAsyncLoader );
        pAsyncLoader->retain();
        
        for( int i = 0; szImageName[i] != NULL; i++ )
        {
            pAsyncLoader->addLoadImage( szImageName[i] );
        }
        
        
        pAsyncLoader->start( this,
                            callfuncO_selector(PlayScene::asyncResourceCallback),
                            this,
                            ASYNC_LOADER_DISPLAY,
                            ASYNC_LOADER_USE_THREAD );
        
		return true;
	}
	else
	{
		return false;
	}
}

void PlayScene::addEffectLayer(const SlotInfo::EFFECT_TYPE effectType
                               , const SlotInfo::WHOLE_MADE wholeEffect /*= SlotInfo::WHOLE_MADE_NONE*/ )
{
    if(NULL == _effectLayer){return;}
    _effectLayer->setVisible(true);
    _effectLayer->playEffect(effectType, wholeEffect);
    
}

void PlayScene::removeEffectLayer()
{
    if(NULL == _effectLayer){return;}
    _effectLayer->setVisible(false);
}

PlayScene::~PlayScene()
{
    CC_SAFE_RELEASE(_layer);
    CC_SAFE_RELEASE(_slotLayer);
    CC_SAFE_RELEASE(_effectLayer);
    CC_SAFE_RELEASE(_layerOption);
}


PlayLayer::PlayLayer()
{
    _slotLayer = NULL;
    _coinSprite = NULL;
    gPlayLayer = this;
    _moneyLabel = NULL;
    _diamondLabel = NULL;
    _betLabel = NULL;
    _lvLabel = NULL;
    _winLabel = NULL;
    memset(_winSpin, 0, sizeof(_winSpin) );
    _remainLabel = NULL;
    _offsetMoneyLabelPlus = _offsetMoneyLabelMinus = NULL;
    _offsetExpLabel = NULL;
    
    _menu = NULL;
    _backItem = NULL;
    _spinItem = NULL;
    _miniGameItem = NULL;
    _betItem = NULL;
    _betMaxItem = NULL;
    _fortuneItem = NULL;
    
    
    _expGauge = NULL;
    
    _enableButtons = PLAY_BUTTONS::enableAll();
    
    _neonRight = _neonLeft = NULL;
    _actionsNeonLeft = _actionsNeonRight = NULL;
    
    _bg2 = _bg2 = NULL;

    _pauseFrame = false;
    memset(_missionBird, 0, sizeof(_missionBird));
    _missionAnimating = false;
}

void PlayLayer::onEnter()
{
    CCLayer::onEnter();
    
    _frameCnt = 0;
    
    SND()->setEffectsVolume(1.0f);
    SND()->stopBackgroundMusic();
    
    if( NULL != _moneyLabel )
    {
        return;
    }
    
    char moneyBuf[255];
    sprintf(moneyBuf, "%d", PlayerData::coin);
    _moneyLabel = CCLabelBMFont::create(moneyBuf, "menu/default_number.fnt");
    SystemConfig::setPosition(320, 640, _moneyLabel);
    this->addChild(_moneyLabel, 3);
    _moneyLabel->retain();
    
    // 다이아몬드
    sprintf(moneyBuf, "%d", PlayerData::diamond);
    _diamondLabel = CCLabelBMFont::create(moneyBuf, "menu/default_number.fnt");
    SystemConfig::setPosition(77, 640, _diamondLabel);
    this->addChild(_diamondLabel, 3);
    _diamondLabel->retain();
    
    
    
    _betLabel = CCLabelBMFont::create("1", "menu/default_number.fnt");
    SystemConfig::setPosition(581, 640, _betLabel);
    this->addChild(_betLabel, 3);
    _betLabel->retain();
    
    
    char lvRemain[10];
    sprintf(lvRemain, "%d", PlayerData::remainBell);
    _remainLabel = CCLabelBMFont::create(lvRemain, "number.fnt");
    SystemConfig::setPosition(580, 786, _remainLabel);
    _remainLabel->setScale(0.6f);
    this->addChild(_remainLabel, 3);
    _remainLabel->retain();
    
    
    _offsetMoneyLabelPlus = CCLabelBMFont::create("----", "menu/default_number.fnt");
    _offsetMoneyLabelPlus->retain();
    _offsetMoneyLabelPlus->setVisible(false);
    addChild(_offsetMoneyLabelPlus, 4);
    
    _offsetMoneyLabelMinus = CCLabelBMFont::create("----", "menu/n_number.fnt");
    _offsetMoneyLabelMinus->retain();
    _offsetMoneyLabelMinus->setVisible(false);
    addChild(_offsetMoneyLabelMinus, 4);
    
    initPosLabelOffsetMoney();
    
    
    // 경험지 변화표시
    _offsetExpLabel = CCLabelBMFont::create("", "menu/p_number.fnt");
    _offsetExpLabel->retain();
    //initPosLabelExp();
    SystemConfig::setPosition( SystemConfig::relativePixel(100), EXP_LABEL_Y, _offsetExpLabel);
}

void PlayLayer::onExit()
{
    SND()->setEffectsVolume(1.0f);
    
    CCTextureCache::sharedTextureCache()->removeAllTextures();
    
    CCLayer::onExit();
}


bool PlayLayer::init()
{
	if ( CCLayerColor::initWithColor( ccc4(0,0,0,0) ) )
	{
        // ask director the window size
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        _bg1 = CCSprite::create( "inGame/sky.png" );
        SystemConfig::setPosition(320, 816, _bg1);
        this->addChild(_bg1);
        _bg1->retain();
        
        _bg2 = CCSprite::create( "inGame/sky.png" );
        SystemConfig::setPosition(320 + 640, 816, _bg2);
        this->addChild(_bg2);
        _bg2->retain();
        
        
        CCSprite *ingameBase = CCSprite::create( "inGame/ingame_base.png" );
        ingameBase->setPosition( ccp(winSize.width/2
                                     , winSize.height/2) );
        this->addChild(ingameBase);
        
        
        // exp 게이지
        _exp = 0.0f;
        
        CCRect expRect; // w:622 h:8
        _expGauge = CCSprite::create("inGame/exp_gauge.png");
        SystemConfig::setPosition(EXP_LABEL_X, EXP_LABEL_Y, _expGauge);
        _expGauge->retain();
        setExp(0, 0); //초기화
        this->addChild(_expGauge);
        
                
        // Back 버튼
        _backItem = CCMenuItemImage::create(
                                            "inGame/bt_stop_default.png",
                                            "inGame/bt_stop_touch.png",
                                            this,
                                            menu_selector(PlayLayer::touchSpin) );
        SystemConfig::setPosition(25, 933, _backItem);
        _backItem->setTag(BTN_BACK);
        _backItem->retain();
        
        
        // 스핀버튼
        _spinItem = CCMenuItemImage::create(
                                            "inGame/bt_spin_off.png",
                                            "inGame/bt_spin_on.png",
                                            this,
                                            menu_selector(PlayLayer::touchSpin) );
        SystemConfig::setPosition(322, 48, _spinItem);
        _spinItem->setTag(BTN_SPIN);
        _spinItem->retain();
        
        
        // 미니게임
        _miniGameItem = CCMenuItemImage::create(
                                                "inGame/bt_high_low_off.png",
                                                "inGame/bt_high_low_on.png",
                                                this,
                                                menu_selector(PlayLayer::touchSpin) );
        SystemConfig::setPosition(166, 66, _miniGameItem);
        _miniGameItem->setTag(BTN_MINIGAME);
        _miniGameItem->retain();
        
        // 버튼 비활성
        _miniGameItem->cocos2d::CCMenuItem::setEnabled(false);
        
        // 미니게임 비활성버튼
        _minigameDisableSpr = CCSprite::create("inGame/bt_high_low_disable.png");
        SystemConfig::setPosition(166, 66, _minigameDisableSpr);
        _minigameDisableSpr->retain();
        addChild(_minigameDisableSpr, 2);
        
        
        
        
        
        // BET
        _betItem = CCMenuItemImage::create(
                                           "inGame/bt_bet_off.png",
                                           "inGame/bt_bet_on.png",
                                           this,
                                           menu_selector(PlayLayer::touchSpin) );
        SystemConfig::setPosition(477, 67, _betItem);
        _betItem->setTag(BTN_BET);
        _betItem->retain();
        
        // MAX BET
        _betMaxItem = CCMenuItemImage::create(
                                              "inGame/bt_maxbet_off.png",
                                              "inGame/bt_maxbet_on.png",
                                              this,
                                              menu_selector(PlayLayer::touchSpin) );
        SystemConfig::setPosition(579, 74, _betMaxItem);
        _betMaxItem->setTag(BTN_MAXBET);
        _betMaxItem->retain();
        
        // FORTUNE
        _fortuneItem = CCMenuItemImage::create(
                                               "inGame/bt_heart_off.png",
                                               "inGame/bt_heart_on.png",
                                               this,
                                               menu_selector(PlayLayer::touchSpin) );
        SystemConfig::setPosition(64, 74, _fortuneItem);
        _fortuneItem->setTag(BTN_FORTUNE);
        _fortuneItem->retain();
        
        
        _menu = CCMenu::create(_backItem, _miniGameItem, _spinItem, _betItem, _betMaxItem, _fortuneItem, NULL);
        _menu->setPosition( CCPointZero );
        this->addChild(_menu, 1);
        _menu->retain();
        
        
        
        // HOLD 1
        _hold1.area._sprite = CCSprite::create("inGame/holdArea.png");
        SystemConfig::setPosition(BaseBoxXPos1, 380, _hold1.area._sprite);
        _hold1.area._notificationID = NOTI_HOLD_1;
        _hold1.area.addChild(_hold1.area._sprite);
        this->addChild(&_hold1.area, 3);
        
        _hold1.led = CCSprite::create("inGame/bt_left_hold_disable.png");
        SystemConfig::setPosition(126, 142, _hold1.led);
        this->addChild(_hold1.led);
        
        
        // HOLD 2
        _hold2.area._sprite = CCSprite::create("inGame/holdArea.png");
        SystemConfig::setPosition(BaseBoxXPos2, 380, _hold2.area._sprite);
        _hold2.area._notificationID = NOTI_HOLD_2;
        _hold2.area.addChild(_hold2.area._sprite);
        this->addChild(&_hold2.area, 3);
        
        _hold2.led = CCSprite::create("inGame/bt_center_hold_disable.png");
        SystemConfig::setPosition(320, 140, _hold2.led);
        this->addChild(_hold2.led);
        
        
        
        // HOLD 3
        _hold3.area._sprite = CCSprite::create("inGame/holdArea.png");
        SystemConfig::setPosition(BaseBoxXPos3, 380, _hold3.area._sprite);
        _hold3.area._notificationID = NOTI_HOLD_3;
        _hold3.area.addChild(_hold3.area._sprite);
        this->addChild(&_hold3.area, 3);
        
        _hold3.led = CCSprite::create("inGame/bt_right_hold_disable.png");
        SystemConfig::setPosition(522, 142, _hold3.led);
        this->addChild(_hold3.led);
        
        
        // 코인 스프라이트.
        _coinSprite = CCSprite::create( "inGame/pop_win.png" );
        initPosCoinSprite();
        _coinSprite->retain();
        addChild(_coinSprite, 3);
        
        char lvWin[40];
        sprintf(lvWin, "%d", 0);
        _winLabel = CCLabelBMFont::create(lvWin, "number.fnt", SystemConfig::relativePixel(320), kCCTextAlignmentRight); // 정렬 먹지 않음 -> cocos버그
        _coinSprite->addChild(_winLabel);
        _winLabel->setPositionY(_coinSprite->getContentSize().height / 3);
        _winLabel->retain();

        
        
        _writtenMoney = PlayerData::coin;
        _writtenDiamond = PlayerData::diamond;
        
        
        int i=0;
        char bufWinSpin[100];
        for( int j=0; j<5; ++j)
        {            
            for( i=0; i<4; ++i){
                sprintf(bufWinSpin, "inGame/eff_coin_%d.png", i+1);
                _winSpin[j][i] = CCSprite::create(bufWinSpin);
                this->addChild(_winSpin[j][i], 4);
                _winSpin[j][i]->setVisible(false);
                _winSpin[j][i]->retain();
                SystemConfig::setPosition(WINS_COIN_START_X[j], WINS_COIN_START_Y[j], _winSpin[j][i]);
                _winSpin[j][i]->setScale(0.5f);
            }
        }
            
        _scalePauseCnt = 0;
        
        _coinAnimating = 0;
        this->schedule(schedule_selector(PlayLayer::frameAction));
        this->schedule(schedule_selector(PlayLayer::frameNotice), 90.0f);
        
        
        
        // 모든 버튼 활성화
        enableButtonAll();
        
        
        //공지라벨
        _noticeBack = CCLayerColor::create( ccc4(0,0,0,154), 0, 0);
        SystemConfig::setPosition(1200, 920, _noticeBack);
        _noticeBack->retain();
        addChild(_noticeBack);
        
        _notice = CCLabelTTF::create("공지사항", "고딕체", SystemConfig::getTTFSize(12) );
        CCSize noticeBackSize = _notice->getContentSize();
//        noticeBackSize.width += SystemConfig::relativePixel(80);
//        noticeBackSize.height += SystemConfig::relativePixel(10);
//        _noticeBack->setContentSize( noticeBackSize );
        
        _notice->setPosition(ccp(noticeBackSize.width / 2, noticeBackSize.height / 2) );
        _notice->setColor(ccc3(173,255,47) );
        _notice->retain();
        _noticeBack->addChild(_notice);
        
        
        // 네온싸인
        {
            CCAnimation *neonAnimation = CCAnimation::create();
            neonAnimation->setDelayPerUnit( 0.09f );
            neonAnimation->setLoops(INFINITY);
            
            for( int i=0; i<12; ++i)
            {
                char fileName[255];
                sprintf(fileName, "effect/eff_neon/eff_neon_left_%d.png", i+1);
                neonAnimation -> addSpriteFrameWithFileName( fileName );
            }
            
            CCAnimate *animate = CCAnimate::create( neonAnimation );
            
            _neonLeft = CCSprite::create( "effect/eff_neon/eff_neon_left_1.png" );
            SystemConfig::setPosition( 1, 379, _neonLeft);
            addChild(_neonLeft, 5);
            _neonLeft->setVisible(false);
            _neonLeft->retain();
            
            _actionsNeonLeft = CCSequence::create(
                                                             animate,
                                                             NULL
                                                             );
            _actionsNeonLeft->setTag(1155);
            _actionsNeonLeft->retain();
            
        }
        {
            CCAnimation *neonAnimation = CCAnimation::create();
            neonAnimation->setDelayPerUnit( 0.09f );
            neonAnimation->setLoops(INFINITY);
            
            for( int i=0; i<12; ++i)
            {
                char fileName[255];
                sprintf(fileName, "effect/eff_neon/eff_neon_right_%d.png", i+1);
                neonAnimation -> addSpriteFrameWithFileName( fileName );
            }
            
            CCAnimate *animate = CCAnimate::create( neonAnimation );
            
            _neonRight = CCSprite::create( "effect/eff_neon/eff_neon_right_1.png" );
            SystemConfig::setPosition( 637, 379, _neonRight);
            addChild(_neonRight, 5);
            _neonRight->setVisible(false);
            _neonRight->retain();
            
            _actionsNeonRight = CCSequence::create(
                                                  animate,
                                                  NULL
                                                  );
            _actionsNeonRight->setTag(1156);
            _actionsNeonRight->retain();
        }
        
        
        _holdPrev = false;
        
		return true;
	}
	else
	{
		return false;
	}
}

void PlayLayer::frameNotice(float dt)
{
    if( true == _pauseFrame ) return;
    
    _notice->setString( NOTICES[ arc4random() % NOTICE_CNT_TOTAL ]);
    CCSize noticeBackSize = _notice->getContentSize();
    noticeBackSize.width += SystemConfig::relativePixel(80);
    noticeBackSize.height += SystemConfig::relativePixel(10);
    _noticeBack->setContentSize( noticeBackSize );
    _notice->setPosition(ccp(noticeBackSize.width / 2, noticeBackSize.height / 2) );
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint pt;
    pt.setPoint( -(winSize.width * 2) , SystemConfig::relativePixel(920) );
    
    
    CCFiniteTimeAction *actions = CCSequence::create(
                                                     CCMoveTo::create(40.0f, pt ),
                                                     CCCallFunc::create(this, callfunc_selector(PlayLayer::finishedNoticeMove)),
                                                     NULL
                                                     );
    _noticeBack->runAction(actions);
}

void PlayLayer::finishedNoticeMove()
{
    SystemConfig::setPosition(1200, 920, _noticeBack);
}

PlayLayer::~PlayLayer()     // 소멸시 에러남.
{
    CC_SAFE_RELEASE(_coinSprite);
    CC_SAFE_RELEASE(_moneyLabel);
    CC_SAFE_RELEASE(_diamondLabel);
    CC_SAFE_RELEASE(_betLabel);
    CC_SAFE_RELEASE(_lvLabel);
    CC_SAFE_RELEASE(_winLabel);
    CC_SAFE_RELEASE(_remainLabel);
    CC_SAFE_RELEASE(_offsetMoneyLabelPlus);
    CC_SAFE_RELEASE(_offsetMoneyLabelMinus);
    CC_SAFE_RELEASE(_offsetExpLabel);
    
    
    CC_SAFE_RELEASE(_menu);
    CC_SAFE_RELEASE(_backItem);
    CC_SAFE_RELEASE(_spinItem);
    CC_SAFE_RELEASE(_miniGameItem);
    CC_SAFE_RELEASE(_betItem);
    CC_SAFE_RELEASE(_betMaxItem);
    CC_SAFE_RELEASE(_fortuneItem);
    
    CC_SAFE_RELEASE(_expGauge);
    CC_SAFE_RELEASE(_minigameDisableSpr);
    
    for( int j=0; j<5; ++j )
    {
        for( int i=0; i<4; ++i){
            CC_SAFE_RELEASE(_winSpin[j][i]);
        }
    }
    
    
    CC_SAFE_RELEASE(_notice);
    CC_SAFE_RELEASE(_noticeBack);
    
    CC_SAFE_RELEASE(_neonLeft);
    CC_SAFE_RELEASE(_neonRight);
    CC_SAFE_RELEASE(_actionsNeonLeft);
    CC_SAFE_RELEASE(_actionsNeonRight);
    
    CC_SAFE_RELEASE(_bg1);
    CC_SAFE_RELEASE(_bg2);
    
    for( int i=0; i<8; ++i)
    {
        CC_SAFE_RELEASE(_missionBird[i]);
    }
}



void PlayLayer::touchSpin(CCObject* pSender)
{
    CCMenuItem *item = (CCMenuItem *)pSender;
    
    switch (item->getTag()) {
        case BTN_MINIGAME:
        {
            SND()->playEffect(SoundPath::path(SoundPath::ST_HIGHLOW_START));
            
            if( false == (_enableButtons & PLAY_BUTTONS::UPDOWNGAME) ){ return;}
            _slotLayer->updownGame();
        }break;
        case BTN_BET:
        {
            SND()->playEffect(SoundPath::path(SoundPath::ST_GAME_BUTTON_CLICK));
            
            if( false == (_enableButtons & PLAY_BUTTONS::BET) ){ return;}
            _slotLayer->bet();
        }break;
        case BTN_MAXBET:
        {
            SND()->playEffect(SoundPath::path(SoundPath::ST_GAME_BUTTON_CLICK));
            
            if( false == (_enableButtons & PLAY_BUTTONS::MAX_BET) ){ return;}
            _slotLayer->betMax();
        }break;
        case BTN_FORTUNE:
        {
            SND()->playEffect(SoundPath::path(SoundPath::ST_GAME_BUTTON_CLICK));
            
            if( false == (_enableButtons & PLAY_BUTTONS::FORTUNE) ){ return;}
            //            _slotLayer->betMax();
        }break;
        case BTN_SPIN:
        {
            //SND
            SND()->playEffect(SoundPath::path(SoundPath::ST_GAME_SPIN_CLICK));
            
            if( false == (_enableButtons & PLAY_BUTTONS::SPIN) ){ return;}
            _enableButtons = _slotLayer->spin();
            if( 0 == _enableButtons ){ return;}
            
            _spinItem->setEnabled(false);
            
            _holdPrev = false;
            if( isHold(0) ){_holdPrev = true;}
            else if( isHold(1) ){_holdPrev = true;}
            else if( isHold(2) ){_holdPrev = true;}
            
            updateEnableButtons();
        }break;
        case BTN_BACK:
        {
            if( false == (_enableButtons ^ PLAY_BUTTONS::BACK) ){ return;}
            
            //SND
            SND()->playEffect(SoundPath::path(SoundPath::ST_SELECT_NORMAL));
            
            pauseFrame(true);
            
        }break;
        default:
        {
            assert(0);
        }
    }
}

void PlayLayer::showWinsLabel(int const wins)
{
    setWinLabel(wins);
    
    _coinSprite->setVisible(true);
    
    _coinScaleCurrent = COIN_SCALE_MIN;
    _scaleOffsetIndex = 0;
    _coinScaleNext = _coinScaleCurrent - COIN_FACTOR;
    
    _coinAnimating = 1;
}

void PlayLayer::initPosCoinSprite()
{
    SystemConfig::setPosition( 318, 814, _coinSprite);
    _coinSprite->setVisible(false);
    //    _coinSprite->setOpacity(0.0f);
}

void PlayLayer::initPosLabelOffsetMoney()
{
    SystemConfig::setPosition( 550, 655, _offsetMoneyLabelPlus);
    SystemConfig::setPosition( 550, 655, _offsetMoneyLabelMinus);
    //    _offsetMoneyLabel->setOpacity(0.0f);
}

void PlayLayer::initPosLabelExp()
{
    float const start = SystemConfig::relativePixel(EXP_LABEL_X) - (SystemConfig::relativePixel(EXP_GUAGE_WIDTH)/2);
    float pos = start + (EXP_GUAGE_WIDTH*_expGauge->getScaleX());
    
    if( SystemConfig::relativePixel(100) > pos )
    {
        pos = SystemConfig::relativePixel(100);
    }
    else if( SystemConfig::relativePixel(640 - 100) < pos )
    {
        SystemConfig::relativePixel(640 - 100);
    }
    
    SystemConfig::setPosition( pos, EXP_LABEL_Y, _offsetExpLabel);
}



void PlayLayer::finishedCoinAction(CCObject* pSender)
{
    return;
    
    this->removeChild(_coinSprite, false);
}

void PlayLayer::finishedCoinActionOffset(CCObject* pSender)
{
    _offsetMoneyLabelPlus->setVisible(false);
    _offsetMoneyLabelMinus->setVisible(false);
    initPosLabelOffsetMoney();
}

void PlayLayer::finishedExpAction(CCObject* pSender)
{
    initPosLabelExp();
    this->removeChild(_offsetExpLabel, false);
}


void PlayLayer::setCoin(int const offset)
{
    // 돈 갱신
    char label[255];
    PlayerData::coin = PlayerData::coin + PlayerData::winsFinal + offset;
    
    sprintf(label, "%d", PlayerData::coin);
    _moneyLabel->setString(label);
    _moneyLabel->updateLabel();
    
    // wins 처리
    char bufPrev[255] = {0,};
    
    if( true == PlayerData::waitWins)
    {
        SND()->playEffect(SoundPath::path(SoundPath::ST_GAME_GETWINS));
        
        PlayerData::waitWins = false;
        gPlayLayer->closeWinLabel();
        
        if( PlayerData::winsFinal <= (GameData::BET_MIN[PlayerData::currentGirlNo] * 3) ){
            _winsSpriteCnt = 1;
        }else if( PlayerData::winsFinal <= (GameData::BET_MIN[PlayerData::currentGirlNo] * 6) ){
            _winsSpriteCnt = 2;
        }else if( PlayerData::winsFinal <= (GameData::BET_MIN[PlayerData::currentGirlNo] * 12) ){
            _winsSpriteCnt = 3;
        }else if( PlayerData::winsFinal <= (GameData::BET_MIN[PlayerData::currentGirlNo] * 24) ){
            _winsSpriteCnt = 4;
        }else{
            _winsSpriteCnt = 5;
        }
        
        for( int j=0; j<_winsSpriteCnt; ++j)
        {
            _currentWinSpinPosY[j] = WINS_COIN_START_Y[j];
            _currentWinSpinIndex[j] = 0;
        }
        
        _winSpinFrames = 0;
        _currentWinSpinSprite = 0;

        _coinAnimating = 2;
        
        
        sprintf(bufPrev, "%d\n\r", PlayerData::winsFinal );
    }
    
    // 돈 변위 표시
    CCLabelBMFont *moneyLabelOffset = NULL;
    if( 0 > (PlayerData::winsFinal + offset) )
    {
        sprintf(label, "-%d", PlayerData::winsFinal - offset);
        moneyLabelOffset = _offsetMoneyLabelMinus;
    }
    else
    {
        sprintf(label, "+%d", PlayerData::winsFinal + offset);
        moneyLabelOffset = _offsetMoneyLabelPlus;
    }
    PlayerData::winsFinal = PlayerData::winsFirst = 0;
    
    //    sprintf(label, "%d", offset);
    
    moneyLabelOffset->setVisible(true);
    moneyLabelOffset->setString(label);
    moneyLabelOffset->updateLabel();
    
    CCPoint ptCoinDown;
    ptCoinDown.setPoint(moneyLabelOffset->getPositionX(), moneyLabelOffset->getPositionY() + SystemConfig::relativePixel(60) );
    
    CCFiniteTimeAction *actions = CCSequence::create(
                                                     CCMoveTo::create(0.4f, ptCoinDown ),
                                                     CCDelayTime::create(0.3),
                                                     CCCallFuncN::create(this, callfuncN_selector(PlayLayer::finishedCoinActionOffset)),
                                                     NULL
                                                     );
    moneyLabelOffset->runAction(actions);
}

void PlayLayer::setBet(int const bet)
{
    char label[255];
    sprintf(label, "%d", bet);
    _betLabel->setString(label);
    _betLabel->updateLabel();
    
    PlayerData::currentBet = bet;
}

void PlayLayer::setWinLabel(int const win)
{
    char label[255];
    sprintf(label, "%d", win);
    _winLabel->setString(label);
    _winLabel->updateLabel();
    
    float const margineRight = SystemConfig::relativePixel(30);
    
    if( _coinSprite->getContentSize().width > _winLabel->getContentSize().width ){
        
        _winLabel->setPositionX(
                                (_coinSprite->getContentSize().width - _winLabel->getContentSize().width)
                                + (_winLabel->getContentSize().width/2)
                                - margineRight );
    }else{
        _winLabel->setPositionX( _coinSprite->getContentSize().width / 2 );
    }
}


void PlayLayer::setRemain(int const remain)
{
    PlayerData::remainBell = remain;
    
    char label[255];
    sprintf(label, "%d", PlayerData::remainBell);
    _remainLabel->setString(label);
    _remainLabel->updateLabel();
}

void PlayLayer::updateMoneyLabel()
{
    if( PlayerData::coin != _writtenMoney )
    {
        char moneyBuf[255];
        sprintf(moneyBuf, "%d", PlayerData::coin);
        _moneyLabel->setString(moneyBuf);
        _moneyLabel->updateLabel();
        
        _writtenMoney = PlayerData::coin;
    }
    
    if( PlayerData::diamond != _writtenDiamond )
    {
        char moneyBuf[255];
        sprintf(moneyBuf, "%d", PlayerData::diamond);
        _diamondLabel->setString(moneyBuf);
        _diamondLabel->updateLabel();
        
        _writtenDiamond = PlayerData::diamond;
    }
}

void PlayLayer::frameAction(float dt)
{
    if( true == _pauseFrame ) return;
    
    updateMoneyLabel();

    
    if( 0 == (_frameCnt % 6))
    {
        _bg1->setPositionX(_bg1->getPositionX()-1);
        _bg2->setPositionX(_bg2->getPositionX()-1);
        if( _bg1->getPositionX() <= ( SystemConfig::relativePixel(320 - 640)) )
        {
            _bg1->setPositionX(_bg1->getPositionX() + SystemConfig::relativePixel(1280) );
        }
        if( _bg2->getPositionX() <= ( SystemConfig::relativePixel(320 - 640)) )
        {
            _bg2->setPositionX(_bg2->getPositionX() + SystemConfig::relativePixel(1280) );
        }
    }
    _frameCnt++;
    
    if( true == _missionAnimating)
    {
        if( 0 == (_frameCnt % FRAME_FOR_MISSION_MOVE))
        {
            int prevBirdIDX = _currentMissinBird - 1;
            if( 0 > prevBirdIDX ){ prevBirdIDX = 7;}
            CCSprite &birdPrev = *_missionBird[prevBirdIDX];
            birdPrev.setVisible(false);
            
            CCSprite &bird = *_missionBird[_currentMissinBird];
            bird.setVisible(true);
            bird.setPositionX(birdPrev.getPositionX() + SystemConfig::relativePixel(MISSION_BIRD_OFFSET));
            
            _currentMissinBird++;
            _currentMissinBird %= 8;
            
            if( SystemConfig::relativePixel(640 + 64) < bird.getPositionX() )
            {
                hideMissionAnimation();
            }
        }
    }

    
    if( 1 == _coinAnimating)    // 윈즈 줌인/줌아웃 애니메이션
    {
        if( _coinScaleNext < _coinScaleCurrent )
        {
            
            _coinScaleCurrent -= COIN_FACTOR;
            
            if( COIN_SCALE_MIN > _coinScaleCurrent ){
                _scaleOffsetIndex = 0;
                _scalePauseCnt = 0;
                
                _coinScaleNext = _coinScaleCurrent + COIN_FACTOR;
            }else{
                _coinScaleNext = _coinScaleCurrent - COIN_FACTOR;
                
                _scaleOffsetIndex++;
                _scaleOffsetIndex = MIN( _scaleOffsetIndex, sizeof(COIN_SCALES) / sizeof(1.0f)  - 1 );
            }
        }
        else
        {
            if( SCALE_PAUSE_CNT > _scalePauseCnt++ )
            {
                return;
            }
            
            
            _coinScaleCurrent += COIN_FACTOR;
            
            if( 1.0f < _coinScaleCurrent ){
                _scaleOffsetIndex = 0;
                _scalePauseCnt = 0;
                
                _coinScaleNext = _coinScaleCurrent - COIN_FACTOR;
            }else{
                _coinScaleNext = _coinScaleCurrent + COIN_FACTOR;
                
                _scaleOffsetIndex++;
                _scaleOffsetIndex = MIN( _scaleOffsetIndex, sizeof(COIN_SCALES) / sizeof(1.0f) - 1 );
            }
        }
        
        _coinSprite->setScale(_coinScaleCurrent);
//        _winLabel->setScale(_coinScaleCurrent * 1.5f);
    }
    else if( 2 == _coinAnimating)   // 윈즈 획득시 동전 튀어돌아올라가는 애니메이션
    {
        if( 0 == (_winSpinFrames % FRAME_PER_WINSPIN_CHANGE)  )
        {
            _currentWinSpinSprite++;
            _currentWinSpinSprite %= 4; // 에니메이션 스프라이트 갯수 4개.
            
            if( true == moveWinSpin() )
            {
                _coinAnimating = 0;
                
                for( int j=0; j<_winsSpriteCnt; ++j)
                {
                    for(int i=0 ; i<4; ++i)
                    {
                        _winSpin[j][i]->setVisible(false);
                    }
                }
                return;
            }
        }
        
        _winSpinFrames++;
    }
}

// return : 에니메이션 종료
bool PlayLayer::moveWinSpin()
{
    static const int waitCnt[5] = {
        0 * CNT_WINSPIN_DELAY,
        1 * CNT_WINSPIN_DELAY,
        2 * CNT_WINSPIN_DELAY,
        3 * CNT_WINSPIN_DELAY,
        4 * CNT_WINSPIN_DELAY
    };
    static const int offsetMax = sizeof(WINS_SPIN_OFFSET) / sizeof(int);
    
    int const enterCnt = 1 + (_winSpinFrames / FRAME_PER_WINSPIN_CHANGE);
    
    for( int j=0; j<_winsSpriteCnt; ++j){
        for(int i=0 ; i<4; ++i){
            _winSpin[j][i]->setVisible(false);
        }
    }
    
                              
    for( int j=0; j<_winsSpriteCnt; ++j)
    {
        if( enterCnt >= waitCnt[j] && enterCnt < (waitCnt[j] + offsetMax) )
        {
            float &winsPosY = _currentWinSpinPosY[j];
            int &idx = _currentWinSpinIndex[j];
            const int& offset = WINS_SPIN_OFFSET[ idx ];
            assert( offsetMax > idx);
            
            if( idx < 4){
                winsPosY += offset;
            }else if( idx < 5 ){
                winsPosY += offset;
            }else if( idx < 8 ){
                winsPosY += offset;
            }else if( idx < 9 ){
                // 여기부터 동전 떨어짐.
                winsPosY -= offset;
            }else{
                winsPosY -= offset;
            }
            
            _winSpin[j][_currentWinSpinSprite]->setVisible(true);
            SystemConfig::setPositionY(winsPosY, _winSpin[j][_currentWinSpinSprite]);
            
            idx++;
        }
    }
    
    if( 13 < _currentWinSpinIndex[_winsSpriteCnt-1] )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PlayLayer::holdOffAll()
{
    holdOff(_hold1, "inGame/bt_left_hold_disable.png");
    holdOff(_hold2, "inGame/bt_center_hold_disable.png");
    holdOff(_hold3, "inGame/bt_right_hold_disable.png");
}

void PlayLayer::holdOff(HoldButton &hold, const char *imgPath)
{
    if( true == hold.holdOn )
    {
        hold.holdOn = false;
        
        CCPoint pt = hold.led->getPosition();
        this->removeChild(hold.led, true);
        hold.led = CCSprite::create(imgPath);
        hold.led->setPosition(pt);
        this->addChild(hold.led);
    }
}
void PlayLayer::receiveNotification(int const notificationNo)
{
    //SND
    SND()->playEffect(SoundPath::path(SoundPath::ST_GAME_HOLD_CLICK));
    
    if( false == (_enableButtons & PLAY_BUTTONS::HOLD1) ){ return;}
    
    // 메이드된 직후 홀드할 수 없습니다.
    if( true == PlayerData::isMade){ return; }
    
    // 게임 시작하자마자 홀드할 수 없습니다.
    if( 0 == PlayerData::gameCnt ){ return;}
    
    // 보너스 스핀중에는 홀들할 수 없습니다.
    if( gPlaySlot->isBonusGame()){return;}
    
    // 이 전 게임에서 홀드하였으면 홀드할 수 없습니다.
    if( true == _holdPrev ){ return;}

    
    
    assert( notificationNo == NOTI_HOLD_1
           || notificationNo == NOTI_HOLD_2
           || notificationNo == NOTI_HOLD_3 );
    
    
    HoldButton &hold = (notificationNo == NOTI_HOLD_1) ? _hold1
    : (notificationNo == NOTI_HOLD_2) ? _hold2 : _hold3;
    
    const char *filePath = (notificationNo == NOTI_HOLD_1) ? "inGame/bt_left_hold_disable.png"
    : (notificationNo == NOTI_HOLD_2) ? "inGame/bt_center_hold_disable.png" : "inGame/bt_right_hold_disable.png";

    if( true == hold.holdOn )
    {
        holdOff(hold, filePath);
    }
    else
    {
        if( (_hold1.holdOn && _hold2.holdOn)
           || ( _hold1.holdOn && _hold3.holdOn)
           || ( _hold2.holdOn && _hold3.holdOn) )
        {//
            return;
        }
        
        
        hold.holdOn = true;
        
        CCPoint pt = hold.led->getPosition();
        this->removeChild(hold.led, true);
        
        if( NOTI_HOLD_1 == notificationNo){
            hold.led = CCSprite::create("inGame/bt_left_hold_enable.png");
        }else if( NOTI_HOLD_2 == notificationNo){
            hold.led = CCSprite::create("inGame/bt_center_hold_enable.png");
        }else if( NOTI_HOLD_3 == notificationNo){
            hold.led = CCSprite::create("inGame/bt_right_hold_enable.png");
        }else{
            assert(0);
        }
        
        hold.led->setPosition(pt);
        this->addChild(hold.led);
    }
}

bool PlayLayer::isHold(const int lineNo) const
{
    if( 0 == lineNo){
        return _hold1.holdOn;
    }else if( 1 == lineNo){
        return _hold2.holdOn;
    }else if( 2 == lineNo){
        return _hold3.holdOn;
    }
    
    //    if( true == _hold1.holdOn ) { return 1; }
    //    if( true == _hold2.holdOn ) { return 2; }
    //    if( true == _hold3.holdOn ) { return 3; }
    
    //    return 0;
}

void PlayLayer::enableButtonAll()
{
    _enableButtons = PLAY_BUTTONS::enableAll();
    _menu->setEnabled(true);
    _spinItem->setEnabled(true);
}

void PlayLayer::updateEnableButtons()
{
    if( false == (_enableButtons & PLAY_BUTTONS::BET) ){
        _menu->setEnabled(false);
    }
    else{
        
    }
}

// return : 미션 발동 여부
bool PlayLayer::incExp(float const incPt /* incPt 수치는 현재 0 과 0 이 아닌 값으로 사용되고 있음.*/)
{
    
    if(0.0f == incPt)
    {
        setExp(0.0f, -EXP_GUAGE_WIDTH);
        return false;
    }
    
    float const offset = EXP_GUAGE_WIDTH / (10 * (PlayerData::currentGirlNo + 1) );
    
    _exp += offset;
    
    if( EXP_GUAGE_WIDTH <= _exp )
    {
        // 미션 발동~~~
        setExp(EXP_GUAGE_WIDTH, offset);
        
        gPlaySlot->setMissionEffect(true);
        _exp = 0;
        
        showMissionAnimation();
        
        return true;
    }
    else
    {
        setExp(_exp, offset);
        return false;
    }
}

void PlayLayer::setExp(float const exp, float const offset)
{
    float scale;
    
    if( 0.0f == exp )
    {
        scale = 0;
    }
    else
    {
        scale = exp / EXP_GUAGE_WIDTH;
    }
    
    
    float const offX = SystemConfig::relativePixel( ((EXP_GUAGE_WIDTH - (EXP_GUAGE_WIDTH * scale)) /2) );
    
    CCPoint pt;
    pt.y = _expGauge->getPositionY();
    pt.x = SystemConfig::relativePixel(EXP_LABEL_X) - offX ;
    
    if( 0 == offset)//초기화
    {
        _expGauge->setScaleX(scale);
        CCLog("현재x:%f, offX:%f",_expGauge->getPositionX(), offX );
        _expGauge->setPositionX(pt.x ) ;
        
        return;
    }
    else
    {
        ///
        CCFiniteTimeAction *actions = CCSequence::create(
                                                         CCTintBy::create(0.15f, 255, 0, 0),
                                                         CCTintBy::create(0.15f, -255, 0, 0),
                                                         CCTintBy::create(0.15f, 255, 0, 0),
                                                         CCTintBy::create(0.15f, -255, 0, 0),
                                                         CCSpawn::create( CCScaleTo::create(0.4f, scale, 1.0f),
                                                                         CCMoveTo::create(0.4f, pt),
                                                                         NULL),
                                                         CCDelayTime::create(0.5f),
                                                         NULL
                                                         );
        _expGauge->runAction( actions );
    }
    
    
    
    
    
    //
    
    //// 포인트 증가 라벨 표시
    char label[255];
    sprintf(label, "+%d", (int)offset);
    _offsetExpLabel->setString(label);
    _offsetExpLabel->updateLabel();
    
    CCPoint ptCoinDown;
    ptCoinDown.setPoint(_offsetExpLabel->getPositionX(), _offsetExpLabel->getPositionY() + SystemConfig::relativePixel(32) );
    
    CCFiniteTimeAction *actions = CCSequence::create(
                                                     CCMoveTo::create(0.4f, ptCoinDown ),
                                                     CCDelayTime::create(0.3),
                                                     CCCallFuncN::create(this, callfuncN_selector(PlayLayer::finishedExpAction)),
                                                     NULL
                                                     );
    actions->setTag(3389);
    
    this->addChild(_offsetExpLabel, 4);
    _offsetExpLabel->runAction(actions);
}

void PlayLayer::closeWinLabel()
{
    _coinSprite->setVisible(false);
//    _winLabel->setVisible(false);
}

void PlayLayer::readyMiniGame()
{
    // 업다운 게임 활성화.
    // 1.비활성 버튼 숨기기
    // 2.메뉴버튼 활성화
    
    // 1.
    _minigameDisableSpr->setVisible(false);
    
    // 2.
    _miniGameItem->setEnabled(true);
}

void PlayLayer::closeMiniGame()
{
    // 업다운 게임 비활성화.
    _minigameDisableSpr->setVisible(true);
    _miniGameItem->setEnabled(false);
    
    if( 0 < PlayerData::winsFinal){
        // win 금액을 수정해준다.
        setWinLabel(PlayerData::winsFinal);
    }else{
        _coinSprite->setVisible(false);
//        _winLabel->setVisible(false);
        
        _coinAnimating = 0;
    }
}

void PlayLayer::runNeonSign()
{
    {
        _neonLeft->setVisible(true);
        _neonLeft->runAction( _actionsNeonLeft );
    }
    
    {
        _neonRight->setVisible(true);
        _neonRight->runAction( _actionsNeonRight );
    }
}


void PlayLayer::stopNeonSign()
{
    stopAction(_actionsNeonLeft);
    stopAction(_actionsNeonRight);
//    stopActionByTag(1155);
//    stopActionByTag(1156);
    _neonLeft->setVisible(false);
    _neonRight->setVisible(false);
}

void PlayLayer::pauseFrame(const bool pause)
{
    _pauseFrame = pause;
    
    gPlaySlot->pauseFrame(pause);
    
    if( true == pause)
    {
        ((PlayScene*)getParent())->_layerOption->setOption(2);
        ((PlayScene*)getParent())->_layerOption->setVisible(true);
        
        _menu->setEnabled(false);
    }
    else
    {
        _menu->setEnabled(true);
    }
}

void PlayLayer::exitGame()
{
    //
    PlayerData::waitWins = false;
    
    //
    PlayerData::coin += PlayerData::winsFinal;
    PlayerData::winsFinal = PlayerData::winsFirst = 0;
    
    //            CCDirector::sharedDirector()->popSceneWithTransition<CCTransitionFade>(0.4);
    CCScene *s = ThemeScene::create();
    CCTransitionFade *tr = CCTransitionFade::create(1.0f, s);
    CCDirector::sharedDirector()->replaceScene(tr);
}


void PlayLayer::continueSelectedNo()
{
    pauseFrame(false);
}

void PlayLayer::continueSelectedYes()
{
    exitGame();
}

void PlayLayer::showMissionAnimation()
{
    char path[255];
    for(int i=0; i<8; ++i ){
        sprintf(path, "inGame/bird_%d.png", i+1);
        
        _missionBird[i] = CCSprite::create(path);
        SystemConfig::setPosition(64, 780, _missionBird[i]);
        addChild(_missionBird[i]);
        _missionBird[i]->retain();
        _missionBird[i]->setVisible(false);
    }
    
    _currentMissinBird = 0;
    _missionAnimating = true;
}

void PlayLayer::hideMissionAnimation()
{
    for(int i=0; i<8; ++i ){
        removeChild(_missionBird[i], true);
        CC_SAFE_RELEASE_NULL(_missionBird[i]);
    }
    
    _missionAnimating = false;
}











LAPlayUserOption::LAPlayUserOption()
{
    _pMenu = NULL;
    _msgBox = NULL;
    _contents = NULL;
}

LAPlayUserOption::~LAPlayUserOption()
{
    CC_SAFE_RELEASE(_pMenu);
    CC_SAFE_RELEASE(_msgBox);
    CC_SAFE_RELEASE(_contents);
}

bool LAPlayUserOption::init()
{
	if ( CCLayerColor::initWithColor( ccc4(0,0,0,100) ) )
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        // 메세지박스
        _msgBox = CCSprite::create("pop_window.png");
        SystemConfig::setPosition(320, 490, _msgBox);
        _msgBox->retain();
        this->addChild(_msgBox, 1);
        
        
//        CCSize titleSize( SystemConfig::relativePixel(400), SystemConfig::relativePixel(60) );
//        _title = CCLabelTTF::create("", "고딕체"
//                                    , SystemConfig::getTTFSize(18)
//                                    , titleSize
//                                    , kCCTextAlignmentCenter);
//        SystemConfig::setPosition(200, 230, _title);
//        _title->setColor(ccc3(0,255,0) );
//        
//        _title->retain();
//        _msgBox->addChild(_title);
        
        
        CCSize contentsSize(SystemConfig::relativePixel(400), SystemConfig::relativePixel(60) );
        _contents = CCLabelTTF::create("", "고딕체"
                                       , SystemConfig::getTTFSize(16)
                                       , contentsSize
                                       , kCCTextAlignmentCenter);
        
        SystemConfig::setPosition(220, 160, _contents);
        _contents->setColor(ccc3(255,255,255) );
        _contents->retain();
        _msgBox->addChild(_contents);
        
        
        // Yes
        _btnYes = CCMenuItemImage::create(
                                          "updown/bt_yes_normal.png",
                                          "updown/bt_yes_touch.png",
                                          this,
                                          menu_selector(LAPlayUserOption::menuCallback) );
        SystemConfig::setPosition(210, 425, _btnYes);
        _btnYes->setTag(13);
        _btnYes->retain();
        
        // No
        _btnNo = CCMenuItemImage::create(
                                         "updown/bt_no_normal.png",
                                         "updown/bt_no_touch.png",
                                         this,
                                         menu_selector(LAPlayUserOption::menuCallback) );
        SystemConfig::setPosition(445, 425, _btnNo);
        _btnNo->setTag(14);
        _btnNo->retain();
        
        
        _pMenu = CCMenu::create(_btnYes, _btnNo, NULL);
        _pMenu->retain();
        _pMenu->setPosition( CCPointZero );
        this->addChild(_pMenu, 1);
                
        hideAll();
        
		return true;
	}
	else
	{
		return false;
	}
}

void LAPlayUserOption::hideAll()
{
    _msgBox->setVisible(false);
    
    _btnYes->setVisible(false);
    _btnNo->setVisible(false);
    
    _contents->setVisible(false);
}

void LAPlayUserOption::menuCallback(CCObject* pSender)
{
    CCMenuItem *item = (CCMenuItem *)pSender;
    
    switch (item->getTag()) {
        case 13: // yes
        {
            SND()->playEffect(SoundPath::path(SoundPath::ST_SELECT_NORMAL));
            
            ((PlayScene*)getParent())->_layer->continueSelectedYes();
            this->setVisible(false);
        }
            break;
        case 14: // no
        {
            SND()->playEffect(SoundPath::path(SoundPath::ST_SELECT_NORMAL));
            
//            ((PlayScene*)getParent())->_layer->_pMenu->setEnabled(true);
            ((PlayScene*)getParent())->_layer->continueSelectedNo();
            this->setVisible(false);
        }
            break;
        default:
            assert(0);
    }
}

void LAPlayUserOption::setOption(int const option)
{
    hideAll();
    
    if( 2 == option)
    {
        _msgBox->setVisible(true);
        _contents->setVisible(true);
        
        
        _btnYes->setVisible(true);
        _btnNo->setVisible(true);
        
        _contents->setString("Do you want to quit the game?");
    }
    else
    {
        assert(0);
    }
}


