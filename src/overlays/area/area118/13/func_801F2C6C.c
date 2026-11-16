#include "area118_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2C6C(void) {
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
    if ((u8)g_Game.members[2].u.field.mode_12B.s8_value == 2) {
        return;
    }
    if (g_GameStateIndex == GAME_REQUEST_MENU) {
        return;
    }
    if (g_GameEntryState == 3) {
        return;
    }
    if ((g_InputPressed & g_InputMasks[FIELD_INPUT_MENU]) != 0) {
        return;
    }

    clock  = D_801F59E4;
    phase  = clock >> 15;
    frames = (clock & 0x7F00) >> 8;
    tick   = clock;
    frames++;
    if (phase == 0) {
        if (frames >= 0x1E) {
            frames = 0;
            tick++;
        }
    } else if (frames >= 0x28) {
        frames = 0;
        tick++;
    }
    D_801F59E4 = tick | (frames << 8) | (phase << 15);
    if (tick >= 0xF) {
        g_Task->header.mode++;
    }
}
#else
INCLUDE_ASM(func_801F2C6C);
#endif
