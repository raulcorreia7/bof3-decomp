#include "game_00.h"

/* Slot-selection cursor D_80146262, its capacity g_Game.party_size, the per-slot
 * active bits g_Game.flags and the selection flag D_80146260. */

MATCH s32 func_801C0F9C(u8 source_row) {
    s32 i;
    s32 prev;

    if (D_80146262 != 0) {
        if (((g_Game.flags >> D_80146262) & 0x1) == 0) {
            prev = D_80146262 - 1;
            if (((g_Game.flags >> prev) & 0x1) != 0) {
                goto select_slot; /* the previous slot is active, take it */
            }
            if (g_Game.members[prev].header.mode != 1) {
                return 0;
            }
        }
    }
    /* The two labelled exits below are the retail block layout: the tests at the
     * head and at check_prev share select_slot, and select_slot falls back into
     * the reloaded cursor. */
check_prev:
    if (((g_Game.flags >> (D_80146262 - 0x1)) & 1) == 0) {
        goto reload_slot; /* the previous slot is free, reload the cursor */
    }
select_slot:
    i = D_80146262;
    if (i != 2) {
        goto scan_slot; /* the cursor is not 2, scan the slot */
    }
    if (g_Game.members[0].header.mode != 1) {
        return 0;
    }
reload_slot:
    i = D_80146262;
scan_slot:
    if (i != 0) {
        if (((g_Game.flags >> i) & 0x1) == 0) {
            prev = i - 1;
            if (((g_Game.flags >> prev) & 0x1) != 0) {
                goto clear_bit; /* the slot's active bit is clear, clear the selection bit */
            }
            if (g_Game.members[prev].header.mode != 1) {
                return 0;
            }
        }
    clear_bit:
        g_AreaWalkFlags &= ~BIT(D_80146262);
    }
    {
        u8* cursor = &D_80146262;

        if (((g_Game.flags >> *cursor) & 0x1) == 0) {
            g_Game.members[*cursor].header.flags &= ~ACTOR_FLAG_HIDDEN;
            g_Game.members[*cursor].header.mode = D_801CD4AC[source_row].unk_00;
            g_Game.members[*cursor].header.step = D_801CD4AC[source_row].unk_01;
            g_Game.members[*cursor].unk_03      = D_801CD4AC[source_row].unk_02;
            g_Game.members[*cursor].unk_04      = D_801CD4AC[source_row].unk_03;
            g_Game.members[*cursor].status.field.flags_12C.u8_value &= 0xFD;
        }
        (*cursor)++;
        if (*cursor != g_Game.party_size) {
            return 1;
        }
        D_80146260 = 0;
        g_Game.walk_flags &= ~AREA_WALK_ACCEPT_LOCK;
        return 2;
    }
}
