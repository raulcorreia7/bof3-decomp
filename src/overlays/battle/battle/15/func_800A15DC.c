#include "battle_15.h"

/* sets flag bit 0x80 and increments the battler counter while below two.
 */
MATCH void func_800A15DC(void) {
    u32          playerIndex;
    s32          enemy_index;
    u8           counter;
    volatile u8* battlerPtr;
    u32          battler;

    Battle_MarkDamageApplied();
    battlerPtr = &g_Battle.active_battler;
    if ((battler = LOBU(*battlerPtr)) < 3U) {
        g_Game.members[battler].u.turn.action_flags.value |= COMBATANT_FLAG_MEDITATION;
        playerIndex = *battlerPtr;
        counter     = g_Game.members[playerIndex].unk_139;
        if (counter < 2U) {
            g_Game.members[playerIndex].unk_139 = counter + 1;
        }
    } else {
        ENEMY_COMBATANT(battler).turn.action_flags.value |= COMBATANT_FLAG_MEDITATION;
        enemy_index = *battlerPtr - 3;
        counter     = g_BattleEnemyBattlers[enemy_index].unk_115;
        if (counter < 2U) {
            g_BattleEnemyBattlers[enemy_index].unk_115 = counter + 1;
        }
    }
}
