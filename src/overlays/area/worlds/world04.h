#ifndef WORLD04_FAMILY_H
#define WORLD04_FAMILY_H

#include "menu/gameui.h"
#include "overlays/area/area.h"
#include "overlays/area/shared/UI_MessageShowParty.h"
#include "overlays/area/shared/WorldAreaRequest.h"

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT    0xFF

/* The work-window byte offset, row stride and row count this overlay clears. */
#define SCRATCH_COLUMN_COUNT  8
#define SCRATCH_COLUMN_OFFSET 0
#define SCRATCH_COLUMN_STRIDE 0x18

/* g_SaveData.desert.clock and .days, and g_SaveData.return_point.pending and .facing, as scalars. */
extern u16 D_80144F54;
extern u8  D_80144F56;
extern s8  D_8014504A;
extern s8  D_8014504B;
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

/* Restores the party after a battle and copies it in field order into the battle records. */
/* func_801C16B8 */
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
    *target = g_UiMessageChoice;
}

/* A trigger rectangle in tile units. */
typedef struct TriggerBox {
    u8 x0;
    u8 y0;
    u8 x1;
    u8 y1;
    u8 unk_04;
} TriggerBox;

ASSERT_SIZE(TriggerBox, 0x5);

#endif
