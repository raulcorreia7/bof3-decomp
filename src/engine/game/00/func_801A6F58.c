#include "game_00.h"

MATCH void func_801A6F58(u8* script) {
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

    work                           = TASK(Actor);
    g_Actors[*counter].walk_dest_x = work->pos.x.fixed = (script[6] << 16) | (script[5] != 0 ? 0x8000 : 0);
    /* FAKE: forces the counter re-read before the next shadow store. */
    FAKE_BARRIER();

    g_Actors[*counter].walk_dest_y = work->pos.y.fixed = (script[8] << 16) | (script[7] != 0 ? 0x8000 : 0);
    /* FAKE: forces the counter re-read before the next shadow store. */
    FAKE_BARRIER();

    g_Actors[*counter].unk_88 = 0;

    COORD_INT(TASK(Actor)->pos.z) = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);
    TASK(Actor)->header.mode      = script[9];
    TASK(Actor)->header.step      = script[0xB];
    TASK(Actor)->direction        = script[0] & 0xF;
    TASK(Actor)->unk_06           = script[0] >> 4;
    TASK(Actor)->unk_18           = script[0x10];
    TASK(Actor)->unk_1C           = script[0x11];

    FIELD(u16, &D_80146914, *counter * ACTOR_SIZE) = script[3];
    FIELD(s16, &D_80146916, *counter * ACTOR_SIZE) = script[4];
    g_Actors[*counter].unk_7C                      = (script[0xE] | (script[0xD] << 8));
    /* FAKE: forces the counter re-read before the next shadow store. */
    FAKE_BARRIER();
    g_Actors[*counter].unk_77 = script[0xF];
    g_Actors[*counter].unk_78 = script[0xA];
    g_Actors[*counter].unk_94 = 0x7F;

    Actor_SetOptionFlags(script + 0xC);

    TASK(Actor)->tint.bytes.rgb.r = 0;
    TASK(Actor)->tint.bytes.rgb.b = 0;
    TASK(Actor)->tint.bytes.rgb.g = 0;
    TASK(Actor)->tint.bytes.flags = 2;

    Actor_StartFacingScript();

    (FAKE_VOLATILE(u16, g_ScratchPad)) = (FAKE_VOLATILE(u16, g_ScratchPad)) + 1;
}
