#include "area121_14.h"

MATCH void func_801F6068(void) {
    u8 temp_v0;

    temp_v0 = g_SpadWork->unk_0A;
    if (temp_v0 == 0) {
        g_SpadWork->x.fixed = *D_80145EC4;
        do {
        } while (0); /* FAKE: the empty loop keeps the x load with its store. */
        g_SpadWork->y.fixed = D_80145EC8;
        g_SpadWork->z.fixed = D_80145ECC + 0x800000;
        func_801F60F4(g_SpadWork);
        g_SpadWork->unk_01 += 1;
        return;
    }
    g_SpadWork->unk_0A = temp_v0 - 1;
}
