#include "battle_03.h"

/* derives queued-slot position offsets from either the local or enemy
 * source tables and writes them into the current queued object.
 */
MATCH void func_801E8DD8(void) {
    u8* slot = (u8*)g_BattleEffectBattler;
    s8  offset_x;
    u8  offset_y;
    s32 battler_slot;

    if (slot[5] < 3u) {
        PartyMember* dst;

        dst                 = SELF(PartyMember);
        offset_x            = g_BattlePanelOffsets[g_Game.members[slot[5]].chr.character_id * 8u + slot[8] * 2u];
        dst->screen_x.value = *(u16*)((slot + 0x2Eu)) + offset_x;
        if (slot[8] < 2u) {
            battler_slot = slot[5];
            offset_y     = s_BattlePanelYOffsets[g_Game.members[battler_slot].chr.character_id * 2u];
        } else {
            battler_slot = slot[5];
            offset_y     = D_801EB109[g_Game.members[battler_slot].chr.character_id * 2u];
        }
        dst->screen_y.value      = *(u16*)((slot + 0x30u)) - offset_y - 8u;
        SELF(PartyMember)->depth = g_BattleEffectBattler->depth;
    } else {
        battler_slot = slot[5];
        battler_slot -= 3;
        offset_x                          = g_BattleEnemyBattlers[battler_slot].panel_offset_x;
        SELF(PartyMember)->screen_x.value = *(u16*)((slot + 0x2Eu)) + offset_x;
        battler_slot                      = slot[5];
        battler_slot -= 3;
        offset_y                          = ENCOUNTER_ENEMIES[g_BattleEnemyBattlers[battler_slot].type].height;
        SELF(PartyMember)->screen_y.value = *(u16*)((slot + 0x30u)) - offset_y - 8u;
        SELF(PartyMember)->depth          = *(u16*)((slot + 0x32u));
    }
}
