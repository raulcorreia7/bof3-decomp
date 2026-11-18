#include "area030_04.h"

/* Starts the lure cast and positions the camera over its travel height. */
/* func_801D210C */
#ifdef NON_MATCHING
NON_MATCHING void Fishing_LureCast(void) {
    FishingState* work;
    s32           value;
    s32           index;

    work                = FISHING_STATE;
    work->motion.unk_34 = D_80145EC4;
    FAKE_BARRIER();
    work->y_38.pos_y               = D_80145EC8 - COORD_HALF;
    FISHING_STATE->bounce.half.key = (s16)(Area_SampleHeight(work->motion.unk_34, work->y_38.pos_y) + 0x100);

    value                    = g_FishingRodRow->max_distance * D_801440BC / 255 + 8;
    FISHING_STATE->cursor_10 = value;
    FISHING_STATE->cue_index = (u8)(value / 15);
    if (FISHING_STATE->cue_index >= 4) {
        FISHING_STATE->cue_index = 3;
    }
    value = FISHING_STATE->y_38.pos_y;
    value -= FISHING_STATE->cursor_10 << 15;
    FISHING_STATE->cursor_10 = value;
    if (value >= FISHING_CAMERA_Y_MAX) {
        g_AreaScrollTargetY = FISHING_CAMERA_Y_MAX;
    } else if (value >= FISHING_CAMERA_Y_MIN) {
        g_AreaScrollTargetY = value;
    } else {
        g_AreaScrollTargetY = FISHING_CAMERA_Y_MIN;
    }

    g_AreaCameraStep            = 0;
    TASK_BYTES[0xC]             = 0;
    FISHING_STATE->step_14      = *(u32*)(D_801E1D38 + FISHING_STATE->cue_index * 8);
    FISHING_STATE->step_limit   = *(u32*)(D_801E1D3C + FISHING_STATE->cue_index * 8);
    FISHING_STATE->active_flags = 0;
    FISHING_STATE->state_29     = 5;
    FISHING_STATE->counter_48   = 1;
    FISHING_STATE->flags        = (u8)(FISHING_STATE->flags & ~ACTOR_FLAG_SEMI_TRANSPARENT);
    FISHING_STATE->saved_index  = 0;
    FISHING_STATE->tint_5D      = 0;
    FISHING_STATE->tint_5E      = 0;
    FISHING_STATE->tint_5F      = 0;
    FISHING_STATE->state_2A     = 0;
    FISHING_STATE->unk_60       = 0;
    FISHING_STATE->unk_64       = 0;
    FISHING_STATE->unk_68       = 0;
    FISHING_STATE->unk_6C       = 0;
    FISHING_STATE->counter_48   = 1;

    Area_SelectSceneRecord(g_FishingLureRow->unk_0C);
    Actor_SelectScript(1);
    index = Actor_FindFreeSpawned() & BYTE_MASK;
    if (index != GAME_NONE) {
        g_SpawnedActors[index].header.flags = 1;
        g_SpawnedActors[index].type         = 10;
    }
    FISHING_STATE->counter_07    = g_FishingLureRow->unk_0F;
    FISHING_STATE->handler_index = (u8)(FISHING_STATE->handler_index + 1);
}
#else
INCLUDE_ASM(Fishing_LureCast);
#endif
