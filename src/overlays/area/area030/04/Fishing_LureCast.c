#include "area030_04.h"

/* Starts the lure cast and positions the camera over its travel height. */
/* func_801D210C */
MATCH void Fishing_LureCast(void) {
    FishingState* work;
    s32           distance;
    s32           value;
    s32           index;

    work                = FISHING_STATE;
    work->motion.unk_34 = D_80145EC4;
    /* FAKE: keeps the x store ahead of the y load; without it the loads are scheduled first. */
    FAKE_BARRIER();
    work->y_38.pos_y               = D_80145EC8 - COORD_HALF;
    FISHING_STATE->bounce.half.key = Area_HeightSample(work->motion.unk_34, work->y_38.pos_y) + 0x100;

    distance                 = g_FishingRodRow->max_distance * D_801440BC / 255 + 8;
    FISHING_STATE->cursor_10 = distance;
    FISHING_STATE->cue_index = distance / 15;
    if (FISHING_STATE->cue_index >= 4) {
        FISHING_STATE->cue_index = 3;
    }
    value                    = FISHING_STATE->y_38.pos_y - (FISHING_STATE->cursor_10 << 15);
    FISHING_STATE->cursor_10 = value;
    if (value >= FISHING_CAMERA_Y_MAX) {
        g_AreaScrollTargetY = FISHING_CAMERA_Y_MAX;
    } else if (value < FISHING_CAMERA_Y_MIN) {
        g_AreaScrollTargetY = FISHING_CAMERA_Y_MIN;
    } else {
        g_AreaScrollTargetY = value;
    }

    g_AreaCameraStep            = 0;
    FISHING_STATE->pos_x        = 0;
    FISHING_STATE->step_14      = g_FishingLureCastSteps[FISHING_STATE->cue_index].step;
    FISHING_STATE->step_limit   = g_FishingLureCastSteps[FISHING_STATE->cue_index].limit;
    FISHING_STATE->active_flags = 0;
    FISHING_STATE->state_29     = 5;
    FISHING_STATE->counter_48   = 1;
    FISHING_STATE->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
    FISHING_STATE->saved_index = 0;
    FISHING_STATE->tint_5D     = 0;
    FISHING_STATE->tint_5E     = 0;
    FISHING_STATE->tint_5F     = 0;
    FISHING_STATE->unk_60      = 0;
    FISHING_STATE->unk_64      = 0;
    FISHING_STATE->unk_68      = 0;
    FISHING_STATE->unk_6C      = 0;
    FISHING_STATE->state_2A    = 0;
    FISHING_STATE->counter_48  = 1;

    Area_SceneSelectRecord(g_FishingLureRow->unk_0C);
    Script_Select(1);
    index = Actor_FindFreeSpawned() & BYTE_MASK;
    if (index != GAME_NONE) {
        g_SpawnedActors[index].header.flags = 1;
        g_SpawnedActors[index].type         = 10;
    }
    FISHING_STATE->counter_07 = g_FishingLureRow->unk_0F;
    FISHING_STATE->handler_index++;
}
