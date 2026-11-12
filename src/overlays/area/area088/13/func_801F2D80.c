#include "area088_13.h"

MATCH void func_801F2D80(void) {
    u8 remaining;

    func_801F2F28((u8*)AREA_WORK);
    func_801F3258((u8*)AREA_WORK);
    remaining     = g_Task->timer - 1;
    g_Task->timer = remaining;
    if (!(remaining & BYTE_MASK)) {
        g_Task->timer = 16;
        g_Task->header.mode += 1;
    }
}
