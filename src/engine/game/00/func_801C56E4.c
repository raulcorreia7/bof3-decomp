#include "game_00.h"

MATCH void func_801C56E4(void) {
    u8     index;
    Actor* work;
    Actor* state;

    work               = g_Task;
    work->direction_08 = (work->direction_08 ^ 4);
    index              = 0x3B;
    if (g_Task->direction_08 == 3) {
        index = 0x3A;
    }
    Actor_RequestScript(index);
    GFX_StagePalette((g_Task->unk_05 << 6) + GAME_PALETTE_STAGE, 0);
    Actor_ClearVelocity();
    state               = g_Task;
    state->gravity      = -8;
    state->header.mode  = 2;
    g_Task->header.step = 3;
    g_Task->unk_03      = 3;
}
