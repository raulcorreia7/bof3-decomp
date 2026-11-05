#include "area048_13.h"

MATCH void func_801F3944(void) {
    func_801F3AE4(0x400, 0x858000, 0x10);
    func_801F3AE4(0xC00, 0x878000, 0x11);
    g_Task->unk_09 += 1;
    if (g_Task->unk_09 >= 5U) {
        g_Task->step += 1;
        g_Task->unk_09 = 0;
    }
}
