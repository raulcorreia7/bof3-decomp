#include "battle_03.h"

MATCH void func_801E71EC(void) {
    u8* field;
    u32 flags;
    u8  index;

    if ((g_BattleState & BATTLE_STATE_EFFECT_PLAYING) != 0) {
        field = &g_BattleEffectBattler->slot;
        index = *field;
        if (index < 3) {
            flags = g_BattlePartyBattlers[index].chr.status & (STATUS_BLIND | STATUS_SILENCED | STATUS_SLEEPING);
        } else {
            flags = ENEMY_COMBATANT(index).status & (STATUS_BLIND | STATUS_SILENCED | STATUS_SLEEPING);
        }
        if (flags == 0) {
            g_Task->header.mode = 0;
            return;
        }
        g_Task->header.mode = g_Task->header.mode - 1;
    }
}
