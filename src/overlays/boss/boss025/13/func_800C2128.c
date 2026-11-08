#include "boss025_13.h"

MATCH void func_800C2128(void) {
    if (!(g_Battle.boss_flags & 0x8)) {
        g_Battle.target_selector = 3;
    } else {
        g_Battle.action_type = BATTLE_ACTION_NONE;
    }
}
