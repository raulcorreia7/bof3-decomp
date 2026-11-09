#include "area048_13.h"

MATCH void func_801F40B4(void) {
    func_801F41F0(*(s16*)((u8*)g_Task + 0x36), D_801F4E70[(u8)(g_Task->timer / 3)]);
    g_Task->timer++;
    if (g_Task->timer >= 4) {
        g_Task->header.step = 1;
    }
}
