/* The dispatch dance keeps every work-cell write. */
#define TASK_VOLATILE
#include "area134_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3D88(void) {
    Actor* work;
    s32    edge;

    work              = g_Task;
    edge              = FIELD(s32, D_801468BC, 0x0);
    g_Task            = g_Actors;
    D_80146875        = 0x1E;
    g_GameState       = g_Game.members;
    work->pos.x.fixed = g_Game.members[0].pos.x.fixed - edge;
    g_Task            = work;
    TASK_SET(g_Game.members);
    g_Task = work;
    Actor_Clear();
}
#else
INCLUDE_ASM(func_801F3D88);
#endif
