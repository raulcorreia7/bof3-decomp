#include "area199_13.h"

MATCH void func_801F2E14(void) {
    s32 i;
    s32 offset;
    s32 j;
    s32 cell;
    u8  fill;

    i      = 0;
    fill   = 0xFF;
    offset = 0;
    do {
        D_801F44B4[i] = 0;
        j             = 0x1F;
        cell          = offset + 0xBA;
        do {
            D_801F54D0[cell] = fill;
            j -= 1;
            cell -= 6;
        } while (j >= 0);
        i += 1;
        offset += 3;
    } while (i < 2);
    D_801F54D2      = 1;
    D_801F54D5      = 0;
    g_AreaSceneMode = 0;
}
