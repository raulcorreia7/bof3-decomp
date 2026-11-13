#include "engine/slus/slus.h"

/* lifted draft, best score 39.27%; semantics unverified
 */
#ifdef NON_MATCHING
NON_MATCHING void func_80167428(void) {
    s32   tmp0;
    s32   tmp1;
    s32   tmp2;
    s32   tmp3;
    s32   tmp4;
    s32   tmp5;
    s32   tmp6;
    s32   tmp7;
    s32   val0;
    s32   val1;
    s32   val2;
    s32   val3;
    s8    val4;
    s8    val5;
    void* tmp8;
    void* tmp9;
    void* tmp10;
    void* tmp11;
    void* tmp12;

    if (g_InputPressed & PADstart) {
        g_AreaCameraStep = 0x20;
        tmp3             = FIELD(s32, g_Game.current, 0x34u);
        tmp7             = g_AreaScrollTargetX - tmp3;
        val3             = tmp7;
        if (tmp7 < 0) {
            val3 = -val3;
        }
        tmp6 = g_AreaScrollTargetY - FIELD(s32, g_Game.current, 0x38u);
        val1 = tmp6;
        if (tmp6 < 0) {
            val1 = -val1;
        }
        g_AreaScrollTargetX = tmp3;
        g_AreaScrollTargetY = FIELD(s32, g_Game.current, 0x38u);
        val3                = MAX(val3, val1);
        tmp1                = ((u32)val3 >> 0xD) & BYTE_MASK;
        if (tmp1 != 0) {
            g_AreaCameraHeightStep = (u16)((s16)(FIELD(u16, g_Game.current, 0x3Eu) - g_AreaCameraHeight) / tmp1);
        } else {
            g_AreaCameraHeightStep = 0;
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
        FIELD(u8, tmp9, 0x9u)             = 0U;
        FIELD(s32, tmp9, 0xCu)            = 0;
        FIELD(s32, tmp9, 0x10u)           = 0;
        FIELD(s32, tmp9, 0x14u)           = 0;
        g_AreaCameraStep                  = 0;
        g_AreaCameraHeightStep            = 0;
        FIELD(s8, (g_Task), 0x1u)         = 1;
        return;
    }
    if (!(func_801B0E44() & BYTE_MASK)) {
        tmp8 = g_Task;
        tmp0 = FIELD(u8, tmp8, 0x8u) * 8;
        tmp2 = ((s32*)g_FacingSteps)[tmp0];
        tmp4 = D_80145EC4 - (FIELD(s32, tmp8, 0x34u) + tmp2);
        val2 = tmp4;
        if (tmp4 < 0) {
            val2 = -val2;
        }
        tmp5 = D_80145EC8 - (FIELD(s32, tmp8, 0x38u) + *(g_FacingStepY + tmp0));
        val0 = tmp5;
        if (tmp5 < 0) {
            val0 = -val0;
        }
        if ((val2 > TO_COORD(6)) || (val0 > TO_COORD(6)) || (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE)) {
            tmp10                    = g_Task;
            FIELD(u8, tmp10, 0x9u)   = 0U;
            FIELD(s32, tmp10, 0xCu)  = 0;
            FIELD(s32, tmp10, 0x10u) = 0;
            FIELD(s32, tmp10, 0x14u) = 0;
            g_AreaCameraStep         = 0;
            g_AreaCameraHeightStep   = 0;
            val4                     = 1;
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
            func_801C24D0();
            func_801C4C48();
            tmp11                  = g_Task;
            FIELD(u8, tmp11, 0x9u) = (u8)(FIELD(u8, tmp11, 0x9u) - 1);
            Actor_UpdateMovement();
            val4 = 2;
        }
    } else {
        FIELD(s8, g_Game.current, 0x11Cu) = 3;
        FIELD(u8, (g_Task), 0x9u)         = 0U;
        val4                              = 1;
    }
    FIELD(s8, (g_Task), 0x1u) = val4;
    g_GameStateIndex          = GAME_REQUEST_SCENE_CAMERA;
    g_Game.walk_flags &= 0x1F;
}
#else
INCLUDE_ASM(func_80167428);
#endif
