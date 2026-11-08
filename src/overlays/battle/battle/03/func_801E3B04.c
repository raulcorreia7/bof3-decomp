#include "battle_03.h"

MATCH void func_801E3B04(void) {
    if (func_801E30F8() != 0u) {
        func_800A9820(g_Battle.target_selector);
        Battle_TriggerCritical();
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E567C();
    }
}
