#include "area118_13.h"

MATCH void func_801F2C6C(void) {
    u16 clock;
    u8  phase;
    u8  frames;
    u8  tick;
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        return;
    }
    if (g_GameEntryState == 4) {
        return;
    }
    if ((u8)g_Game.members[2].u.field.mode.value == 2) {
        return;
    }
    if (g_GameStateIndex == GAME_REQUEST_MENU) {
        return;
    }
    if (g_GameEntryState == 3) {
        return;
    }
    if ((g_PadStates[0].pressed & g_InputMasks[FIELD_INPUT_MENU]) != 0) {
        return;
    }

    clock  = D_801F59E4;
    phase  = clock >> 15;
    frames = (clock & 0x7F00) >> 8;
    tick   = clock;
    frames++;
    if ((phase == 0 && frames >= 0x1E) || (phase != 0 && frames >= 0x28)) {
        frames = 0;
        tick++;
    }
    clock      = (phase << 15) | (frames << 8) | tick;
    D_801F59E4 = clock;
    if ((clock & 0xFF) >= 0xF) {
        g_Task->header.mode++;
    }
}
