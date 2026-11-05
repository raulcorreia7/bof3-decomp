#include "game_00.h"

MATCH void func_801A6F58(u8* script) {
    s16*   counter = (s16*)&D_1F800000;
    s16    slot;
    Actor* work;

    slot = *counter;
    if (slot >= ENTITY_MAX) {
        return;
    }

    g_Task             = &g_Actors[slot];
    GAME_WORK_AREA_PTR = &g_Actors[slot];

    D_1F800002 = (u16)((script[1] << 8) | script[2]);

    func_801A4AA8();
    Area_FindSceneRecord(D_1F800002);

    g_Task->flags = ACTOR_FLAG_IN_USE;

    work                    = g_Task;
    D_80146908[*counter][0] = work->x.fixed = (script[6] << 16) | (script[5] != 0 ? 0x8000 : 0);
    /* FAKE: forces the counter re-read before the next shadow store. */
    MATCH_BARRIER();

    D_8014690C[*counter][0] = work->y.fixed = (script[8] << 16) | (script[7] != 0 ? 0x8000 : 0);
    /* FAKE: forces the counter re-read before the next shadow store. */
    MATCH_BARRIER();

    D_80146910[*counter][0] = 0;

    COORD_INT(g_Task->z) = Area_SampleHeight(work->x.fixed, work->y.fixed);
    g_Task->mode           = script[9];
    g_Task->step           = script[0xB];
    g_Task->direction_08   = script[0] & 0xF;
    g_Task->unk_06         = script[0] >> 4;
    g_Task->unk_18         = script[0x10];
    g_Task->unk_1C         = script[0x11];

    FIELD(u16, &D_80146914, *counter * ACTOR_SIZE) = script[3];
    FIELD(s16, &D_80146916, *counter * ACTOR_SIZE) = script[4];
    D_80146904[*counter][0]                        = (u16)(script[0xE] | (script[0xD] << 8));
    /* FAKE: forces the counter re-read before the next shadow store. */
    MATCH_BARRIER();
    *(&D_801468FF + *counter * ACTOR_SIZE) = script[0xF];
    D_80146900[*counter][0]                = script[0xA];
    D_8014691C[*counter][0]                = 0x7F;

    func_801A4990(script + 0xC);

    g_Task->tint.bytes.unk_5D = 0;
    g_Task->tint.bytes.unk_5F = 0;
    g_Task->tint.bytes.unk_5E = 0;
    g_Task->tint.bytes.flags  = 2;

    func_801A4914();

    (VOL(u16, D_1F800000)) = (VOL(u16, D_1F800000)) + 1;
}
