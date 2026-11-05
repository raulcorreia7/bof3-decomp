#include "battle_15.h"

MATCH void func_800A0660(void) {
    u8* battler;
    u8  kind;
    u16 saved;
    u32 slot;

    slot = (*(u8*)&g_BattleActingBattler);
    if (BATTLER_IS_PLAYER(slot)) {
        saved = g_BattlePartyBattlers[slot].stats.status & STATUS_BLIND;
        g_BattlePartyBattlers[slot].stats.status &= ~STATUS_BLIND;
    } else {
        saved = ENEMY_COMBATANT(slot).status_82 & STATUS_BLIND;
        ENEMY_COMBATANT(slot).status_82 &= 0xFFF7;
    }
    battler                 = (u8*)&g_BattleActingBattler;
    D_801EC324              = 0x64;
    slot                    = *battler;
    kind                    = (*(u8*)&g_BattleTarget);
    g_BattleTargetRecord[2] = Battle_CalcDamage(slot, kind, 0xFFFF) / 2;
    slot                    = *battler;
    if (BATTLER_IS_PLAYER(slot)) {
        g_BattlePartyBattlers[slot].stats.status |= saved;
        return;
    }
    ENEMY_COMBATANT(slot).status_82 |= saved;
}
