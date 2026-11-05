#include "game_00.h"

#define WORK ((Actor*)g_Task)

MATCH void func_8019D270(void) {
    Area_StoreHeight(WORK->x.part.integer, WORK->y.part.integer, 0x10U);
    g_Task->vz = (Area_GetCellCode(WORK->x.part.integer, WORK->y.part.integer) & BYTE_MASK);
    Area_SetCellCode(WORK->x.part.integer, WORK->y.part.integer, 0x11);
    if (WORK->x.part.fraction != 0) {
        Area_StoreHeight((s16)(WORK->x.part.integer + 1), WORK->y.part.integer, 0x10U);
        g_Task->vz =
            (g_Task->vz |
                  ((Area_GetCellCode((s16)(WORK->x.part.integer + 1), WORK->y.part.integer) & BYTE_MASK) << 8));
        Area_SetCellCode((WORK->x.part.integer + 1), WORK->y.part.integer, 0x11);
    }
    if (WORK->y.part.fraction != 0) {
        Area_StoreHeight(WORK->x.part.integer, (s16)(*(u16*)&WORK->y.part.integer + 1), 0x10U);
        g_Task->vz =
            (g_Task->vz |
                  ((Area_GetCellCode(WORK->x.part.integer, (s16)(WORK->y.part.integer + 1)) & BYTE_MASK) << 0x10));
        Area_SetCellCode(WORK->x.part.integer, (WORK->y.part.integer + 1), 0x11);
    }
    if ((WORK->x.part.fraction != 0) && (WORK->y.part.fraction != 0)) {
        Area_StoreHeight((s16)(WORK->x.part.integer + 1), (s16)(WORK->y.part.integer + 1), 0x10U);
        g_Task->vz = (g_Task->vz |
                           (Area_GetCellCode((s16)(WORK->x.part.integer + 1), (s16)(WORK->y.part.integer + 1))
                            << 0x18));
        Area_SetCellCode((WORK->x.part.integer + 1), (WORK->y.part.integer + 1), 0x11);
    }
}
