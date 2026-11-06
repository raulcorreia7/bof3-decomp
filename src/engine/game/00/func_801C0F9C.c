#include "game_00.h"

/* Slot-selection cursor D_80146262, its capacity g_PartySize, the per-slot
 * active bits g_GameFlags and the selection flag D_80146260. */

MATCH s32 func_801C0F9C(u8 source_row) {
    s32 i;
    s32 prev;

    if (D_80146262 != 0) {
        if (((g_GameFlags >> D_80146262) & 1) == 0) {
            prev = D_80146262 - 1;
            if (((g_GameFlags >> prev) & 1) != 0) {
                goto select_slot; /* the previous slot is active, take it */
            }
            if (g_BattlePartyBattlers[prev].header.mode != 1) {
                return 0;
            }
        }
    }
    /* The two labelled exits below are the retail block layout: the tests at the
     * head and at check_prev share select_slot, and select_slot falls back into
     * the reloaded cursor. */
check_prev:
    if (((g_GameFlags >> (D_80146262 - 1)) & 1) == 0) {
        goto reload_slot; /* the previous slot is free, reload the cursor */
    }
select_slot:
    i = D_80146262;
    if (i != 2) {
        goto scan_slot; /* the cursor is not 2, scan the slot */
    }
    if (g_BattlePartyBattlers[0].header.mode != 1) {
        return 0;
    }
reload_slot:
    i = D_80146262;
scan_slot:
    if (i != 0) {
        if (((g_GameFlags >> i) & 1) == 0) {
            prev = i - 1;
            if (((g_GameFlags >> prev) & 1) != 0) {
                goto clear_bit; /* the slot's active bit is clear, clear the selection bit */
            }
            if (g_BattlePartyBattlers[prev].header.mode != 1) {
                return 0;
            }
        }
    clear_bit:
        g_AreaWalkFlags &= ~BIT(D_80146262);
    }
    {
        u8* cursor = &D_80146262;

        if (((g_GameFlags >> *cursor) & 1) == 0) {
            g_BattlePartyBattlers[*cursor].header.flags &= ~ACTOR_FLAG_HIDDEN;
            g_BattlePartyBattlers[*cursor].header.mode = D_801CD4AC[source_row].unk_00;
            g_BattlePartyBattlers[*cursor].header.step = D_801CD4AC[source_row].unk_01;
            g_BattlePartyBattlers[*cursor].unk_03      = D_801CD4AC[source_row].unk_02;
            g_BattlePartyBattlers[*cursor].unk_04      = D_801CD4AC[source_row].unk_03;
            g_BattlePartyBattlers[*cursor].unk_12C[0] &= 0xFD;
        }
        (*cursor)++;
        if (*cursor != g_PartySize) {
            return 1;
        }
        D_80146260 = 0;
        g_AreaWalkFlags &= ~AREA_WALK_ACCEPT_LOCK;
        return 2;
    }
}
