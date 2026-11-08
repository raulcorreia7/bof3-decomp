#include "area197_13.h"

MATCH void func_801F36F0(void) {
    g_Task->timer += 1;
    if (g_Task->timer >= 16) {
        Actor_Clear();
    }
    func_801F3768(0x80 - (g_Task->timer << 3), g_Task->timer << 3);
}
