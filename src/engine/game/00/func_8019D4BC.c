#include "game_00.h"

MATCH void func_8019D4BC(void) {
    Area_StoreHeight(COORD_INT(g_Task->x), COORD_INT(g_Task->y), 0);
    Area_SetCellCode(COORD_INT(g_Task->x), COORD_INT(g_Task->y), FIELD(u8, g_Task, 0x14u));
    if (COORD_FRAC(g_Task->x) != 0) {
        Area_StoreHeight((s16)(COORD_INT(g_Task->x) + 1), COORD_INT(g_Task->y), 0);
        Area_SetCellCode((s16)(COORD_INT(g_Task->x) + 1), COORD_INT(g_Task->y),
                                                    FIELD(u8, g_Task, 0x15u));
    }
    if (COORD_FRAC(g_Task->y) != 0) {
        Area_StoreHeight(COORD_INT(g_Task->x), (s16)((u16)COORD_INT(g_Task->y) + 1), 0);
        Area_SetCellCode(COORD_INT(g_Task->x), (s16)((u16)COORD_INT(g_Task->y) + 1),
                                                    FIELD(u8, g_Task, 0x16u));
    }
    if ((COORD_FRAC(g_Task->x) != 0) && (COORD_FRAC(g_Task->y) != 0)) {
        Area_StoreHeight((s16)(COORD_INT(g_Task->x) + 1), (s16)(COORD_INT(g_Task->y) + 1), 0);
        Area_SetCellCode((s16)(COORD_INT(g_Task->x) + 1), (s16)(COORD_INT(g_Task->y) + 1),
                                                    FIELD(u8, g_Task, 0x17u));
    }
}
