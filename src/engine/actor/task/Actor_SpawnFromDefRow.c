/* FAKE: the area id read stays below the actor address; a plain read moves above it. */
#define FAKE_DECL_GAME_AREA_ID_VOLATILE
#include "engine/game/00/game_00.h"

/* func_801A68C0 */
/* Spawns an actor from a type 10 setup record that names its scene record by row index. */
MATCH void Actor_SpawnFromDefRow(u8* script) {
    s16*   counter = (s16*)&g_ScratchPad;
    s16    slot;
    s32    tile;
    Actor* actors;
    Actor* work;
    s32    x;
    s32    y;
    u32    offset;

    slot = *counter;
    if (slot >= ENTITY_MAX) {
        return;
    }

    tile               = g_GameAreaId;
    offset             = script[9] * 8;
    g_Task             = &g_Actors[slot];
    GAME_WORK_AREA_PTR = &g_Actors[slot];
    actors             = g_Actors;

    tile                   = FIELD(s32, g_AreaLoads[tile], 0x8u) + offset;
    TASK(Actor)->direction = script[0] & 0xF;
    Actor_ResetMotion();
    SYS_InitScratchpad((u8*)tile);
    Actor_TurnRampClear(4);

    work = TASK(Actor);
    x    = script[2] << 16;
    if (script[1] != 0) {
        x |= 32768;
    }
    work->pos.x.fixed = x;
    y                 = script[4] << 16;
    if (script[3] != 0) {
        y |= 32768;
    }
    work->pos.y.fixed = y;

    COORD_INT(TASK(Actor)->pos.z) = Area_HeightSample(work->pos.x.fixed, y);
    TASK(Actor)->header.mode      = script[5];
    TASK(Actor)->header.step      = script[7];
    TASK(Actor)->unk_06           = script[0] >> 4;
    TASK(Actor)->gravity          = 0;
    TASK(Actor)->unk_1C           = 0;
    TASK(Actor)->unk_18           = 0;
    TASK(Actor)->voice_flags.raw  = FIELD(u8, TASK(Actor)->range_54.table, 0x2u);

    actors[*counter].unk_88                             = 0;
    actors[*counter].walk_dest_y                        = 0;
    FIELD(s32, g_ActorWalkDestX, *counter * ACTOR_SIZE) = 0;
    FIELD(u8, &D_801468FF, *counter * ACTOR_SIZE)       = script[0xA];
    FIELD(u8, D_80146900, *counter * ACTOR_SIZE)        = script[6];
    FIELD(u16, D_80146904, *counter * ACTOR_SIZE)       = script[0xD] | (script[0xC] << 8);
    FIELD(u8, D_8014691C, *counter * ACTOR_SIZE)        = 0x7F;

    Actor_SetOptionFlags(script + 8);

    TASK(Actor)->tint.steps.delta.r = -0x80;
    TASK(Actor)->tint.steps.delta.b = -0x80;
    TASK(Actor)->tint.steps.delta.g = -0x80;
    TASK(Actor)->tint.bytes.flags   = 2;

    if (D_80146900[*counter][0] == 0) {
        Area_CellSetCode(COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y), 0x10);
        if (COORD_FRAC(TASK(Actor)->pos.x) != 0) {
            Area_CellSetCode((s16)((u16)COORD_INT(TASK(Actor)->pos.x) + 1), COORD_INT(TASK(Actor)->pos.y), 0x10);
        }
        if (COORD_FRAC(TASK(Actor)->pos.y) != 0) {
            Area_CellSetCode(COORD_INT(TASK(Actor)->pos.x), (s16)((u16)COORD_INT(TASK(Actor)->pos.y) + 1), 0x10);
        }
        if ((COORD_FRAC(TASK(Actor)->pos.x) != 0) && (COORD_FRAC(TASK(Actor)->pos.y) != 0)) {
            Area_CellSetCode((s16)((u16)COORD_INT(TASK(Actor)->pos.x) + 1), (s16)((u16)COORD_INT(TASK(Actor)->pos.y) + 1), 0x10);
        }
    }

    (FAKE_VOLATILE(u16, g_ScratchPad)) = (FAKE_VOLATILE(u16, g_ScratchPad)) + 1;
}
