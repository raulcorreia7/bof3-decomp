#include "game_00.h"

MATCH s32 func_801C5474(void) {
    Actor* work;
    Actor* state;
    u8     countdown;
    work      = g_Task;
    countdown = work->unk_09;
    if (countdown == 0) {
        Actor_RequestScript(work->direction_08);
        Actor_ClearVelocity();
        g_GameState->mode_12B.u8_value = 0;
        g_Task->mode                   = 1;
        ACTOR_CLEAR_STEP();
        g_Task->unk_03 = 0;
        g_Task->unk_04 = 0;
        return 1;
    }
    work->unk_09 = (countdown - 1);
    func_801C57B4();
    state = g_Task;
    if (state->unk_09 == state->unk_0A) {
        GFX_StagePalette(((state->unk_05 << 6) + MEM_PTR(u8, 0x80035600u)), 0);
    }
    func_8014D978();
    return 0;
}
