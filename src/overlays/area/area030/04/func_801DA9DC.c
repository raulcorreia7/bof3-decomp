#include "area030_04.h"

/* Runs the area-030 actor's aim: picks the facing from the target
 * record, moves the actor's aim box and keeps the follow distance in range. */
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
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
        FISHING_STATE->sub_index_03    = (u8)(FISHING_STATE->sub_index_03 + 1);
        D_801440B1                     = 0;
        g_SpawnedActors[0].header.mode = 0;
        D_80144125                     = 7;
        return;
    }
    if (g_SpawnedActors[0].pos.y.fixed >= FISHING_CATCH_HEIGHT) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
        D_801440B1                     = 0;
        g_SpawnedActors[0].header.mode = 0;
        FISHING_STATE->mode_index_02   = 1;
        FISHING_STATE->sub_index_03    = 0U;
        return;
    }
    if (Area_SampleHeight(g_SpawnedActors[0].pos.x.fixed, g_SpawnedActors[0].pos.y.fixed) >= COORD_INT(g_SpawnedActors[0].pos.z)) {
        chance = g_FishingLureRow->unk_11;
        if ((RANDOM_MASK(0xF) < chance) && !(g_FrameCount & 0xF)) {
            g_SpawnedActors[0].scene_step = 0;
            g_SpawnedActors[0].selection  = 0;
            g_SpawnedActors[0].unk_14     = 0;
            follow_ptr                    = &g_AreaScrollTargetY;
            if ((s32)*follow_ptr < g_SpawnedActors[0].pos.y.fixed) {
                *follow_ptr = (u32)g_SpawnedActors[0].pos.y.fixed;
            }
            g_AreaCameraStep             = 0x10;
            FISHING_STATE->mode_index_02 = 5;
            FISHING_STATE->sub_index_03  = 0U;
            return;
        }
        COORD_INT(g_SpawnedActors[0].pos.z) = Area_SampleHeight(g_SpawnedActors[0].pos.x.fixed, g_SpawnedActors[0].pos.y.fixed);
        goto box_16; /* joins the common update calls */
    }
box_16:
    func_801DDEEC();
    func_801DE018();
    D_801E31FC = D_801E31F8;
    if (g_SpawnedActors[0].link == 0) {
        limit = 6;
        if (g_InputHeld & PADLleft) {
            g_SpawnedActors[0].scene_step = -ONE;
            g_SpawnedActors[0].selection  = ONE;
            g_SpawnedActors[0].unk_14     = g_FishingLureRow->unk_08;
            D_801E31F8                    = 1;
        } else {
            limit = 5;
            if (g_InputHeld & PADLright) {
                g_SpawnedActors[0].scene_step = ONE;
                g_SpawnedActors[0].selection  = ONE;
                D_801E31F8                    = 1;
                g_SpawnedActors[0].unk_14     = g_FishingLureRow->unk_08;
            } else if (g_InputHeld & PADRdown) {
                g_SpawnedActors[0].scene_step = 0;
                if (SP_REF(u8, 0x0) != 0) {
                    limit                        = 4;
                    g_SpawnedActors[0].selection = 0x2000;
                    D_801E31F8                   = 2;
                    g_SpawnedActors[0].unk_14    = g_FishingLureRow->unk_08;
                } else {
                    limit                        = 3;
                    g_SpawnedActors[0].selection = ONE;
                    D_801E31F8                   = 1;
                    g_SpawnedActors[0].unk_14    = g_FishingLureRow->unk_04;
                }
            } else {
                limit = 4;
                if (SP_REF(void*, 0x0) != 0) {
                    g_SpawnedActors[0].scene_step = 0;
                    g_SpawnedActors[0].selection  = ONE;
                    D_801E31F8                    = 2;
                    g_SpawnedActors[0].unk_14     = g_FishingLureRow->unk_08;
                } else {
                    g_SpawnedActors[0].scene_step = 0;
                    g_SpawnedActors[0].selection  = 0;
                    limit                         = 3;
                    g_SpawnedActors[0].unk_14     = g_FishingLureRow->unk_00;
                    D_801E31F8                    = 0;
                }
            }
        }
        Actor_RequestScript(limit);
    }
    func_801DDD4C();
    g_AreaScrollTargetY = (u32)g_SpawnedActors[0].pos.y.fixed;
    follow              = g_SpawnedActors[0].selection >> 8;
    if (g_SpawnedActors[0].selection == 0) {
        follow = 0x10;
    }
    g_AreaCameraStep = (u16)follow;
    if ((s32)g_AreaScrollTargetY >= FISHING_CAMERA_Y_MIN) {
        capped = FISHING_CAMERA_Y_MAX;
        if ((s32)g_AreaScrollTargetY <= FISHING_CAMERA_Y_MAX) {
            capped = g_AreaScrollTargetY;
        }
    } else {
        capped = FISHING_CAMERA_Y_MIN;
    }
    g_AreaScrollTargetY = capped;
    if (((g_SpawnedActors[0].pos.x.fixed <= TO_COORD(8)) && (g_SpawnedActors[0].scene_step < 0)) || ((g_SpawnedActors[0].pos.x.fixed > 0x11FFFF) && (g_SpawnedActors[0].scene_step > 0))) {
        g_SpawnedActors[0].scene_step = 0;
    }
    if (g_SpawnedActors[0].selection > 0) {
        Actor_StepAnimLoop();
    }
}
#else
INCLUDE_ASM(func_801DA9DC);
#endif
