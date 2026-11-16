#include "area040_13.h"

MATCH void func_801F3A00(void) {
    u8* mode;
    u8  y;
    u8  x;

    mode = &D_80144EA9;
    if (g_GameCellType != 1) {
        *mode &= 0xF0;
        for (y = 0; y < 7; y++) {
            func_801A4BC0(0x41, y + 3, 0xA4);
            func_801A4BC0(0x42, y + 3, 0xA4);
            func_801A4BC0(0x43, y + 3, 0xA4);
            func_801A4BC0(0x44, y + 3, 0xA4);
        }
    }
    if (g_GameCellType == 6 && SYS_TestFlag(g_SceneEventFlags, 0x27) == 0) {
        func_801A4BC0(0x92, 0x1D, 0);
        func_801A4BC0(0x93, 0x1D, 0);
        func_801A4BC0(0x92, 0x1C, 0x50);
        func_801A4BC0(0x93, 0x1C, 0x50);
    }
    if (g_GameLastCellType == 6) {
        if (g_GameCellType == 2) {
            g_GameFlags &= ~BIT(12);
            SYS_ClearFlag(g_SceneEventFlags, 0x27);
            g_ScriptVars[0] = 0;
        }
    }
    if (g_GameLastCellType == 4) {
        for (y = 0; y < 4; y++) {
            for (x = 0; x < 4; x++) {
                if (D_801F4960[y][x] != 0) {
                    Area_SetCellPalette((s16)(x + 0x94), (s16)(y + 0x20));
                }
            }
        }
    }
}
