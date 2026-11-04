#include "area189_13.h"

MATCH void func_801F5440(void) {
    Actor* work;
    u16*   angle;

    work   = g_SpadWork;
    angle  = &D_801492DC;
    *angle = (*angle + (s8)work->unk_0B) & 0xFFF;
    if ((((0x12 - work->direction_08) & 0xF) << 8) == *angle) {
        g_GameState->mode_12B.s8_value = 0;
        g_SpadWork->state_02  = 2;
    }
}
