#include "game_00.h"

MATCH s32 func_801C364C(s32 wanted_code, s32 cell_code, s32 find_facing) {
    s32 i;
    s32 route;
    s32 result;
    s32 enabled;

    if (func_801C472C(g_SpadWork->x.fixed, g_SpadWork->y.fixed, g_SpadWork->state_70.byte, wanted_code & BYTE_MASK, 0) &
        BYTE_MASK) {
        return 0;
    }
    enabled = find_facing & BYTE_MASK;
    /* FAKE: holds the loop init after the gate mask. */
    MATCH_BARRIER();
    i = 0;
    if (enabled) {
        for (;;) {
            route  = ((g_SpadWork->direction_08 ^ 4) + i) & 7;
            result = func_801C3E40(g_SpadWork->x.fixed + g_FacingSteps[route].x * 2,
                                   g_SpadWork->y.fixed + g_FacingSteps[route].y * 2, 0, g_SpadWork->z.part.integer) &
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
        g_SpadWork->direction_08 = route ^ 4;
    }
    g_SpadWork->unk_01   = 2;
    g_SpadWork->state_02 = 8;
    g_SpadWork->unk_03   = 0;
    g_SpadWork->unk_04   = 0;
    g_SpadWork->unk_0B   = cell_code;
    return 1;
}
