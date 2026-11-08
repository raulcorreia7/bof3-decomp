#include "area085_13.h"

MATCH void func_801F2CB4(void) {
    g_Task->timer -= 1;
    if (g_Task->timer != 0) {
        g_Task->tint.bytes.unk_5D += 4;
        g_Task->tint.bytes.unk_5E += 4;
        g_Task->tint.bytes.unk_5F += 4;
    } else {
        g_Task->timer       = 0xC;
        g_Task->header.mode = 3;
    }
    Area_DrawScreenTint();
    func_801F2FCC();
}
