#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F82F4(void) {
    switch (g_SceneState.step_05) {
        case 0:
            Game_SetScriptActive();
            SCENE_MESSAGE_WAIT(0x30, 1);
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                if (g_ScriptVars[0] == 0xBE) {
                    g_SceneState.step_05 = 2;
                }
                if (g_ScriptVars[0] == 0xBF) {
                    g_SceneState.step_05 = 5;
                }
            }
            break;
        case 2:
            g_ScriptVars[0]      = 0;
            g_SceneState.step_05 = 3;
            Game_RequestAreaChange(0xF, 0x110000, 0x3E0000, 0x88);
            g_GamePrevSelection = 0x11;
            g_GameFlags |= 0x80;
            break;
        case 3:
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
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 5:
            Game_ClearScriptActive();
            g_ScriptVars[0]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            if (SYS_TestFlag(g_SceneFlags, 0x3A) == 0) {
                g_ScriptVars[1] = 0;
            } else {
                g_ScriptVars[1] = 1;
            }
            break;
    }
}
