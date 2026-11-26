#include "engine/game/00/game_00.h"

/* The scalars D_80146914 and D_80146916 are per-slot columns too,
 * addressed through byte offsets because the headers declare them as scalars. */

/* func_801A50C0 */
/* Spawns an actor from a type 1 setup record: Actor_SpawnFromRecord without the route row byte. */
MATCH void Actor_SpawnNoRoute(u8* script) {
    s16    slot;
    Actor* work;

    slot = g_ScratchPad.cells.halves[0];
    if (slot >= ENTITY_MAX) {
        return;
    }

    TASK_SET(&g_Actors[slot]);
    GAME_WORK_AREA_PTR = &g_Actors[slot];

    g_ScratchPad.cells.ray.y = ((script[1] << 8) | script[2]);

    Actor_ResetMotion();
    Area_SceneSelectRecord(g_ScratchPad.cells.ray.y);

    TASK(Actor)->header.flags = ACTOR_FLAG_IN_USE;

    work                                               = TASK(Actor);
    g_Actors[g_ScratchPad.cells.halves[0]].walk_dest_x = work->pos.x.fixed = (script[7] << 16) | (script[6] != 0 ? 0x8000 : 0);

    g_Actors[g_ScratchPad.cells.halves[0]].walk_dest_y = work->pos.y.fixed = (script[9] << 16) | (script[8] != 0 ? 0x8000 : 0);

    g_Actors[g_ScratchPad.cells.halves[0]].unk_88 = 0;

    COORD_INT(TASK(Actor)->pos.z) = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);
    TASK(Actor)->header.mode      = script[0xA];
    TASK(Actor)->header.step      = script[0xC];
    TASK(Actor)->direction        = script[0] & 0xF;
    TASK(Actor)->unk_06           = script[0] >> 4;

    FIELD(u16, &D_80146914, g_ScratchPad.cells.halves[0] * ACTOR_SIZE) = script[4];
    FIELD(s16, &D_80146916, g_ScratchPad.cells.halves[0] * ACTOR_SIZE) = script[5];
    g_Actors[g_ScratchPad.cells.halves[0]].unk_7C                      = (script[0xF] | (script[0xE] << 8));
    D_80146900[g_ScratchPad.cells.halves[0]][0]                        = script[0xB];
    D_8014691C[g_ScratchPad.cells.halves[0]][0]                        = 0x7F;

    Actor_SetOptionFlags(script + 0xD);

    if (script[3] & 0x80) {
        TASK(Actor)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    }

    TASK(Actor)->tint.bytes.rgb.r = 0;
    TASK(Actor)->tint.bytes.rgb.b = 0;
    TASK(Actor)->tint.bytes.rgb.g = 0;
    TASK(Actor)->tint.bytes.flags = script[3] & 0xF;

    Actor_StartFacingScript();

    g_ScratchPad.cells.halves[0]++;
}
