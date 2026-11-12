#include "game_00.h"

/* Entity spawn counter in scratchpad (signed 16-bit slot index). */

/* Packed spawn record staging halfword in scratchpad. */

/* Parallel per-slot shadow tables overlaying the 0x98-byte work-area
 * records; each column stores one field of every slot at a fixed address.
 * The scalars D_801468FF, D_80146914 and D_80146916 are columns too,
 * addressed through byte offsets because the headers declare them as scalars. */

MATCH void func_801A57F0(u8* script) {
    s16*   counter = (s16*)&D_1F800000;
    s32    coord_x;
    s32    coord_y;
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
    Area_SelectSceneRecord(D_1F800002);

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
    g_Task->header.mode      = script[0xA];
    g_Task->header.step      = script[0xC];
    g_Task->unk_18           = script[0x11];
    g_Task->unk_1C           = script[0x12];
    g_Task->direction_08     = script[0] & 0xF;
    g_Task->unk_06           = script[0] >> 4;

    FIELD(u16, &D_80146914, *counter * ACTOR_SIZE) = script[4];
    FIELD(s16, &D_80146916, *counter * ACTOR_SIZE) = script[5];
    g_Actors[*counter].unk_7C                      = (script[0xF] | (script[0xE] << 8));
    /* FAKE: forces the counter re-read before the next shadow store. */
    FAKE_BARRIER();
    D_80146900[*counter][0]                       = script[0xB];
    FIELD(u8, &D_801468FF, *counter * ACTOR_SIZE) = script[0x10];
    D_8014691C[*counter][0]                       = 0x7F;

    func_801A4990(script + 0xD);

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
