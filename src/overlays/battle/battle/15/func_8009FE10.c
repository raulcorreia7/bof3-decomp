#include "battle_15.h"

MATCH void func_8009FE10(void) {
    func_800A31E0(g_BattleTarget, 0x40);
    g_BattleTargetRecord->target_flags |= 2;
    g_BattleTargetRecord->hp_change = -0x14;
    g_BattleTargetRecord->ap_change = -4;
}
