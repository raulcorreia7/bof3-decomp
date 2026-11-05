#include "game_00.h"

/* Entity spawn counter in scratchpad (signed 16-bit slot index). */

MATCH void func_801A5EFC(u8* script) {
    s16*   counter = (s16*)&D_1F800000;
    s16    slot;
    Actor* work;

    slot = *counter;
    if (slot >= ENTITY_MAX) {
        return;
    }

    g_Task             = &g_Actors[slot];
    GAME_WORK_AREA_PTR = &g_Actors[slot];

    D_1F800002 = (script[1] << 8) | script[2];

    func_801A4AA8();
    Area_FindSceneRecord(D_1F800002);

    g_Task->flags = ACTOR_FLAG_IN_USE;

    /* The outer shadow assignment forms the slot offset before the position
     * flag test, as retail schedules it. */
    work                    = g_Task;
    D_80146908[*counter][0] = work->x.fixed = (script[7] << 16) | (script[6] != 0 ? 0x8000 : 0);
    /* FAKE: forces the counter re-read before the next shadow store. */
    MATCH_BARRIER();

    D_8014690C[*counter][0] = work->y.fixed = (script[9] << 16) | (script[8] != 0 ? 0x8000 : 0);
    /* FAKE: forces the counter re-read before the next shadow store. */
    MATCH_BARRIER();

    D_80146910[*counter][0] = 0;

    COORD_INT(g_Task->z) = Area_SampleHeight(work->x.fixed, work->y.fixed);
    g_Task->mode           = script[0xA];
    g_Task->step           = script[0xC];
    g_Task->direction_08   = script[0] & 0xF;
    g_Task->unk_06         = script[0] >> 4;

    /* The headers declare the per-slot columns D_80146914 and D_80146916 as scalars,
     * so their slot offset stays byte arithmetic on the column address. */
    *(u16*)((u8*)&D_80146914 + *counter * ACTOR_SIZE) = script[4];
    *(s16*)((u8*)&D_80146916 + *counter * ACTOR_SIZE) = script[5];
    D_80146904[*counter][0]                           = script[0xF] | (script[0xE] << 8);
    /* FAKE: forces the counter re-read before the next shadow store. */
    MATCH_BARRIER();
    D_80146900[*counter][0] = script[0xB];
    D_8014691C[*counter][0] = script[0x10];

    func_801A4990(script + 0xD);

    if (script[3] & 0x80) {
        g_Task->flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    }

    g_Task->tint.bytes.unk_5D = 0;
    g_Task->tint.bytes.unk_5F = 0;
    g_Task->tint.bytes.unk_5E = 0;
    g_Task->tint.bytes.flags  = script[3] & 0xF;

    func_801A4914();

    (VOL(u16, D_1F800000)) = (VOL(u16, D_1F800000)) + 1;
}
