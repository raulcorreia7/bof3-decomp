#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801F87C4(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA05_013, 1);
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Scene_SetupParty(0);
                g_ScenarioState.step_05 = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 1) {
                g_AreaScrollTargetX     = TO_COORD(53);
                g_AreaCameraStep        = 0x20;
                g_ScenarioState.step_05 = 3;
                g_AreaScrollTargetY     = g_Game.members[0].pos.y.fixed;
            }
            break;
        case 3:
            if (g_AreaCameraMoving == 0) {
                g_ScriptVars[0]         = 2;
                g_ScenarioState.step_05 = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0xA) {
                UI_SetMode(0xD);
                g_ScenarioState.step_05 = 5;
            }
            break;
        case 5:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SCENARIO_MESSAGE_WAIT(MSG_SCENA05_026, 6);
            break;
        case 6:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[2]         = 1;
                g_ScenarioState.step_05 = 7;
                SYS_SetFlag(g_SceneFlags, 13);
                Game_RequestAreaChange(AREA_ID_RHAPALA_DOCK, TO_COORD(51), TO_COORD(33), AREA_ENTRY_MAP_LOADING | FACING_UP);
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 0xD) {
                SYS_SetFlag(g_SceneFlags, 15);
                Game_ClearScriptActive();
                Scene_ClearScriptState(&g_ScenarioState.step_05);
            }
            break;
        case 10:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA05_041, 11);
            break;
        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Scene_SetupParty(2);
                g_ScenarioState.step_05 = 12;
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 0x15) {
                SYS_SetFlag(g_SceneFlags, 14);
                Game_ClearScriptActive();
                Scene_ClearScriptState(&g_ScenarioState.step_05);
            }
            break;
        case 20:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA05_041, 21);
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Scene_SetupParty(0);
                g_ScenarioState.step_05 = 22;
            }
            break;
        case 22:
            if (g_ScriptVars[0] == 1) {
                SYS_SetFlag(g_SceneFlags, 16);
                Game_ClearScriptActive();
                Scene_ClearScriptState(&g_ScenarioState.step_05);
            }
            break;
        case 30:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA05_019, 31);
            break;
        case 31:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScenarioState.step_05  = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}
#else
INCLUDE_ASM(func_801F87C4);
#endif

MATCH void func_801F8B94(void) {
    if (g_ScenarioState.step_05 == 0) {
        if (g_ScriptVars[0] == 0x18) {
            SYS_SetFlag(g_SceneFlags, 10);
            Game_ClearScriptActive();
            SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
            SCENARIO_RETURN_TO_START();
        }
    }
}

MATCH void func_801F8C1C(void) {
    u8* state;

    state = &g_ScenarioState.step_05;
    switch (*state) {
        case 0:
            MESSAGE_START_WAIT(MSG_SCENA05_038);
            *state = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                *state                   = 0;
                g_ScenarioState.state_04 = 0;
            }
            return;
    }
}
