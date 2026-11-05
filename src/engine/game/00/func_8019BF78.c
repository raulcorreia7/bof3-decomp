#include "game_00.h"

MATCH void func_8019BF78(void) {
    g_Task->unk_0B = (u8)Area_GetCellCode(COORD_INT(g_Task->x), COORD_INT(g_Task->y));
    Area_SetCellCode(COORD_INT(g_Task->x), COORD_INT(g_Task->y), 0x10);
}
