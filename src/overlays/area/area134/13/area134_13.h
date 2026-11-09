#ifndef OVERLAY_WORLD03_AREA134_13_H
#define OVERLAY_WORLD03_AREA134_13_H

/* The world03/area134/13 overlay: one file per split function and its data. */

#include "common/vector.h"
#include "overlays/area/world03.h"
#include "area/spad.h"

typedef struct AreaSprite {
    u8       unk_00[3];
    u8       flags_03;  /* the shade of the sprite */
    u16      half_size; /* the projected half-size */
    u8       unk_06[2];
    Point2DL origin;
} AreaSprite;

/* The row count this overlay clears. */
#define SCRATCH_COLUMN_COUNT 32

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The game-overlay state bytes the area request paths write. */

extern u8       D_801F5724[];
/* The state handler tables the dispatchers index. */
extern Callback D_801F5744[];
extern Callback D_801F57A4[];
extern s32      D_801F5818;
extern Callback D_801F581C[];
extern Callback D_801F5828[];
extern Callback D_801F5838[];
extern s32      D_801F5848[];
extern s32      D_801F5858[];

/* The shared work-area reset; the executable map has no name for it yet. */

/* The overlay's gate the request wrapper tests. */
s32 func_801F49A0(void);

/* The request bytes the selection clear tests. */
/* Spawn an actor record at the focus point and copy the work position into it. */
static inline void World_SpawnActorAtFocus(void) {
    ActorSlot* slot;
    Actor*     work;
    u8         index;

    index = Actor_FindFreeSlot();
    if (index != GAME_NONE) {
        slot               = &g_ActorSlots[index];
        slot->header.flags = 1;
        slot->type         = 0x90;
        slot->header.mode  = 0;
        work               = g_Task;
        WorldPos_Copy(&slot->pos, &work->pos);
    }
}

void func_801F4E64(s32* center, s32 radius);

void func_801F4F0C(s32* center, s32 radius, u16 angle, s32 offset_x, s32 offset_y);

extern u8    D_80146865;
extern u8    D_80146866;
extern u8    D_80146867;
extern u8    D_80146110;
extern u8    D_80146875;
extern Actor D_80146920;
extern s32   D_80146954;

void func_801F48B0(void);
void func_801F4B6C(void);

#endif
