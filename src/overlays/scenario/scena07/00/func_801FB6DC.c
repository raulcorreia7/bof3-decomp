#include "scena07_00.h"

#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB6DC(void) {
    switch (g_ScenarioState.step) {
        case 0:
            if (g_ScriptVars[0] == 3) {
                g_ScenarioState.step = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 0xD) {
                g_ScenarioState.step = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0x10) {
                UI_ModeSet(UI_MODE_FADE_OUT);
                g_ScenarioState.step = 3;
            }
            break;
        case 3:
            if (g_UiWindowEffectBusy == 0) {
                g_ScriptVars[0]++;
                func_801C16B8();
                SND_BGMPause(g_SndBGMId);
                SND_XAStartStream(0, 1);
                g_AreaDrawFlags      = 0;
                g_ScenarioState.step = 4;
            }
            break;
        case 4:
            if (SND_XAIsIdle()) {
                SND_BGMResume(g_SndBGMId);
                g_ScenarioState.flags_01 &= 0xFE;
                SYS_SetFlag(g_SceneFlags, 2);
                Game_RequestAreaChange(0xAF, TO_COORD(0x2D) + COORD_HALF, TO_COORD(0x5E), 0x83);
                g_GameArea.request_type = 0xFF;
                g_GameArea.entry_mode   = 0xFF;
                g_ScenarioState.step    = 5;
            }
            break;
        case 5:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0x1F;
                UI_ModeSet(UI_MODE_FADE_IN);
                g_ScenarioState.step = 6;
            }
            break;
        case 6:
            if (g_UiWindowEffectBusy == 0) {
                g_ScriptVars[0]++;
                Game_ClearScriptActive();
                g_GameFlags &= ~GAME_FLAG_SCROLL_LOCK;
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
    }
}
