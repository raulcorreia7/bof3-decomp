#include "battle_15.h"

/* sets flag bit 0x80 and increments the battler counter while below two.
 */
MATCH void func_800A15DC(void) {
    u32          playerIndex;
    s32          enemyRowOffset;
    u8           counter;
    volatile u8* battlerPtr;
    u32          battler;

    func_800A3F28();
    battlerPtr = &g_BattleActiveBattler;
    if ((battler = LOBU(*battlerPtr)) < 3U) {
        g_BattlePartyBattlers[battler].turn.action_flags.value |= COMBATANT_FLAG_MEDITATION;
        playerIndex = *battlerPtr;
        counter     = g_BattlePartyBattlers[playerIndex].unk_139;
        if (counter < 2U) {
            g_BattlePartyBattlers[playerIndex].unk_139 = counter + 1;
        }
    } else {
        ENEMY_COMBATANT(battler).turn.action_flags.value |= COMBATANT_FLAG_MEDITATION;
        enemyRowOffset = (*battlerPtr - 3) * BATTLE_ENEMY_STRIDE;
        counter        = D_801EB745[enemyRowOffset];
        if (counter < 2U) {
            D_801EB745[enemyRowOffset] = counter + 1;
        }
    }
}
