#include "area030_04.h"

/* Runs the area-030 actor's aim: picks the facing from the target
 * record, moves the actor's aim box and keeps the follow distance in range. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DA9DC(void) {
    s32           distance;
    s32           follow;
    s32           chance;
    u32           capped;
    u32*          follow_ptr;
    u32*          target;
    SpawnedActor* actor;

    if ((TASK(FishingState)->cue_index != 0) && (g_SpawnedActors[4].header.mode == 3)) {
        TASK(FishingState)->cue_index = 0;
        func_801DDE94(1);
    }
    if ((g_PadStates[0].pressed & PADRup) && (g_SpawnedActors[4].header.mode == 0)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
        TASK(FishingState)->sub_index  = (u8)(TASK(FishingState)->sub_index + 1);
        g_SpawnedActors[2].header.mode = 0;
        g_SpawnedActors[0].header.mode = 0;
        g_SpawnedActors[3].header.mode = 7;
        return;
    }
    actor = g_SpawnedActors;
    if (g_SpawnedActors[0].pos.y.fixed >= FISHING_CATCH_HEIGHT) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
        g_SpawnedActors[2].header.mode = 0;
        g_SpawnedActors[0].header.mode = 0;
        TASK(FishingState)->mode_index = 1;
        TASK(FishingState)->sub_index  = 0U;
        return;
    }
    if (Area_HeightSample(g_SpawnedActors[0].pos.x.fixed, g_SpawnedActors[0].pos.y.fixed) >= COORD_INT(g_SpawnedActors[0].pos.z)) {
        chance = g_FishingLureRow->unk_11;
        if ((RANDOM_MASK(0xF) < chance) && !(g_FrameCount & 0xF)) {
            g_SpawnedActors[0].vx        = 0;
            g_SpawnedActors[0].selection = 0;
            g_SpawnedActors[0].unk_14    = 0;
            follow_ptr                   = &g_AreaScrollTargetY;
            if ((s32)*follow_ptr < g_SpawnedActors[0].pos.y.fixed) {
                *follow_ptr = (u32)g_SpawnedActors[0].pos.y.fixed;
            }
            g_AreaCameraSpeed              = 0x10;
            TASK(FishingState)->mode_index = 5;
            TASK(FishingState)->sub_index  = 0U;
            return;
        }
        COORD_INT(actor->pos.z) = Area_HeightSample(actor->pos.x.fixed, actor->pos.y.fixed);
        goto box_16; /* joins the common update calls */
    }
box_16:
    func_801DDEEC();
    func_801DE018();
    D_801E31FC = D_801E31F8;
    if (actor->link == 0) {
        if (g_PadStates[0].held & PADLleft) {
            actor->vx        = -ONE;
            actor->selection = ONE;
            actor->unk_14    = g_FishingLureRow->unk_08;
            D_801E31F8       = 1;
            Script_Request(6);
        } else if (g_PadStates[0].held & PADLright) {
            actor->vx        = ONE;
            actor->selection = ONE;
            D_801E31F8       = 1;
            actor->unk_14    = g_FishingLureRow->unk_08;
            Script_Request(5);
        } else if (g_PadStates[0].held & PADRdown) {
            actor->vx = 0;
            if (SP_REF(u8, 0x0) != 0) {
                actor->selection = 0x2000;
                D_801E31F8       = 2;
                actor->unk_14    = g_FishingLureRow->unk_08;
                Script_Request(4);
            } else {
                actor->selection = ONE;
                D_801E31F8       = 1;
                actor->unk_14    = g_FishingLureRow->unk_04;
                Script_Request(3);
            }
        } else if (SP_REF(u8, 0x0) != 0) {
            actor->vx        = 0;
            actor->selection = ONE;
            D_801E31F8       = 2;
            actor->unk_14    = g_FishingLureRow->unk_08;
            Script_Request(4);
        } else {
            actor->vx        = 0;
            actor->selection = 0;
            actor->unk_14    = g_FishingLureRow->unk_00;
            D_801E31F8       = 0;
            Script_Request(3);
        }
    }
    func_801DDD4C();
    g_AreaScrollTargetY = (u32)actor->pos.y.fixed;
    follow              = actor->selection >> 8;
    if (actor->selection == 0) {
        follow = 0x10;
    }
    g_AreaCameraSpeed = (u16)follow;
    target            = &g_AreaScrollTargetY;
    if ((s32)*target >= FISHING_CAMERA_Y_MIN) {
        capped = FISHING_CAMERA_Y_MAX;
        if ((s32)*target <= FISHING_CAMERA_Y_MAX) {
            capped = *target;
        }
    } else {
        capped = FISHING_CAMERA_Y_MIN;
    }
    *target = capped;
    if (((actor->pos.x.fixed <= TO_COORD(8)) && (actor->vx < 0)) || ((actor->pos.x.fixed > 0x11FFFF) && (actor->vx > 0))) {
        actor->vx = 0;
    }
    if (actor->selection > 0) {
        Script_AnimStepLoop();
    }
}
#else
INCLUDE_ASM(func_801DA9DC);
#endif
