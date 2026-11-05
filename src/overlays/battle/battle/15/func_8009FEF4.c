#include "battle_15.h"

MATCH void func_8009FEF4(void) {
    s16* record;
    s16  value;

    g_BattleActionType      = 4;
    MEM(u16, 0x801463C0u)   = 0x66;
    value                   = func_800A2880(g_BattleActiveBattler, g_BattleTarget, D_801CAF13, 0);
    g_BattleTargetRecord[2] = value;
    record                  = (s16*)g_BattleTargetRecord;
    record[2]               = (s16)((u16*)record)[2] / 2;
}
