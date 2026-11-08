#include "area198_13.h"

MATCH void func_801F2CB8(void) {
    g_Task->timer += 1;
    func_801F2D28(g_Task->timer);
    if (g_Task->timer >= 128) {
        Actor_Clear();
    }
}
