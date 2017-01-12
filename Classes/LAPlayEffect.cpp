//
//  LAPlayEffect.cpp
//  gameTest
//
//  Created by Chase on 12. 11. 11..
//  Copyright (c) 2012년 넥스테일. All rights reserved.
//

#include "LAPlayEffect.h"
#include "SystemConfig.h"
#include "SCPlay.h"
#include "SimpleAudioEngine.h"
#include "SCDice.h"
#include "PlayerData.h"

using namespace cocos2d;

bool LAPlayEffect::init()
{
	if ( CCLayerColor::initWithColor( ccc4(0,0,0,100) ) )
    {
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
     
        particleSystem[0] = NULL;
        particleSystem[1] = NULL;

        //loadEffects();
        
        return true;
	}
	else
	{
		return false;
	}
}

LAPlayEffect::~LAPlayEffect()
{
    struct Releaser
    {
        Releaser(EffectUnit &unit)
        {
            CC_SAFE_RELEASE_NULL(unit.animate);
            CC_SAFE_RELEASE_NULL(unit.animation);
            CC_SAFE_RELEASE_NULL(unit.sprite);
        }
    };
    
    Releaser    u1(_unitSeven);
    Releaser    u2(_unitBell);
    Releaser    u3(_unitHeart);
    Releaser    u4(_unitFruit);
    Releaser    u5(_unitPocket);
    
    CC_SAFE_RELEASE_NULL(_heartMentions);
    CC_SAFE_RELEASE_NULL(_heartBack);
}

void LAPlayEffect::onEnter()
{
    CCLayer::onEnter();
}

void LAPlayEffect::onExit()
{
    CCLayer::onExit();
}


