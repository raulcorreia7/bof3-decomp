#include "battle_15.h"

MATCH void func_8009EC48(void) {
    volatile u16* p_flag;
    u16           flag;
    u16           saved;
    u32           slot;
    u8            slot_arg;
    u8            kind_arg;

    slot = (*(u8*)&g_BattleActiveBattler);
    if (BATTLER_IS_PLAYER(slot)) {
        saved = g_Game.members[slot].chr.status & STATUS_BLIND;
        g_Game.members[slot].chr.status &= ~STATUS_BLIND;
    } else {
        saved = ENEMY_COMBATANT(slot).status & STATUS_BLIND;
        ENEMY_COMBATANT(slot).status &= ~STATUS_BLIND;
    }
    p_flag     = &g_BattleState;
    flag       = *p_flag;
    D_801EC324 = 0x64;
    *p_flag    = flag | BATTLE_STATE_CRITICAL;
    /* FAKE: statement boundary keeps the retail register order and schedule. */
    ORDER_LOCK(slot_arg = g_BattleActiveBattler);
    kind_arg                        = g_BattleTarget;
    g_BattleTargetRecord->hp_change = Battle_CalcDamage(slot_arg, kind_arg, BATTLE_ELEMENT_FROM_WEAPON);
    /* FAKE: keeps the slot reload after the pointer store. */
    MATCH_BARRIER();
    slot = (*(u8*)&g_BattleActiveBattler);
    if (BATTLER_IS_PLAYER(slot)) {
        g_Game.members[slot].chr.status |= saved;
        return;
    }
    ENEMY_COMBATANT(slot).status |= saved;
}
