#include "battle_15.h"

/* Main-executable battle-selection cell consumed by the countdown arm. */

MATCH void func_800AE09C(void) {
    u8 count;

    count = SELF(Actor)->timer;
    if (count == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    } else {
        SELF(Actor)->timer = count - 1;
    }
}
