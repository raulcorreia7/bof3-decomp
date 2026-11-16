#include "scena07_00.h"

#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB6DC(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if (g_ScriptVars[0] == 3) {
                g_SceneState.step_05 = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 0xD) {
                g_SceneState.step_05 = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0x10) {
                UI_SetMode(UI_MODE_FADE_OUT);
                g_SceneState.step_05 = 3;
            }
            break;
        case 3:
            if (g_UiWindowEffectBusy == 0) {
                g_ScriptVars[0]++;
                func_801C16B8();
                SND_PauseBGM(g_SndBGMId);
                SND_StartXAStream(0, 1);
                g_AreaDrawFlags      = 0;
                g_SceneState.step_05 = 4;
            }
            break;
        case 4:
            if (SND_IsXAIdle()) {
                SND_ResumeBGM(g_SndBGMId);
                g_SceneState.flags_01 &= 0xFE;
                SYS_SetFlag(g_SceneFlags, 2);
                Game_RequestAreaChange(0xAF, TO_COORD(0x2D) + COORD_HALF, TO_COORD(0x5E), 0x83);
                g_GameArea.request_kind = 0xFF;
                g_GameArea.entry_mode   = 0xFF;
                g_SceneState.step_05    = 5;
            }
            break;
        case 5:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0x1F;
                UI_SetMode(UI_MODE_FADE_IN);
                g_SceneState.step_05 = 6;
            }
            break;
        case 6:
            if (g_UiWindowEffectBusy == 0) {
                g_ScriptVars[0]++;
                Game_ClearScriptActive();
                g_GameFlags &= ~GAME_FLAG_SCROLL_LOCK;
                g_SceneState.state_04 = 0;
                g_SceneState.step_05  = 0;
            }
            break;
    }
}
