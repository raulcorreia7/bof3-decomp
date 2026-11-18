#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9148(void) {
    u8* step = &g_ScenarioState.step_05;

    switch (*step) {
        case 0:
            if (*g_ScriptVars == 0x23) {
                *step = 1;
            }
            break;
        case 1:
            if (*g_ScriptVars == 0x23) {
                *step = 4;
                SYS_SetFlag(g_SceneFlags, 24);
                if (SYS_TestFlag(g_SceneFlags, 23) == 0) {
                    g_ScriptVars[2] = 4;
                    Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, 0x270000, 0xAD0000, FACING_RIGHT);
                    g_GamePrevSelection = 0xFF;
                }
                if (SYS_TestFlag(g_SceneFlags, 22) == 0) {
                    g_ScriptVars[2] = 1;
                    Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, 0x270000, 0xAD0000, 0x83);
                    g_GamePrevSelection = 0xFF;
                }
            }
            break;
        case 4:
            if (*g_ScriptVars == 3) {
                SYS_SetFlag(g_SceneFlags, 25);
                SYS_SetFlag(g_SceneFlags, 20);
                SYS_SetFlag(g_SceneFlags, 26);
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                g_ScriptVars[3] = 0;
                Game_ClearScriptActive();
                *step                    = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}

MATCH void func_801F92EC(void) {
    u8* state;

    state = &g_ScenarioState.step_05;
    switch (*state) {
        case 0:
            MESSAGE_START_WAIT(MSG_SCENA05_000);
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

MATCH void func_801F937C(void) {
}
