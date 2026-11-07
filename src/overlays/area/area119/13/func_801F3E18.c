#include "area119_13.h"

MATCH void func_801F3E18(void) {
    func_801F3F04(7);
    g_Task->timer += 1;
    if (g_Task->timer >= 0x1FU) {
        g_Task->timer = 0x1F;
        g_Task->header.step += 1;
    }
}
