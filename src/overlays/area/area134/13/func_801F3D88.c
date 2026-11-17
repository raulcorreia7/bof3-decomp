/* The dispatch dance keeps every work-cell write. */
#define FAKE_DECL_TASK_VOLATILE
#include "area134_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3D88(void) {
    u8* work;
    s32 edge;

    work                   = (u8*)g_Task;
    edge                   = FIELD(s32, D_801468BC, 0x0);
    g_Task                 = g_Actors;
    g_GameState            = g_Game.members;
    FIELD(s32, work, 0x34) = D_80145EC4 - edge;
    g_Task                 = work;
    TASK_SET(g_Game.members);
    g_Task                  = work;
    g_ScenarioState.step_05 = 0x1E;
    Actor_Clear();
}
#else
INCLUDE_ASM(func_801F3D88);
#endif
