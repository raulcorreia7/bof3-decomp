#ifndef OVERLAY_WORLD03_AREA134_13_H
#define OVERLAY_WORLD03_AREA134_13_H

/* The world03/area134/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "work/area_spad.h"

typedef struct AreaSprite {
    u8  unk_00[3];
    u8  flags_03;  /* the shade of the sprite */
    u16 half_size; /* the projected half-size */
    u8  unk_06[2];
    s32 origin_x; /* the camera x */
    s32 origin_y; /* the camera y */
} AreaSprite;

/* The row count this overlay clears. */
#define SCRATCH_COLUMN_COUNT 32

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The game-overlay state bytes the area request paths write. */

extern u8       D_801F5724[];
/* The state handler tables the dispatchers index. */
extern Callback D_801F5744[];
extern Callback D_801F57A4[];
extern Callback D_801F581C[];
extern Callback D_801F5828[];
extern Callback D_801F5838[];
extern s32      D_801F5848[];
extern s32      D_801F5858[];
extern s32      D_801F5818;

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
        slot           = &g_ActorSlots[index];
        slot->flags_00 = 1;
        slot->type     = 0x90;
        slot->unk_01   = 0;
        work           = g_SpadWork;
        slot->x.fixed  = work->x.fixed;
        slot->y.fixed  = work->y.fixed;
        slot->z.fixed  = work->z.fixed;
    }
}

void Area_ProjectPoint(s32* pos, long* screen_xy);

void func_801F4F0C(const s32* center, s32 radius, u16 angle, s32 offset_x, s32 offset_y);

void func_801F4E64(const s32* center, s32 radius);

extern s32 D_80145EC4;
extern s32 D_80146954;
extern Actor D_80146920;
extern u8 D_80146865;
extern u8 D_80146866;

#endif
