#include "boss004_13.h"

MATCH void func_800C1A04(void) {
    Battle_RequestEnemyScript(4);
    g_Task->unk_09 = 60;
    g_Task->header.step++;
}
