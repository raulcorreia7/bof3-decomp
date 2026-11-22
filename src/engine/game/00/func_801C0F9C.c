#include "game_00.h"

/* Slot-selection cursor D_80146262, its capacity g_Game.party_size, the per-slot
 * active bits g_Game.flags and the selection flag D_80146260. */

MATCH s32 func_801C0F9C(u8 source_row) {
    s32 i;
    s32 prev;

    if (g_Game.unk_3CE[4] != 0) {
        if (((g_Game.flags >> g_Game.unk_3CE[4]) & 0x1) == 0) {
            prev = g_Game.unk_3CE[4] - 1;
            if (((g_Game.flags >> prev) & 0x1) != 0) {
                goto select_slot;
            }
            if (g_Game.members[prev].header.mode != 1) {
                return 0;
            }
        }
    }
check_prev:
    if (((g_Game.flags >> (g_Game.unk_3CE[4] - 0x1)) & 1) == 0) {
        goto reload_slot;
    }
select_slot:
    i = g_Game.unk_3CE[4];
    if (i != 2) {
        goto scan_slot;
    }
    if (g_Game.members[0].header.mode != 1) {
        return 0;
    }
reload_slot:
    i = g_Game.unk_3CE[4];
scan_slot:
    if (i != 0) {
        if (((g_Game.flags >> i) & 0x1) == 0) {
            prev = i - 1;
            if (((g_Game.flags >> prev) & 0x1) != 0) {
                goto clear_bit;
            }
            if (g_Game.members[prev].header.mode != 1) {
                return 0;
            }
        }
    clear_bit:
        g_AreaWalkFlags &= ~BIT(g_Game.unk_3CE[4]);
    }
    {
        u8* cursor = &g_Game.unk_3CE[4];

        if (((g_Game.flags >> *cursor) & 0x1) == 0) {
            g_Game.members[*cursor].header.flags &= ~ACTOR_FLAG_HIDDEN;
            g_Game.members[*cursor].header.mode = D_801CD4AC[source_row].unk_00;
            g_Game.members[*cursor].header.step = D_801CD4AC[source_row].unk_01;
            g_Game.members[*cursor].unk_03      = D_801CD4AC[source_row].unk_02;
            g_Game.members[*cursor].unk_04      = D_801CD4AC[source_row].unk_03;
            g_Game.members[*cursor].status.field.flags.unsigned_value &= 0xFD;
        }
        (*cursor)++;
        if (*cursor != g_Game.party_size) {
            return 1;
        }
        g_Game.unk_3CE[2] = 0;
        g_Game.walk_flags &= ~AREA_WALK_ACCEPT_LOCK;
        return 2;
    }
}
