#include "area119_13.h"

MATCH void func_801F3E94(void) {
    func_801F3F04(g_Task->timer >> 2);
    g_Task->timer--;
    if (g_Task->timer < 8) {
        Actor_Clear();
    }
}
