#include "game_00.h"

MATCH void func_801A5400(u8* script) {
    Actor* coord_record;
    Actor* cell_record_a;
    Actor* slot_record;
    Actor* dist_record;
    Actor* flags_record;
    Actor* bits_record;
    Actor* cell_record_b;
    Actor* cell_record_c;
    s16    dist;
    u8*    data;
    s16*   counter;

    counter = (s16*)&D_1F800000;
    data    = script;
    if (*counter < 30) {
        slot_record               = &g_Actors[*counter];
        g_SpadWork                = slot_record;
        g_CurrentActor            = slot_record;
        FIELD(u16, counter, 0x2u) = data[0x2] | (data[0x1] << 8);
        func_801A4AA8();
        Area_FindSceneRecord(FIELD(u16, counter, 0x2u));
        g_SpadWork->flags_00    = ACTOR_FLAG_IN_USE;
        coord_record            = g_SpadWork;
        D_80146908[*counter][0] = coord_record->x.fixed = (data[0x5] << 0x10) | (data[0x4] != 0 ? 0x8000 : 0);
        /* FAKE: forces the counter re-read before the next shadow store. */
        MATCH_BARRIER();
        D_8014690C[*counter][0] = coord_record->y.fixed = (data[0x7] << 0x10) | (data[0x6] != 0 ? 0x8000 : 0);
        /* FAKE: forces the counter re-read before the next shadow store. */
        MATCH_BARRIER();
        *D_80146910[*counter]       = 0;
        dist                        = Area_SampleHeight(coord_record->x.fixed, coord_record->y.fixed);
        dist_record                 = g_SpadWork;
        dist_record->z.part.integer = dist;
        dist_record->unk_01         = data[0x8];
        g_SpadWork->state_02        = data[0xA];
        g_SpadWork->direction_08    = data[0] & 0xF;
        g_SpadWork->unk_06          = data[0] >> 4;
        D_80146904[*counter][0]     = 0xFFFF;
        /* FAKE: forces the counter re-read before the next shadow store. */
        MATCH_BARRIER();
        *D_80146900[*counter] = data[0x9];
        *D_8014691C[*counter] = 0x7F;
        func_801A4990(data + 0xB);
        if (data[0x3] & 0x80) {
            flags_record = g_SpadWork;
            flags_record->flags_00 |= ACTOR_FLAG_SEMI_TRANSPARENT;
        }
        g_SpadWork->tint.bytes.unk_5D = 0;
        g_SpadWork->tint.bytes.unk_5F = 0;
        g_SpadWork->tint.bytes.unk_5E = 0;
        g_SpadWork->tint.bytes.flags  = data[0x3] & 0xF;
        bits_record                   = g_SpadWork;
        bits_record->unk_2A           = (bits_record->option_flags >> 4) & 1;
        Actor_SelectScript(g_SpadWork->direction_08);
        cell_record_a = g_SpadWork;
        Area_SetCellCode(cell_record_a->x.part.integer, cell_record_a->y.part.integer, 0x10);
        cell_record_b = g_SpadWork;
        if (cell_record_b->x.part.fraction != 0) {
            Area_SetCellCode((s16)((u16)cell_record_b->x.part.integer + 1), cell_record_b->y.part.integer, 0x10);
        }
        if (g_SpadWork->y.part.fraction != 0) {
            Area_SetCellCode(g_SpadWork->x.part.integer, (s16)(g_SpadWork->y.part.integer + 1), 0x10);
        }
        cell_record_c = g_SpadWork;
        if ((cell_record_c->x.part.fraction != 0) && (cell_record_c->y.part.fraction != 0)) {
            Area_SetCellCode((s16)((u16)cell_record_c->x.part.integer + 1),
                             (s16)((u16)cell_record_c->y.part.integer + 1), 0x10);
        }
        VOL(u16, D_1F800000) += 1;
    }
}
