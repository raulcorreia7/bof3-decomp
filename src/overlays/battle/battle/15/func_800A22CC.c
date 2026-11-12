#include "battle_15.h"

MATCH void func_800A22CC(void) {
    volatile u8* battler_index_cell;
    u32          battler_index;

    func_800A3F28();
    battler_index_cell = &g_Battle.active_battler;
    battler_index      = LOBU(*battler_index_cell);
    if (BATTLER_IS_PLAYER(battler_index)) {
        g_Game.members[battler_index].u.turn.action_flags.volatile_value |= COMBATANT_FLAG_CHARGING;
        g_Game.members[*battler_index_cell].counter_136 = 0;
    } else {
        ENEMY_COMBATANT(battler_index).turn.action_flags.value |= COMBATANT_FLAG_CHARGING;
        ENEMY_COMBATANT(*battler_index_cell).unk_112 = 0;
    }
    Battle_RescaleStats(g_Battle.target);
}
