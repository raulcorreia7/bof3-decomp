#include "boss025_13.h"

MATCH void func_800C1CB0(void) {
    Actor_RequestScript(0xF);
    g_Task->unk_2A = 0;
    Actor_StepAnimOnce();
    Battle_DefeatEnemy();
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->header.mode = 3;
    g_Task->header.step = 0;
    g_Task->unk_03      = 0;
}
