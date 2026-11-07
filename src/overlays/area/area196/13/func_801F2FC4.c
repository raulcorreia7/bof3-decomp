#include "area196_13.h"

MATCH void func_801F2FC4(void) {
    g_Task->timer -= 4;
    if (g_Task->timer == 0) {
        Actor_Clear();
    }
    func_801F3030(g_Task->timer);
}
