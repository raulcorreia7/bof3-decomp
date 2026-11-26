#include "engine/game/00/game_00.h"

/* Entity spawn counter in scratchpad (signed 16-bit slot index). */

/* func_801A5B78 */
/* Spawns a map actor from a type 3 setup record: the entity record plus its voice flags. */
MATCH void Actor_SpawnVoiced(u8* script) {
    s16*   counter = (s16*)&g_ScratchPad;
    s16    slot;
    Actor* work;

    slot = *counter;
    if (slot >= ENTITY_MAX) {
        return;
    }

    g_Task             = &g_Actors[slot];
    GAME_WORK_AREA_PTR = &g_Actors[slot];

    g_ScratchPad.cells.ray.y = ((script[1] << 8) | script[2]);

    Actor_ResetMotion();
    Area_SceneSelectRecord(g_ScratchPad.cells.ray.y);

    TASK(Actor)->header.flags = ACTOR_FLAG_IN_USE;

    /* The outer shadow assignment forms the slot offset before the position
     * flag test, as retail schedules it. */
    work                           = TASK(Actor);
    g_Actors[*counter].walk_dest_x = work->pos.x.fixed = (script[7] << 16) | (script[6] != 0 ? 0x8000 : 0);
    /* FAKE: forces the counter re-read before the next shadow store. */
    FAKE_BARRIER();

    g_Actors[*counter].walk_dest_y = work->pos.y.fixed = (script[9] << 16) | (script[8] != 0 ? 0x8000 : 0);
    /* FAKE: forces the counter re-read before the next shadow store. */
    FAKE_BARRIER();

    g_Actors[*counter].unk_88 = 0;

    COORD_INT(TASK(Actor)->pos.z) = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);
    TASK(Actor)->unk_06           = script[0] >> 4;
    TASK(Actor)->direction        = script[0] & 0xF;
    TASK(Actor)->header.mode      = script[0xA];
    TASK(Actor)->header.step      = script[0xC];
    TASK(Actor)->voice_flags.raw  = script[0x11];

    FIELD(u16, &D_80146914, *counter * ACTOR_SIZE) = script[4];
    FIELD(s16, &D_80146916, *counter * ACTOR_SIZE) = script[5];
    g_Actors[*counter].unk_7C                      = (script[0xF] | (script[0xE] << 8));
    /* FAKE: forces the counter re-read before the next shadow store. */
    FAKE_BARRIER();
    g_Actors[*counter].unk_77 = script[0x10];
    g_Actors[*counter].unk_78 = script[0xB];
    g_Actors[*counter].unk_94 = 0x7F;

    Actor_SetOptionFlags(script + 0xD);

    if (script[3] & 0x80) {
        TASK(Actor)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    }

    TASK(Actor)->tint.bytes.rgb.r = 0;
    TASK(Actor)->tint.bytes.rgb.b = 0;
    TASK(Actor)->tint.bytes.rgb.g = 0;
    TASK(Actor)->tint.bytes.flags = script[3] & 0xF;

    Actor_StartFacingScript();

    (FAKE_VOLATILE(u16, g_ScratchPad)) = (FAKE_VOLATILE(u16, g_ScratchPad)) + 1;
}
