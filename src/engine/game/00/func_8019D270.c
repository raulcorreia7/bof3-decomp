#include "game_00.h"

#define WORK ((Actor*)g_Task)

MATCH void func_8019D270(void) {
    Area_StoreHeight((s32)COORD_INT(WORK->x), (s32)COORD_INT(WORK->y), 0x10U);
    g_Task->vz = (s32)(Area_GetCellCode(COORD_INT(WORK->x), COORD_INT(WORK->y)) & BYTE_MASK);
    Area_SetCellCode(COORD_INT(WORK->x), COORD_INT(WORK->y), 0x11);
    if (COORD_FRAC(WORK->x) != 0) {
        Area_StoreHeight((s32)(s16)((u16)COORD_INT(WORK->x) + 1), (s32)COORD_INT(WORK->y), 0x10U);
        g_Task->vz =
            (s32)(g_Task->vz |
                  ((Area_GetCellCode((s16)((u16)COORD_INT(WORK->x) + 1), COORD_INT(WORK->y)) & BYTE_MASK) << 8));
        Area_SetCellCode((s16)((u16)COORD_INT(WORK->x) + 1), COORD_INT(WORK->y), 0x11);
    }
    if (COORD_FRAC(WORK->y) != 0) {
        Area_StoreHeight((s32)COORD_INT(WORK->x), (s32)(s16)(*(u16*)&COORD_INT(WORK->y) + 1), 0x10U);
        g_Task->vz =
            (s32)(g_Task->vz |
                  ((Area_GetCellCode(COORD_INT(WORK->x), (s16)((u16)COORD_INT(WORK->y) + 1)) & BYTE_MASK) << 0x10));
        Area_SetCellCode(COORD_INT(WORK->x), (s16)((u16)COORD_INT(WORK->y) + 1), 0x11);
    }
    if ((COORD_FRAC(WORK->x) != 0) && (COORD_FRAC(WORK->y) != 0)) {
        Area_StoreHeight((s32)(s16)((u16)COORD_INT(WORK->x) + 1), (s32)(s16)((u16)COORD_INT(WORK->y) + 1), 0x10U);
        g_Task->vz = (s32)(g_Task->vz |
                           (Area_GetCellCode((s16)((u16)COORD_INT(WORK->x) + 1), (s16)((u16)COORD_INT(WORK->y) + 1))
                            << 0x18));
        Area_SetCellCode((s16)((u16)COORD_INT(WORK->x) + 1), (s16)((u16)COORD_INT(WORK->y) + 1), 0x11);
    }
}
