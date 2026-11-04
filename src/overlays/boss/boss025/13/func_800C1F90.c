#include "boss025_13.h"

MATCH void func_800C1F90(void) {
    if (func_801E30F8()) {
        func_800A9820(g_BattleTargetSelector);
        if (RANDOM_MASK(3) == 0) {
            g_BattleState |= BATTLE_STATE_CRITICAL;
            g_BattleBossFlags |= 0x10;
            Battle_AllocEffect(0, 2);
        }
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E567C();
    }
}
