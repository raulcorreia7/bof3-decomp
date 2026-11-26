#include "battle_03.h"

/* func_801E6D28 */
MATCH void Battle_WaitAilment(void) {
    u8*  field;
    u16* status;
    u32  flags;
    u8   index;
    u32  slot;

    if ((g_Battle.flags & BATTLE_STATE_EFFECT_LOADING) != 0 && g_BattleEffectBattler->slot == g_Battle.active_battler) {
        return;
    }
    field = &g_BattleEffectBattler->slot;
    index = *field;
    if (index < 3U) {
        if ((Battle_SlotIsBlocked(index) & BYTE_MASK) != 0) {
            return;
        }
        field  = &g_BattleEffectBattler->slot;
        index  = *field;
        status = &g_Game.members[index].chr.status;
        flags  = *status & (STATUS_BLIND | STATUS_SILENCED | STATUS_SLEEPING);
    } else {
        if ((Battle_SlotIsBlocked(index) & BYTE_MASK) != 0) {
            return;
        }
        field  = &g_BattleEffectBattler->slot;
        index  = *field;
        slot   = index - 3;
        status = &g_BattleEnemyBattlers[slot].status;
        flags  = *status & (STATUS_BLIND | STATUS_SILENCED | STATUS_SLEEPING);
    }
    if (flags != 0) {
        SELF(PartyMember)->header.mode++;
    }
}
