#include "battle_03.h"

MATCH void func_801D3F6C(void) {
    if (EMI_IsReady() != 0) {
        if (BATTLE_IS_SCRIPTED()) {
            g_Battle.boss_event_hook(BOSS_EVENT_EFFECTS_LOADED);
        }
        g_Battle.phase.step     = 3;
        g_Battle.phase.sub_step = 0;
        g_Battle.state &= ~BATTLE_STATE_EFFECT_LOADING;
        GFX_CopyPalette(0x1A);
    }
}
