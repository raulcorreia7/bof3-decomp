#include "area119_13.h"

MATCH void func_801F3E18(void) {
    func_801F3F04(7);
    g_Task->timer += 1;
    if (g_Task->timer >= 31U) {
        g_Task->timer = 31;
        g_Task->header.step += 1;
    }
}
