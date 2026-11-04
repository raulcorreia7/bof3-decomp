#include "game_00.h"

MATCH void func_8019BBA4(void) {
    s32 x;
    s32 y;
    s32 limit;
    s32 dist;

    x = g_SpadWork->x.fixed;
    y = g_SpadWork->y.fixed;
    if (g_SpadWork->unk_18 != 0) {
        if (g_SpadWork->unk_0C != 0) {
            g_SpadWork->x.fixed = x + g_SpadWork->unk_0C;
            if (g_SpadWork->unk_0C > 0) {
                if (g_SpadWork->unk_18 < g_SpadWork->x.fixed) {
                    g_SpadWork->x.fixed = g_SpadWork->unk_18;
                    g_SpadWork->unk_18  = 0;
                }
            } else {
                if (g_SpadWork->x.fixed < g_SpadWork->unk_18) {
                    g_SpadWork->x.fixed = g_SpadWork->unk_18;
                    g_SpadWork->unk_18  = 0;
                }
            }
        } else {
            g_SpadWork->y.fixed = y + g_SpadWork->unk_10;
            if (g_SpadWork->unk_10 > 0) {
                if (g_SpadWork->unk_18 < g_SpadWork->y.fixed) {
                    g_SpadWork->y.fixed = g_SpadWork->unk_18;
                    g_SpadWork->unk_18  = 0;
                }
            } else {
                if (g_SpadWork->y.fixed < g_SpadWork->unk_18) {
                    g_SpadWork->y.fixed = g_SpadWork->unk_18;
                    g_SpadWork->unk_18  = 0;
                }
            }
        }
    }
    dist = (s16)Area_SampleHeight(g_SpadWork->x.fixed, g_SpadWork->y.fixed);
    if (dist < (s16)g_SpadWork->z.part.integer) {
        g_SpadWork->gravity = -8;
    } else {
        g_SpadWork->gravity = 0;
        g_SpadWork->vz      = 0;
    }
    g_SpadWork->vz += g_SpadWork->gravity;
    g_SpadWork->z.part.integer += g_SpadWork->vz;
    if ((func_8019C028() & BYTE_MASK) == 0) {
        if ((s16)g_SpadWork->z.part.integer < dist) {
            g_SpadWork->z.part.integer = (u16)Area_SampleHeight(x, y);
            g_SpadWork->vz             = 0;
            g_SpadWork->gravity        = 0;
        }
        if ((g_SpadWork->unk_18 == 0) && (g_SpadWork->vz == 0)) {
            limit = g_SpadWork->unk_0C;
            if (limit < 0) {
                limit = -limit;
            }
            if (limit >= 16385) {
                g_SpadWork->unk_01 = 4;
            } else {
                limit = g_SpadWork->unk_10;
                if (limit < 0) {
                    limit = -limit;
                }
                if (limit >= 16385) {
                    g_SpadWork->unk_01 = 4;
                } else if ((func_8019C4F0(g_SpadWork->x.part.integer, g_SpadWork->y.part.integer) & BYTE_MASK) != 0) {
                    g_SpadWork->unk_01 = 4;
                } else {
                    g_SpadWork->option_flags = 0;
                    g_SpadWork->unk_0A       = 0;
                    func_8019BF78();
                    Actor_SelectScript(0);
                    g_SpadWork->unk_01 = 5;
                }
            }
        }
        func_8014D978();
        Area_SetDrawMode();
    }
}
