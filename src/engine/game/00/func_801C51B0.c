#include "game_00.h"

MATCH void func_801C51B0(void) {
    Actor* work;
    u8     field;
    u32    route;
    s32    index;

    work                                             = g_Task;
    field                                            = work->unk_05;
    g_GfxPalettePending                              = 1;
    *(u16*)(MEM_PTR(u8, 0x8003963Eu) + (field << 6)) = 0;
    route                                            = work->direction_08;
    /* FAKE: barrier keeps saved ra from sinking below work load. */
    FAKE_BARRIER();
    index = 52;
    if (route == 7) {
        index = 55;
    }
    Actor_RequestScript(index);
}
