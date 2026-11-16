#include "scena02_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8538(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_ScriptVars[2] = 5;
            Scene_SetupParty(6);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 0x21) {
                UI_SetMode(UI_MODE_LONG_FADE_OUT);
                g_SceneState.step_05 = 2;
            }
            break;
        case 2:
            if (!WINDOW_EFFECT_BUSY()) {
                g_AreaDrawFlags = 0;
                SCENE_MESSAGE_WAIT(MSG_022, 3);
            }
            break;
        case 3:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[2]      = 0;
                g_ScriptVars[0]      = 0;
                g_SceneState.step_05 = 4;
                Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR_AREA, TO_COORD(38), TO_COORD(25), AREA_ENTRY_MAP_LOADING | FACING_DOWN_LEFT);
                g_GamePrevSelection = 0x11;
                g_GameFlags |= 0x80;
            }
            break;
        case 4:
            Game_ClearScriptActive();
            SCENE_RETURN_TO_START();
            SYS_ClearFlag(g_SceneFlags, 0x24);
            if (SYS_TestFlag(g_SceneFlags, 7)) {
                SYS_ClearFlag(g_SceneFlags, 0x2B);
                SYS_ClearFlag(g_SceneFlags, 0x2C);
                SYS_ClearFlag(g_SceneFlags, 0x3E);
                SYS_SetFlag(g_SceneFlags, 0x34);
                SYS_ClearFlag(g_SceneFlags, 0x35);
                SYS_ClearFlag(g_SceneFlags, 9);
                SYS_ClearFlag(g_SceneFlags, 0xA);
                SYS_ClearFlag(g_SceneFlags, 0xB);
            }
            break;
    }
}
