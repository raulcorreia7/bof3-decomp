#include "boss025_13.h"

MATCH void func_800C1CB0(void) {
    Actor_RequestScript(0xF);
    g_Task->unk_2A = 0;
    func_8014DAEC();
    Battle_CollectEnemySpoils();
    g_Task->flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->mode   = 3;
    g_Task->step   = 0;
    g_Task->unk_03 = 0;
}
