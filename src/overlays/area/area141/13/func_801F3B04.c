#include "area141_13.h"

MATCH void func_801F3B04(void) {
    u8 i;

    if (g_GameCellType == 0) {
        Area_SetCellRun(&D_801F4D94, 1);
        Area_SetCellRun(&D_801F4D94 + 5, 1);
    }
    if (g_GameCellType == 1) {
        if (SYS_TestFlag(g_SceneEventFlags, 122) == 0) {
            i = 2;
            do {
                Area_SetCellRun(i * 5 + &D_801F4D94, 1);
                i++;
            } while (i < 4);
        } else {
            i = 2;
            do {
                Area_SetCellRun(i * 5 + &D_801F4D94, 0);
                i++;
            } while (i < 4);
        }
        if (SYS_TestFlag(g_SceneEventFlags, 123) == 0) {
            i = 4;
            do {
                Area_SetCellRun(i * 5 + &D_801F4D94, 1);
                i++;
            } while (i < 6);
        } else {
            i = 4;
            do {
                Area_SetCellRun(i * 5 + &D_801F4D94, 0);
                i++;
            } while (i < 6);
        }
        if (SYS_TestFlag(g_SceneEventFlags, 124) == 0) {
            i = 6;
            do {
                Area_SetCellRun(i * 5 + &D_801F4D94, 1);
                i++;
            } while (i < 8);
        } else {
            i = 6;
            do {
                Area_SetCellRun(i * 5 + &D_801F4D94, 0);
                i++;
            } while (i < 8);
        }
    }
    if (g_GameCellType == 2) {
        Area_SetCellRun(D_801F4DBC, 1);
    }
}
