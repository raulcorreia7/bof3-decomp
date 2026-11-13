#include "game_00.h"

MATCH void func_801B76F4(void) {
    s16 dist;

    g_Task->vz += g_Task->gravity;
    Actor_UpdateMovement();
    dist = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    if ((s16)COORD_INT(g_Task->pos.z) < dist) {
        COORD_INT(g_Task->pos.z) = dist;
        if (g_Task->vz < -0x80) {
            Actor_RequestScript((g_Task->direction_08 >> 1) + 0x34);
        } else if (g_Task->direction_08 == FACING_RIGHT) {
            Actor_RequestScript(0x38);
        } else {
            Actor_RequestScript(0x39);
        }
        g_Task->vz      = 0;
        g_Task->gravity = 0;
        g_Task->unk_03  = 4;
    }
    if ((g_Task->unk_05 == 0) && (((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE)) == 0)) {
        Area_AdvanceScroll((s16)COORD_INT(g_Task->pos.z));
    }
    Actor_StepAnimLoop();
}
