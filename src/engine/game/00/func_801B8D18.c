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
        if (g_Task->direction_08 == 3) {
            if (g_Task->x.part.fraction != 0) {
                return false;
            }
            x     = g_Task->x.fixed + 0x8000;
            y     = g_Task->y.fixed & 0xFFFF0000;
            value = Area_ReadStepHeight(x, y, 3);
            if (SPAD_ACTIVE == 0 || value < 0x41) {
                return false;
            }
            if (g_Task->y.part.fraction != 0) {
                value = Area_ReadStepHeight(x, y + 0x8000, 3);
                if (SPAD_ACTIVE == 0 || value < 0x41) {
                    return false;
                }
            }
            return true;
        }
        if (g_Task->direction_08 == 5) {
            if (g_Task->y.part.fraction != 0) {
                return false;
            }
            x     = g_Task->x.fixed & 0xFFFF0000;
            y     = g_Task->y.fixed + 0x8000;
            value = Area_ReadStepHeight(x, y, 5);
            if (SPAD_ACTIVE == 0 || value < 0x41) {
                return false;
            }
            if (g_Task->x.part.fraction != 0) {
                value = Area_ReadStepHeight(x + 0x8000, y, 5);
                if (SPAD_ACTIVE == 0 || value < 0x41) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    if (g_Task->direction_08 == 3) {
        if (g_Task->x.part.fraction == 0) {
            return false;
        }
        x     = g_Task->x.fixed + 0x10000;
        y     = g_Task->y.fixed & 0xFFFF0000;
        value = Area_ReadStepHeight(x, y, 3);
        if (SPAD_ACTIVE == 0 || value < 0x41) {
            return false;
        }
        y |= 0x8000;
        value = Area_ReadStepHeight(x, y, 3);
        if (SPAD_ACTIVE == 0 || value < 0x41) {
            return false;
        }
        if (g_Task->y.part.fraction == 0) {
            value = Area_ReadStepHeight(x, y - 0x10000, 3);
            if (SPAD_ACTIVE == 0 || value < 0x41) {
                return false;
            }
        }
        return true;
    }
    if (g_Task->direction_08 == 5) {
        if (g_Task->y.part.fraction == 0) {
            return false;
        }
        x     = g_Task->x.fixed & 0xFFFF0000;
        y     = g_Task->y.fixed + 0x10000;
        value = Area_ReadStepHeight(x, y, 5);
        if (SPAD_ACTIVE == 0 || value < 0x41) {
            return false;
        }
        x |= 0x8000;
        value = Area_ReadStepHeight(x, y, 5);
        if (SPAD_ACTIVE == 0 || value < 0x41) {
            return false;
        }
        if (g_Task->x.part.fraction == 0) {
            value = Area_ReadStepHeight(x - 0x10000, y, 3);
            if (SPAD_ACTIVE == 0 || value < 0x41) {
                return false;
            }
        }
        return true;
    }
    return false;
}
