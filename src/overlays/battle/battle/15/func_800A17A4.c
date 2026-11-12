#include "battle_15.h"

/* gcc 2.7.2 treats a union member as an aggregate access, so the slot byte
 * is reloaded after each row store, as in retail. */
#define ACTIVE_BATTLER (((BattleSelectionContext*)&g_Battle.target)->sel)

/* clears the active battler's eight status bytes and its status flag bits, then
 * passes that battler to Battle_RescaleStats.
 */
MATCH void func_800A17A4(void) {
    u8 i;

    func_800A3F28();
    if (BATTLER_IS_PLAYER(ACTIVE_BATTLER)) {
        for (i = 0; i < 8; i++) {
            D_80145FB4[ACTIVE_BATTLER].pad_08[i] = 0;
        }
        g_Game.members[ACTIVE_BATTLER].u.turn.damage_flags.volatile_value &= ~(COMBATANT_FLAG_REPRISAL | COMBATANT_FLAG_DAMAGE_IMMUNE);
        g_Game.members[ACTIVE_BATTLER].u.turn.action_flags.volatile_value &= 0xFFFBC43F;
        Battle_RescaleStats(ACTIVE_BATTLER);
    } else {
        for (i = 0; i < 8; i++) {
            ENEMY_COMBATANT(ACTIVE_BATTLER).stat_multipliers[i] = 0;
        }
        ENEMY_COMBATANT(ACTIVE_BATTLER).turn.damage_flags.value &= ~(COMBATANT_FLAG_REPRISAL | COMBATANT_FLAG_DAMAGE_IMMUNE);
        ENEMY_COMBATANT(ACTIVE_BATTLER).turn.action_flags.value &= 0xFFFBC43F;
        Battle_RescaleStats(ACTIVE_BATTLER);
    }
}
