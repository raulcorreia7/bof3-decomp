#include "area135_14.h"

MATCH void func_801F48DC(void) {
    u8  i;
    u8  none = 0xFF;
    s32 x;
    s32 y;

    for (i = 0; i < 4; i++) {
        s32 off = i * 2;
        x       = (D_801F6B2C[off] << 16) | 0x8000;
        y       = (D_801F6B2D[off] << 16) | 0x8000;
        if (g_Task->pos.x.fixed == x && g_Task->pos.y.fixed == y &&
            func_801F5C60(g_Task->pos.x.fixed, g_Task->pos.y.fixed) != none) {
            break;
        }
    }
    g_ScriptState->cursor += i * 3;
}
