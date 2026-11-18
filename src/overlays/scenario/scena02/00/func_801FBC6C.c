#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "shared/etc.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FBC6C(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            Message_StartAreaMessage(MSG_SCENA02_111);
            g_GameStateIndex        = 2;
            g_ScenarioState.step_05 = 1;
            break;

        case 1:
            if (g_GameStateIndex != 2) {
                g_ScriptVars[0] = 0;
                goto reset;
            }
            break;

        case 2:
        case 3:
        case 4:
            break;

        case 5:
            if ((g_UiWindowChannel & 2) != 0) {
                if (g_ScriptVars[0] == 0x5A) {
                    g_ScriptVars[0] = 0;
                    goto reset;
                }
                if (g_ScriptVars[0] != 0x5B) {
                    break;
                }
                g_ScriptVars[2]         = 1;
                g_ScenarioState.step_05 = 20;
                UI_SetMode(0xD);
            }
            break;

        case 6:
        case 7:
        case 8:
        case 9:
            break;

        case 20:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0;
                func_801C16B8();
                g_ScenarioState.step_05 = 21;
                SND_PauseBGM(0x21);
            }
            break;

        case 21:
            SND_StartXAStream(0, 1);
            g_ScenarioState.step_05 = 22;
            break;

        case 22:
            if (SND_IsXAIdle()) {
                SND_ResumeBGM(0x21);
                g_ScenarioState.step_05 = 23;
            }
            break;

        case 23:
            g_ScriptVars[2]         = 2;
            g_ScenarioState.step_05 = 24;
            Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR, TO_COORD(73), TO_COORD(10), 0x99);
            break;

        case 24:
            if ((g_UiWindowChannel & 2) != 0) {
                if (g_ScriptVars[0] == 0x5C) {
                    D_8014865C              = -2;
                    D_80148698              = 1;
                    g_GameEntryState        = 7;
                    g_MenuStep.step         = 0;
                    D_80148699              = 0;
                    g_ScenarioState.step_05 = 25;
                    break;
                }
                if (g_ScriptVars[0] == 0x5D) {
                    goto reset;
                }
            }
            break;

        case 25:
            if (g_GameStateIndex == 0) {
                goto reset;
            }
            break;

        case 10:
            if (g_GameStateIndex != 2) {
                if (g_ScriptVars[0] == 0x5C) {
                    D_8014865C              = -2;
                    D_80148698              = 1;
                    g_GameEntryState        = 7;
                    g_MenuStep.step         = 0;
                    D_80148699              = 0;
                    g_ScenarioState.step_05 = 25;
                    break;
                }
                if (g_ScriptVars[0] != 0x5D) {
                    break;
                }
                g_ScriptVars[0] = 0;
                goto reset;
            }
            break;

        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            break;
    }
    return;

reset:
    g_ScriptVars[1] = 0;
    g_ScriptVars[2] = 0;
    g_ScriptVars[3] = 0;
    Game_ClearScriptActive();
    SCENARIO_RETURN_TO_START();
}
