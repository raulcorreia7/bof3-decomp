#include "battle_03.h"

/* derives queued-slot position offsets from either the local or enemy
 * source tables and writes them into the current queued object.
 */
MATCH void func_801E8DD8(void) {
    u8* slot = (u8*)g_BattleEffectBattler;
    s8  offset_x;
    u8  offset_y;
    s32 row;

    if (slot[5] < 3u) {
        PartyBattler* dst;

        dst              = g_Task;
        offset_x         = g_BattlePanelOffsets[g_BattlePartyBattlers[slot[5]].chr.character_id * 8u + slot[8] * 2u];
        dst->unk_2E.half = *(u16*)((slot + 0x2Eu)) + offset_x;
        if (slot[8] < 2u) {
            row      = slot[5];
            offset_y = s_BattlePanelYOffsets[g_BattlePartyBattlers[row].chr.character_id * 2u];
        } else {
            row      = slot[5];
            offset_y = D_801EB109[g_BattlePartyBattlers[row].chr.character_id * 2u];
        }
        dst->unk_30.half = *(u16*)((slot + 0x30u)) - offset_y - 8u;
        g_Task->depth    = *(u16*)(((u8*)g_BattleEffectBattler + 0x32u));
    } else {
        row = slot[5];
        row -= 3;
        offset_x            = g_BattleEnemyBattlers[row].unk_E2;
        g_Task->unk_2E.half = *(u16*)((slot + 0x2Eu)) + offset_x;
        row                 = slot[5];
        row -= 3;
        offset_y            = ENCOUNTER_ENEMIES[g_BattleEnemyBattlers[row].kind].height;
        g_Task->unk_30.half = *(u16*)((slot + 0x30u)) - offset_y - 8u;
        g_Task->depth       = *(u16*)((slot + 0x32u));
    }
}
