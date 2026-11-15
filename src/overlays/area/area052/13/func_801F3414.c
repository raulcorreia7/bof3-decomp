#include "area052_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3414(void) {
    Coord x;
    Coord y;

    if ((u8)Area_GetCursor(&x.fixed, &y.fixed) != 0) {
        Area_StoreHeight(COORD_INT(x), COORD_INT(y), 0);
        Area_SetCellCode(COORD_INT(x), COORD_INT(y), (u8)g_Task->unk_18);
        Area_StoreHeight(COORD_INT(x) + 1, COORD_INT(y), 0);
        /* FAKE: retail passes the widened column untruncated, while the owner body proves s16
         * parameters; a caller-side s32 view of Area_SetCellCode is the missing declaration. */
        ((void (*)(s32, s32, u8))Area_SetCellCode)(COORD_INT(x) + 1, COORD_INT(y), (u8)(g_Task->unk_18 >> 8));
        g_Task->unk_18 = g_Task->unk_1C;
        g_Task->unk_1C = 0;
        Area_StoreHeight(COORD_INT(x), COORD_INT(y) += 2, 0x10);
        g_Task->unk_1C |= (u8)Area_GetCellCode(COORD_INT(x), COORD_INT(y));
        Area_SetCellCode(COORD_INT(x), COORD_INT(y), 0x11);
        Area_StoreHeight(++COORD_INT(x), COORD_INT(y), 0x10);
        g_Task->unk_1C |= (u8)Area_GetCellCode(COORD_INT(x), COORD_INT(y)) << 8;
        Area_SetCellCode(COORD_INT(x), COORD_INT(y), 0x11);
        g_Task->direction_08 = FACING_DOWN;
        Area_MoveActorRoute(g_ScriptState, 5);
        g_ScriptState->unk_07 = 2;
    }
}
#else
INCLUDE_ASM(func_801F3414);
#endif
