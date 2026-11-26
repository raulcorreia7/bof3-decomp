#include "area030_04.h"

/* Starts the lure cast and positions the camera over its travel height. */
/* func_801D210C */
MATCH void Fishing_LureCast(void) {
    FishingState* work;
    s32           distance;
    s32           value;
    s32           index;

    work                                = TASK(FishingState);
    work->motion.unk_34                 = g_Game.members[0].pos.x.fixed;
    work->y_38.pos_y                    = g_Game.members[0].pos.y.fixed - COORD_HALF;
    TASK(FishingState)->bounce.half.key = Area_HeightSample(work->motion.unk_34, work->y_38.pos_y) + 0x100;

    distance                      = g_FishingRodRow->max_distance * g_SpawnedActors[2].vx / 255 + 8;
    TASK(FishingState)->cursor_10 = distance;
    TASK(FishingState)->cue_index = distance / 15;
    if (TASK(FishingState)->cue_index >= 4) {
        TASK(FishingState)->cue_index = 3;
    }
    value                         = TASK(FishingState)->y_38.pos_y - (TASK(FishingState)->cursor_10 << 15);
    TASK(FishingState)->cursor_10 = value;
    if (value >= FISHING_CAMERA_Y_MAX) {
        g_AreaScrollTargetY = FISHING_CAMERA_Y_MAX;
    } else if (value < FISHING_CAMERA_Y_MIN) {
        g_AreaScrollTargetY = FISHING_CAMERA_Y_MIN;
    } else {
        g_AreaScrollTargetY = value;
    }

    g_AreaCameraSpeed                = 0;
    TASK(FishingState)->pos_x        = 0;
    TASK(FishingState)->bounce_speed = g_FishingLureCastSteps[TASK(FishingState)->cue_index].step;
    TASK(FishingState)->bounce_accel = g_FishingLureCastSteps[TASK(FishingState)->cue_index].limit;
    TASK(FishingState)->active_flags = 0;
    TASK(FishingState)->state_29     = 5;
    TASK(FishingState)->counter_48   = 1;
    TASK(FishingState)->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
    TASK(FishingState)->saved_index = 0;
    TASK(FishingState)->tint_5D     = 0;
    TASK(FishingState)->tint_5E     = 0;
    TASK(FishingState)->tint_5F     = 0;
    TASK(FishingState)->unk_60      = 0;
    TASK(FishingState)->unk_64      = 0;
    TASK(FishingState)->unk_68      = 0;
    TASK(FishingState)->unk_6C      = 0;
    TASK(FishingState)->state_2A    = 0;
    TASK(FishingState)->counter_48  = 1;

    Area_SceneSelectRecord(g_FishingLureRow->unk_0C);
    Script_Select(1);
    index = Actor_FindFreeSpawned() & BYTE_MASK;
    if (index != GAME_NONE) {
        g_SpawnedActors[index].header.flags = 1;
        g_SpawnedActors[index].type         = 10;
    }
    TASK(FishingState)->counter_07 = g_FishingLureRow->unk_0F;
    TASK(FishingState)->handler_index++;
}
