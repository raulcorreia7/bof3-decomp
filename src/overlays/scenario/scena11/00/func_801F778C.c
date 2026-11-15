#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F778C(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_GameFlags |= 8;
            g_SceneState.step_05 = 1;
            switch (D_80145E98) {
                case 6:
                    func_801BE1B0(3);
                    break;
                case 7:
                    func_801BE1B0(1);
                    break;
                case 0:
                    func_801BE1B0(4);
                    break;
            }
            break;
        case 1:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            UI_SetMode(0xD);
            g_SceneState.step_05 = 2;
            break;
        case 2:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_AreaDrawFlags      = 0;
            g_SceneState.step_05 = 3;
            break;
        case 3: {
            u8* progress = &g_ScriptVars[0];

            if (*progress != 2) {
                break;
            }
            *progress            = 0;
            g_ScriptVars[2]      = 2;
            g_SceneState.step_05 = 4;
            Game_RequestAreaChange(0x83, 0x50000, 0x5D0000, 0x83);
            g_GameEntryMode = 0xFF;
            break;
        }
        case 4: {
            u8* progress = &g_ScriptVars[0];

            if (*progress != 1) {
                break;
            }
            *progress                = 0;
            g_AreaCameraRefreshCount = 2;
            g_ScriptVars[2]          = 0;
            g_AreaCameraOffsetY      = 0;
            g_SceneState.step_05     = 5;
            Game_RequestAreaChange(0x9C, 0x190000, 0x190000, 0x80);
            g_GamePrevSelection = 0x92;
            break;
        }
        case 5:
            g_SceneState.step_05 = 6;
            break;
        case 6:
            g_SceneState.step_05 = 7;
            break;
        case 7:
            g_SceneState.step_05 = 8;
            break;
        case 8: {
            u8* progress = &g_ScriptVars[0];

            if (*progress != 1) {
                break;
            }
            *progress            = 0;
            g_SceneState.step_05 = 9;
            SYS_SetFlag(g_SceneFlags, 1);
            Game_RequestAreaChange(0x83, 0x50000, 0x5D0000, 0x84);
            break;
        }
        case 9: {
            u8* progress = &g_ScriptVars[0];

            if (*progress != 2) {
                break;
            }
            *progress            = 0;
            g_ScriptVars[2]      = 1;
            g_SceneState.step_05 = 0xA;
            Game_RequestAreaChange(0x83, 0x200000, 0x2F0000, 0x85);
            break;
        }
        case 10:
            Area_StartScrollRoute(0);
            Area_AdvanceScroll(0x498);
            g_AreaCameraRefreshCount = 2;
            g_SceneState.step_05     = 0xB;
            break;
        case 11:
            if (g_AreaCameraMoving == 0) {
                g_ScriptVars[0]      = 1;
                g_SceneState.step_05 = 0xC;
            }
            /* Falls into the sub-state 12 body. */
        case 12:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            UI_SetMode(0xD);
            g_SceneState.step_05 = 0xD;
            break;
        case 13:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_AreaDrawFlags      = 0;
            g_SceneState.step_05 = 0xE;
            break;
        case 14: {
            u8* progress = &g_ScriptVars[0];

            if (*progress != 3) {
                break;
            }
            g_ScriptVars[2]      = 3;
            *progress            = 0;
            g_SceneState.step_05 = 0xF;
            SYS_SetFlag(g_SceneFlags, 2);
            Game_RequestAreaChange(0x83, 0x70000, 0x5C0000, 0x86);
            break;
        }
        case 15: {
            u8* progress = &g_ScriptVars[0];

            if (*progress != 0x14) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0);
            SYS_SetFlag(g_SceneFlags, 4);
            Game_ClearScriptActive();
            g_GameFlags ^= 8;
            *progress             = 0;
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        }
        case 0x32:
            Message_StartAreaMessage(6);
            g_GameStateIndex     = 2;
            g_SceneState.step_05 = 0x33;
            break;
        case 0x33:
            if (g_GameStateIndex == 2) {
                break;
            }
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 0x3C:
            Message_StartAreaMessage(7);
            g_GameStateIndex     = 2;
            g_SceneState.step_05 = 0x33;
            break;
    }
}
