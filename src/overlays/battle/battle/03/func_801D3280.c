#include "battle_03.h"

MATCH void func_801D3280(void) {
    if (D_801463C2 == 0) {
        g_Battle.phase.step     = 3;
        g_Battle.phase.sub_step = 0;
        g_Battle.ui_step        = 0;
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
    }
}
