#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801F87C4);

MATCH void func_801F8B94(void) {
    if (g_SceneState.step_05 == 0) {
        if (g_ScriptVars[0] == 0x18) {
            SYS_SetFlag(g_SceneFlags, 10);
            Game_ClearScriptActive();
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
        }
    }
}

MATCH void func_801F8C1C(void) {
    u8* state;

    state = &g_SceneState.step_05;
    switch (*state) {
        case 0:
            MESSAGE_START_WAIT(38);
            *state = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                *state                = 0;
                g_SceneState.state_04 = 0;
            }
            return;
    }
}
