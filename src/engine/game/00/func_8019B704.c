#include "game_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_8019B704(void) {
    s32 saved;
    s32 acc;
    s32 gap;
    s16 dist;
    s16 temp;

    SELF(Actor)->unk_06       = 0;
    SELF(Actor)->option_flags = 0;
    if (SELF(Actor)->vx != 0) {
        saved           = SELF(Actor)->vx;
        acc             = saved + SELF(Actor)->unk_18;
        SELF(Actor)->vx = acc;
        acc             = ABS(acc);
        if (acc < ONE) {
            SELF(Actor)->vx     = saved;
            SELF(Actor)->unk_18 = 0;
        }
        SELF(Actor)->pos.x.fixed += SELF(Actor)->vx;
        gap = SELF(Actor)->pos.x.fixed - g_Game.members[0].pos.x.fixed;
    } else {
        saved           = SELF(Actor)->vy;
        acc             = saved + SELF(Actor)->unk_1C;
        SELF(Actor)->vy = acc;
        acc             = ABS(acc);
        if (acc < ONE) {
            SELF(Actor)->vy     = saved;
            SELF(Actor)->unk_1C = 0;
        }
        SELF(Actor)->pos.y.fixed += SELF(Actor)->vy;
        gap = SELF(Actor)->pos.y.fixed - g_Game.members[0].pos.y.fixed;
    }
    if (gap < 0) {
        gap = -gap;
    }
    if ((SELF(Actor)->unk_18 == 0) && (SELF(Actor)->unk_1C == 0)) {
        SELF(Actor)->unk_06       = 1;
        SELF(Actor)->option_flags = 0;
    }
    SELF(Actor)->vz += SELF(Actor)->gravity;
    COORD_INT(SELF(Actor)->pos.z) += SELF(Actor)->vz;
    if ((g_AreaCameraMoving == 0) && (gap > TO_COORD(4)) && (g_AreaScrollTargetX == g_Game.members[0].pos.x.fixed) && (g_AreaScrollTargetY == g_Game.members[0].pos.y.fixed)) {
        if (SELF(Actor)->vx > 0) {
            g_AreaTargetCellX = (s16)(g_AreaTargetCellX + 5);
        } else if (SELF(Actor)->vx < 0) {
            g_AreaTargetCellX = (s16)(g_AreaTargetCellX - 5);
        } else if (SELF(Actor)->vy > 0) {
            g_AreaTargetCellY = (s16)(g_AreaTargetCellY + 5);
        } else if (SELF(Actor)->vy < 0) {
            g_AreaTargetCellY = (s16)(g_AreaTargetCellY - 5);
        }
        temp                    = Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
        g_AreaCameraHeightDelta = 0;
        if (temp < (s16)g_AreaCameraHeight) {
            g_AreaCameraHeightDelta = (s16)((temp - (s16)g_AreaCameraHeight) / 20);
        }
        g_AreaCameraSpeed  = 0x40;
        SELF(Actor)->timer = 20;
    }
    dist = Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    if (dist < (s16)COORD_INT(SELF(Actor)->pos.z)) {
        SELF(Actor)->gravity = -8;
    } else {
        SELF(Actor)->vz               = 0;
        SELF(Actor)->gravity          = 0;
        COORD_INT(SELF(Actor)->pos.z) = (u16)dist;
    }
    if ((Actor_RockHit() & 0xFF) == 0) {
        if ((Actor_RockIsPointBlocked(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) & 0xFF) != 0) {
            SELF(Actor)->unk_06       = 1;
            SELF(Actor)->option_flags = 2;
        } else if ((Actor_RockIsBlockedAhead() & 0xFF) != 0) {
            SELF(Actor)->unk_06       = 1;
            SELF(Actor)->option_flags = 1;
        }
        if (SELF(Actor)->unk_06 != 0) {
            switch (SELF(Actor)->option_flags) {
                case 0:
                    if ((COORD_FRAC(SELF(Actor)->pos.x) == 0) && (COORD_FRAC(SELF(Actor)->pos.y) == 0)) {
                        SELF(Actor)->option_flags = 0;
                        SELF(Actor)->unk_0A       = 0;
                        Script_Select(0);
                        SELF(Actor)->header.mode = ACTOR_ROCK_MODE_REST;
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