void LAPlayEffect::particleTest()
{ // 파티클 테스트
    
    if( particleSystem[0] == 0 )
    {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        particleSystem[0] = CCParticleSystemQuad::create("particles/money.plist");
        SystemConfig::setPosition(200, 1000 , particleSystem[0]);
        this->addChild( particleSystem[0] );
        
        particleSystem[1] = CCParticleSystemQuad::create("particles/money.plist");
        SystemConfig::setPosition(600, 1000 , particleSystem[1]);
        this->addChild( particleSystem[1] );
    } else
    {
        //            particleSystem->removeFromParentAndCleanup(false);
        particleSystem[0]->resetSystem();
        particleSystem[1]->resetSystem();
        //            particleSystem->setPosition( pPoint );
    }
    
}
void LAPlayEffect::playEffect(SlotInfo::EFFECT_TYPE const effectType,
    const SlotInfo::WHOLE_MADE wholeEffect)
{
    if( SlotInfo::EFF_BELL == effectType){
        
        particleTest();
        
        SND()->playEffect(SoundPath::path(SoundPath::ST_EFFECT_BELL));
        
        // remain 수정
        PlayerData::remainBell--;
        gPlayLayer->setRemain(PlayerData::remainBell);
        //
        
        // load effect.
        loadEffects(SlotInfo::EFF_BELL);
        
        CCFiniteTimeAction *actions = CCSequence::create(
                                                         _unitBell.animate,
                                                         CCCallFuncN::create(this, callfuncN_selector(LAPlayEffect::menuCloseCallback)),
                                                         NULL
                                                         );
        this->addChild(_unitBell.sprite, 1);
        _unitBell.sprite->runAction( actions );
    }
    else if( SlotInfo::EFF_SEVEN == effectType
            || SlotInfo::WHOLE_MADE_SEVEN == wholeEffect
            || SlotInfo::WHOLE_MADE_SEVEN_CROSS == wholeEffect
            || SlotInfo::WHOLE_MADE_SEVEN_TWO == wholeEffect ){
        
        SND()->playEffect(SoundPath::path(SoundPath::ST_EFFECT_SEVEN));
        
        particleTest();
        
        // load effect.
        loadEffects(SlotInfo::EFF_SEVEN);
        
        CCFiniteTimeAction *actions = CCSequence::create(
                                                        _unitSeven.animate,
                                                        CCCallFuncN::create(this, callfuncN_selector(LAPlayEffect::menuCloseCallback)),
                                                        NULL
                                                        );
        this->addChild(_unitSeven.sprite, 1);
        _unitSeven.sprite->runAction( actions );
    }
    else if( SlotInfo::EFF_MISSION == effectType ){
        _heartBack = CCSprite::create("effect/eff_heart/back.png");
        assert(_heartBack);
        SystemConfig::setPosition(319, 462, _heartBack);
        _heartBack->retain();
        
        CCPoint pt;
        pt.setPoint(_heartBack->getPositionX(), _heartBack->getPositionY());
        _heartBack->setPositionX(_heartBack->getPositionX() + 1000 );
        CCMoveTo *moveActoin = CCMoveTo::create(0.4f, pt);
        
        // load effect.
        loadEffects(SlotInfo::EFF_HEART);
        
        CCFiniteTimeAction *actions = CCSequence::create(
                                                         moveActoin,
                                                         CCDelayTime::create(0.5),
                                                         CCCallFuncN::create(this, callfuncN_selector(LAPlayEffect::startHeartActoin)),
                                                         NULL
                                                         );
        this->addChild(_heartBack, 1);
        _heartBack->runAction( actions );
    }
    else if( SlotInfo::EFF_HEART == effectType){
        
        SND()->playEffect(SoundPath::path(SoundPath::ST_EFFECT_HEART));
        
        CCFiniteTimeAction *actions = CCSequence::create(
                                                         CCDelayTime::create(2.0),
                                                         CCCallFunc::create(this, callfunc_selector(LAPlayEffect::startDice)),
                                                         NULL
                                                         );
        this->runAction( actions );
        
        
    }
    else if( SlotInfo::EFF_POCKET3 == effectType
            || SlotInfo::EFF_POCKET4 == effectType
            || SlotInfo::EFF_POCKET5 == effectType
            || SlotInfo::EFF_POCKET_MIXED
            || SlotInfo::WHOLE_MADE_POCKET == wholeEffect )
    {
        SND()->playEffect(SoundPath::path(SoundPath::ST_EFFECT_HEART));
        
        particleTest();
        
        // load effect.
        loadEffects(SlotInfo::EFF_POCKET3);
        
        CCFiniteTimeAction *actions = CCSequence::create(
                                                         _unitPocket.animate,
                                                         CCDelayTime::create(3.0f),
                                                         CCCallFuncN::create(this, callfuncN_selector(LAPlayEffect::menuCloseCallback)),
                                                         NULL
                                                         );
        this->addChild(_unitPocket.sprite, 1);
        _unitPocket.sprite->runAction( actions );
    }
    else if( SlotInfo::WHOLE_MADE_FRUIT == wholeEffect ){
        SND()->playEffect(SoundPath::path(SoundPath::ST_EFFECT_FRUIT));
        
        particleTest();
        
        // load effect.
        loadEffects(SlotInfo::EFF_FRUIT);
        
        CCFiniteTimeAction *actions = CCSequence::create(
                                                         _unitFruit.animate,
                                                         CCDelayTime::create(3.0f),
                                                         CCCallFuncN::create(this, callfuncN_selector(LAPlayEffect::menuCloseCallback)),
                                                         NULL
                                                         );
        this->addChild(_unitFruit.sprite, 1);
        _unitFruit.sprite->runAction( actions );
    }
}

