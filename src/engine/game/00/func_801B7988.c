#include "game_00.h"

MATCH void func_801B7988(void) {
    u16 next;

    next = COORD_INT(g_Task->pos.z);
    next += 0x10;
    COORD_INT(g_Task->pos.z) = next;
    if ((s16)next > Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) + 0x200)
        g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
    Actor_StepAnimLoop();
}
