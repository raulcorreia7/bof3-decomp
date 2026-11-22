#include "battle_15.h"

/* publishes the active battler's work record for the pending-action update: local battlers (type under 3)
 * take their 0x140-byte record and queue the two effect bytes; enemy battlers queue the base halfword, or hand the
 * record's byte (doubled, tagged 0x600) to the selection-voice step.
 */
/* func_800AFC98 */
MATCH void Battle_PlayActiveBattlerSE(s32 effect_0, s32 effect_1) {
    u32 type;

    u8  sel;
    s32 test;
    u16 other;

    type  = *(u8*)&g_Battle.active_battler;
    sel   = effect_0;
    other = effect_1;
    if (type < 3u) {
        g_GameState = &g_Game.members[type];
        test        = sel & BYTE_MASK;
        if (test != 0) {
            Battle_PlayEffectSE((effect_0 + 1) & BYTE_MASK);
        }
        if ((u8)other != 0u) {
            Battle_PlayEffectSE((u8)other);
        }
    } else if (BATTLE_IS_SCRIPTED()) {
        Battle_PlayEnemySE(*ENEMY_COMBATANT(type).unk_E8);
    } else {
        SND_SEQueueSelection((ENEMY_COMBATANT(type).type * 2u) | 0x600u);
    }
}
