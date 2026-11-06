#include "game_00.h"

MATCH s32 func_801C364C(s32 wanted_code, s32 cell_code, s32 find_facing) {
    s32 i;
    s32 route;
    s32 result;
    s32 enabled;

    if (func_801C472C(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->state_70.byte, wanted_code & 0xFF, 0) & 0xFF) {
        return 0;
    }
    enabled = find_facing & 0xFF;
    /* FAKE: holds the loop init after the gate mask. */
    MATCH_BARRIER();
    i = 0;
    if (enabled) {
        for (;;) {
            route  = ((g_Task->direction_08 ^ 4) + i) & 7;
            result = func_801C3E40(g_Task->pos.x.fixed + g_FacingSteps[route].x * 2,
                                   g_Task->pos.y.fixed + g_FacingSteps[route].y * 2, 0, COORD_INT(g_Task->pos.z)) &
                     0xFF;
            /* FAKE: holds the increment after the probe call. */
            MATCH_BARRIER();
            i++;
            if (!result) {
                break;
            }
            if (i >= 8) {
                break;
            }
        }
        g_Task->direction_08 = route ^ 4;
    }
    g_Task->header.mode = 2;
    g_Task->header.step = 8;
    g_Task->unk_03      = 0;
    g_Task->unk_04      = 0;
    g_Task->unk_0B      = cell_code;
    return 1;
}
