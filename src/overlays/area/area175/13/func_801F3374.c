#include "area175_13.h"

MATCH void func_801F3374(void) {
    g_Task->timer -= 1;
    if (g_Task->timer != 0) {
        g_Task->tint.bytes.unk_5D -= 6;
        g_Task->tint.bytes.unk_5E -= 6;
        g_Task->tint.bytes.unk_5F -= 6;
    } else {
        g_Task->header.mode = 4;
    }
    Area_DrawScreenTint();
}
