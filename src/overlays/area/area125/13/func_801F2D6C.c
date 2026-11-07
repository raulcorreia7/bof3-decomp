#include "area125_13.h"

MATCH void func_801F2D6C(void) {
    u8 count;

    if (g_Task->timer % 15 == 0) {
        func_801F3268(2);
    }
    func_801F33B0();
    count         = g_Task->timer - 1;
    g_Task->timer = count;
    if (count == 0) {
        g_Task->header.mode += 1;
    }
}
