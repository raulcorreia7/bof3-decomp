#include "area041_13.h"

MATCH void func_801F32FC(void) {
    g_Task->timer += 1;
    g_Task->pos.x.fixed = ((g_Task->timer & 0x1) * 8) - 0x2B80;
    if (g_Task->timer >= 8U) {
        g_Task->timer       = 0;
        g_Task->pos.x.fixed = -0x2B80;
        g_Task->header.step += 1;
    }
    func_801F2EFC();
    func_801F3064();
}
