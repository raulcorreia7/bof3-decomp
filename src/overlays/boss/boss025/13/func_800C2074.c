#include "boss025_13.h"

MATCH void func_800C2074(void) {
    Actor_RequestScript(0xD);
    g_Task->unk_2A = 0;
    func_8014DAEC();
    Battle_DefeatEnemy();
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->header.mode = 3;
    g_Task->header.step = 0;
    g_Task->unk_03      = 0;
}
