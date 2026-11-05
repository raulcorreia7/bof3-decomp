#include "game_00.h"

/* Plain scratchpad cell read; emits a fresh absolute load per use. */
#define WORK_PTR (*SP_PTR(Actor*, 0x44u))

MATCH void func_801B3690(void) {
    u8 hint;

    hint = g_EmiLoadedCharacterIndex;
    D_801CD164[hint & 0x7F]();
    if (g_GameState->mode_12B.u8_value == 0) {
        Actor_RequestScript(g_Task->direction_08);
        Party_ClearBattlerState(0);
        g_Task->mode = 1;
    }
}
