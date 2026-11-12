#include "boss025_13.h"

MATCH void func_800C1F90(void) {
    if (func_801E30F8()) {
        Battle_MarkDamaged(g_Battle.target_selector);
        if (RANDOM_MASK(3) == 0) {
            g_Battle.state |= BATTLE_STATE_CRITICAL;
            g_Battle.boss_flags |= 0x10;
            Battle_AllocEffect(0, 2);
        }
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E567C();
    }
}
