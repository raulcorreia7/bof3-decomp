#include "game_00.h"

MATCH void func_8019BF78(void) {
    g_Task->unk_0B = (u8)Area_GetCellCode(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y));
    Area_SetCellCode(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y), 0x10);
}
