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
        g_Task                    = slot_record;
        g_CurrentActor            = slot_record;
        FIELD(u16, counter, 0x2u) = data[0x2] | (data[0x1] << 8);
        func_801A4AA8();
        Area_SelectSceneRecord(FIELD(u16, counter, 0x2u));
        g_Task->header.flags           = ACTOR_FLAG_IN_USE;
        coord_record                   = g_Task;
        g_Actors[*counter].walk_dest_x = coord_record->pos.x.fixed = (data[0x5] << 0x10) | (data[0x4] != 0 ? 0x8000 : 0);
        /* FAKE: forces the counter re-read before the next shadow store. */
        FAKE_BARRIER();
        g_Actors[*counter].walk_dest_y = coord_record->pos.y.fixed = (data[0x7] << 0x10) | (data[0x6] != 0 ? 0x8000 : 0);
        /* FAKE: forces the counter re-read before the next shadow store. */
        FAKE_BARRIER();
        g_Actors[*counter].unk_88     = 0;
        dist                          = Area_SampleHeight(coord_record->pos.x.fixed, coord_record->pos.y.fixed);
        dist_record                   = g_Task;
        COORD_INT(dist_record->pos.z) = dist;
        dist_record->header.mode      = data[0x8];
        g_Task->header.step           = data[0xA];
        g_Task->direction_08          = data[0] & 0xF;
        g_Task->unk_06                = data[0] >> 4;
        g_Actors[*counter].unk_7C     = 0xFFFF;
        /* FAKE: forces the counter re-read before the next shadow store. */
        FAKE_BARRIER();
        *D_80146900[*counter] = data[0x9];
        *D_8014691C[*counter] = 0x7F;
        Actor_SetOptionFlags(data + 0xB);
        if (data[0x3] & 0x80) {
            flags_record = g_Task;
            flags_record->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        }
        g_Task->tint.bytes.unk_5D = 0;
        g_Task->tint.bytes.unk_5F = 0;
        g_Task->tint.bytes.unk_5E = 0;
        g_Task->tint.bytes.flags  = data[0x3] & 0xF;
        bits_record               = g_Task;
        bits_record->unk_2A       = (bits_record->option_flags >> ACTOR_OPT_NO_SCRIPT_START) & 0x1;
        Actor_SelectScript(g_Task->direction_08);
        cell_record_a = g_Task;
        Area_SetCellCode(COORD_INT(cell_record_a->pos.x), COORD_INT(cell_record_a->pos.y), 0x10);
        cell_record_b = g_Task;
        if (COORD_FRAC(cell_record_b->pos.x) != 0) {
            Area_SetCellCode((s16)((u16)COORD_INT(cell_record_b->pos.x) + 1), COORD_INT(cell_record_b->pos.y), 0x10);
        }
        if (COORD_FRAC(g_Task->pos.y) != 0) {
            Area_SetCellCode(COORD_INT(g_Task->pos.x), (s16)(COORD_INT(g_Task->pos.y) + 1), 0x10);
        }
        cell_record_c = g_Task;
        if ((COORD_FRAC(cell_record_c->pos.x) != 0) && (COORD_FRAC(cell_record_c->pos.y) != 0)) {
            Area_SetCellCode((s16)((u16)COORD_INT(cell_record_c->pos.x) + 1), (s16)((u16)COORD_INT(cell_record_c->pos.y) + 1), 0x10);
        }
        VOL(u16, D_1F800000) += 1;
    }
}
