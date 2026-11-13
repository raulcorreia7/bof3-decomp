#include "game_00.h"

/* Entity spawn counter in scratchpad (signed 16-bit slot index). */

MATCH void func_801A5B78(u8* script) {
    s16*   counter = (s16*)&D_1F800000;
    s16    slot;
    Actor* work;

    slot = *counter;
    if (slot >= ENTITY_MAX) {
        return;
    }

    g_Task             = &g_Actors[slot];
    GAME_WORK_AREA_PTR = &g_Actors[slot];

    D_1F800002 = ((script[1] << 8) | script[2]);

    func_801A4AA8();
    Area_FindSceneRecord(D_1F800002);

    g_Task->header.flags = ACTOR_FLAG_IN_USE;

    /* The outer shadow assignment forms the slot offset before the position
     * flag test, as retail schedules it. */
    work                           = g_Task;
    g_Actors[*counter].walk_dest_x = work->pos.x.fixed = (script[7] << 16) | (script[6] != 0 ? 0x8000 : 0);
    /* FAKE: forces the counter re-read before the next shadow store. */
    FAKE_BARRIER();

    g_Actors[*counter].walk_dest_y = work->pos.y.fixed = (script[9] << 16) | (script[8] != 0 ? 0x8000 : 0);
    /* FAKE: forces the counter re-read before the next shadow store. */
    FAKE_BARRIER();

    g_Actors[*counter].unk_88 = 0;

    COORD_INT(g_Task->pos.z) = Area_SampleHeight(work->pos.x.fixed, work->pos.y.fixed);
    g_Task->unk_06           = script[0] >> 4;
    g_Task->direction_08     = script[0] & 0xF;
    g_Task->header.mode      = script[0xA];
    g_Task->header.step      = script[0xC];
    g_Task->state_70.word    = script[0x11];

    FIELD(u16, &D_80146914, *counter * ACTOR_SIZE) = script[4];
    FIELD(s16, &D_80146916, *counter * ACTOR_SIZE) = script[5];
    g_Actors[*counter].unk_7C                      = (script[0xF] | (script[0xE] << 8));
    /* FAKE: forces the counter re-read before the next shadow store. */
    FAKE_BARRIER();
    *(&D_801468FF + *counter * ACTOR_SIZE) = script[0x10];
    D_80146900[*counter][0]                = script[0xB];
    D_8014691C[*counter][0]                = 0x7F;

    Actor_SetOptionFlags(script + 0xD);

    if (script[3] & 0x80) {
        g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    }

    g_Task->tint.bytes.unk_5D = 0;
    g_Task->tint.bytes.unk_5F = 0;
    g_Task->tint.bytes.unk_5E = 0;
    g_Task->tint.bytes.flags  = script[3] & 0xF;

    func_801A4914();

    (VOL(u16, D_1F800000)) = (VOL(u16, D_1F800000)) + 1;
}
