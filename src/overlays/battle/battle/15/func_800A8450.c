#include "battle_15.h"

MATCH void func_800A8450(void) {
    volatile u8* selection_index;
    u8           value;

    selection_index                                 = &g_BattleActiveBattler;
    g_BattlePartyBattlers[*selection_index].step_01 = 6u;
    value                                           = 4u;
    g_BattlePartyBattlers[*selection_index].unk_02  = value;
    g_BattlePartyBattlers[*selection_index].unk_03  = value;
    g_BattlePartyBattlers[*selection_index].unk_04  = 0u;
    BATTLE_WORK->step_01++;
}
