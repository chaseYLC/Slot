#ifndef __gameTest__SlotInfo__
#define __gameTest__SlotInfo__

class SlotInfo
{
public:
    enum
    {
        BOX_SEVEN = 0,   // 배열 인덱스로 사용합니다. 값을 변경하지 마세요.
        BOX_BANANA,
        BOX_CHERRY,
        BOX_GRAPE,
        BOX_LEMON,
        BOX_POCKETBLUE,
        BOX_POCKETRED,
        BOX_POCKETYELLOW,
        BOX_HEART,
        BOX_NORMALBELL,
        BOX_SUPERBELL,
        BOX_EMPTY,
                
        BOX_MAX
    };
    
    enum EFFECT_TYPE
    {
        EFF_NONE = 0,
        EFF_NORMAL_LINE = 1,
        EFF_COIN,
        EFF_BELL,
        EFF_SEVEN,
        EFF_HEART,
        EFF_POCKET3,
        EFF_POCKET4,
        EFF_POCKET5,
        EFF_MISSION,
        EFF_BONUS_LINE,
        EFF_FRUIT,
        EFF_POCKET_MIXED,
    };
    
    enum WHOLE_MADE
    {
        WHOLE_MADE_NONE = 0,
        
        WHOLE_MADE_SEVEN = 1,
        WHOLE_MADE_SEVEN_CROSS = 2,
        WHOLE_MADE_SEVEN_TWO = 3,
        
        
        WHOLE_MADE_POCKET = 4,
        WHOLE_MADE_FRUIT = 5,
    };
};

namespace MADE_SLOT
{
    enum
    {
        CHERRY_2 = 2,           // 체리 한라인에 2개
        NORMAL_3 = 3,           // 잡박스 한라인에 3개
        POCKET = 3,             // 주머니류 한라인에 3개
        POCKET_LINE = 4,        // 주머니류 한라인 통일
        
        
        HEART = 3,              // 하느 한라인에 3개
        
        
        FRUIT_ALL = 10,              // 화면 전부 과일
        POCKET_ALL = 10,             // 화면 전부 돈주머니
        
        BELL = 10,              // 슈퍼벨, 일반벨 섞에서 라인에 3개
        BELL_THREE = 12,         // 일반벨 한라인에 3개
        BELL_SUPER_THREE = 20,  // 슈퍼벨 한라인에 3개
        
        SEVEN_TWO = 30,              // 세븐이 한 화면에 2개 이상
        SEVEN_MADE = 50,              // 세븐으로 한 라인
        SEVEN_CROSS = 100,             // 세븐으로 십자
        SEVEN_ALL = 500,                // 전 화면 세븐
    };
}

class LAPlaySlot;
extern LAPlaySlot *gPlaySlot;

class PlayLayer;
extern PlayLayer *gPlayLayer;


class PlayScene;
extern PlayScene *gPlayScene;

class ThemeLayer;
extern ThemeLayer *gThemeLayer;




#endif /* defined(__gameTest__SlotInfo__) */
