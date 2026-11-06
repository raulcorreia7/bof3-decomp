#include "battle_15.h"

MATCH void func_800A0660(void) {
    u8* battler;
    u8  kind;
    u16 saved;
    u32 slot;

    slot = (*(u8*)&g_BattleActiveBattler);
    if (BATTLER_IS_PLAYER(slot)) {
        saved = g_BattlePartyBattlers[slot].chr.status & STATUS_BLIND;
        g_BattlePartyBattlers[slot].chr.status &= ~STATUS_BLIND;
    } else {
        saved = ENEMY_COMBATANT(slot).status & STATUS_BLIND;
        ENEMY_COMBATANT(slot).status &= ~STATUS_BLIND;
    }
    battler                         = (u8*)&g_BattleActiveBattler;
    D_801EC324                      = 0x64;
    slot                            = *battler;
    kind                            = (*(u8*)&g_BattleTarget);
    g_BattleTargetRecord->hp_change = Battle_CalcDamage(slot, kind, BATTLE_ELEMENT_FROM_WEAPON) / 2;
    slot                            = *battler;
    if (BATTLER_IS_PLAYER(slot)) {
        g_BattlePartyBattlers[slot].chr.status |= saved;
        return;
    }
    ENEMY_COMBATANT(slot).status |= saved;
}
