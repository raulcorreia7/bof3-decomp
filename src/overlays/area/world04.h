#ifndef WORLD04_FAMILY_H
#define WORLD04_FAMILY_H

/* Declarations shared by two or more world04 images; an image header that
 * reads one includes this file. */

#include "sys/gameui.h"
#include "overlays/area/area.h"
#include "overlays/area/Message_ShowParty.h"
#include "overlays/area/WorldAreaRequest.h"

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT    0xFF

/* The work-window byte offset, row stride and row count this overlay clears. */
#define SCRATCH_COLUMN_OFFSET 0
#define SCRATCH_COLUMN_COUNT  8
#define SCRATCH_COLUMN_STRIDE 0x18

extern u16 D_80144F54;
extern u8  D_801455C7;
/* The battle record rows whose first byte is a slot tag. */
extern u8  D_80145F09[][BATTLE_PARTY_STRIDE];
/* The global state byte the area update gates on. */
extern u8  D_801F2944;
extern u8  D_801F2945;
extern u8  D_801F294C;
extern u8  D_801F294D;
extern u8  D_801F294E;
extern u8  D_801F294F;
extern u8  D_801F3418[];

/* The scenario state byte the request writes. */

void Fairy_VillageInit(void);
/* The overlay's frame update; the bounds checks and origin step run it. */
/* func_801F30D4 (area158), func_801F30D4 (area160), func_801F30D4 (area161), func_801F30D4 (area162), func_801F30D4 (area163), func_801F30D4 (area164), func_801F30D4 (area165), func_801F30D4 (area166), func_801F30E8 (area169), func_801F3108 (area157), func_801F313C (area147), func_801F31AC (area148), func_801F31BC (area167), func_801F347C (area152), func_801F34EC (area033), func_801F3528 (area151), func_801F35B8 (area016), func_801F35B8 (area045), func_801F35BC (area115), func_801F35D0 (area121), func_801F35EC (area087), func_801F35F0 (area065), func_801F367C (area104), func_801F3914 (area168), func_801F3958 (area174), func_801F3F84 (area139), func_801F40F0 (area170), func_801F411C (area088), func_801F45E0 (area173) */
void Area_Update();

/* Reset the answer message request, then copy the menu selection into the
 * image's byte. */
static inline void World04_ResetAnswerAndCopySelection(u8* target) {
    MESSAGE_REQUEST_CLEAR();
    *target = D_801490C7;
}

#endif
