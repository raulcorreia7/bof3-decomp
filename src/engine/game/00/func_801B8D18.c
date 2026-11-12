#include "game_00.h"

/* Scratch byte 0: nonzero while the current route probe is active. The retail
 * code materializes this symbol address in each branch, so keep the pointer
 * expression rather than a cached direct access. */
#define SPAD_ACTIVE (*(volatile u8*)&D_1F800000)

MATCH bool func_801B8D18(void) {
    s16 value;
    s32 x;
    s32 y;

    if (g_Task->state_70.byte == 0) {
        if (g_Task->direction_08 == FACING_RIGHT) {
            if (COORD_FRAC(g_Task->pos.x) != 0) {
                return false;
            }
            x     = g_Task->pos.x.fixed + COORD_HALF;
            y     = g_Task->pos.y.fixed & 0xFFFF0000;
            value = Area_ReadStepHeight(x, y, 3);
            if (SPAD_ACTIVE == 0 || value < 0x41) {
                return false;
            }
            if (COORD_FRAC(g_Task->pos.y) != 0) {
                value = Area_ReadStepHeight(x, y + 0x8000, 3);
                if (SPAD_ACTIVE == 0 || value < 0x41) {
                    return false;
                }
            }
            return true;
        }
        if (g_Task->direction_08 == FACING_DOWN) {
            if (COORD_FRAC(g_Task->pos.y) != 0) {
                return false;
            }
            x     = g_Task->pos.x.fixed & 0xFFFF0000;
            y     = g_Task->pos.y.fixed + COORD_HALF;
            value = Area_ReadStepHeight(x, y, 5);
            if (SPAD_ACTIVE == 0 || value < 0x41) {
                return false;
            }
            if (COORD_FRAC(g_Task->pos.x) != 0) {
                value = Area_ReadStepHeight(x + 0x8000, y, 5);
                if (SPAD_ACTIVE == 0 || value < 0x41) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    if (g_Task->direction_08 == FACING_RIGHT) {
        if (COORD_FRAC(g_Task->pos.x) == 0) {
            return false;
        }
        x     = g_Task->pos.x.fixed + TO_COORD(1);
        y     = g_Task->pos.y.fixed & 0xFFFF0000;
        value = Area_ReadStepHeight(x, y, 3);
        if (SPAD_ACTIVE == 0 || value < 0x41) {
            return false;
        }
        y |= 32768;
        value = Area_ReadStepHeight(x, y, 3);
        if (SPAD_ACTIVE == 0 || value < 0x41) {
            return false;
        }
        if (COORD_FRAC(g_Task->pos.y) == 0) {
            value = Area_ReadStepHeight(x, y - TO_COORD(1), 3);
            if (SPAD_ACTIVE == 0 || value < 0x41) {
                return false;
            }
        }
        return true;
    }
    if (g_Task->direction_08 == FACING_DOWN) {
        if (COORD_FRAC(g_Task->pos.y) == 0) {
            return false;
        }
        x     = g_Task->pos.x.fixed & 0xFFFF0000;
        y     = g_Task->pos.y.fixed + TO_COORD(1);
        value = Area_ReadStepHeight(x, y, 5);
        if (SPAD_ACTIVE == 0 || value < 0x41) {
            return false;
        }
        x |= 32768;
        value = Area_ReadStepHeight(x, y, 5);
        if (SPAD_ACTIVE == 0 || value < 0x41) {
            return false;
        }
        if (COORD_FRAC(g_Task->pos.x) == 0) {
            value = Area_ReadStepHeight(x - TO_COORD(1), y, 3);
            if (SPAD_ACTIVE == 0 || value < 0x41) {
                return false;
            }
        }
        return true;
    }
    return false;
}
