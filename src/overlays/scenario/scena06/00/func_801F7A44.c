#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7A44(void) {
    switch (g_ScenarioState.step) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 1;
                Scene_SetupParty(0);
                g_ScenarioState.step = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 0x08) {
                g_ScenarioState.step = 2;
                SYS_SetFlag(g_SceneFlags, 0x3E);
                Game_RequestAreaChange(AREA_ID_WYNDIA_CASTLE, TO_COORD(30), TO_COORD(39), AREA_ENTRY_MAP_LOADING | FACING_UP);
            }
            break;
        case 2:
            Area_ScrollStartRoute(1);
            SYS_SetFlag(g_SceneFlags, 3);
            g_ScenarioState.step = 3;
            break;
        case 3:
            if (g_ScriptVars[0] == 0x11) {
                g_ScriptVars[0]          = 0;
                g_ScenarioState.step     = 4;
                g_ScenarioState.timer_06 = 180;
                g_AreaDrawFlags          = 0;
                Game_RequestAreaChange(AREA_ID_WYNDIA_CASTLE, TO_COORD_HALF(89), TO_COORD(16), AREA_ENTRY_MAP_LOADING | FACING_UP_RIGHT);
            }
            break;
        case 4:
            if (g_ScenarioState.timer_06-- == 0) {
                UI_ModeSet(UI_MODE_SLOW_FADE_IN);
                g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
                g_ScenarioState.step = 7;
            }
            break;
        case 7:
            if (WINDOW_EFFECT_IDLE()) {
                g_ScriptVars[0]      = 1;
                g_ScenarioState.step = 10;
            }
            break;
        case 10:
            if (g_ScriptVars[0] == 2 && g_AreaCameraMoving == 0) {
                SYS_ClearFlag(g_SceneFlags, 0x3E);
                SYS_SetFlag(g_SceneFlags, 3);
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}
