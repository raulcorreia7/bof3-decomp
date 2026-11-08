#include "battle_03.h"

MATCH void func_801E6D28(void) {
    u8*  field;
    u16* row_flags;
    u32  flags;
    u8   index;
    u32  slot;

    if ((g_BattleState & BATTLE_STATE_EFFECT_LOADING) != 0 && g_BattleEffectBattler->slot == g_BattleActiveBattler) {
        return;
    }
    field = &g_BattleEffectBattler->slot;
    index = *field;
    if (index < 3U) {
        if ((Battle_SlotIsBlocked(index) & BYTE_MASK) != 0) {
            return;
        }
        field     = &g_BattleEffectBattler->slot;
        index     = *field;
        row_flags = &g_Game.members[index].chr.status;
        flags     = *row_flags & (STATUS_BLIND | STATUS_SILENCED | STATUS_SLEEPING);
    } else {
        if ((Battle_SlotIsBlocked(index) & BYTE_MASK) != 0) {
            return;
        }
        field     = &g_BattleEffectBattler->slot;
        index     = *field;
        slot      = index - 3;
        row_flags = &g_BattleEnemyBattlers[slot].status;
        flags     = *row_flags & (STATUS_BLIND | STATUS_SILENCED | STATUS_SLEEPING);
    }
    if (flags != 0) {
        g_Task->header.mode++;
    }
}
