#include "game_00.h"

MATCH void func_8019E7C4(void) {
    Actor* work;
    Actor* other;

    Area_SelectSceneRecord(0x18);

    g_Task->active_flags = 0;
    g_Task->mirror       = 0;
    g_Task->unk_2B       = (g_Task->unk_2B + 1);
    g_Task->unk_48       = 0;

    work                    = g_Task;
    work->tint.bytes.rgb.r  = 0;
    other                   = g_Task;
    work->vz                = 0;
    work->gravity           = -8;
    other->tint.bytes.rgb.g = 0;

    g_Task->tint.bytes.rgb.b = 0;
    Actor_SelectScript(9);

    g_Task->header.step = (g_Task->header.step + 1);
}
