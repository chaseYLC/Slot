//
//  LAPlayEffect.h
//  gameTest
//
//  Created by Chase on 12. 11. 11..
//  Copyright (c) 2012년 넥스테일. All rights reserved.
//

#ifndef __gameTest__LAPlayEffect__
#define __gameTest__LAPlayEffect__

#include "cocos2d.h"
#include "SlotInfo.h"

using namespace cocos2d;

class LAPlayEffect : public cocos2d::CCLayerColor
{
public:
    struct EffectUnit
    {
        EffectUnit()
        {
            animation = NULL;
            animate = NULL;
            sprite = NULL;
        }
        
        CCAnimation *animation;
        CCAnimate *animate;
        CCSprite *sprite;
    };

    CCParticleSystemQuad* particleSystem[2];
public:
    LAPlayEffect()
    {
        _heartMentions = NULL;
        _heartBack = NULL;
    };
    
    virtual ~LAPlayEffect();
    bool init();
    CREATE_FUNC(LAPlayEffect);
    
    virtual void onEnter();
    virtual void onExit();
    
private:
    void loadEffects();
    void loadEffects(const SlotInfo::EFFECT_TYPE type);
    void menuCloseCallback(CCObject* pSender);
    void startHeartActoin(CCObject* pSender);

    void startDice();
    
    void particleTest();
    
public:
    void playEffect(SlotInfo::EFFECT_TYPE const effectType,
                    const SlotInfo::WHOLE_MADE wholeEffect);

    
private:
    EffectUnit _unitSeven;
    EffectUnit _unitBell;
    EffectUnit _unitFruit;
    EffectUnit _unitPocket;

    EffectUnit _unitHeart;
    CCSprite *_heartBack;
    CCSprite *_heartMentions;
};



#endif /* defined(__gameTest__LAPlayEffect__) */
