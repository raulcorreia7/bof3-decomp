#include "battle_15.h"

MATCH void func_800A0660(void) {
    u8* battler;
    u8  kind;
    u16 saved;
    u32 slot;

    slot = (*(u8*)&g_Battle.active_battler);
    if (BATTLER_IS_PLAYER(slot)) {
        saved = g_Game.members[slot].chr.status & STATUS_BLIND;
        g_Game.members[slot].chr.status &= ~STATUS_BLIND;
    } else {
        saved = ENEMY_COMBATANT(slot).status & STATUS_BLIND;
        ENEMY_COMBATANT(slot).status &= ~STATUS_BLIND;
    }
    battler                           = (u8*)&g_Battle.active_battler;
    D_801EC324                        = 0x64;
    slot                              = *battler;
    kind                              = (*(u8*)&g_Battle.target);
    g_Battle.target_record->hp_change = Battle_CalcDamage(slot, kind, BATTLE_ELEMENT_FROM_WEAPON) / 2;
    slot                              = *battler;
    if (BATTLER_IS_PLAYER(slot)) {
        g_Game.members[slot].chr.status |= saved;
        return;
    }
    ENEMY_COMBATANT(slot).status |= saved;
}
