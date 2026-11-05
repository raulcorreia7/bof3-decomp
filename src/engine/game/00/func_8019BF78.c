#include "game_00.h"

MATCH void func_8019BF78(void) {
    g_Task->unk_0B = Area_GetCellCode(g_Task->x.part.integer, g_Task->y.part.integer);
    Area_SetCellCode(g_Task->x.part.integer, g_Task->y.part.integer, 0x10);
}
