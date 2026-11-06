#include "game_00.h"

MATCH void func_8019BBA4(void) {
    s32 x;
    s32 y;
    s32 limit;
    s32 dist;

    x = g_Task->x.fixed;
    y = g_Task->y.fixed;
    if (g_Task->unk_18 != 0) {
        if (g_Task->vx != 0) {
            g_Task->x.fixed = x + g_Task->vx;
            if (g_Task->vx > 0) {
                if (g_Task->unk_18 < g_Task->x.fixed) {
                    g_Task->x.fixed = g_Task->unk_18;
                    g_Task->unk_18  = 0;
                }
            } else {
                if (g_Task->x.fixed < g_Task->unk_18) {
                    g_Task->x.fixed = g_Task->unk_18;
                    g_Task->unk_18  = 0;
                }
            }
        } else {
            g_Task->y.fixed = y + g_Task->vy;
            if (g_Task->vy > 0) {
                if (g_Task->unk_18 < g_Task->y.fixed) {
                    g_Task->y.fixed = g_Task->unk_18;
                    g_Task->unk_18  = 0;
                }
            } else {
                if (g_Task->y.fixed < g_Task->unk_18) {
                    g_Task->y.fixed = g_Task->unk_18;
                    g_Task->unk_18  = 0;
                }
            }
        }
    }
    dist = (s16)Area_SampleHeight(g_Task->x.fixed, g_Task->y.fixed);
    if (dist < (s16)COORD_INT(g_Task->z)) {
        g_Task->gravity = -8;
    } else {
        g_Task->gravity = 0;
        g_Task->vz      = 0;
    }
    g_Task->vz += g_Task->gravity;
    COORD_INT(g_Task->z) += g_Task->vz;
    if ((func_8019C028() & BYTE_MASK) == 0) {
        if ((s16)COORD_INT(g_Task->z) < dist) {
            COORD_INT(g_Task->z) = (u16)Area_SampleHeight(x, y);
            g_Task->vz           = 0;
            g_Task->gravity      = 0;
        }
        if ((g_Task->unk_18 == 0) && (g_Task->vz == 0)) {
            limit = g_Task->vx;
            limit = ABS(limit);
            if (limit >= 16385) {
                g_Task->header.mode = 4;
            } else {
                limit = g_Task->vy;
                limit = ABS(limit);
                if (limit >= 16385) {
                    g_Task->header.mode = 4;
                } else if ((func_8019C4F0(COORD_INT(g_Task->x), COORD_INT(g_Task->y)) & BYTE_MASK) != 0) {
                    g_Task->header.mode = 4;
                } else {
                    g_Task->option_flags = 0;
                    g_Task->unk_0A       = 0;
                    func_8019BF78();
                    Actor_SelectScript(0);
                    g_Task->header.mode = 5;
                }
            }
        }
        func_8014D978();
        Area_SetDrawMode();
    }
}
