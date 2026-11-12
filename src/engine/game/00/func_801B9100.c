#include "game_00.h"

MATCH void func_801B9100(void) {
    Actor* work;
    s32    adjustment;
    s16    distance;

    work               = g_Task;
    work->direction_08 = (work->direction_08 + 1) & 0x7;
    adjustment         = work->vz - 8;
    COORD_INT(work->pos.z) += adjustment;
    work->vz = adjustment;
    Actor_RequestScript(g_Task->direction_08);
    distance = Area_ReadHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    if (distance - (s16)COORD_INT(g_Task->pos.z) >= 257) {
        u8* state = &g_GameStateIndex;

        if (*state != GAME_REQUEST_AREA_CHANGE) {
            *state = GAME_REQUEST_AREA_CHANGE;
            g_AreaWalkFlags |= 0x200;
        }
    }
}
