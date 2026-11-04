#include "area103_13.h"

MATCH void func_801F478C(void) {
    s32 beat;

    beat = g_SpadWork->unk_09 / 5;
    if (beat == 4) {
        Area_ClearCellPalette(0x43, 0x1A);
        func_80196070();
        return;
    }
    if (g_SpadWork->unk_09 % 5 == 0) {
        func_801F4E70(7 - beat);
    }
    g_SpadWork->unk_09++;
}
