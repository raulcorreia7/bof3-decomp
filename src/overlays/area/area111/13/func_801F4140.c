#include "area111_13.h"

#ifdef NON_MATCHING
/* Tests the area's crossing boundaries and scene trigger. */
NON_MATCHING s32 func_801F4140(s32 x, s32 y) {
    s16 cell_x;
    s16 cell_y;

    if (g_GameCellType == 0) {
        SYS_ClearFlag(g_SceneEventFlags, 40);
    }
    if (g_GameCellType != 1) {
        return 0;
    }
    cell_x = x >> 15;
    cell_y = y >> 15;
    if ((s16)cell_x == 22 && (u16)(cell_y - 354) < 27 && D_80181B00[SELF(Actor)->direction & 7][0] == (s16)cell_x - 21) {
        func_801F4510(3);
        return 0;
    }
    if ((s16)cell_x == 48 && (u16)(cell_y - 354) < 27 && D_80181B00[SELF(Actor)->direction & 7][0] == (s16)cell_x - 49) {
        func_801F4510(7);
        return 0;
    }
    if ((s16)cell_y == 354 && (u16)(cell_x - 22) < 27 && D_80181B00[SELF(Actor)->direction & 7][1] == (s16)cell_y - 353) {
        func_801F4510(5);
        return 0;
    }
    if ((s16)cell_y == 380 && (u16)(cell_x - 22) < 27 && D_80181B00[SELF(Actor)->direction & 7][1] == (s16)cell_y - 381) {
        func_801F4510(1);
        return 0;
    }
    if ((s16)cell_x == 32 && (u16)(cell_y - 366) < 3 && D_80181B00[SELF(Actor)->direction & 7][0] == (s16)cell_x - 33) {
        func_801F4510(7);
        return 0;
    }
    if ((s16)cell_x == 38 && (u16)(cell_y - 366) < 3 && D_80181B00[SELF(Actor)->direction & 7][0] == (s16)cell_x - 37) {
        func_801F4510(3);
        return 0;
    }
    if ((s16)cell_y == 364 && (u16)(cell_x - 34) < 3 && D_80181B00[SELF(Actor)->direction & 7][1] == (s16)cell_y - 365) {
        func_801F4510(1);
        return 0;
    }
    if ((s16)cell_y == 370 && (u16)(cell_x - 34) < 3 && D_80181B00[SELF(Actor)->direction & 7][1] == (s16)cell_y - 369) {
        func_801F4510(5);
        return 0;
    }
    if ((u32)((x >> 16) - 17) < 2 && (u32)((y >> 16) - 183) < 2 && !SYS_TestFlag(g_SceneEventFlags, 40)) {
        Game_SetScriptActive();
        g_SceneEventMode = 17;
        g_SceneEventStep = 20;
    }
    return 0;
}
#else
INCLUDE_ASM(func_801F4140);
#endif
