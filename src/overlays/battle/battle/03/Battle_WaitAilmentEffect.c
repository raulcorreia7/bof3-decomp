#include "battle_03.h"

/* func_801E71EC */
MATCH void Battle_WaitAilmentEffect(void) {
    u8* field;
    u32 flags;
    u8  index;

    if ((g_Battle.flags & BATTLE_STATE_EFFECT_PLAYING) != 0) {
        field = &g_BattleEffectBattler->slot;
        index = *field;
        if (index < 3) {
            flags = g_Game.members[index].chr.status & (STATUS_BLIND | STATUS_SILENCED | STATUS_SLEEPING);
        } else {
            flags = ENEMY_COMBATANT(index).status & (STATUS_BLIND | STATUS_SILENCED | STATUS_SLEEPING);
        }
        if (flags == 0) {
            SELF(PartyMember)->header.mode = 0;
            return;
        }
        SELF(PartyMember)->header.mode = SELF(PartyMember)->header.mode - 1;
    }
}
