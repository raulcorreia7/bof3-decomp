#include "engine/game/00/game_00.h"

/* Entity spawn counter in scratchpad (signed 16-bit slot index). */

/* Packed spawn record staging halfword in scratchpad. */

/* func_801A57F0 */
/* Spawns an actor from a type 2 setup record: Actor_SpawnFromRecord plus the attach actor and offset row bytes. */
MATCH void Actor_SpawnAttached(u8* script) {
    s16*   counter = (s16*)&g_ScratchPad;
    s32    coord_x;
    s32    coord_y;
    s16    slot;
    Actor* work;

    slot = *counter;
    if (slot >= ENTITY_MAX) {
        return;
    }

    SELF_SET(&g_Actors[slot]);
    GAME_WORK_AREA_PTR = &g_Actors[slot];

    g_ScratchPad.cells.ray.y = ((script[1] << 8) | script[2]);

    Actor_ResetMotion();
    Area_SceneSelectRecord(g_ScratchPad.cells.ray.y);

    SELF(Actor)->header.flags = ACTOR_FLAG_IN_USE;

    /* The outer shadow assignment forms the slot offset before the position
     * flag test, as retail schedules it. */
    work                           = SELF(Actor);
    g_Actors[*counter].walk_dest_x = work->pos.x.fixed = (script[7] << 16) | (script[6] != 0 ? 0x8000 : 0);
    /* FAKE: forces the counter re-read before the next shadow store. */
    FAKE_BARRIER();

    g_Actors[*counter].walk_dest_y = work->pos.y.fixed = (script[9] << 16) | (script[8] != 0 ? 0x8000 : 0);
    /* FAKE: forces the counter re-read before the next shadow store. */
    FAKE_BARRIER();

    g_Actors[*counter].unk_88 = 0;

    COORD_INT(SELF(Actor)->pos.z) = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);
    SELF(Actor)->header.mode      = script[0xA];
    SELF(Actor)->header.step      = script[0xC];
    SELF(Actor)->unk_18           = script[0x11];
    SELF(Actor)->unk_1C           = script[0x12];
    SELF(Actor)->direction        = script[0] & 0xF;
    SELF(Actor)->unk_06           = script[0] >> 4;

    FIELD(u16, &D_80146914, *counter * ACTOR_SIZE) = script[4];
    FIELD(s16, &D_80146916, *counter * ACTOR_SIZE) = script[5];
    g_Actors[*counter].unk_7C                      = (script[0xF] | (script[0xE] << 8));
    /* FAKE: forces the counter re-read before the next shadow store. */
    FAKE_BARRIER();
    g_Actors[*counter].unk_78 = script[0xB];
    g_Actors[*counter].unk_77 = script[0x10];
    g_Actors[*counter].unk_94 = 0x7F;

    Actor_SetOptionFlags(script + 0xD);

    if (script[3] & 0x80) {
        SELF(Actor)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    }

    SELF(Actor)->tint.bytes.rgb.r = 0;
    SELF(Actor)->tint.bytes.rgb.b = 0;
    SELF(Actor)->tint.bytes.rgb.g = 0;
    SELF(Actor)->tint.bytes.flags = script[3] & 0xF;

    Actor_StartFacingScript();

    (FAKE_VOLATILE(u16, g_ScratchPad)) = (FAKE_VOLATILE(u16, g_ScratchPad)) + 1;
}
