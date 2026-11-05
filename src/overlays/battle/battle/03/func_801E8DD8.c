#include "battle_03.h"

/* Queued-slot position/offset tables (stride noted per use). The 2-D form for
 * D_80145F09 mirrors the matched Battle_SetTextPartyName, which emits the original's
 * `lui+%lo` relocation pair (a `volatile` 1-D declaration forces gcc to
 * materialize the base as `lui+addiu`, diverging). */

/* derives queued-slot position offsets from either the local or enemy
 * source tables and writes them into the current queued object.
 */
MATCH void func_801E8DD8(void) {
    u8* slot = (u8*)D_801EB4E0;
    s8  offset_x;
    u8  offset_y;
    s32 row;

    if (slot[5] < 3u) {
        PartyBattler* dst;

        dst              = g_SpadWork;
        offset_x         = (s8)g_BattlePanelOffsets[(u32)D_80145F09[slot[5]][0] * 8u + (u32)slot[8] * 2u];
        dst->unk_2E.half = *(u16*)((slot + 0x2Eu)) + offset_x;
        if (slot[8] < 2u) {
            row      = slot[5];
            offset_y = s_BattlePanelYOffsets[(u32)D_80145F09[row][0] * 2u];
        } else {
            row      = slot[5];
            offset_y = D_801EB109[(u32)D_80145F09[row][0] * 2u];
        }
        dst->unk_30.half = *(u16*)((slot + 0x30u)) - offset_y - 8u;
        g_SpadWork->z    = *(u16*)(((u8*)D_801EB4E0 + 0x32u));
    } else {
        row = slot[5];
        row -= 3;
        offset_x                = (s8)D_801EB712[row * 0x118];
        g_SpadWork->unk_2E.half = *(u16*)((slot + 0x2Eu)) + offset_x;
        row                     = slot[5];
        row -= 3;
        offset_y                = ENCOUNTER_ENEMIES[D_801EB710[row * 0x118]].height;
        g_SpadWork->unk_30.half = *(u16*)((slot + 0x30u)) - offset_y - 8u;
        g_SpadWork->z           = *(u16*)((slot + 0x32u));
    }
}
