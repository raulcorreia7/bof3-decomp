#include "battle_03.h"

MATCH void func_801E4F34(void) {
    if ((g_Battle.flags & BATTLE_STATE_EFFECT_PLAYING) == 0u) {
        return;
    }

    func_801E567C();
}
