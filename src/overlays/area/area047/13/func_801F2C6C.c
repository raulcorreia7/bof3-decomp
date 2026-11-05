#include "area047_13.h"
#include "work/area_spad.h"

MATCH void func_801F2C6C(void) {
    s32 remaining;

    remaining      = g_SpadWork->vx - 1;
    g_SpadWork->vx = remaining;
    if (remaining == 0) {
        g_SpadWork->vx = 0x230;
        func_801F3298();
        g_SpadWork->unk_01 += 1;
    }
}
