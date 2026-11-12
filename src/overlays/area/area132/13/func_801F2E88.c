#include "area132_13.h"

MATCH void func_801F2E88(void) {
    u8* result;
    u8  count;

    if (!(g_Task->timer & 0x3)) {
        result = func_801F3800();
        if (result != 0) {
            func_801F37A4(result);
        }
    }
    func_801F38B0();
    count         = g_Task->timer - 1;
    g_Task->timer = count;
    if (count == 0) {
        g_Task->header.step += 1;
    }
}
