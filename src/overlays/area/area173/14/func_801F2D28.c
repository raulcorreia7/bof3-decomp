#include "area173_14.h"

MATCH void func_801F2D28(void) {
    u8 mode;

    mode = g_Task->unk_09;
    func_801F3060(mode >> 3, (mode >> 2) & 1);
    g_Task->unk_09 += 1;
    if (g_Task->unk_09 >= 0xD0U) {
        g_Task->step += 1;
    }
}
