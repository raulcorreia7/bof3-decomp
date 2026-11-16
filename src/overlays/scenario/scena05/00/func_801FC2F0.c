#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC2F0(void) {
    u8* state;

    state = &g_SceneState.step_05;
    switch (*state) {
        case 0:
            MESSAGE_START_WAIT(MSG_132);
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
