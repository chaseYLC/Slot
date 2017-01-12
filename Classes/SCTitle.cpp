#include "SCTitle.h"

#include "SystemConfig.h"
//#include "SCTheme.h"
//#include "ThemeMgr.h"
//#include "SimpleAudioEngine.h"

using namespace cocos2d;

bool GameTitleScene::init()
{
    CCLOG( __FUNCTION__ );
	if( CCScene::init() )
	{
		this->_layer = GameTitleLayer::create();
		this->_layer->retain();
		this->addChild(_layer);
        
		return true;
	}
	else
	{
		return false;
	}
}

GameTitleScene::~GameTitleScene()
{
    CC_SAFE_RELEASE(_layer);
}

bool GameTitleLayer::init()
{
    CCLOG( __FUNCTION__ );
	if ( LayerColor::initWithColor(Color4B(255,255,255,255) ) )
	{
        // 전역 스케일 값 설정
        SystemConfig::gScaleX = 1;
        SystemConfig::gScaleY = 1;
        
        loadTitle();
        
        // 터치 활성화
        // setTouchEnabled(true);
		return true;
	}
	else
	{
		return false;
	}
}

void GameTitleLayer::onEnter()
{
	cocos2d::LayerColor::onEnter();

	m_touchLabel = Sprite::create("title/start_1.png");
	m_touchLabel->retain();
}

void GameTitleLayer::onExit()
{
	m_touchLabel->release();

	cocos2d::LayerColor::onExit();
}

void GameTitleLayer::loadedTitle()
{
	float posCenter = SystemConfig::getWinSize().width / 2;

    // 터치 라벨 배경
    Sprite *crbg = Sprite::create("title/touch_back.png");
	crbg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	crbg->setPosition(posCenter, _rp(107));
	this->addChild(crbg);

	// 터치 애니.
	Animation *touchAni = Animation::create( );
    touchAni -> setDelayPerUnit( 0.1f );
    touchAni -> setLoops( INFINITY );
    
    touchAni ->addSpriteFrameWithFile( "title/start_1.png" );
    touchAni ->addSpriteFrameWithFile( "title/start_2.png" );
    touchAni ->addSpriteFrameWithFile( "title/start_3.png" );
    touchAni ->addSpriteFrameWithFile( "title/start_4.png" );
    touchAni ->addSpriteFrameWithFile( "title/start_5.png" );
    
    Animate *theAnimation = Animate::create( touchAni );
	m_touchLabel->setAnchorPoint(crbg->getAnchorPoint());
	m_touchLabel->setPosition(crbg->getPosition().x, crbg->getPosition().y + _rp(10));
	this-> addChild(m_touchLabel, 2 );

	m_touchLabel-> runAction( theAnimation );

    
    // 터치 활성화
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(GameTitleLayer::onTouchBegan, this);
	//touchListener->onTouchMoved = CC_CALLBACK_2(GameTitleLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameTitleLayer::onTouchEnded, this);
	//touchListener->onTouchCancelled = CC_CALLBACK_2(GameTitleLayer::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameTitleLayer::loadedTitleCharacter()
{
	float posCenter = SystemConfig::getWinSize().width / 2;
	float posCenterH = SystemConfig::getWinSize().height / 2;

    // 타이틀(제목)
    Sprite *title = Sprite::create("title/title.png");
	title->setPosition(posCenter, posCenterH + _rp(100));
    title->setScale(2.0f);
	this->addChild(title);
    
    FiniteTimeAction *actions = Sequence::create(
                                                     ScaleTo::create(0.3f, 1.0f),
		CallFunc::create(CC_CALLBACK_0(GameTitleLayer::loadedTitle, this)),
                                                     NULL );
    title->runAction(actions);
}

void GameTitleLayer::loadTitle()
{
    Size winSize = Director::getInstance()->getWinSize();
	float posCenter = SystemConfig::getWinSize().width / 2;
    
    Sprite *bg = Sprite::create( "title/back.png");
    bg->setPosition( cocos2d::Vec2(winSize.width/2
                         , winSize.height/2) );
    this->addChild(bg);
    
    // 배경
    Sprite *bgCopyright = Sprite::create( "title/copyright.png" );
	bgCopyright->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	bgCopyright->setPosition(posCenter, _rp(23));
	
    this->addChild(bgCopyright, 1);

	
	// 배경 캐릭
	Sprite *character = Sprite::create("title/title_girl.png");
    character->setPosition( Vec2(winSize.width/2, winSize.height/2) );
    character->setOpacity(0);
    this->addChild(character);
    
	FiniteTimeAction *actions = Sequence::create(
		FadeIn::create(0.8f),
		CallFunc::create(CC_CALLBACK_0(GameTitleLayer::loadedTitleCharacter, this)),
		NULL);
    
    character->runAction(actions);
}

bool GameTitleLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	return true;
}

void GameTitleLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    /*SND()->playEffect(SoundPath::path(SoundPath::ST_SELECT_NORMAL));*/
    //

	touch->getLocation();
	Point pt = Director::getInstance()->convertToGL(touch->getLocationInView());
	char tempString[80];
	sprintf(tempString, "%f, %f", pt.x, pt.y);
	CCLOG(tempString);
    
//    // 터치된 지점 중 첫번째 요소를 가져 온다.
//    CCTouch *pATouch = (CCTouch *)pTouches->anyObject();
//    // 치지 지점을 화면 좌표에 맞게 변환 해준다.
//    CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pATouch->getLocationInView());
//    
//    char tempString[80];
//    sprintf(tempString, "%f, %f", touchPoint.x, touchPoint.y);
    

    
     테마 선택화면을 로딩합니다.
    gThemeMgr->setCurrentThemeNum(1);
    
    CCScene *s = ThemeScene::create();
    CCDirector::sharedDirector()->setDepthTest(true);

    CCTransitionScene *tr = CCTransitionFade::create(0.7f, s);
    CCDirector::sharedDirector()->pushScene(tr);
}

GameTitleLayer::~GameTitleLayer()
{
    CCLOG( __FUNCTION__ );
}