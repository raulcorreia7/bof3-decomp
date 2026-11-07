#include "game_00.h"

MATCH s32 func_801C4E14(void) {
    Actor* work;
    Actor* state;
    u8     countdown;
    u8     region;
    s32    inactive;

    work      = g_Task;
    countdown = work->timer;
    inactive  = 0;
    if (countdown != 0) {
        work->timer = (countdown - 1);
        func_801C57B4();
        state = g_Task;
        if (state->timer == state->unk_0A) {
            region                                            = state->unk_05;
            g_GfxPalettePending                               = 1;
            *(u16*)(MEM_PTR(u8, 0x8003963Eu) + (region << 6)) = 0;
        }
    } else {
        inactive = 1;
        Actor_RequestScript(work->direction_08);
        g_Task->unk_0A = 4U;
    }
    func_8014D978();
    return inactive;
}
