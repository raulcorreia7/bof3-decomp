#include "battle_15.h"

MATCH void func_8009FEF4(void) {
    BattleTurn* record;
    s16         value;

    g_BattleActionType    = BATTLE_ACTION_ABILITY;
    MEM(u16, 0x801463C0u) = 0x66;
    value                 = func_800A2880(g_BattleActiveBattler, g_BattleTarget, D_801CAF13, 0);
    ((volatile BattleTurn*)g_BattleTargetRecord)->hp_change = value;
    record                                                  = g_BattleTargetRecord;
    record->hp_change                                       = (s16)(u16)record->hp_change / 2;
}
