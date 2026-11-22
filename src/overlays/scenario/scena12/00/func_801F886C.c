#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F886C(void) {
    SYS_DISPATCH_BYTE(D_801FD1C4, g_ScenarioState.state_04);
}

MATCH void func_801F88A8(void) {
}

MATCH void func_801F88B0(void) {
    u8* state;
    u8* script;

    state = &g_ScenarioState.step_05;
    switch (*state) {
        case 0xA:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 0x32;
                *state          = 0xB;
            }
            return;
        case 0xB:
            script = &g_ScriptVars[1];
            if (*script == 0xA) {
                *script = 0;
                Game_ClearScriptActive();
                *state                   = 0;
                g_ScenarioState.state_04 = 0;
            }
            return;
    }
}

MATCH void func_801F894C(void) {
    switch (g_ScenarioState.step_05) {
        case 51:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScenarioState.step_05  = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;

        case 50:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA12_006, 51);
            break;

        case 60:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA12_007, 51);
            break;
    }
}

MATCH void func_801F89FC(void) {
}
