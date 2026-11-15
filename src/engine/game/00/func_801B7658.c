#include "game_00.h"

MATCH void func_801B7658(void) {
    u8 count;

    count = g_Task->timer;
    if (count == 0) {
        g_Task->vx     = 0;
        g_Task->vy     = 0;
        g_Task->unk_03 = 3;
    } else {
        g_Task->timer = (count - 1);
    }
    g_Task->vz += g_Task->gravity;
    Actor_UpdateMovement();
    if (g_Task->unk_05 == 0) {
        Area_AdvanceScroll(COORD_INT(g_Task->pos.z));
    }
    Actor_StepAnimLoop();
}
