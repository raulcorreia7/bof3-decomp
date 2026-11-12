#ifndef WORLD04_FAMILY_H
#define WORLD04_FAMILY_H

#include "sys/gameui.h"
#include "overlays/area/area.h"
#include "overlays/area/Message_ShowParty.h"
#include "overlays/area/WorldAreaRequest.h"

/* Message ids of the faerie village text, used by area175 through area185. */
enum {
    FAIRY_MESSAGE_MUSICIAN_THANKS               = 0x5A,
    FAIRY_MESSAGE_COPY_SHOP_DECLINED            = 0x5F,
    FAIRY_MESSAGE_COPY_SHOP_WORKING             = 0x62,
    FAIRY_MESSAGE_COPY_SHOP_CHOOSE_OTHER        = 0x63,
    FAIRY_MESSAGE_CASINO_NOT_PLAYING            = 0x6E,
    FAIRY_MESSAGE_HIGH_LOW_RULES_KNOWN          = 0x6F,
    FAIRY_MESSAGE_HIGH_LOW_RULES                = 0x70,
    FAIRY_MESSAGE_HIGH_LOW_DECLINED             = 0x72,
    FAIRY_MESSAGE_HIGH_LOW_QUIT                 = 0x77,
    FAIRY_MESSAGE_HIGH_LOW_PLAY_AGAIN           = 0x78,
    FAIRY_MESSAGE_CASINO_CHOOSE_GAME            = 0x7A,
    FAIRY_MESSAGE_NUMBERS_DECLINED              = 0x7B,
    FAIRY_MESSAGE_CASINO_NOT_ENOUGH_ZENNY       = 0x7C,
    FAIRY_MESSAGE_NUMBERS_RULES_NEEDED          = 0x7D,
    FAIRY_MESSAGE_NUMBERS_RULES                 = 0x7E,
    FAIRY_MESSAGE_NUMBERS_START                 = 0x7F,
    FAIRY_MESSAGE_PICK_NUMBERS_DECLINED         = 0x88,
    FAIRY_MESSAGE_PICK_NUMBERS_RULES_REMEMBERED = 0x89,
    FAIRY_MESSAGE_PICK_NUMBERS_RULES            = 0x8A,
    FAIRY_MESSAGE_FORTUNE_TELLER_CONFIRMED      = 0x9F,
    FAIRY_MESSAGE_FORTUNE_TELLER_REFUTED        = 0xA0,
    FAIRY_MESSAGE_NICKNAME_PICK_FAIRY           = 0xEF,
    FAIRY_MESSAGE_NICKNAME_GOODBYE              = 0xF7,
    FAIRY_MESSAGE_HELP_MENU                     = 0xF8,
    FAIRY_MESSAGE_HELP_UP_TO_YOU                = 0xF9,
    FAIRY_MESSAGE_HELP_JOBS                     = 0xFA,
    FAIRY_MESSAGE_HELP_ASSIGNING                = 0xFB,
    FAIRY_MESSAGE_HELP_ABILITIES                = 0xFC,
    FAIRY_MESSAGE_HELP_HOUSING                  = 0xFD,
    FAIRY_MESSAGE_SINGER_GOODBYE                = 0x2A1,
};

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT    0xFF

/* The work-window byte offset, row stride and row count this overlay clears. */
#define SCRATCH_COLUMN_COUNT  8
#define SCRATCH_COLUMN_OFFSET 0
#define SCRATCH_COLUMN_STRIDE 0x18

extern u16 D_80144F54;
extern u8  D_801455C7;
/* The battle record rows whose first byte is a slot tag. */
/* The global state byte the area update gates on. */
extern u8  D_801F2944;
extern u8  D_801F2945;
extern u8  D_801F294C;
extern u8  D_801F294D;
extern u8  D_801F294E;
extern u8  D_801F294F;
/* The payload's handler pointers, then its entry coordinate pairs at 0x14. */
extern u8  D_801F3418[];

/* The scenario state byte the request writes. */

void Fairy_InitVillage(void);
/* The overlay's frame update; the bounds checks and origin step run it. */
/* func_801F30D4 (area158), func_801F30D4 (area160), func_801F30D4 (area161), func_801F30D4 (area162), func_801F30D4
   (area163), func_801F30D4 (area164), func_801F30D4 (area165), func_801F30D4 (area166), func_801F30E8 (area169),
   func_801F3108 (area157), func_801F313C (area147), func_801F31AC (area148), func_801F31BC (area167), func_801F347C
   (area152), func_801F34EC (area033), func_801F3528 (area151), func_801F35B8 (area016), func_801F35B8 (area045),
   func_801F35BC (area115), func_801F35D0 (area121), func_801F35EC (area087), func_801F35F0 (area065), func_801F367C
   (area104), func_801F3914 (area168), func_801F3958 (area174), func_801F3F84 (area139), func_801F40F0 (area170),
   func_801F411C (area088), func_801F45E0 (area173) */
void Area_Update();

/* Reset the answer message request, then copy the menu selection into the
 * image's byte. */
static inline void World04_StoreAnswerChoice(u8* target) {
    MESSAGE_REQUEST_CLEAR();
    *target = g_MessageChoice;
}

/* One cell of a payload's data tables: `offset` is the table's byte offset and
 * `index` the byte offset of the row. */
#define WORLD04_ENTRY_TABLE(payload, type, offset, index) (*(type*)&(payload)[(offset) + (index)])

/* A trigger rectangle in tile units. */
typedef struct TriggerBox {
    u8 x0;
    u8 y0;
    u8 x1;
    u8 y1;
    u8 unk_04;
} TriggerBox;

/* The index of the first of the two boxes the party member stands in, or 0xFF. */
#define WORLD04_FIND_TRIGGER_BOX(member, boxes)                                                                                     \
    do {                                                                                                                            \
        s32 i;                                                                                                                      \
        s32 x = g_Game.members[(member)].pos.x.fixed;                                                                               \
        s32 y = g_Game.members[(member)].pos.y.fixed;                                                                               \
        for (i = 0; i < 2; i++) {                                                                                                   \
            if (x < ((boxes)[i].x0 << 16) || x > ((boxes)[i].x1 << 16) || y < ((boxes)[i].y0 << 16) || y > ((boxes)[i].y1 << 16)) { \
                continue;                                                                                                           \
            }                                                                                                                       \
            return i;                                                                                                               \
        }                                                                                                                           \
        return 0xFF;                                                                                                                \
    } while (0)

#endif