void LAPlayEffect::loadEffects(const SlotInfo::EFFECT_TYPE type)
{
    if( SlotInfo::EFF_SEVEN == type)
    {
        // seven effect...
        _unitSeven.animation = CCAnimation::create();
        _unitSeven.animation->setDelayPerUnit( 0.1f );
        _unitSeven.animation->setLoops(5);
        
        _unitSeven.animation -> addSpriteFrameWithFileName( "effect/eff_777/eff_777_1.png" );
        _unitSeven.animation -> addSpriteFrameWithFileName( "effect/eff_777/eff_777_2.png" );
        _unitSeven.animation -> addSpriteFrameWithFileName( "effect/eff_777/eff_777_3.png" );
        _unitSeven.animation -> addSpriteFrameWithFileName( "effect/eff_777/eff_777_4.png" );
        _unitSeven.animation -> addSpriteFrameWithFileName( "effect/eff_777/eff_777_5.png" );
        _unitSeven.animation -> addSpriteFrameWithFileName( "effect/eff_777/eff_777_6.png" );
        _unitSeven.animation -> addSpriteFrameWithFileName( "effect/eff_777/eff_777_7.png" );
        _unitSeven.animation -> addSpriteFrameWithFileName( "effect/eff_777/eff_777_8.png" );
        
        _unitSeven.animate = CCAnimate::create( _unitSeven.animation );
        _unitSeven.sprite = CCSprite::create( "effect/eff_777/eff_777_1.png" );
        SystemConfig::setPosition( 319, 501, _unitSeven.sprite);
        
        _unitSeven.animate->retain();
        _unitSeven.animation->retain();
        _unitSeven.sprite->retain();
    }
    else if( SlotInfo::EFF_BELL == type)
    {
        // bell effect
        _unitBell.animation = CCAnimation::create();
        _unitBell.animation->setDelayPerUnit( 0.1f );
        _unitBell.animation->setLoops(8);
        
        _unitBell.animation -> addSpriteFrameWithFileName( "effect/eff_bell/eff_bell_1.png" );
        _unitBell.animation -> addSpriteFrameWithFileName( "effect/eff_bell/eff_bell_2.png" );
        _unitBell.animation -> addSpriteFrameWithFileName( "effect/eff_bell/eff_bell_3.png" );
        _unitBell.animation -> addSpriteFrameWithFileName( "effect/eff_bell/eff_bell_4.png" );
        _unitBell.animation -> addSpriteFrameWithFileName( "effect/eff_bell/eff_bell_5.png" );
        _unitBell.animation -> addSpriteFrameWithFileName( "effect/eff_bell/eff_bell_6.png" );
        
        _unitBell.animate = CCAnimate::create( _unitBell.animation );
        _unitBell.sprite = CCSprite::create( "effect/eff_bell/eff_bell_1.png" );
        SystemConfig::setPosition( 319, 488, _unitBell.sprite);
        
        _unitBell.animate->retain();
        _unitBell.animation->retain();
        _unitBell.sprite->retain();
    }
    else if(SlotInfo::EFF_HEART == type)
    {
        // heart effect
        _unitHeart.animation = CCAnimation::create();
        _unitHeart.animation->setDelayPerUnit( 0.1f );
        _unitHeart.animation->setLoops(5);
        
        _unitHeart.animation -> addSpriteFrameWithFileName( "effect/eff_heart/ani_1.png" );
        _unitHeart.animation -> addSpriteFrameWithFileName( "effect/eff_heart/ani_2.png" );
        _unitHeart.animation -> addSpriteFrameWithFileName( "effect/eff_heart/ani_3.png" );
        _unitHeart.animation -> addSpriteFrameWithFileName( "effect/eff_heart/ani_4.png" );
        _unitHeart.animation -> addSpriteFrameWithFileName( "effect/eff_heart/ani_5.png" );
        _unitHeart.animation -> addSpriteFrameWithFileName( "effect/eff_heart/ani_6.png" );
        _unitHeart.animation -> addSpriteFrameWithFileName( "effect/eff_heart/ani_7.png" );
        _unitHeart.animation -> addSpriteFrameWithFileName( "effect/eff_heart/ani_8.png" );
        
        _unitHeart.animate = CCAnimate::create( _unitHeart.animation );
        _unitHeart.sprite = CCSprite::create( "effect/eff_heart/ani_1.png" );
        SystemConfig::setPosition( 433, 492, _unitHeart.sprite);
        
        _unitHeart.animate->retain();
        _unitHeart.animation->retain();
        _unitHeart.sprite->retain();
    }
    else if( SlotInfo::EFF_FRUIT == type)
    {
        // fruit effect...
        _unitFruit.animation = CCAnimation::create();
        _unitFruit.animation->setDelayPerUnit( 0.1f );
        _unitFruit.animation->setLoops(1);
        
        _unitFruit.animation -> addSpriteFrameWithFileName( "effect/eff_fruit/eff_all_fruits_1.png" );
        _unitFruit.animation -> addSpriteFrameWithFileName( "effect/eff_fruit/eff_all_fruits_2.png" );
        _unitFruit.animation -> addSpriteFrameWithFileName( "effect/eff_fruit/eff_all_fruits_3.png" );
        _unitFruit.animation -> addSpriteFrameWithFileName( "effect/eff_fruit/eff_all_fruits_4.png" );
        _unitFruit.animation -> addSpriteFrameWithFileName( "effect/eff_fruit/eff_all_fruits_5.png" );
        _unitFruit.animation -> addSpriteFrameWithFileName( "effect/eff_fruit/eff_all_fruits_6.png" );
        _unitFruit.animation -> addSpriteFrameWithFileName( "effect/eff_fruit/eff_all_fruits_7.png" );
        _unitFruit.animation -> addSpriteFrameWithFileName( "effect/eff_fruit/eff_all_fruits_8.png" );
                
        _unitFruit.animate = CCAnimate::create( _unitFruit.animation );
        _unitFruit.sprite = CCSprite::create( "effect/eff_fruit/eff_all_fruits_1.png" );
        SystemConfig::setPosition( 320, 480, _unitFruit.sprite);
        
        _unitFruit.animate->retain();
        _unitFruit.animation->retain();
        _unitFruit.sprite->retain();
    }
    else if( SlotInfo::EFF_POCKET3 == type)
    {
        // fruit effect...
        _unitPocket.animation = CCAnimation::create();
        _unitPocket.animation->setDelayPerUnit( 0.1f );
        _unitPocket.animation->setLoops(1);
        
        _unitPocket.animation -> addSpriteFrameWithFileName( "effect/eff_pocket/eff_goldpot_1.png" );
        _unitPocket.animation -> addSpriteFrameWithFileName( "effect/eff_pocket/eff_goldpot_2.png" );
        _unitPocket.animation -> addSpriteFrameWithFileName( "effect/eff_pocket/eff_goldpot_3.png" );
        _unitPocket.animation -> addSpriteFrameWithFileName( "effect/eff_pocket/eff_goldpot_4.png" );
        _unitPocket.animation -> addSpriteFrameWithFileName( "effect/eff_pocket/eff_goldpot_5.png" );
        _unitPocket.animation -> addSpriteFrameWithFileName( "effect/eff_pocket/eff_goldpot_6.png" );
        _unitPocket.animation -> addSpriteFrameWithFileName( "effect/eff_pocket/eff_goldpot_7.png" );
        _unitPocket.animation -> addSpriteFrameWithFileName( "effect/eff_pocket/eff_goldpot_8.png" );
        
        _unitPocket.animate = CCAnimate::create( _unitPocket.animation );
        _unitPocket.sprite = CCSprite::create( "effect/eff_pocket/eff_goldpot_1.png" );
        SystemConfig::setPosition( 320, 480, _unitPocket.sprite);
        
        _unitPocket.animate->retain();
        _unitPocket.animation->retain();
        _unitPocket.sprite->retain();
    }
}

