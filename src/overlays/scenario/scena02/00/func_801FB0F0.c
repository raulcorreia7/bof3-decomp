#include "scena02_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB0F0(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            SND_PlayBGM(15, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            func_801C601C(0);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_AreaCameraMoving != 0 || g_ScriptVars[0] != 3) {
                break;
            }
            func_801C16B8();
            g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
            SYS_SetFlag(g_SceneFlags, 0x1F);
            g_ScriptVars[0] = 0;
            D_80146865      = 0;
            D_80146867      = 0;
            g_GameFlags |= 0x80;
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 5:
            if (g_ScriptVars[0] == 1) {
                UI_SetMode(UI_MODE_SLOW_FADE_IN);
                g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
                g_SceneState.step_05 = 6;
            }
            break;
        case 6:
            if (!WINDOW_EFFECT_BUSY()) {
                g_ScriptVars[0]      = 2;
                g_SceneState.step_05 = 7;
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 0x0F) {
                SYS_SetFlag(g_SceneFlags, 0x20);
                g_ScriptVars[0] = 0;
                D_80146865      = 0;
                D_80146866      = 0;
                D_80146867      = 0;
                g_GameFlags ^= 0x80;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
                func_801A78F8();
            }
            break;
    }
}
