#ifndef WORLD03_FAMILY_H
#define WORLD03_FAMILY_H

#include "overlays/area/area.h"
#include "overlays/area/Message_ShowParty.h"
#include "overlays/area/WorldAreaRequest.h"

extern u16 D_80146876;

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x2E
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x10

/* The work-window byte offset and row stride this overlay clears. */
#define SCRATCH_COLUMN_OFFSET    0
#define SCRATCH_COLUMN_STRIDE    0x28

/* One 0x28-byte row of the area work window as the world03 sprites read it:
 * area125 writes the size at +0x04 and the projected origin at +0x08
 * (func_801F31B0), area134 draws the same cells (func_801F46EC). The
 * AreaSprite in AreaSprite.h is another view of the window, used by world00
 * to world02: it names +0x04 as its origin. */
typedef struct AreaSprite {
    u8       unk_00[3];
    u8       flags_03;  /* the shade of the sprite */
    u16      half_size; /* the projected half-size */
    u8       unk_06[2];
    Point2l origin;
    s32      unk_10;
    s32      unk_14;
    s32      unk_18;
    s32      unk_1C;
    s32      unk_20;
    s32      unk_24;
} AreaSprite;

ASSERT_SIZE(AreaSprite, 0x28);
ASSERT_OFFSET(AreaSprite, flags_03, 0x03);
ASSERT_OFFSET(AreaSprite, half_size, 0x04);
ASSERT_OFFSET(AreaSprite, origin, 0x08);

/* The global state byte the area update gates on. */

/* The scenario state byte the request writes. */
/* The actor-record byte the copy reads. */
/* The battle record rows whose first byte is a slot tag. */

/* The overlay's frame update; the bounds checks and origin step run it. */
/* func_801F30D4 (area158), func_801F30D4 (area160), func_801F30D4 (area161), func_801F30D4 (area162), func_801F30D4
   (area163), func_801F30D4 (area164), func_801F30D4 (area165), func_801F30D4 (area166), func_801F30E8 (area169),
   func_801F3108 (area157), func_801F313C (area147), func_801F31AC (area148), func_801F31BC (area167), func_801F347C
   (area152), func_801F34EC (area033), func_801F3528 (area151), func_801F35B8 (area016), func_801F35B8 (area045),
   func_801F35BC (area115), func_801F35D0 (area121), func_801F35EC (area087), func_801F35F0 (area065), func_801F367C
   (area104), func_801F3914 (area168), func_801F3958 (area174), func_801F3F84 (area139), func_801F40F0 (area170),
   func_801F411C (area088), func_801F45E0 (area173) */
void Area_Update();

/* The world-overlay position resolver used by the origin handlers. */

#endif
