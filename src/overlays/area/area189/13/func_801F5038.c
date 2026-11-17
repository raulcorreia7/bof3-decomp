#include "area189_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F5038(void) {
    SVECTOR* vertex;
    u16*     screen;
    u8*      flags;
    long     depth;
    long     flag;

    vertex            = g_ScratchPadVectors;
    screen            = D_1F800034;
    vertex->vx        = (s16)(((((g_AreaScrollTargetX - 1) & 0xFFFFFF) + 1) >> 9) - 0x4000);
    SP_REF(s16, 0x16) = (s16)(((((g_AreaScrollTargetY - 1) & 0xFFFFFF) + 1) >> 9) - 0x4000);
    SP_REF(s16, 0x18) = (s16)(-COORD_INT(g_Task->pos.z) / 2);
    RotTransPers(vertex, (long*)screen, &depth, &flag);

    flags            = D_80144EF8;
    g_Task->screen_y = SP_REF(u16, 0x36);
    g_Task->vz       = 0;
    if (SYS_TestFlag(flags, 9) != 0 && SYS_TestFlag(flags, 10) == 0) {
        g_SpawnedActors[0].header.flags |= ACTOR_FLAG_HIDDEN;
        g_Task->header.step      = 3;
        g_Task->vy               = -0x2000;
        g_Task->timer            = 0x78;
        g_ScenarioState.timer_06 = 0x3C;
    } else {
        g_Task->header.step = 2;
    }
}
#else
INCLUDE_ASM(func_801F5038);
#endif
