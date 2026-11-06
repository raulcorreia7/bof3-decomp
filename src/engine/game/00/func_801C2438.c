#include "game_00.h"

MATCH void func_801C2438(void) {
    Actor* work;
    u16*   table;
    u16    value;
    s32    i;
    u32    base;
    u8     field;

    i    = 0;
    base = GAME_PALETTE_MIRROR;
    work = g_Task;
    do {
        table = (u16*)(i * 2 + ((work->unk_05 << 6) + base));
        value = *table;
        i += 1;
        *table = (value | 0x8000);
    } while (i < 31);
    g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    field                                                            = g_Task->unk_05;
    g_GfxPalettePending                                              = 1;
    *(u16*)(MEM_PTR(u8, GAME_PALETTE_MIRROR) + (field << 6) + 0x3Eu) = 0;
}
