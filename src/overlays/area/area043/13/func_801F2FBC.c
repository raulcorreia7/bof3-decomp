#include "area043_13.h"

MATCH void func_801F2FBC(void) {
    Actor* work;

    func_80196718(g_SpadWork);
    Area_FindSceneRecord(0x1BD);
    Actor_SelectScript(0);
    g_SpadWork->unk_2A             = 0;
    g_SpadWork->unk_40             = 0xE000;
    g_SpadWork->unk_44             = 0xE000;
    g_CurrentActor->unk_93         = func_8019651C((u8*)g_SpadWork, 0, 0, 0, 1);
    g_SpadWork->tint.bytes.flags   = 1;
    work                           = g_SpadWork;
    work->tint.signed_bytes.unk_5F = 0x14;
    work->tint.signed_bytes.unk_5E = 0x14;
    work->tint.signed_bytes.unk_5D = 0x14;
    g_SpadWork->unk_2B             = 3;
}
