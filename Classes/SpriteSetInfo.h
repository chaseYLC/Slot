//
//  SpriteSetInfo.h
//  gameTest
//
//  Created by Chase on 12. 11. 4..
//  Copyright (c) 2012년 넥스테일. All rights reserved.
//

#ifndef __gameTest__SpriteSetInfo__
#define __gameTest__SpriteSetInfo__

#include <cocos2d.h>
#include "SlotInfo.h"
#include "SystemConfig.h"

struct SpriteSetInfo
{
    cocos2d::CCArray *sprSet;       // 세로 라인 스프라이트
    int slots[ 6 /*SlotSpace::LOAD_ROWS*/ ];
    
    int currentOffsetIndex;
    int currentBottomIndex;
    int accMove;
    bool spining;
    int waitFrameCnt;
    bool adjustedBox;
    int shuffleCnt;

    
    SpriteSetInfo()
    {
        sprSet = new cocos2d::CCArray;
        currentBottomIndex = 0;
        accMove = 0;
        spining = false;
        waitFrameCnt = 0;
        shuffleCnt = 0;
        memset(slots, 0, sizeof(slots));
    }
    
    ~SpriteSetInfo()
    {
        if(sprSet)
        {
            sprSet->release();
            sprSet = NULL;
        }
    }
    
    void Clear()
    {
        currentOffsetIndex = 0;
        
        accMove = 0;
        spining = false;
        waitFrameCnt = 0;
        adjustedBox = false;
        shuffleCnt = 0;
    }
    
    //  Pos ...
    //    0 1 2
    //    3 4 5
    //    6 7 8
    cocos2d::CCSprite * getSpriteByStandPosition(int const pos)
    {
        assert( 6 == SlotSpace::LOAD_ROWS );
        
        
        
    }
};


#endif /* defined(__gameTest__SpriteSetInfo__) */
