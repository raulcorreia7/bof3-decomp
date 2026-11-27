#include "engine/game/00/game_00.h"

/* func_801A6F58 */
/* Spawns an actor from a type 5 setup record: attach bytes, no tint byte, tint flags fixed at 2. */
MATCH void Actor_SpawnAttachedFixedFlags(u8* script) {
    s16    slot;
    Actor* work;

    slot = g_ScratchPad.cells.halves[0];
    if (slot >= ENTITY_MAX) {
        return;
    }

    SELF_SET(&g_Actors[slot]);
    GAME_WORK_AREA_PTR = &g_Actors[slot];

    g_ScratchPad.cells.ray.y = ((script[1] << 8) | script[2]);

    Actor_ResetMotion();
    Area_SceneSelectRecord(g_ScratchPad.cells.ray.y);

    SELF(Actor)->header.flags = ACTOR_FLAG_IN_USE;

    work                                               = SELF(Actor);
    g_Actors[g_ScratchPad.cells.halves[0]].walk_dest_x = work->pos.x.fixed = (script[6] << 16) | (script[5] != 0 ? 0x8000 : 0);

    g_Actors[g_ScratchPad.cells.halves[0]].walk_dest_y = work->pos.y.fixed = (script[8] << 16) | (script[7] != 0 ? 0x8000 : 0);

    g_Actors[g_ScratchPad.cells.halves[0]].unk_88 = 0;

    COORD_INT(SELF(Actor)->pos.z) = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);
    SELF(Actor)->header.mode      = script[9];
    SELF(Actor)->header.step      = script[0xB];
    SELF(Actor)->direction        = script[0] & 0xF;
    SELF(Actor)->unk_06           = script[0] >> 4;
    SELF(Actor)->unk_18           = script[0x10];
    SELF(Actor)->unk_1C           = script[0x11];

    FIELD(u16, &D_80146914, g_ScratchPad.cells.halves[0] * ACTOR_SIZE) = script[3];
    FIELD(s16, &D_80146916, g_ScratchPad.cells.halves[0] * ACTOR_SIZE) = script[4];
    g_Actors[g_ScratchPad.cells.halves[0]].unk_7C                      = (script[0xE] | (script[0xD] << 8));
    g_Actors[g_ScratchPad.cells.halves[0]].unk_77                      = script[0xF];
    g_Actors[g_ScratchPad.cells.halves[0]].unk_78                      = script[0xA];
    g_Actors[g_ScratchPad.cells.halves[0]].unk_94                      = 0x7F;

    Actor_SetOptionFlags(script + 0xC);

    SELF(Actor)->tint.bytes.rgb.r = 0;
    SELF(Actor)->tint.bytes.rgb.b = 0;
    SELF(Actor)->tint.bytes.rgb.g = 0;
    SELF(Actor)->tint.bytes.flags = 2;

    Actor_StartFacingScript();

    g_ScratchPad.cells.halves[0]++;
}
