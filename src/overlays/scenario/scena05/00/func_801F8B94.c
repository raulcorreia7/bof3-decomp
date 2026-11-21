#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
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
