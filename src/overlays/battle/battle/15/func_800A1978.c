#include "battle_15.h"

MATCH void func_800A1978(void) {
    u32 mode;
    u16 base;

    if (rand() & 1) {
        if (func_800A3A10(g_BattleActiveBattler, g_BattleTarget) == 0) {
            mode = *MEM_PTR(u8, &g_BattleTarget);
            if (mode < 3u) {
                base = g_BattlePartyBattlers[mode].chr.hp;
            } else {
                base = ENEMY_COMBATANT(mode).hp;
            }
            ((s16*)g_BattleTargetRecord)[2] = base - 1;
        }
    }
}
