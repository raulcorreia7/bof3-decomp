#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F83EC(void) {
    SYS_DISPATCH_BYTE(D_801FD5E8, g_ScenarioState.state_04);
}

MATCH void func_801F8428(void) {
}

MATCH void func_801F8430(void) {
    u8* step;

    step = &g_ScenarioState.step_05;
    switch (*step) {
        case 0:
            MESSAGE_START_WAIT(MSG_SCENA05_005);
            *step = 1;
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[2] = 1;
                *step           = 2;
                SYS_SetFlag(g_SceneFlags, 0);
                func_8019FA28(0x44, 0x1D0000, 0x1E0000, 0x80);
            }
            break;
        case 2:
            if (*g_ScriptVars == 0x2D) {
                SYS_SetFlag(g_SceneFlags, 1);
                Game_ClearScriptActive();
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScriptVars[3]          = 0;
                *step                    = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}

MATCH void func_801F8554(void) {
}

MATCH void func_801F855C(void) {
}
