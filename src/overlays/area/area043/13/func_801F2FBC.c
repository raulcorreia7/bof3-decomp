#include "area043_13.h"

MATCH void func_801F2FBC(void) {
    Actor* work;

    func_80196718(g_Task);
    Area_SceneSelectRecord(0x1BD);
    Script_Select(0);
    g_Task->mirror           = 0;
    g_Task->scale.x          = 57344;
    g_Task->scale.y          = 57344;
    g_CurrentActor->unk_93   = func_8019651C((u8*)g_Task, 0, 0, 0, 1);
    g_Task->tint.bytes.flags = 1;
    work                     = g_Task;
    work->tint.steps.delta.b = 0x14;
    work->tint.steps.delta.g = 0x14;
    work->tint.steps.delta.r = 0x14;
    g_Task->unk_2B           = 3;
}
