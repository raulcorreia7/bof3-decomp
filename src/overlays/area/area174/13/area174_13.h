#ifndef OVERLAY_WORLD04_AREA174_13_H
#define OVERLAY_WORLD04_AREA174_13_H

/* The world04/area174/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world04.h"

/* The work origin offset, step and threshold this overlay advances. */
#define AREA_ORIGIN_OFFSET       0x30
#define ACTOR_SCREEN_X_STEP      0x10
#define ACTOR_SCREEN_X_THRESHOLD 0x80

/* The multiplier that derives the link byte from the current actor's byte offset. */
#define ACTOR_LINK_MULTIPLIER    3616814565u

/* The scratchpad cell holding this mode's work pointer. */

/* The current map row in the field-loader table. */
/* The party position in 16.16 fixed point. */
/* The payload's first words: the per-state handler pointers. */
extern u8          D_801F4FAC[];
/* The screen spread of the quad's far edge, a signed byte a sprite row, in the payload. */
extern volatile u8 D_801F4FE4[];
/* The palette callbacks this overlay animates. */
extern Callback    D_801F66D4[17];
/* The row table the step lookup reads through the load entry. */
extern u8*         D_801F6748[];
/* The signed per-step offsets the scripted move adds to x and subtracts from y, indexed by the 4-bit step. */
extern s8          D_801F6754[];

/* Claims a spawn slot for an actor of the given actor_type linked to the current actor; with no slot free it backs the script cursor up by 2. func_801F43FC and func_801F4D90 share it; every change must verify both. A statement macro: an inline function loads actor_type before the call and moves the bytes. */
#define AREA_SPAWN_LINKED_ACTOR(actor_type)                                              \
    SELF(Actor)->param.actor_slot = Actor_FindFreeSpawned();                             \
    if (SELF(Actor)->param.actor_slot != GAME_NONE) {                                    \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags      = 1;            \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].type              = (actor_type); \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].unk_06            = 1;            \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].unk_07            = 0;            \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].link              = 1;            \
        *(s32*)&g_SpawnedActors[SELF(Actor)->param.actor_slot].pad_4B[1] = (s32)g_Self;  \
    } else {                                                                             \
        g_ScriptState->cursor -= 2;                                                      \
    }

/* Claims a spawn slot for an 0xA2 actor placed 256 units ahead of the current actor and sets its mode; with no slot free it backs the script cursor up by 2. func_801F4278 and func_801F4688 share it; every change must verify both. */
#define AREA_SPAWN_AHEAD_ACTOR(actor_mode)                                                                      \
    SELF(Actor)->param.actor_slot = Actor_FindFreeSpawned();                                                    \
    if (SELF(Actor)->param.actor_slot != GAME_NONE) {                                                           \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags = 1;                                        \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].type         = 0xA2;                                     \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].pos.x.fixed  = SELF(Actor)->pos.x.fixed;                 \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].pos.y.fixed  = SELF(Actor)->pos.y.fixed;                 \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].pos.z.fixed  = SELF(Actor)->pos.z.fixed + TO_COORD(256); \
        g_SpawnedActors[SELF(Actor)->param.actor_slot].header.mode  = (actor_mode);                             \
    } else {                                                                                                    \
        g_ScriptState->cursor -= 2;                                                                             \
    }

u8*         func_801F2E88(void);
extern u8   Area_UpdateShots(void);
extern void func_801F4A5C(u8* pairs, s32 facing);
extern void func_801F4B0C(void);

extern void func_801F4C68(void);

void func_801F2E5C(void);

typedef struct AreaShot {
    u8       pad_00[3];
    u8       active;
    u8       unk_04;
    u8       timer;
    u16      angle;
    s16      unk_08;
    s16      unk_0A;
    WorldPos pos;
    u8       pad_18[4];
    Pos3     velocity;
    u8       pad_28[4];
} AreaShot;

ASSERT_OFFSET(AreaShot, angle, 0x06);
ASSERT_OFFSET(AreaShot, pos, 0x0C);
ASSERT_OFFSET(AreaShot, velocity, 0x1C);
ASSERT_SIZE(AreaShot, 0x2C);

void func_801F2FEC(s32* pos, s16, s16, u16 angle, u8, u8);
void func_801F3378(AreaShot* shot);

#endif
