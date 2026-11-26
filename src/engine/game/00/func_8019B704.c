#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_8019B704(void) {
    s32 saved;
    s32 acc;
    s32 delta;
    s32 gap;
    s16 dist;
    s16 temp;

    TASK(Actor)->unk_06       = 0;
    TASK(Actor)->option_flags = 0;
    if (TASK(Actor)->vx != 0) {
        saved           = TASK(Actor)->vx;
        acc             = saved + TASK(Actor)->unk_18;
        TASK(Actor)->vx = acc;
        acc             = ABS(acc);
        if (acc < ONE) {
            TASK(Actor)->vx     = saved;
            TASK(Actor)->unk_18 = 0;
        }
        TASK(Actor)->pos.x.fixed += TASK(Actor)->vx;
        delta = TASK(Actor)->pos.x.fixed - g_Game.members[0].pos.x.fixed;
    } else {
        saved           = TASK(Actor)->vy;
        acc             = saved + TASK(Actor)->unk_1C;
        TASK(Actor)->vy = acc;
        acc             = ABS(acc);
        if (acc < ONE) {
            TASK(Actor)->vy     = saved;
            TASK(Actor)->unk_1C = 0;
        }
        TASK(Actor)->pos.y.fixed += TASK(Actor)->vy;
        delta = TASK(Actor)->pos.y.fixed - g_Game.members[0].pos.y.fixed;
    }
    gap = delta;
    if (gap < 0) {
        gap = -gap;
    }
    if ((TASK(Actor)->unk_18 == 0) && (TASK(Actor)->unk_1C == 0)) {
        TASK(Actor)->unk_06       = 1;
        TASK(Actor)->option_flags = 0;
    }
    TASK(Actor)->vz += TASK(Actor)->gravity;
    COORD_INT(TASK(Actor)->pos.z) += TASK(Actor)->vz;
    if ((g_AreaCameraMoving == 0) && (gap > TO_COORD(4)) && (g_AreaScrollTargetX == g_Game.members[0].pos.x.fixed) && (g_AreaScrollTargetY == g_Game.members[0].pos.y.fixed)) {
        if (TASK(Actor)->vx > 0) {
            g_AreaTargetCellX = (s16)(g_AreaTargetCellX + 5);
        } else if (TASK(Actor)->vx < 0) {
            g_AreaTargetCellX = (s16)(g_AreaTargetCellX - 5);
        } else if (TASK(Actor)->vy > 0) {
            g_AreaTargetCellY = (s16)(g_AreaTargetCellY + 5);
        } else if (TASK(Actor)->vy < 0) {
            g_AreaTargetCellY = (s16)(g_AreaTargetCellY - 5);
        }
        temp                    = Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
        g_AreaCameraHeightDelta = 0;
        if (temp < (s16)g_AreaCameraHeight) {
            g_AreaCameraHeightDelta = (s16)((temp - (s16)g_AreaCameraHeight) / 20);
        }
        g_AreaCameraSpeed  = 0x40;
        TASK(Actor)->timer = 20;
    }
    dist = Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    if (dist < (s16)COORD_INT(TASK(Actor)->pos.z)) {
        TASK(Actor)->gravity = -8;
    } else {
        TASK(Actor)->vz               = 0;
        TASK(Actor)->gravity          = 0;
        COORD_INT(TASK(Actor)->pos.z) = (u16)dist;
    }
    if ((Actor_RockHit() & 0xFF) == 0) {
        if ((Actor_RockIsPointBlocked(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) & 0xFF) != 0) {
            TASK(Actor)->unk_06       = 1;
            TASK(Actor)->option_flags = 2;
        } else if ((Actor_RockIsBlockedAhead() & 0xFF) != 0) {
            TASK(Actor)->unk_06       = 1;
            TASK(Actor)->option_flags = 1;
        }
        if (TASK(Actor)->unk_06 != 0) {
            switch (TASK(Actor)->option_flags) {
                case 0:
                    if ((COORD_FRAC(TASK(Actor)->pos.x) == 0) && (COORD_FRAC(TASK(Actor)->pos.y) == 0)) {
                        TASK(Actor)->option_flags = 0;
                        TASK(Actor)->unk_0A       = 0;
                        Script_Select(0);
                        TASK(Actor)->header.mode = ACTOR_ROCK_MODE_REST;
                    } else {
                        Actor_RockSetTarget(0);
                    }
                    break;
                case 1:
                    Actor_RockSetTarget(0);
                    break;
                case 2:
                    Actor_RockSetTarget(1);
                    break;
            }
        }
        Script_AnimStepLoop();
        Area_SetDrawMode();
    }
}
#else
INCLUDE_ASM(func_8019B704);
#endif