void LAPlayEffect::loadEffects()
{
    loadEffects(SlotInfo::EFF_SEVEN);
    loadEffects(SlotInfo::EFF_BELL);
    loadEffects(SlotInfo::EFF_HEART);
    loadEffects(SlotInfo::EFF_FRUIT);
    loadEffects(SlotInfo::EFF_POCKET3);
}

void LAPlayEffect::menuCloseCallback(CCObject* pSender)
{
    struct Releaser
    {
        Releaser(EffectUnit &unit)
        {
            CC_SAFE_RELEASE_NULL(unit.animate);
            CC_SAFE_RELEASE_NULL(unit.animation);
            CC_SAFE_RELEASE_NULL(unit.sprite);
        }
    };
        
    if( _unitSeven.sprite == pSender ){
        this->removeChild(_unitSeven.sprite, false);
        Releaser    u1(_unitSeven);
    }else if( _unitBell.sprite == pSender){
        this->removeChild(_unitBell.sprite, false);
        Releaser    u2(_unitBell);
    }else if( _unitHeart.sprite == pSender){
        this->removeChild(_unitHeart.sprite, false);
        this->removeChild(_heartMentions, false);
        CC_SAFE_RELEASE_NULL(_heartMentions);
        this->removeChild(_heartBack, false);
        CC_SAFE_RELEASE_NULL(_heartBack);
        Releaser    u3(_unitHeart);
    }else if( _unitFruit.sprite == pSender){
        this->removeChild(_unitFruit.sprite, false);
        Releaser    u4(_unitFruit);
    }else if( _unitPocket.sprite == pSender){
        this->removeChild(_unitPocket.sprite, false);
        Releaser    u4(_unitPocket);
    }
    

    gPlaySlot->closeEffectLayer();
}

void LAPlayEffect::startHeartActoin(CCObject* pSender)
{
    CCFiniteTimeAction *actions = CCSequence::create(
                                                     _unitHeart.animate,
                                                     CCCallFuncN::create(this, callfuncN_selector(LAPlayEffect::menuCloseCallback)),
                                                     NULL
                                                     );
    this->addChild(_unitHeart.sprite, 1);
    _unitHeart.sprite->runAction( actions );
    
    
    // 미션 멘트
    _heartMentions = CCSprite::create("effect/eff_heart/mission.png");
    assert(_heartMentions);
    SystemConfig::setPosition(184, 575, _heartMentions);
    this->addChild(_heartMentions, 1);
    _heartMentions->retain();
}

void LAPlayEffect::startDice()
{
    CCScene *s = SCDice::create();
    CCTransitionSlideInR *tr = CCTransitionSlideInR::create(0.4f, s);
    CCDirector::sharedDirector()->pushScene(tr);
}
