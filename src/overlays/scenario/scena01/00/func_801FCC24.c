#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/Area_DrawDimQuad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FCC24(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            SND_StopSequence(0, 0);
            SND_PlayBGM(26, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_GameFlags |= 0x80;
            Scene_SetupParty(0xB);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            Game_ClearScriptActive();
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScenarioState.step_05  = 0x2D;
            g_ScenarioState.state_04 = 9;
            break;
    }
}

MATCH void func_801FCCF4(void) {
}

MATCH void func_801FCCFC(void) {
    u8* state;

    state = &g_ScenarioState.step_05;
    switch (*state) {
        case 0:
            MESSAGE_START_WAIT(MSG_024);
            *state = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                *state                   = 0;
                g_ScenarioState.state_04 = 0;
            }
            return;
    }
}

MATCH void func_801FCD9C(void) {
    u8* state;

    state = &g_ScenarioState.step_05;
    switch (*state) {
        case 0:
            MESSAGE_START_WAIT(MSG_052);
            *state = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                *state                   = 0;
                g_ScenarioState.state_04 = 0x6;
            }
            return;
    }
}

MATCH void func_801FCE30(void) {
    u8* state;

    state = &g_ScenarioState.step_05;
    switch (*state) {
        case 0:
            MESSAGE_START_WAIT(MSG_052);
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
