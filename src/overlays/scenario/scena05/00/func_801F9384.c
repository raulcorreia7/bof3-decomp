#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9384(void) {
    switch (g_ScenarioState.step) {
        case 0:
            if (g_UIWindowChannel & 2) {
                switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                    case 1:
                        g_ScenarioState.step = 0xF;
                        break;
                    case 2:
                        g_ScenarioState.step = 1;
                        break;
                }
            }
            break;

        case 1:
            if (g_UIWindowChannel & 2) {
                UI_MessageStartArea(MSG_SCENA05_032);
                g_GameStateIndex     = 2;
                g_ScenarioState.step = 2;
            }
            break;

        case 2:
            if (g_GameStateIndex != 2) {
                g_ScenarioState.step = 3;
            }
            break;

        case 3:
            if (g_ScriptVars[0] == 0x2B) {
                if (g_GameStateIndex != 2) {
                    g_ScriptVars[0]      = 0x2D;
                    g_ScenarioState.step = 4;
                }
            } else if (g_ScriptVars[0] == 0x2C) {
                if (g_GameStateIndex != 2) {
                    g_ScriptVars[0]      = 0x32;
                    g_ScenarioState.step = 5;
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
                    g_ScenarioState.step = 6;
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
                SCENARIO_RETURN_TO_START();
            }
            break;

        case 15:
            if (g_UIWindowChannel & 2) {
                UI_MessageStartArea(MSG_SCENA05_031);
                g_GameStateIndex     = 2;
                g_ScenarioState.step = 0x11;
            }
            break;

        case 17:
            if (g_ScriptVars[0] == 0x2B) {
                if (g_GameStateIndex != 2) {
                    g_ScriptVars[0]      = 0x2D;
                    g_ScenarioState.step = 4;
                }
            } else if (g_ScriptVars[0] == 0x2C) {
                if (g_GameStateIndex != 2) {
                    g_ScriptVars[0]      = 0x32;
                    g_ScenarioState.step = 0x12;
                }
            }
            break;

        case 18:
            if (g_ScriptVars[0] == 0x33) {
                if (g_GameStateIndex != 2) {
                    g_ScriptVars[2]      = 5;
                    g_ScenarioState.step = 6;
                    SYS_SetFlag(g_SceneFlags, 0x16);
                    SYS_ClearFlag(g_SceneFlags, 0x17);
                    func_8019FA28(0x4E, 0x270000, 0xAD0000, 3);
                }
            }
            break;
    }
}
