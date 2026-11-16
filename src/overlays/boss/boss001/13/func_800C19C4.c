#include "boss001_13.h"

MATCH void func_800C19C4(void) {
    Battle_RequestEnemyScript(4);
    Area_SetCellPalette(99, 20);
    g_Task->header.step++;
}
