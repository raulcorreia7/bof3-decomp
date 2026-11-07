#include "area119_13.h"

MATCH void func_801F3D90(void) {
    func_801F3F04(g_Task->timer);
    g_Task->timer += 1;
    if (g_Task->timer >= 8U) {
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}
