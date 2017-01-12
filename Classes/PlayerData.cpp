//
//  PlayerData.cpp
//  gameTest
//
//  Created by Chase on 12. 11. 11..
//  Copyright (c) 2012년 넥스테일. All rights reserved.
//

#include "PlayerData.h"

///class LAPlaySlot : public cocos2d::CCLayerColor


namespace PlayerData{
    int coin;
    int diamond;
    
    bool unlockedThemes[MAX_THEMES];
    int clothesLv[MAX_THEMES];  // 0 부터 시작.
    int currentGirlNo;  // 0 부터 시작
    
    

    ////
    bool restartBGM = true;
    int gameCnt = 0;
    int slotBox = -1; // SlotInfo's enumeration
    
    //
    int dicePos = 0;
    int currentBet = 1;
    int remainBell = 5;
    int winsFirst = 0;
    int winsFinal = 0;
    
    bool waitWins = false;
    bool isMade = false;
    
    bool hitGrade[20];
};

namespace GameData {

    int menuMode = 0;       // 0 : 테마, 1 : 갤러리, 2 : 인갤러리
    int currentScene;
    

    const int BET_MIN[MAX_THEMES] = {1,2,4,8};
    const int BET_MAX[MAX_THEMES] = {16,32,64,128};
};

namespace SoundPath{
    
const char* path(const SOUND_TYPE type)
{
    switch (type) {
        case ST_SELECT_NORMAL:
            return "snd/suc.mp3";
        case ST_SELECT_FAILED:
            return "snd/buttonPress4.mp3";
            
        case ST_MENU_GIRLS_MOVED:
            return "snd/camera_shutter.mp3";
            
        case ST_GALLERY_SELECTED:
            return "snd/turnup.mp3";
            
        case ST_GAME_BUTTON_CLICK:
            return "snd/main_spinstop.mp3";
        case ST_GAME_SPIN_CLICK:
        case ST_GAME_HOLD_CLICK:
            return "snd/buttonPress1.mp3";
        case ST_GAME_GETWINS:
            return "snd/getWins.mp3";
            
        case ST_LINE_MADE:
            return "snd/magic_bell_3.mp3";
        case ST_LINE_CROSS:
            return "snd/line.mp3";
            
        case ST_GET_COIN_BY_TOUCHBONUS:
            return "snd/gold_coins.mp3";
            
        case ST_SPIN_BG:
            return "snd/frantic.mp3";
        case ST_SPIN_LINESTART:
            return "snd/eff_slotstart.mp3";
        case ST_SPIN_LINESTOP:
            return "snd/main_spinstop.mp3";
            
        case ST_EFFECT_BELL:
            return "snd/bell5.mp3";
        case ST_EFFECT_SEVEN:
            return "snd/wow.mp3";
        case ST_EFFECT_HEART:
            return "snd/buttonPress3.mp3";
        case ST_EFFECT_POKET:
            return "snd/shot3.mp3";
        case ST_EFFECT_FRUIT:
            return "snd/machine_gun_fire.mp3";
            
        case ST_MISSION_START:
            return "snd/buttonPress3.mp3";
        case ST_BONUSGAME_START:
            return "snd/alert.mp3";
            
        case ST_MOAN_1:
            return "snd/sex_moan_female.mp3";
        case ST_MOAN_2:
            return "snd/moan1.mp3";
        case ST_MOAN_3:
            return "snd/moan2.mp3";
        case ST_MOAN_4:
            return "snd/moan3.mp3";
            
        case ST_DICE_CURSOR:
            return "snd/line.mp3";
        case ST_DICE_DICING:
            return "snd/2_dice_throw_on_table.mp3";
        case ST_DICE_FAILED:
            return "snd/female_grunt_could_be_in_pain_or_anger.mp3";
        case ST_DICE_LIFE:
            return "snd/magic_bell_3.mp3";
        case ST_DICE_HIGHREWARD:
            return "snd/female_says_ooo_reaction.mp3";
        case ST_DICE_REWARD:
            return "snd/slotMade.mp3";
            
        case ST_HIGHLOW_START:
            return "snd/buttonPress2.mp3";
        case ST_HIGHLOW_STAND:
            return "snd/buttonPress1.mp3";
        case ST_HIGHLOW_RESULTING:
            return "snd/line.mp3";
        case ST_HIGHLOW_SUCCESSED:
            return "snd/buttonPress2.mp3";
            
        case ST_BG_START:
            return "snd/music3.mp3";
        case ST_BG_BONUS:
            return "snd/funky_drum_and_bass.mp3";
        case ST_BG_DICE:
            return "snd/150_drum_loop.mp3";
        case ST_BG_GALLERY:
            return "snd/down_by_the_lake_warm_sincere_acoustic_music.mp3";
        case ST_BG_THEME:
            return "snd/music5.mp3";
        case ST_BG_HIGHLOW:
            return "snd/techno_house_break_loop_with_drums_and_bass_120_bpm.mp3";            
            
        default:
            break;
    }
    
    return NULL;
}
    
};
