#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8F18(void) {
    switch (g_SceneState.step_05) {
        case 0:
            UI_SetMode(UI_MODE_LONG_FADE_OUT);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (WINDOW_EFFECT_IDLE()) {
                g_AreaDrawFlags      = 0;
                g_SceneState.step_05 = 2;
                Game_RequestAreaChange(AREA_ID_CAMP_BEFORE_ANGEL_TOWER, TO_COORD(18), TO_COORD(24), AREA_ENTRY_MAP_LOADING | FACING_UP);
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0x0C) {
                UI_SetMode(UI_MODE_LONG_FADE_OUT);
                Char_RebuildPartyStats();
                g_SceneState.step_05 = 3;
                SYS_SetFlag(g_SceneFlags, 0x11);
                SND_FadeOutSequence(0, 0, 4, 0x1E);
            }
            break;
        case 3:
            if (WINDOW_EFFECT_IDLE()) {
                g_AreaDrawFlags = 0;
                SND_StartXAStream(0, 1);
                g_SceneState.step_05 = 4;
            }
            break;
        case 4:
            if (SND_IsXAIdle() != 0) {
                g_SceneState.step_05 = 5;
                Game_RequestAreaChange(AREA_ID_RHAPALA_WORLD_MAP, TO_COORD(49), TO_COORD(46), FACING_RIGHT);
            }
            break;
        case 5:
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            Game_ClearScriptActive();
            Scene_ClearScriptState(&g_SceneState.step_05);
            break;
    }
}
