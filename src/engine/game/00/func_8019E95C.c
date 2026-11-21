#include "game_00.h"

MATCH void func_8019E95C(void) {
    Actor* work;
    Actor* other;

    if ((u8)Area_SelectSceneRecord(0x46) != 0) {
        Actor_Clear();
        return;
    }

    g_Task->draw_layer   = (g_Task->draw_layer + 1);
    g_Task->mirror       = 0;
    g_Task->active_flags = 0;
    g_Task->unk_2B       = (g_Task->unk_2B + 1);
    g_Task->unk_48       = 1;

    work                     = g_Task;
    work->tint.bytes.rgb.r   = 0;
    other                    = g_Task;
    work->vy                 = -0x2000;
    work->vx                 = 0;
    work->vz                 = 64;
    other->tint.bytes.rgb.g  = 0;
    g_Task->tint.bytes.rgb.b = 0;
    Actor_SelectScript(0);
    g_Task->header.step = (g_Task->header.step + 1);
}
