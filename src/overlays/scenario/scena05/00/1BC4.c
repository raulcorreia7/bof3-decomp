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
            D_80146865            = 0;
            D_80146866            = 0;
            D_80146867            = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
        }
    }
}

MATCH void func_801F8C1C(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(38);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                *state     = 0;
                D_80146874 = 0;
            }
            return;
    }
}
