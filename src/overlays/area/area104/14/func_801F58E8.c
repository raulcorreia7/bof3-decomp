#include "area104_14.h"

MATCH void func_801F58E8(void) {
    u8* heading;

    heading = &D_80145E98;
    if (g_SpadWork->direction_08 != *heading) {
        if ((u8)func_801F5988(g_SpadWork->direction_08, *heading) != 0) {
            return;
        }
        if ((u8)func_801F5988(g_SpadWork->direction_08 ^ 4, *heading) != 0) {
            return;
        }
        *heading = g_SpadWork->direction_08;
    }
    func_801F5738();
}
