#include "area030_04.h"

/* Runs the area-030 actor's aim: picks the facing from the target
 * record, moves the actor's aim box and keeps the follow distance in range. */
/* nonmatching 79.64%: writing the sub_index_03 clear and return at both call sites instead of jumping to one shared
 * block removed one shared label (79.29 -> 79.64); the four arms' D_801E31F8 and g_ActorSlots[0].unk_14 tails still
 * cross-jump, so the candidate is 64 bytes short. Remaining branch@+0xb4: the arm tails need to differ enough that
 * GCC 2.7.2's jump2 cannot share them. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DA9DC(void) {
    u8   limit;
    s32  distance;
    s32  follow;
    s8   chance;
    u32  capped;
    u32* follow_ptr;

    if ((FISHING_STATE->cue_index_06 != 0) && (D_80144199 == 3)) {
        FISHING_STATE->cue_index_06 = 0;
        func_801DDE94(1);
    }
    if ((g_InputPressed & PADRup) && (D_80144199 == 0)) {
        SND_PlayCue(EMI_CUE_ID(2, 3));
        FISHING_STATE->sub_index_03 = (u8)(FISHING_STATE->sub_index_03 + 1);
        D_801440B1                  = 0;
        g_ActorSlots[0].mode        = 0;
        D_80144125                  = 7;
        return;
    }
    if (g_ActorSlots[0].y.fixed > 0x3E7FFF) {
        SND_PlayCue(EMI_CUE_ID(2, 3));
        D_801440B1                   = 0;
        g_ActorSlots[0].mode         = 0;
        FISHING_STATE->mode_index_02 = 1;
        FISHING_STATE->sub_index_03  = 0U;
        return;
    }
    if (Area_SampleHeight(g_ActorSlots[0].x.fixed, g_ActorSlots[0].y.fixed) >= g_ActorSlots[0].depth.part.integer) {
        chance = D_801E3210->unk_11;
        if (((RANDOM_MASK(0xF)) < chance) && !(g_FrameCount & 0xF)) {
            g_ActorSlots[0].step_0C      = 0;
            g_ActorSlots[0].selection_10 = 0;
            g_ActorSlots[0].unk_14       = 0;
            follow_ptr                   = &g_AreaScrollTargetY;
            if ((s32)*follow_ptr < g_ActorSlots[0].y.fixed) {
                *follow_ptr = (u32)g_ActorSlots[0].y.fixed;
            }
            g_AreaCameraStep             = 0x10;
            FISHING_STATE->mode_index_02 = 5;
            FISHING_STATE->sub_index_03  = 0U;
            return;
        }
        g_ActorSlots[0].depth.part.integer = Area_SampleHeight(g_ActorSlots[0].x.fixed, g_ActorSlots[0].y.fixed);
        goto box_16; /* joins the common update calls */
    }
box_16:
    func_801DDEEC();
    func_801DE018();
    D_801E31FC = D_801E31F8;
    if (g_ActorSlots[0].link_0B == 0) {
        limit = 6;
        if (g_InputHeld & PADLleft) {
            g_ActorSlots[0].step_0C      = -ONE;
            g_ActorSlots[0].selection_10 = ONE;
            g_ActorSlots[0].unk_14       = D_801E3210->unk_08;
            D_801E31F8                   = 1;
        } else {
            limit = 5;
            if (g_InputHeld & PADLright) {
                g_ActorSlots[0].step_0C      = ONE;
                g_ActorSlots[0].selection_10 = ONE;
                D_801E31F8                   = 1;
                g_ActorSlots[0].unk_14       = D_801E3210->unk_08;
            } else if (g_InputHeld & PADRdown) {
                g_ActorSlots[0].step_0C = 0;
                if (SP_REF(u8, 0x0) != 0) {
                    limit                        = 4;
                    g_ActorSlots[0].selection_10 = 0x2000;
                    D_801E31F8                   = 2;
                    g_ActorSlots[0].unk_14       = D_801E3210->unk_08;
                } else {
                    limit                        = 3;
                    g_ActorSlots[0].selection_10 = ONE;
                    D_801E31F8                   = 1;
                    g_ActorSlots[0].unk_14       = D_801E3210->unk_04;
                }
            } else {
                limit = 4;
                if (SP_REF(void*, 0x0) != 0) {
                    g_ActorSlots[0].step_0C      = 0;
                    g_ActorSlots[0].selection_10 = ONE;
                    D_801E31F8                   = 2;
                    g_ActorSlots[0].unk_14       = D_801E3210->unk_08;
                } else {
                    g_ActorSlots[0].step_0C      = 0;
                    g_ActorSlots[0].selection_10 = 0;
                    limit                        = 3;
                    g_ActorSlots[0].unk_14       = D_801E3210->flags;
                    D_801E31F8                   = 0;
                }
            }
        }
        Actor_RequestScript(limit);
    }
    func_801DDD4C();
    g_AreaScrollTargetY = (u32)g_ActorSlots[0].y.fixed;
    follow              = g_ActorSlots[0].selection_10 >> 8;
    if (g_ActorSlots[0].selection_10 == 0) {
        follow = 0x10;
    }
    g_AreaCameraStep = (u16)follow;
    if ((s32)g_AreaScrollTargetY > 0x14FFFF) {
        capped = 0x3C0000;
        if ((s32)g_AreaScrollTargetY <= 0x3C0000) {
            capped = g_AreaScrollTargetY;
        }
    } else {
        capped = 0x150000;
    }
    g_AreaScrollTargetY = capped;
    if (((g_ActorSlots[0].x.fixed <= 0x80000) && (g_ActorSlots[0].step_0C < 0)) ||
        ((g_ActorSlots[0].x.fixed > 0x11FFFF) && (g_ActorSlots[0].step_0C > 0))) {
        g_ActorSlots[0].step_0C = 0;
    }
    if (g_ActorSlots[0].selection_10 > 0) {
        func_8014D978();
    }
}
#else
INCLUDE_ASM(func_801DA9DC);
#endif
