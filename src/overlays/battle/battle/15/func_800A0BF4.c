#include "battle_15.h"

MATCH void func_800A0BF4(void) {
    ((volatile BattleTurn*)g_BattleTargetRecord)->hp_change = func_800A30E8(g_BattleActiveBattler, g_BattleTarget);
    func_800A36F0(g_BattleTarget, 0xBFC);
}
