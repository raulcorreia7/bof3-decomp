#include "battle_15.h"

/* publishes the active battler's work record for the pending-action update: local battlers (kind under 3)
 * take their 0x140-byte record and queue the two effect bytes; enemy battlers queue the base halfword, or hand the
 * record's byte (doubled, tagged 0x600) to the selection-voice step.
 */
/* func_800AFC98 */
MATCH void Battle_PlayActiveBattlerSE(s32 effect_0, s32 effect_1) {
    u32 kind;

    /* FAKE: pins the tested byte copy. */
    FAKE_REG(s32, sel, "a2");
    /* FAKE: pins the branch test result to v0. */
    FAKE_REG(s32, test, "v0");
    /* FAKE: holds the effect_1 copy to the retail s0 home. */
    FAKE_REG(s32, other, "s0");

    kind  = *(u8*)&g_Battle.active_battler;
    sel   = effect_0;
    other = effect_1;
    if (kind < 3u) {
        g_GameState = &g_Game.members[kind];
        test        = sel & BYTE_MASK;
        if (test != 0) {
            Battle_PlayEffectSE((effect_0 + 1) & BYTE_MASK);
        }
        if ((u8)other != 0u) {
            Battle_PlayEffectSE((u8)other);
        }
    } else if (BATTLE_IS_SCRIPTED()) {
        Battle_PlayEnemySE(*ENEMY_COMBATANT(kind).unk_E8);
    } else {
        SND_QueueSelectionSE((ENEMY_COMBATANT(kind).type * 2u) | 0x600u);
    }
}
