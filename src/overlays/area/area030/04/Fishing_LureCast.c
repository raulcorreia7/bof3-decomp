#include "area030_04.h"

/* Seeds the AREA030 battle-intro scratch record: it captures the
 * world anchor pair, samples the ground height at it, with Area_SampleHeight, scales the
 * entry's height byte into the record's clip value, clamps the height plus 0x100,
 * and primes the table pointers and draw state for the next frame. */
/* func_801D210C */
#ifdef NON_MATCHING
NON_MATCHING void Fishing_LureCast(void) {
    s32 value;
    u32 index;

    FISHING_STATE->motion_34.unk_34      = D_80145EC4;
    FISHING_STATE->y_38.pos_y            = D_80145EC8 - COORD_HALF;
    FISHING_STATE->bounce_3C.half.key_3E = (s16)(Area_SampleHeight(FISHING_STATE->motion_34.unk_34, D_80145EC8 - COORD_HALF) + 0x100);

    value                       = g_FishingRodRow->max_distance_02 * D_801440BC / 255 + 8;
    FISHING_STATE->cue_index_06 = (u8)(value / 15);
    if (FISHING_STATE->cue_index_06 >= 4) {
        FISHING_STATE->cue_index_06 = 3;
    }
    FISHING_STATE->cursor_10 = value;

    value                    = FISHING_STATE->y_38.pos_y - (FISHING_STATE->cursor_10 << 15);
    FISHING_STATE->cursor_10 = value;
    if (value >= FISHING_CAMERA_Y_MAX) {
        g_AreaScrollTargetY = FISHING_CAMERA_Y_MAX;
    } else if (value >= FISHING_CAMERA_Y_MIN) {
        g_AreaScrollTargetY = value;
    } else {
        g_AreaScrollTargetY = FISHING_CAMERA_Y_MIN;
    }

    g_AreaCameraStep              = 0;
    TASK_BYTES[0xC]               = 0;
    FISHING_STATE->step_14        = *(u32*)(D_801E1D38 + FISHING_STATE->cue_index_06 * 8);
    FISHING_STATE->active_flags   = 0;
    FISHING_STATE->step_limit_20  = *(u32*)(D_801E1D3C + FISHING_STATE->cue_index_06 * 8);
    FISHING_STATE->state_29       = 5;
    FISHING_STATE->counter_48     = 1;
    FISHING_STATE->flags          = (u8)(FISHING_STATE->flags & ~ACTOR_FLAG_SEMI_TRANSPARENT);
    FISHING_STATE->saved_index_0B = 0;
    FISHING_STATE->tint_5D        = 0;
    FISHING_STATE->tint_5E        = 0;
    FISHING_STATE->tint_5F        = 0;
    FISHING_STATE->state_2A       = 0;
    FISHING_STATE->unk_60         = 0;
    FISHING_STATE->unk_64         = 0;
    FISHING_STATE->unk_68         = 0;
    FISHING_STATE->unk_6C         = 0;
    FISHING_STATE->counter_48     = 1;

    Area_SelectSceneRecord(g_FishingLureRow->unk_0C);
    Actor_SelectScript(1);
    index = (u32)Actor_FindFreeSlot() & BYTE_MASK;
    if (index != GAME_NONE) {
        g_SpawnedActors[index].header.flags = 1;
        g_SpawnedActors[index].type         = 10;
    }
    FISHING_STATE->counter_07       = g_FishingLureRow->unk_0F;
    FISHING_STATE->handler_index_01 = (u8)(FISHING_STATE->handler_index_01 + 1);
}
#else
INCLUDE_ASM(Fishing_LureCast);
#endif
