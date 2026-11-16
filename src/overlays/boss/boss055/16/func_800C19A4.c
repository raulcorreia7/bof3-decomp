#include "boss055_16.h"

MATCH void func_800C19A4(void) {
    g_Task->param.unk_0B = 1;
    g_Battle.unk_DE      = 0;
    Battle_RequestEnemyScript(0);
    func_801E30F8();
    g_Task->header.step++;
}
