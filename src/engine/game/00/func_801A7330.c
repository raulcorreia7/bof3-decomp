#include "game_00.h"

/* Entity spawn counter in scratchpad (signed 16-bit slot index). */

/* Parallel per-slot shadow tables overlaying the 0x98-byte work-area slots;
 * each column stores one field of every record at a fixed address. */

MATCH void func_801A7330(const volatile u8* data) {
    s16*   counter = (s16*)&D_1F800000;
    s16    dist;
    s16    slot;
    u8     mode;
    Actor* work;
    Actor* w2;
    Actor* rec;

    slot = *counter;
    if (slot >= ENTITY_MAX) {
        return;
    }

    g_Task             = &g_Actors[slot];
    GAME_WORK_AREA_PTR = &g_Actors[slot];

    D_1F800002 = (u16)((data[1] << 8) | data[2]);

    func_801A4AA8();
    Area_SelectSceneRecord(D_1F800002);

    g_Task->header.flags = ACTOR_FLAG_IN_USE;

    work                           = g_Task;
    g_Actors[*counter].walk_dest_x = (work->pos.x.fixed = (data[5] << 16) | ((data[4] != 0) ? 0x8000 : 0));
    /* FAKE: barrier pins the counter re-read before the shadow store. */
    FAKE_BARRIER();

    g_Actors[*counter].walk_dest_y = (work->pos.y.fixed = (data[7] << 16) | ((data[6] != 0) ? 0x8000 : 0));
    /* FAKE: barrier pins the counter re-read against merging. */
    FAKE_BARRIER();

    g_Actors[*counter].unk_88 = 0;

    dist = Area_SampleHeight(work->pos.x.fixed, work->pos.y.fixed);

    w2                   = g_Task;
    w2->header.mode      = 6;
    COORD_INT(w2->pos.z) = (u16)dist;
    ACTOR_CLEAR_STEP();
    /* FAKE: barrier pins the flags store before the route-index load. */
    FAKE_BARRIER();

    g_Task->direction_08 = data[0] & 0xF;
    g_Task->unk_06       = data[0] >> 4;

    D_80146900[*counter][0] = 0;
    D_8014691C[*counter][0] = 0x7F;

    Actor_SetOptionFlags((u8*)(data + 0xB));

    if (data[3] & 0x80) {
        g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    }

    g_Task->tint.bytes.unk_5D = 0;
    g_Task->tint.bytes.unk_5F = 0;
    g_Task->tint.bytes.unk_5E = 0;
    g_Task->tint.bytes.flags  = data[3] & 0xF;
    g_Task->draw_layer        = 6;

    rec                       = g_Task;
    g_Actors[*counter].unk_7C = 0;
    /* FAKE: lock keeps the packed store ahead of the record stores. */
    FAKE_ORDER_LOCK(rec->unk_18 = (data[9] << 8) | ((const u8*)data)[0xA]);
    g_Task->unk_05       = data[8];
    g_Task->param.unk_0B = data[0xC];
    g_Task->unk_2A       = (g_Task->option_flags >> ACTOR_OPT_NO_SCRIPT_START) & 0x1;

    mode = g_Task->unk_05;
    if ((D_80144FC4[mode >> 3] >> (mode & 0x7)) & 0x1) {
        if (data[0xC] & 0x1) {
            g_Task->header.flags = 0;
            return;
        }
        /* The 16-bit halves of the two position words have no named members. */
        if (COORD_FRAC(g_Task->pos.x) == 0 && COORD_FRAC(g_Task->pos.y) == 0) {
            Area_SetCellCode(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y), 0x10);
        }
        Actor_SelectScript(1);
    } else {
        Actor_SelectScript(0);
    }

    (VOL(u16, D_1F800000)) = (VOL(u16, D_1F800000)) + 1;
}
