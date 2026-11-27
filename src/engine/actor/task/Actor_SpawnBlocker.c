#include "engine/game/00/game_00.h"

/* Actor_SpawnBlocker */
/* func_801A5400 */
/* Spawns an actor from a short type 8 setup record and marks the cells under it with code 0x10. */
MATCH void Actor_SpawnBlocker(u8* script) {
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
    u16*   counter_words;

    counter       = (s16*)&g_ScratchPad;
    counter_words = (u16*)&g_ScratchPad;
    data          = script;
    if (g_ScratchPad.cells.halves[0] < 30) {
        slot_record = &g_Actors[g_ScratchPad.cells.halves[0]];
        SELF_SET(slot_record);
        g_CurrentActor   = slot_record;
        counter_words[1] = data[0x2] | (data[0x1] << 8);
        Actor_ResetMotion();
        Area_SceneSelectRecord(counter_words[1]);
        SELF(Actor)->header.flags                          = ACTOR_FLAG_IN_USE;
        coord_record                                       = SELF(Actor);
        g_Actors[g_ScratchPad.cells.halves[0]].walk_dest_x = coord_record->pos.x.fixed = (data[0x5] << 0x10) | (data[0x4] != 0 ? 0x8000 : 0);
        g_Actors[g_ScratchPad.cells.halves[0]].walk_dest_y = coord_record->pos.y.fixed = (data[0x7] << 0x10) | (data[0x6] != 0 ? 0x8000 : 0);
        g_Actors[g_ScratchPad.cells.halves[0]].unk_88                                  = 0;
        dist                                                                           = Area_HeightSample(coord_record->pos.x.fixed, coord_record->pos.y.fixed);
        dist_record                                                                    = SELF(Actor);
        COORD_INT(dist_record->pos.z)                                                  = dist;
        dist_record->header.mode                                                       = data[0x8];
        SELF(Actor)->header.step                                                       = data[0xA];
        SELF(Actor)->direction                                                         = data[0] & 0xF;
        SELF(Actor)->unk_06                                                            = data[0] >> 4;
        g_Actors[g_ScratchPad.cells.halves[0]].unk_7C                                  = 0xFFFF;
        g_Actors[g_ScratchPad.cells.halves[0]].unk_78                                  = data[0x9];
        g_Actors[g_ScratchPad.cells.halves[0]].unk_94                                  = 0x7F;
        Actor_SetOptionFlags(data + 0xB);
        if (data[0x3] & 0x80) {
            flags_record = SELF(Actor);
            flags_record->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        }
        SELF(Actor)->tint.bytes.rgb.r = 0;
        SELF(Actor)->tint.bytes.rgb.b = 0;
        SELF(Actor)->tint.bytes.rgb.g = 0;
        SELF(Actor)->tint.bytes.flags = data[0x3] & 0xF;
        bits_record                   = SELF(Actor);
        bits_record->mirror           = (bits_record->option_flags >> ACTOR_OPT_NO_SCRIPT_START) & 0x1;
        Script_Select(SELF(Actor)->direction);
        cell_record_a = SELF(Actor);
        Area_CellSetCode(COORD_INT(cell_record_a->pos.x), COORD_INT(cell_record_a->pos.y), 0x10);
        cell_record_b = SELF(Actor);
        if (COORD_FRAC(cell_record_b->pos.x) != 0) {
            Area_CellSetCode((s16)((u16)COORD_INT(cell_record_b->pos.x) + 1), COORD_INT(cell_record_b->pos.y), 0x10);
        }
        if (COORD_FRAC(SELF(Actor)->pos.y) != 0) {
            Area_CellSetCode(COORD_INT(SELF(Actor)->pos.x), (s16)(COORD_INT(SELF(Actor)->pos.y) + 1), 0x10);
        }
        cell_record_c = SELF(Actor);
        if ((COORD_FRAC(cell_record_c->pos.x) != 0) && (COORD_FRAC(cell_record_c->pos.y) != 0)) {
            Area_CellSetCode((s16)((u16)COORD_INT(cell_record_c->pos.x) + 1), (s16)((u16)COORD_INT(cell_record_c->pos.y) + 1), 0x10);
        }
        g_ScratchPad.cells.halves[0]++;
    }
}
