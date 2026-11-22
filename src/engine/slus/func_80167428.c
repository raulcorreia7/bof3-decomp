#include "engine/slus/slus.h"

/* Lifted draft; semantics are unverified. */
#ifdef NON_MATCHING
NON_MATCHING void func_80167428(void) {
    s32          tmp0;
    s32          tmp1;
    s32          tmp2;
    s32          tmp3;
    s32          tmp4;
    s32          tmp5;
    s32          tmp6;
    s32          tmp7;
    s32          val0;
    s32          val1;
    s32          val2;
    s32          val3;
    s8           val4;
    s8           val5;
    void*        tmp8;
    Actor*       tmp9;
    Actor*       tmp10;
    Actor*       tmp11;
    void*        tmp12;
    PartyMember* player;
    Actor*       actor;

    if (g_PadStates[0].pressed & PADstart) {
        g_AreaCameraSpeed   = 0x20;
        player              = g_Game.current;
        tmp3                = player->pos.x.fixed;
        tmp7                = g_AreaScrollTargetX - tmp3;
        val3                = ABS(tmp7);
        tmp6                = g_AreaScrollTargetY - player->pos.y.fixed;
        val1                = ABS(tmp6);
        g_AreaScrollTargetX = tmp3;
        g_AreaScrollTargetY = player->pos.y.fixed;
        val3                = MAX(val3, val1);
        tmp1                = ((u32)val3 >> 0xD) & BYTE_MASK;
        if (tmp1 != 0) {
            g_AreaCameraHeightDelta = (u16)((s16)(player->pos.z.part.integer - g_AreaCameraHeight) / tmp1);
        } else {
            g_AreaCameraHeightDelta = 0;
        }
        FIELD(s8, g_Game.current, 0x11Cu) = 3;
        tmp12                             = g_Task;
        *(u8*)(tmp12)                     = (u8)(*(u8*)(tmp12) | 0x40);
        FIELD(s8, (g_Task), 0x1u)         = 3;
        return;
    }
    if (g_InputMasks[FIELD_INPUT_VIEW] & D_8014625C) {
        FIELD(s8, g_Game.current, 0x11Cu) = 3;
        g_GameEntrySubstate += 1;
        FIELD(s8, (g_Task), 0x1u) = 1;
        FIELD(s8, (g_Task), 0x2u) = 0;
        return;
    }
    if (!(Game_GetInput() & BYTE_MASK)) {
        FIELD(s8, g_Game.current, 0x11Cu) = 3;
        tmp9                              = g_Task;
        tmp9->timer                       = 0U;
        tmp9->vx                          = 0;
        tmp9->vy                          = 0;
        tmp9->vz                          = 0;
        g_AreaCameraSpeed                 = 0;
        g_AreaCameraHeightDelta           = 0;
        FIELD(s8, (g_Task), 0x1u)         = 1;
        return;
    }
    if (!(func_801B0E44() & BYTE_MASK)) {
        actor = g_Task;
        tmp0  = actor->direction * 8;
        tmp2  = ((s32*)g_FacingSteps)[tmp0];
        tmp4  = D_80145EC4 - (actor->pos.x.fixed + tmp2);
        val2  = tmp4;
        if (tmp4 < 0) {
            val2 = -val2;
        }
        tmp5 = D_80145EC8 - (actor->pos.y.fixed + *(g_FacingStepY + tmp0));
        val0 = tmp5;
        if (tmp5 < 0) {
            val0 = -val0;
        }
        if ((val2 > TO_COORD(6)) || (val0 > TO_COORD(6)) || (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE)) {
            tmp10                   = g_Task;
            tmp10->timer            = 0U;
            tmp10->vx               = 0;
            tmp10->vy               = 0;
            tmp10->vz               = 0;
            g_AreaCameraSpeed       = 0;
            g_AreaCameraHeightDelta = 0;
            val4                    = 1;
        } else {
            if (g_InputMasks[FIELD_INPUT_RUN] & D_8014625C) {
                if ((g_AutoRun ^ 1) != 0) {
                    goto block_28; /* retail branch */
                }
                goto block_29; /* retail branch */
            }
            if (g_AutoRun != 0) {
            block_28:
                val5 = 4;
            } else {
            block_29:
                val5 = 3;
            }
            FIELD(s8, g_Game.current, 0x11Cu) = val5;
            Area_RunWalk();
            func_801C4C48();
            tmp11        = g_Task;
            tmp11->timer = (u8)(tmp11->timer - 1);
            Actor_MovementUpdate();
            val4 = 2;
        }
    } else {
        FIELD(s8, g_Game.current, 0x11Cu) = 3;
        TASK(Actor)->timer                = 0U;
        val4                              = 1;
    }
    FIELD(s8, (g_Task), 0x1u) = val4;
    g_GameStateIndex          = GAME_REQUEST_SCENE_CAMERA;
    g_Game.walk_flags &= 0x1F;
}
#else
INCLUDE_ASM(func_80167428);
#endif
