#ifndef OVERLAY_WORLD03_AREA134_13_H
#define OVERLAY_WORLD03_AREA134_13_H

/* The world03/area134/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "common/vector.h"
#include "overlays/area/worlds/world03.h"

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
/* Steps the given actor's x by a quarter cell four times and returns the work the step
 * replaced; the ten x step functions of this overlay differ only in the actor index and
 * the code they store through the returned pointer. The two y steps loop twice, so they
 * keep their own body. */
static inline u8* Area_AdvanceRow(s32 actor_index) {
    Actor* actor;
    u8*    work;
    s32    i;

    i    = 0;
    work = SELF(u8);
    SELF_SET(&g_Actors[actor_index]);
    actor = &g_Actors[actor_index];
    do {
        actor->pos.x.fixed += 0x4000;
        i++;
    } while ((u8)i < 4);
    return work;
}

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
        work               = SELF(Actor);
        WorldPos_Copy(&slot->pos, &work->pos);
    }
}

void func_801F4E64(s32* center, s32 radius);

void func_801F4F0C(s32* center, s32 radius, u16 angle, s32 offset_x, s32 offset_y);

/* The party position x the area compares its work position against. */
extern s32   D_80145EC4;
extern u8    D_80146110;
extern s32   D_80146144;
extern u8    D_80146865;
extern u8    D_80146866;
extern Actor D_80146920;
extern s32   D_80146954;

void func_801F48B0(void);
void func_801F4B6C(void);

/* Returns the area task to the first step of mode 1. */
static inline void Area_EnterMode1(void) {
    SELF(Actor)->timer       = 0;
    SELF(Actor)->header.mode = 1;
    ACTOR_CLEAR_STEP();
}

/* Takes mode 0xD once the party leader's x has reached `bound`, else the given mode; `actor` is the task the
 * dispatch visits. A statement macro: the member declares Actor* work. */
#define AREA_SET_MODE_OR_END(actor, bound, next_mode) \
    work        = g_Self;                             \
    g_Self      = (actor);                            \
    g_GameState = g_Game.members;                     \
    g_Self      = work;                               \
    SELF_SET(g_Game.members);                         \
    g_Self = work;                                    \
    if ((bound) >= g_Game.members[0].pos.x.fixed) {   \
        work->header.mode  = 0xD;                     \
        SELF(Actor)->timer = 0;                       \
        return;                                       \
    }                                                 \
    work->header.mode = (next_mode)

/* Claims an actor slot of the given kind for party member `member`, at its screen position, and stores the
 * claimed slot in the task's byte 0x0B unless none is free. A statement macro: the member declares u8* work,
 * u8 index, s16 y, s16 x, u8 selection and s32 result. */
#define AREA_CLAIM_MEMBER_SLOT(member, kind)                  \
    SELF_SET((u8*)&g_Game.members[member]);                   \
    index     = g_PartyFieldOrder[member];                    \
    y         = g_Game.members[member].screen_y.signed_value; \
    x         = g_Game.members[member].screen_x.signed_value; \
    selection = D_801F5724[0x144u + index];                   \
    result    = Actor_ClaimSlot(kind, 0, selection, x, y);    \
    if ((u8)result != 0xFF) {                                 \
        work      = SELF(u8);                                 \
        work[0xB] = result;                                   \
    }

/* Counts the work byte 0x09 down and takes the given mode when it reaches zero.
 * The member declares work and timer. */
#define AREA_TICK_MODE_CHANGE(next_mode)        \
    work    = SELF(u8);                         \
    timer   = work[9];                          \
    work[9] = timer + 0xFF;                     \
    if (timer == 0) {                           \
        SELF(Actor)->header.mode = (next_mode); \
    }

#endif
