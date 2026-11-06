#include "battle_15.h"

extern u8 D_801CA71B[];

MATCH void func_8009DCC8(void) {
    s32 index;
    u8  battler_index;
    u8  selection_kind;
    u8  base_value;

    index                           = g_BattleActionId;
    battler_index                   = *(u8*)(void*)&g_BattleActiveBattler;
    selection_kind                  = *(u8*)(void*)&g_BattleTarget;
    base_value                      = D_801CA71B[4 * (5 * index)];
    g_BattleTargetRecord->hp_change = func_800A2880(battler_index, selection_kind, base_value, 0);
}
