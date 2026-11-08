#include "battle_15.h"

/* Non-volatile view of the active battler index (0x80146374): battle_15.h
 * declares it volatile, whose byte load cannot feed the index arithmetic
 * without an extra mask. */

MATCH void func_800A0A40(void) {
    volatile u16* pFlag;
    u16           flag;
    u32           battler_index;

    pFlag         = &g_BattleState;
    flag          = *pFlag;
    battler_index = (*(u8*)&g_BattleActiveBattler);
    *pFlag        = flag | BATTLE_STATE_DAMAGE_APPLIED;
    if (BATTLER_IS_PLAYER(battler_index)) {
        u16 base;

        /* FAKE: the destination slot is volatile: without it the scheduler sinks
         * the store past the volatile index reload and the load-delay `nop` the
         * original emits disappears. */
        base                                                    = g_Game.members[battler_index].chr.hp;
        /* FAKE: volatile-drop keeps the original load and store order. */
        ((volatile BattleTurn*)g_BattleTargetRecord)->hp_change = base - 1;
        BATTLE_ACTIVE_PARTY.chr.hp                              = 1;
    } else {
        u16 base;

        base                                                    = ENEMY_COMBATANT(battler_index).hp;
        /* FAKE: volatile-drop keeps the original load and store order. */
        ((volatile BattleTurn*)g_BattleTargetRecord)->hp_change = base - 1;
        ENEMY_COMBATANT(g_BattleActiveBattler).hp               = 1;
    }
}
