#include "battle_15.h"

MATCH void func_8009EFB8(void) {
    u16 index;
    u8  battler_index;
    u16 mask;
    u8  selection_kind;

    index                           = g_BattleActionId;
    battler_index                   = g_BattleActiveBattler;
    mask                            = D_801CA71C[index].mask & 0x1FFu;
    selection_kind                  = g_BattleTarget;
    ((s16*)g_BattleTargetRecord)[2] = (s16)Battle_CalcDamage(battler_index, selection_kind, mask);
}
