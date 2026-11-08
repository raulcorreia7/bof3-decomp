#include "area132_13.h"

MATCH void func_801F37A4(u8* effect) {
    Actor* work = g_Task;

    /* FAKE: the effect record has no proven type yet. */
    FIELD(s32, effect, 0x04) = work->pos.x.fixed;
    FIELD(s32, effect, 0x08) = work->pos.y.fixed;
    FIELD(s32, effect, 0x0C) = work->pos.z.fixed;
    effect[0]                = 1;
    FIELD(u16, effect, 0x14) = 128;
    effect[3]                = 64;
    effect[0x16]             = 7;
    effect[1]                = 0;
    effect[2]                = 32;
}
