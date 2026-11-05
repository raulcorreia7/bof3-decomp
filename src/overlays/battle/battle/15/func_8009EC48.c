#include "battle_15.h"

MATCH void func_8009EC48(void) {
    volatile u16* p_flag;
    u16           flag;
    u16           saved;
    u32           slot;
    u8            slot_arg;
    u8            kind_arg;

    slot = (*(u8*)&g_BattleActingBattler);
    if (BATTLER_IS_PLAYER(slot)) {
        saved = g_BattlePartyBattlers[slot].stats.status & STATUS_BLIND;
        g_BattlePartyBattlers[slot].stats.status &= ~STATUS_BLIND;
    } else {
        saved = ENEMY_COMBATANT(slot).status_82 & STATUS_BLIND;
        ENEMY_COMBATANT(slot).status_82 &= ~STATUS_BLIND;
    }
    p_flag     = &g_BattleState;
    flag       = *p_flag;
    D_801EC324 = 0x64;
    *p_flag    = flag | BATTLE_STATE_CRITICAL;
    /* FAKE: statement boundary keeps the retail register order and schedule. */
    ORDER_LOCK(slot_arg = g_BattleActingBattler);
    kind_arg                = g_BattleTarget;
    g_BattleTargetRecord[2] = Battle_CalcDamage(slot_arg, kind_arg, 0xFFFF);
    /* FAKE: keeps the slot reload after the pointer store. */
    MATCH_BARRIER();
    slot = (*(u8*)&g_BattleActingBattler);
    if (BATTLER_IS_PLAYER(slot)) {
        g_BattlePartyBattlers[slot].stats.status |= saved;
        return;
    }
    ENEMY_COMBATANT(slot).status_82 |= saved;
}
