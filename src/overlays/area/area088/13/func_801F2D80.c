#include "area088_13.h"

MATCH void func_801F2D80(void) {
    u8 remaining;

    func_801F2F28((u8*)AREA_WORK);
    func_801F3258((u8*)AREA_WORK);
    remaining      = g_Task->unk_09 - 1;
    g_Task->unk_09 = remaining;
    if (!(remaining & 0xFF)) {
        g_Task->unk_09 = 0x10;
        g_Task->mode += 1;
    }
}
