#include "boss013_16.h"

MATCH void func_800C1E90(void) {
    u8* flags;

    flags = &g_Battle.boss_flags;
    if (*flags & 0x1) {
        g_Battle.action_type = 3;
    } else if (D_800C26E0 != 0) {
        D_800C26E0--;
        g_Battle.action_type = BATTLE_ACTION_NONE;
    } else {
        g_Battle.action_type     = BATTLE_ACTION_ATTACK;
        g_Battle.target_selector = 4;
        *flags |= 1;
        D_80146322--;
    }
}
