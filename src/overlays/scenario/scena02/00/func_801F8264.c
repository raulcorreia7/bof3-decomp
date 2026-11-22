#include "scena02_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8264(void) {
    u8* state;

    state = &g_ScenarioState.step;
    switch (*state) {
        case 0:
            MESSAGE_START_WAIT(MSG_SCENA02_062);
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
