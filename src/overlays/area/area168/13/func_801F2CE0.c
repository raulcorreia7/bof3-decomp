/* Every step re-reads the scratchpad cell. */
#define TASK_VOLATILE
#include "area168_13.h"

MATCH void func_801F2CE0(void) {
    Actor* actor;
    u8     i;
    s32    z;
    /* FAKE: retail materializes the mode in v0 before reading the task cell. */
    FAKE_REG(u8, mode, "v0");

    g_Task->unk_06     = 0;
    actor              = g_Task;
    actor->unk_18      = TO_COORD(16);
    actor->vx          = TO_COORD(16);
    actor->pos.z.fixed = 0;
    for (i = 0; i < 3; i++) {
        Actor* work   = g_Task;
        work->vy      = D_801F4B44[i].from;
        work->unk_1C  = D_801F4B44[i].to;
        z             = TO_COORD(COORD_INT(work->pos.z) + 0x80);
        work->gravity = z;
        work->vz      = z;
        func_801F2E10(&work->vx, &work->unk_18);
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x91) != 0) {
        mode = 2;
        FAKE_BARRIER(); /* FAKE: keeps the task cell read after the mode constant. */
        g_Task->header.mode = mode;
    }
}
