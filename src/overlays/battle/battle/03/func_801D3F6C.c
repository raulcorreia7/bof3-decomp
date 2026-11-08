#include "battle_03.h"

MATCH void func_801D3F6C(void) {
    if (EMI_LoaderIsReady() != 0) {
        if (g_BattleEncounter != 0) {
            g_BossBattleEventHook(BOSS_EVENT_EFFECTS_LOADED);
        }
        g_BattleStep    = 3;
        g_BattleSubStep = 0;
        g_BattleState &= ~BATTLE_STATE_EFFECT_LOADING;
        GFX_CopyPalette(0x1A);
    }
}
