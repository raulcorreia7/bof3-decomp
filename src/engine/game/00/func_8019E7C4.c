#include "game_00.h"

MATCH void func_8019E7C4(void) {
    Actor* work;
    Actor* other;

    Area_FindSceneRecord(0x18);

    g_Task->flags_24 = 0;
    g_Task->unk_2A   = 0;
    g_Task->unk_2B   = (u8)(g_Task->unk_2B + 1);
    g_Task->unk_48   = 0;

    work                     = g_Task;
    work->tint.bytes.unk_5D  = 0;
    other                    = g_Task;
    work->vz                 = 0;
    work->gravity            = -8;
    other->tint.bytes.unk_5E = 0;

    g_Task->tint.bytes.unk_5F = 0;
    Actor_SelectScript(9);

    g_Task->step = (u8)(g_Task->step + 1);
}
