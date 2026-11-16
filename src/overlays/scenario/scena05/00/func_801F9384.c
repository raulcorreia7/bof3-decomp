#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9384(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if (g_UiWindowChannel & 2) {
                switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                    case 1:
                        g_SceneState.step_05 = 0xF;
                        break;
                    case 2:
                        g_SceneState.step_05 = 1;
                        break;
                }
            }
            break;

        case 1:
            if (g_UiWindowChannel & 2) {
                Message_StartAreaMessage(MSG_032);
                g_GameStateIndex     = 2;
                g_SceneState.step_05 = 2;
            }
            break;

        case 2:
            if (g_GameStateIndex != 2) {
                g_SceneState.step_05 = 3;
            }
            break;

        case 3:
            if (g_ScriptVars[0] == 0x2B) {
                if (g_GameStateIndex != 2) {
                    g_ScriptVars[0]      = 0x2D;
                    g_SceneState.step_05 = 4;
                }
            } else if (g_ScriptVars[0] == 0x2C) {
                if (g_GameStateIndex != 2) {
                    g_ScriptVars[0]      = 0x32;
                    g_SceneState.step_05 = 5;
                }
            }
            break;

        case 4:
            if (g_ScriptVars[0] == 0x2E) {
                if (g_GameStateIndex != 2) {
                    g_ScriptVars[0] = 0;
                    goto scene_end;
                }
            }
            break;

        case 5:
            if (g_ScriptVars[0] == 0x33) {
                if (g_GameStateIndex != 2) {
                    g_ScriptVars[2]      = 6;
                    g_SceneState.step_05 = 6;
                    SYS_SetFlag(g_SceneFlags, 0x17);
                    SYS_ClearFlag(g_SceneFlags, 0x16);
                    func_8019FA28(0x4E, 0x270000, 0xAD0000, 3);
                }
            }
            break;

        case 6:
            if (g_ScriptVars[0] == 2) {
            scene_end:
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                g_ScriptVars[3] = 0;
                Game_ClearScriptActive();
                SCENE_RETURN_TO_START();
            }
            break;

        case 15:
            if (g_UiWindowChannel & 2) {
                Message_StartAreaMessage(MSG_031);
                g_GameStateIndex     = 2;
                g_SceneState.step_05 = 0x11;
            }
            break;

        case 17:
            if (g_ScriptVars[0] == 0x2B) {
                if (g_GameStateIndex != 2) {
                    g_ScriptVars[0]      = 0x2D;
                    g_SceneState.step_05 = 4;
                }
            } else if (g_ScriptVars[0] == 0x2C) {
                if (g_GameStateIndex != 2) {
                    g_ScriptVars[0]      = 0x32;
                    g_SceneState.step_05 = 0x12;
                }
            }
            break;

        case 18:
            if (g_ScriptVars[0] == 0x33) {
                if (g_GameStateIndex != 2) {
                    g_ScriptVars[2]      = 5;
                    g_SceneState.step_05 = 6;
                    SYS_SetFlag(g_SceneFlags, 0x16);
                    SYS_ClearFlag(g_SceneFlags, 0x17);
                    func_8019FA28(0x4E, 0x270000, 0xAD0000, 3);
                }
            }
            break;
    }
}
