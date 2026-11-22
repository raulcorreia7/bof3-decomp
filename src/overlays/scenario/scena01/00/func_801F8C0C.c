#include "scena01_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8C0C(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            if (g_ScriptVars[0] == 2) {
                g_ScriptVars[1]         = 1;
                g_ScenarioState.step_05 = 1;
                Game_RequestAreaChange(0xA, TO_COORD(0x52), TO_COORD(0x23), 3);
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 4) {
                g_ScriptVars[1]         = 2;
                g_ScenarioState.step_05 = 2;
                SND_SeqStop(0, 0);
                SND_BGMPlay(0xE, 0x64, 8);
                g_GameFlags |= 0x80;
                Game_RequestAreaChange(0xA, TO_COORD(0x4F), TO_COORD(5), 3);
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0xA) {
                g_ScriptVars[1]         = 3;
                g_ScriptVars[2]         = 7;
                g_ScenarioState.step_05 = 3;
                SND_SeqStop(0, 1);
                Game_RequestAreaChange(0xA, TO_COORD(0x60), TO_COORD(0x12), 3);
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 1) {
                UI_ModeSet(0xF);
                SND_SEPlay(0x201);
                g_ScenarioState.step_05 = 4;
            }
            break;
        case 4:
            if (WINDOW_EFFECT_IDLE()) {
                UI_ModeSet(0x10);
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags = 0;
                g_ScenarioState.step_05                                   = 8;
            }
            break;
        case 8:
            if (WINDOW_EFFECT_IDLE()) {
                g_ScriptVars[0]         = 2;
                g_ScenarioState.step_05 = 9;
            }
            break;
        case 9:
            if (g_ScriptVars[0] == 3) {
                g_ScriptVars[1]         = 4;
                g_ScriptVars[2]         = 0;
                g_ScenarioState.step_05 = 0xA;
                Game_RequestAreaChange(0xA, TO_COORD(0x5F), TO_COORD(0x31), 3);
            }
            break;
        case 10:
            if (g_ScriptVars[0] == 1) {
                g_ScriptVars[1]         = 5;
                g_ScenarioState.step_05 = 0xB;
                g_GameFlags ^= 0x80;
                Game_RequestAreaChange(0xA, TO_COORD(0x4F), TO_COORD(5), 0x85);
            }
            break;
        case 11:
            if (g_ScriptVars[0] == 1 && g_AreaCameraMoving == 0) {
                SYS_SetFlag(g_SceneFlags, 1);
                Game_ClearScriptActive();
                g_GameFlags |= 0x60;
                SCRIPT_VARS_CLEAR_ALL();
                SCENARIO_RETURN_TO_START();
            }
            break;
    }
}
