#include "area188_13.h"

MATCH void func_801F3400(void) {
    u8 mode;

    func_801F38E0(&g_Task->unk_64, (s16)g_Task->unk_2E, 6);
    mode           = g_Task->unk_09 - 1;
    g_Task->unk_09 = mode;
    if (!(mode & 0xFF)) {
        g_Task->unk_09 = 0x20;
        g_Task->header.mode += 1;
    }
}
