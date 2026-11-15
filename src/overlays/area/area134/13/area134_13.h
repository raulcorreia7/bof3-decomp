#ifndef OVERLAY_WORLD03_AREA134_13_H
#define OVERLAY_WORLD03_AREA134_13_H

/* The world03/area134/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "common/vector.h"
#include "overlays/area/world03.h"
#include "area/spad.h"

/* The row count this overlay clears. */
#define SCRATCH_COLUMN_COUNT 32

/* A 0x28-byte slot of the area work memory: the claim flag the scan
 * (func_801F4938) tests, the task's step stamp, its position and the row's
 * scale word. */
typedef struct AreaSlotRecord {
    u8       active; /* 0x00 */
    u8       unk_01;
    u8       unk_02;
    u8       unk_03;
    u16      unk_04;
    u16      unk_06;
    WorldPos pos; /* 0x08 */
    s32      unk_14;
    s32      unk_18;
    s32      unk_1C;
    s32      unk_20;
    s32      unk_24;
} AreaSlotRecord;

ASSERT_OFFSET(AreaSlotRecord, pos, 0x08);
ASSERT_SIZE(AreaSlotRecord, 0x28);

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
    SpawnedActor* slot;
    Actor*        work;
    u8            index;

    index = Actor_FindFreeSpawned();
    if (index != GAME_NONE) {
        slot               = &g_SpawnedActors[index];
        slot->header.flags = 1;
        slot->type         = 0x90;
        slot->header.mode  = 0;
        work               = g_Task;
        WorldPos_Copy(&slot->pos, &work->pos);
    }
}

void func_801F4E64(s32* center, s32 radius);

void func_801F4F0C(s32* center, s32 radius, u16 angle, s32 offset_x, s32 offset_y);

extern s32   D_80146144;
extern void* D_80146250;
extern u8    D_80146865;
extern u8    D_80146866;
extern u8    D_80146867;
extern u8    D_80146110;
extern u8    D_80146875;
extern Actor D_80146920;
extern s32   D_80146954;

void func_801F48B0(void);
void func_801F4B6C(void);

/* Returns the area task to the first step of mode 1. */
static inline void Area_EnterMode1(void) {
    g_Task->timer       = 0;
    g_Task->header.mode = 1;
    ACTOR_CLEAR_STEP();
}

/* Counts the work byte 0x09 down and takes the given mode when it reaches zero.
 * The member declares work and timer. */
#define AREA_TICK_MODE_CHANGE(next_mode)   \
    work    = (u8*)g_Task;                 \
    timer   = work[9];                     \
    work[9] = timer + 0xFF;                \
    if (timer == 0) {                      \
        g_Task->header.mode = (next_mode); \
    }

#endif
