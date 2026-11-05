#include "battle_03.h"

/* Queued-slot position/offset tables (stride noted per use). The 2-D form for
 * D_80145F09 mirrors the matched Battle_SetTextPartyName, which emits the original's
 * `lui+%lo` relocation pair (a `volatile` 1-D declaration forces gcc to
 * materialize the base as `lui+addiu`, diverging). */

/* derives queued-slot position offsets from either the local or enemy
 * source tables and writes them into the current queued object.
 */
MATCH void func_801E8DD8(void) {
    PartyBattler* active = D_801EB4E0;
    s8            offset_x;
    u8            offset_y;
    s32           row;

    if (active->slot < 3u) {
        PartyBattler* dst;

        dst = g_SpadWork;
        offset_x =
            (s8)g_BattlePanelOffsets[(u32)D_80145F09[active->slot][0] * 8u + (u32)active->word_08.byte.facing_08 * 2u];
        dst->unk_2E.half = active->unk_2E.half + offset_x;
        if (active->word_08.byte.facing_08 < 2u) {
            row      = active->slot;
            offset_y = s_BattlePanelYOffsets[(u32)D_80145F09[row][0] * 2u];
        } else {
            row      = active->slot;
            offset_y = D_801EB109[(u32)D_80145F09[row][0] * 2u];
        }
        dst->unk_30.half = active->unk_30.half - offset_y - 8u;
        g_SpadWork->z    = D_801EB4E0->z;
    } else {
        row = active->slot;
        row -= 3;
        offset_x                = (s8)D_801EB712[row * 0x118];
        g_SpadWork->unk_2E.half = active->unk_2E.half + offset_x;
        row                     = active->slot;
        row -= 3;
        offset_y                = ENCOUNTER_ENEMIES[D_801EB710[row * 0x118]].height;
        g_SpadWork->unk_30.half = active->unk_30.half - offset_y - 8u;
        g_SpadWork->z           = active->z;
    }
}
