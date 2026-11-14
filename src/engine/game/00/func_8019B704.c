#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_8019B704(void) {
    s32 saved;
    s32 acc;
    s32 total;
    s32 delta;
    s16 dist;
    s16 temp;

    g_Task->unk_06       = 0;
    g_Task->option_flags = 0;
    if (g_Task->vx != 0) {
        saved      = g_Task->vx;
        acc        = saved + g_Task->unk_18;
        g_Task->vx = acc;
        acc        = ABS(acc);
        if (acc < ONE) {
            g_Task->vx     = saved;
            g_Task->unk_18 = 0;
        }
        total               = g_Task->pos.x.fixed + g_Task->vx;
        g_Task->pos.x.fixed = total;
        delta               = total - D_80145EC4;
    } else {
        saved          = g_Task->vy;
        acc            = saved + g_Task->unk_1C;
        g_Task->unk_1C = acc;
        acc            = ABS(acc);
        if (acc < ONE) {
            g_Task->vy     = saved;
            g_Task->unk_1C = 0;
        }
        total               = g_Task->pos.y.fixed + g_Task->vy;
        g_Task->pos.y.fixed = total;
        delta               = total - D_80145EC8;
    }
    delta = ABS(delta);
    if ((g_Task->unk_18 == 0) && (g_Task->unk_1C == 0)) {
        g_Task->unk_06       = 1;
        g_Task->option_flags = 0;
    }
    acc        = g_Task->vz + g_Task->gravity;
    g_Task->vz = acc;
    COORD_INT(g_Task->pos.z) += acc;
    if ((g_AreaCameraMoving == 0) && (delta > TO_COORD(4)) && (g_AreaScrollTargetX == D_80145EC4) && (g_AreaScrollTargetY == D_80145EC8)) {
        if (g_Task->vx > 0) {
            g_AreaTargetCellX = (s16)(g_AreaTargetCellX + 5);
        } else if (g_Task->vx < 0) {
            g_AreaTargetCellX = (s16)(g_AreaTargetCellX - 5);
        } else if (g_Task->vy > 0) {
            g_AreaTargetCellY = (s16)(g_AreaTargetCellY + 5);
        } else if (g_Task->vy < 0) {
            g_AreaTargetCellY = (s16)(g_AreaTargetCellY - 5);
        }
        temp                   = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
        g_AreaCameraHeightStep = 0;
        if (temp < (s16)g_AreaCameraHeight) {
            g_AreaCameraHeightStep = (s16)((temp - (s16)g_AreaCameraHeight) / 20);
        }
        g_AreaCameraStep = 0x40;
        g_Task->timer    = 20;
    }
    dist = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    if (dist < (s16)COORD_INT(g_Task->pos.z)) {
        g_Task->gravity = -8;
    } else {
        g_Task->vz               = 0;
        g_Task->gravity          = 0;
        COORD_INT(g_Task->pos.z) = (u16)dist;
    }
    if ((func_8019C028() & 0xFF) == 0) {
        if ((Area_GetVx(g_Task->pos.x.fixed, g_Task->pos.y.fixed) & 0xFF) != 0) {
            g_Task->unk_06       = 1;
            g_Task->option_flags = 2;
        } else if ((func_8019C1E4() & 0xFF) != 0) {
            g_Task->unk_06       = 1;
            g_Task->option_flags = 1;
        }
        if (g_Task->unk_06 != 0) {
            switch (g_Task->option_flags) {
                case 0:
                    if ((COORD_FRAC(g_Task->pos.x) == 0) && (COORD_FRAC(g_Task->pos.y) == 0)) {
                        g_Task->option_flags = 0;
                        g_Task->unk_0A       = 0;
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
        Actor_StepAnimLoop();
        Area_SetDrawMode();
    }
}
#else
INCLUDE_ASM(func_8019B704);
#endif
