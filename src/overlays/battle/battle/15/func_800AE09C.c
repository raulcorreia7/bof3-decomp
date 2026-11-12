#include "battle_15.h"
#include "area/spad.h"

/* Main-executable battle-selection cell consumed by the countdown arm. */

MATCH void func_800AE09C(void) {
    u8 count;

    count = g_Task->timer;
    if (count == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    } else {
        g_Task->timer = count - 1;
    }
}
