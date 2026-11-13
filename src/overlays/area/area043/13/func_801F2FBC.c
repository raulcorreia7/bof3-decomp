#include "area043_13.h"

MATCH void func_801F2FBC(void) {
    Actor* work;

    func_80196718(g_Task);
    Area_SelectSceneRecord(0x1BD);
    Actor_SelectScript(0);
    g_Task->unk_2A                 = 0;
    g_Task->scale.x                = 57344;
    g_Task->scale.y                = 57344;
    g_CurrentActor->unk_93         = func_8019651C((u8*)g_Task, 0, 0, 0, 1);
    g_Task->tint.bytes.flags       = 1;
    work                           = g_Task;
    work->tint.signed_bytes.unk_5F = 0x14;
    work->tint.signed_bytes.unk_5E = 0x14;
    work->tint.signed_bytes.unk_5D = 0x14;
    g_Task->unk_2B                 = 3;
}
