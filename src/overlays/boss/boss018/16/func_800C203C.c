#include "boss018_16.h"

MATCH void func_800C203C(void) {
    Actor* work;

    work = g_Self;
    work->pos.y.fixed += (g_FrameCount & 0x1) << 9;
}
