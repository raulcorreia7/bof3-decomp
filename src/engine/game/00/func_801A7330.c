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

    g_SpadWork         = &g_Actors[slot];
    GAME_WORK_AREA_PTR = &g_Actors[slot];

    D_1F800002 = (u16)((data[1] << 8) | data[2]);

    func_801A4AA8();
    Area_FindSceneRecord(D_1F800002);

    g_SpadWork->flags_00 = ACTOR_FLAG_IN_USE;

    work                    = g_SpadWork;
    D_80146908[*counter][0] = (work->x.fixed = (data[5] << 16) | ((data[4] != 0) ? 0x8000 : 0));
    /* FAKE: barrier pins the counter re-read before the shadow store. */
    MATCH_BARRIER();

    D_8014690C[*counter][0] = (work->y.fixed = (data[7] << 16) | ((data[6] != 0) ? 0x8000 : 0));
    /* FAKE: barrier pins the counter re-read against merging. */
    MATCH_BARRIER();

    D_80146910[*counter][0] = 0;

    dist = Area_SampleHeight(work->x.fixed, work->y.fixed);

    w2                 = g_SpadWork;
    w2->unk_01         = 6;
    w2->z.part.integer = (u16)dist;
    ACTOR_CLEAR_STATE();
    /* FAKE: barrier pins the flags store before the route-index load. */
    MATCH_BARRIER();

    g_SpadWork->direction_08 = data[0] & 0xF;
    g_SpadWork->unk_06       = data[0] >> 4;

    D_80146900[*counter][0] = 0;
    D_8014691C[*counter][0] = 0x7F;

    func_801A4990((u8*)(data + 0xB));

    if (data[3] & 0x80) {
        g_SpadWork->flags_00 |= ACTOR_FLAG_SEMI_TRANSPARENT;
    }

    g_SpadWork->tint.bytes.unk_5D = 0;
    g_SpadWork->tint.bytes.unk_5F = 0;
    g_SpadWork->tint.bytes.unk_5E = 0;
    g_SpadWork->tint.bytes.flags  = data[3] & 0xF;
    g_SpadWork->unk_29            = 6;

    rec                     = g_SpadWork;
    D_80146904[*counter][0] = 0;
    /* FAKE: lock keeps the packed store ahead of the record stores. */
    ORDER_LOCK(rec->unk_18 = (data[9] << 8) | ((const u8*)data)[0xA]);
    g_SpadWork->unk_05 = data[8];
    g_SpadWork->unk_0B = data[0xC];
    g_SpadWork->unk_2A = (g_SpadWork->option_flags >> 4) & 1;

    mode = g_SpadWork->unk_05;
    if ((D_80144FC4[mode >> 3] >> (mode & 7)) & 1) {
        if (data[0xC] & 1) {
            g_SpadWork->flags_00 = 0;
            return;
        }
        /* The 16-bit halves of the two position words have no named members. */
        if (g_SpadWork->x.part.fraction == 0 && g_SpadWork->y.part.fraction == 0) {
            Area_SetCellCode(g_SpadWork->x.part.integer, g_SpadWork->y.part.integer, 0x10);
        }
        Actor_SelectScript(1);
    } else {
        Actor_SelectScript(0);
    }

    (VOL(u16, D_1F800000)) = (VOL(u16, D_1F800000)) + 1;
}
