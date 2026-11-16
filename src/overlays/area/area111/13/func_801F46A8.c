#include "area111_13.h"

MATCH void func_801F46A8(void) {
    s16 i;
    s16 j;

    if (g_GameCellType == 0) {
        SYS_ClearFlag(g_SceneEventFlags, 0x28);
    }
    if (g_GameCellType == 1) {
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 7; j++) {
                func_801F4604(j, i, D_801F5BC8[i][j]);
            }
        }
        for (j = 0; j < 7; j++) {
            LOW(D_801F5C18[j]) = LOW(D_801F5BFC[j]);
        }
        if (SYS_TestFlag(g_SceneEventFlags, 0x28) == 0) {
            func_801A4BC0(0x11, 0xAD, 0x50);
            func_801A4BC0(0x12, 0xAD, 0x50);
            func_801A4BC0(0x11, 0xAE, 0);
            func_801A4BC0(0x12, 0xAE, 0);
        } else {
            func_801A4BC0(0x11, 0xAD, 0xA1);
            func_801A4BC0(0x12, 0xAD, 0xA1);
            func_801A4BC0(0x11, 0xAE, 0xC0);
            func_801A4BC0(0x12, 0xAE, 0xC0);
        }
    }
    if (g_GameCellType == 5) {
        func_801A4BC0(0xA, 8, 0x50);
        func_801A4BC0(0xB, 8, 0x50);
    }
}
