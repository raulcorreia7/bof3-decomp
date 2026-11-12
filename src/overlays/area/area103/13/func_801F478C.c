#include "area103_13.h"

MATCH void func_801F478C(void) {
    s32 beat;

    beat = g_Task->timer / 5;
    if (beat == 4) {
        Area_ClearCellPalette(67, 26);
        Actor_Clear();
        return;
    }
    if (g_Task->timer % 5 == 0) {
        func_801F4E70(7 - beat);
    }
    g_Task->timer++;
}
