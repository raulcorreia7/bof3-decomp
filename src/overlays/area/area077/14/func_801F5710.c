#include "area077_14.h"

MATCH void func_801F5710(void) {
    func_801F529C(3, (((Actor*)g_Task)->timer >> 1) + 5, 3, 3);
    func_801F529C(6, (((Actor*)g_Task)->timer >> 1) + 0xB, 6, 9);
    ((Actor*)g_Task)->timer += 1;
    if (((Actor*)g_Task)->timer >= 6U) {
        ((Actor*)g_Task)->header.step += 1;
    }
}
