#include "area030_04.h"

/* Ticks down the work counter at scratch+9 and dispatches on the
 * new value. */
MATCH void func_801D64E8(void) {
    u8 count;

    g_Task->timer -= 1;
    count = g_Task->timer;
    if (count == 0) {
        Actor_Clear();
        return;
    }
    if (count & 0x8) {
        Area_AddActor();
    }
}
