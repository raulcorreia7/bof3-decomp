#include "game_00.h"

MATCH s32 func_801C4040(s32 pos_x, s32 pos_y, s16 probe_range) {
    s32 dist;
    s32 found;
    u16 saved;

    if ((func_801C3E80(pos_x, pos_y, 0) & BYTE_MASK) != 0) {
        return 1;
    }
    if ((pos_x & HALF_MASK) != 0) {
        if (Area_ReadStepHeight(pos_x, pos_y, 3) >= 0x41) {
            /* Retail reloads the scratch flag per test; clean C may hoist. */
            if (SP_REF(u8, 0x0u) != 0) {
                return 1;
            }
        }
    }
    if ((pos_y & HALF_MASK) != 0) {
        if (Area_ReadStepHeight(pos_x, pos_y, 5) >= 0x41) {
            if (SP_REF(u8, 0x0u) != 0) {
                return 1;
            }
        }
    }
    if (((pos_x & HALF_MASK) != 0) && ((pos_y & HALF_MASK) != 0)) {
        if (Area_ReadStepHeight(pos_x, pos_y, 4) >= 0x41) {
            if (SP_REF(u8, 0x0u) != 0) {
                return 1;
            }
        }
    }
    dist = Area_ReadHeight(pos_x, pos_y) - probe_range;
    dist = ABS(dist);
    if (dist < 193) {
        saved                    = COORD_INT(g_Task->pos.z);
        COORD_INT(g_Task->pos.z) = (u16)probe_range;
        found                    = ~Actor_FindInRange(pos_x, pos_y, 0) != 0;
        COORD_INT(g_Task->pos.z) = saved;
        return found;
    }
    return 1;
}
