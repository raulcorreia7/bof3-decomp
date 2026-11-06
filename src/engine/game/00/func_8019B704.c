#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_8019B704(void) {
    s32 saved;
    s32 acc;
    s32 total;
    s32 delta;
    s16 dist;
    s16 temp;

    g_Task->unk_06 = 0;
    g_Task->unk_07 = 0;
    if (g_Task->unk_0C != 0) {
        saved          = g_Task->unk_0C;
        acc            = saved + g_Task->unk_18;
        g_Task->unk_0C = acc;
        acc = ABS(acc);
        if (acc < 0x1000) {
            g_Task->unk_0C = saved;
            g_Task->unk_18 = 0;
        }
        total               = g_Task->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.x.fixed = total;
        delta               = total - D_80145EC4;
    } else {
        saved          = g_Task->unk_10;
        acc            = saved + g_Task->unk_1C;
        g_Task->unk_1C = acc;
        acc = ABS(acc);
        if (acc < 0x1000) {
            g_Task->unk_10 = saved;
            g_Task->unk_1C = 0;
        }
        total               = g_Task->pos.y.fixed + g_Task->unk_10;
        g_Task->pos.y.fixed = total;
        delta               = total - D_80145EC8;
    }
    delta = ABS(delta);
    if ((g_Task->unk_18 == 0) && (g_Task->unk_1C == 0)) {
        g_Task->unk_06 = 1;
        g_Task->unk_07 = 0;
    }
    acc            = g_Task->unk_14 + g_Task->unk_20;
    g_Task->unk_14 = acc;
    COORD_INT(g_Task->depth) += acc;
    if ((g_AreaCameraMoving == 0) && (delta > 0x40000) && (g_AreaScrollTargetX == D_80145EC4) &&
        (g_AreaScrollTargetY == D_80145EC8)) {
        if (g_Task->unk_0C > 0) {
            D_8014930A = (s16)(D_8014930A + 5);
        } else if (g_Task->unk_0C < 0) {
            D_8014930A = (s16)(D_8014930A - 5);
        } else if (g_Task->unk_10 > 0) {
            D_8014930E = (s16)(D_8014930E + 5);
        } else if (g_Task->unk_10 < 0) {
            D_8014930E = (s16)(D_8014930E - 5);
        }
        temp                   = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
        g_AreaCameraHeightStep = 0;
        if (temp < (s16)g_AreaCameraHeight) {
            g_AreaCameraHeightStep = (s16)((temp - (s16)g_AreaCameraHeight) / 20);
        }
        g_AreaCameraStep = 0x40;
        g_Task->unk_09   = 0x14;
    }
    dist = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    if (dist < (s16)COORD_INT(g_Task->depth)) {
        g_Task->unk_20 = -8;
    } else {
        g_Task->unk_14           = 0;
        g_Task->unk_20           = 0;
        COORD_INT(g_Task->depth) = (u16)dist;
    }
    if ((func_8019C028() & BYTE_MASK) == 0) {
        if ((func_8019C344(g_Task->pos.x.fixed, g_Task->pos.y.fixed) & BYTE_MASK) != 0) {
            g_Task->unk_06 = 1;
            g_Task->unk_07 = 2;
        } else if ((func_8019C1E4() & BYTE_MASK) != 0) {
            g_Task->unk_06 = 1;
            g_Task->unk_07 = 1;
        }
        if (g_Task->unk_06 != 0) {
            switch (g_Task->unk_07) {
                case 0:
                    if ((COORD_FRAC(g_Task->pos.x) == 0) && (COORD_FRAC(g_Task->pos.y) == 0)) {
                        g_Task->unk_07 = 0;
                        g_Task->unk_0A = 0;
                        Actor_SelectScript(0);
                        g_Task->header.mode = 5;
                    } else {
                        func_8019C124(0);
                    }
                    break;
                case 1:
                    func_8019C124(0);
                    break;
                default:
                    func_8019C124(1);
                    break;
            }
        }
        func_8014D978();
        Area_SetDrawMode();
    }
}
#else
INCLUDE_ASM(func_8019B704);
#endif
