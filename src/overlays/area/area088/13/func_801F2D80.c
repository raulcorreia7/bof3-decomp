#include "area088_13.h"

MATCH void func_801F2D80(void) {
    u8 remaining;

    Trail_Update((Trail*)AREA_WORK);
    func_801F3258((u8*)AREA_WORK);
    ACTOR_COUNT_DOWN(remaining, timer);
    if (!(remaining & BYTE_MASK)) {
        g_Task->timer = 16;
        g_Task->header.mode += 1;
    }
}
