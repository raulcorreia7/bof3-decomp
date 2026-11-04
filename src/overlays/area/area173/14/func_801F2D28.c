#include "area173_14.h"

MATCH void func_801F2D28(void) {
    u8 mode;

    mode = g_SpadWork->unk_09;
    func_801F3060(mode >> 3, (mode >> 2) & 1);
    g_SpadWork->unk_09 += 1;
    if ((u8)g_SpadWork->unk_09 >= 0xD0U) {
        g_SpadWork->state_02 += 1;
    }
}
