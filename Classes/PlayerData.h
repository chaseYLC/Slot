#ifndef __gameTest__PlayerData__
#define __gameTest__PlayerData__

#include <iostream>

#define EXP_GUAGE_WIDTH (622.0f)
#define DICE_SIZE 28

#define USAGES_FOR_DICE_CONTINUE        5

namespace PlayerData{
    extern int coin;
    extern int diamond;
   
    extern bool restartBGM;
    extern int gameCnt;
    extern int slotBox; // SlotInfo's enumeration
    
    extern int dicePos;
    extern int currentBet;
    extern int remainBell;
    

    // 스핀의 결과로 얻은 돈(win). win 금액이 하이로우나 부루마불 등의 미니게임의 베팅금액이 됩니다.
    // 미니게임 진입 이전과 후의 wins 금액의 차이를 기록하기 위해 winsFirst, winsFinal 2개의 변수를 두었습니다.
    extern int winsFirst;
    extern int winsFinal;

    
    // 유저는 획득한 wins를 가지고 미니게임을하여 불릴것인지 wins를 그대로 먹고 슬롯을 계속 돌릴것인지 정해야 합니다.
    // 설정 : 슬롯을 메이시 시켰을 때
    // 해제 : wins 를 먹었을 때
    //       하이로우게임 실패 시
    extern bool waitWins;

    // 슬롯 결과. 성패 여부. 한 스핀 이후마다 갱신됩니다.
    extern bool isMade;
    
    // 게임 카운트에 따른 각 등급별로 한방씩 터뜨려줬는지 여부.
    extern bool hitGrade[20];
};

namespace GameData {

    enum {
        CURRENT_TEMP_GIRLS = 8,
    };
    
    enum
    {
        SCENE_MAINMENU,
        SCENE_GALLERY,
        SCENE_NUDE,
        SCENE_SHOP,
        SCENE_GAME,
    };

    extern int menuMode;       // 0 : 테마, 1 : 갤러리, 2: 인갤러리
    extern int currentScene;

    extern const int BET_MIN[MAX_THEMES];
    extern const int BET_MAX[MAX_THEMES];
};

namespace SoundPath{

    enum SOUND_TYPE
    {
        ST_SELECT_NORMAL,           // 메뉴 선택 일반
        ST_SELECT_FAILED,           // 메뉴 선택 실패(언락된 메뉴 선택)
        
        ST_MENU_GIRLS_MOVED,        // 메뉴화면에 각 여자들 등장음
        
        ST_GALLERY_SELECTED,        // 갤러리에서 여자 선택음
        
        ST_GAME_BUTTON_CLICK,       // 게임에서 버튼(베팅, 맥스베팅 등) 클릭
        ST_GAME_SPIN_CLICK,         // 게임에서 스핀버튼 클릭
        ST_GAME_HOLD_CLICK,         // 게임에서 홀드버튼 클릭
        ST_GAME_GETWINS,            // 게임에서 윈즈금액 획득
        
        ST_LINE_CROSS,              // 메이드시 메이드된 라인을 가로지며 나는 소리
        ST_LINE_MADE,               // 슬롯 라인이 메이드
        ST_GET_COIN_BY_TOUCHBONUS,  // 보너스 코인 획득
        
        ST_SPIN_BG,                 // 슬롯이 돌아가는동안의 배경음
        ST_SPIN_LINESTART,          // 슬롯의 라인이 회전하기 시작할때 각 라인별 시작음
        ST_SPIN_LINESTOP,           // 슬롯의 라인이 회전을 마칠때의 각 라인별 종료음
        
        ST_EFFECT_BELL,             // 이펙트 - 종
        ST_EFFECT_SEVEN,            // 이펙트 - 7
        ST_EFFECT_HEART,            // 이펙트 - 하트
        ST_EFFECT_POKET,            // 이펙트 - 돈주머니
        ST_EFFECT_FRUIT,            // 이펙트 - 과일
        
        ST_MISSION_START,           // 미션 발동
        ST_BONUSGAME_START,         // 보너스게임(돈주머니) 발동
        
        ST_MOAN_1,                  // 신음 1
        ST_MOAN_2,
        ST_MOAN_3,
        ST_MOAN_4,
        
        ST_DICE_CURSOR,             // 주사위게임 커서 움직일때
        ST_DICE_DICING,             // 주사위게임 주사위 굴러가는 소리
        ST_DICE_FAILED,             // 주사위게임 꽝 나왔을때
        ST_DICE_LIFE,               // 주사위게임 '한번더' 나왔을때
        ST_DICE_HIGHREWARD,         // 주사위게임 고배당 나왔을 때
        ST_DICE_REWARD,             // 주사위게임 일반배당 나왔을 때
        
        ST_HIGHLOW_START,           // 하이로우 시작
        ST_HIGHLOW_STAND,           // 하이로우 기준숫자 셔플
        ST_HIGHLOW_RESULTING,       // 하이로우 결과숫자 셔플
        ST_HIGHLOW_SUCCESSED,       // 하이로우 성공
        
        
        ST_BG_START = 1000,         // 앱 시작 배경음
        ST_BG_BONUS,                // 보너스 게임 배경
        ST_BG_DICE,                 // 주사위 게임 배경
        ST_BG_GALLERY,              // 갤러리 배경
        ST_BG_THEME,                // 테마 배경
        ST_BG_HIGHLOW,              // 하이로우 배경
    };
    
    const char* path(const SOUND_TYPE type);
};

#endif /* defined(__gameTest__PlayerData__) */