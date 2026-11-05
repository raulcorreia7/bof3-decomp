#include "game_00.h"

MATCH void func_8019D4BC(void) {
    Area_StoreHeight(g_Task->x.part.integer, g_Task->y.part.integer, 0);
    ((void (*)(s16, s16, s32))Area_SetCellCode)(g_Task->x.part.integer, g_Task->y.part.integer,
                                                FIELD(u8, g_Task, 0x14u));
    if (g_Task->x.part.fraction != 0) {
        Area_StoreHeight((s16)(g_Task->x.part.integer + 1), g_Task->y.part.integer, 0);
        ((void (*)(s16, s16, s32))Area_SetCellCode)((g_Task->x.part.integer + 1), g_Task->y.part.integer,
                                                    FIELD(u8, g_Task, 0x15u));
    }
    if (g_Task->y.part.fraction != 0) {
        Area_StoreHeight(g_Task->x.part.integer, (s16)(g_Task->y.part.integer + 1), 0);
        ((void (*)(s16, s16, s32))Area_SetCellCode)(g_Task->x.part.integer, (g_Task->y.part.integer + 1),
                                                    FIELD(u8, g_Task, 0x16u));
    }
    if ((g_Task->x.part.fraction != 0) && (g_Task->y.part.fraction != 0)) {
        Area_StoreHeight((s16)(g_Task->x.part.integer + 1), (s16)(g_Task->y.part.integer + 1), 0);
        ((void (*)(s16, s16, s32))Area_SetCellCode)((g_Task->x.part.integer + 1),
                                                    (g_Task->y.part.integer + 1), FIELD(u8, g_Task, 0x17u));
    }
}
