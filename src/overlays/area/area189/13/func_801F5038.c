#include "area189_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F5038(void) {
    /* FAKE: Pin the mask to a1 so the screen pointer reuses a1 after the transform. */
    FAKE_REG(s32, mask, "a1");
    SVECTOR* vertex;
    long*    screen;
    u8*      flags;
    long     depth;
    long     flag;
    s16      actor_z_int;

    mask              = 0xFFFFFF;
    vertex            = g_ScratchPadVectors;
    vertex->vx        = (s16)(((((g_AreaScrollTargetX - 1) & mask) + 1) >> 9) - 0x4000);
    SP_REF(s16, 0x16) = (s16)(((((g_AreaScrollTargetY - 1) & mask) + 1) >> 9) - 0x4000);
    actor_z_int       = COORD_INT(TASK(Actor)->pos.z);
    /* FAKE: Keep screen setup between the z load and its arithmetic. */
    FAKE_ORDER_LOCK(screen = D_1F800034);
    SP_REF(s16, 0x18) = (s16)(-actor_z_int / 2);
    RotTransPers(vertex, screen, &depth, &flag);

    flags                 = D_80144EF8;
    TASK(Actor)->screen_y = SP_REF(u16, 0x36);
    TASK(Actor)->vz       = 0;
    if (SYS_TestFlag(flags, 9) != 0 && SYS_TestFlag(flags, 10) == 0) {
        g_SpawnedActors[0].header.flags |= ACTOR_FLAG_HIDDEN;
        TASK(Actor)->header.step = 3;
        TASK(Actor)->vy          = -0x2000;
        TASK(Actor)->timer       = 0x78;
        g_ScenarioState.timer_06 = 0x3C;
    } else {
        TASK(Actor)->header.step = 2;
    }
}
#else
INCLUDE_ASM(func_801F5038);
#endif
