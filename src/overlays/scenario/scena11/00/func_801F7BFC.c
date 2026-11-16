#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7BFC(void) {
    u8* state;
    s32 next;

    state = &g_SceneState.step_05;
    switch (*state) {
        case 0:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            next            = 1;
            g_ScriptVars[0] = next;
            Scene_SetupParty(0);
            *state = next;
            break;
        case 1:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 5);
            Game_ClearScriptActive();
            Scene_ClearScriptState(state);
            break;
    }
}
