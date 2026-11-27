#include "area189_13.h"

/* Project the leader onto the screen, then pick its next step from the two scenario flags. */
MATCH void func_801F5038(void) {
    u8*  flags;
    long depth;
    long flag;

    g_ScratchPadVectors[0].vx = (s16)(((((g_AreaScrollTargetX - 1) & 0xFFFFFF) + 1) >> 9) - 0x4000);
    g_ScratchPadVectors[0].vy = (s16)(((((g_AreaScrollTargetY - 1) & 0xFFFFFF) + 1) >> 9) - 0x4000);
    g_ScratchPadVectors[0].vz = -COORD_INT(SELF(Actor)->pos.z) / 2;
    RotTransPers(&g_ScratchPadVectors[0], (long*)D_1F800034, &depth, &flag);

    flags                 = g_SceneFlagRows[SCENARIO_DESERT_OF_DEATH];
    SELF(Actor)->screen_y = D_1F800034[1];
    SELF(Actor)->vz       = 0;
    if (SYS_TestFlag(flags, 9) != 0 && SYS_TestFlag(flags, 10) == 0) {
        g_SpawnedActors[0].header.flags |= ACTOR_FLAG_HIDDEN;
        SELF(Actor)->header.step = 3;
        SELF(Actor)->vy          = -0x2000;
        SELF(Actor)->timer       = 0x78;
        g_ScenarioState.timer_06 = 0x3C;
    } else {
        SELF(Actor)->header.step = 2;
    }
}
