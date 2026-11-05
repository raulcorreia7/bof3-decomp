#include "area103_13.h"

MATCH void func_801F511C(void) {
    u8* work = g_Task;

    FIELD(u8, work, 0x9u)++;
    if (FIELD(u8, g_Task, 0x9u) >= 0x1D) {
        Actor_Clear();
    }
}
