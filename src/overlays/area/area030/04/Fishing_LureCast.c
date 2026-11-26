#include "area030_04.h"

/* Starts the lure cast and positions the camera over its travel height. */
/* func_801D210C */
MATCH void Fishing_LureCast(void) {
    FishingState* work;
    s32           distance;
    s32           value;
    s32           index;

    work                                = SELF(FishingState);
    work->motion.unk_34                 = g_Game.members[0].pos.x.fixed;
    work->y_38.pos_y                    = g_Game.members[0].pos.y.fixed - COORD_HALF;
    SELF(FishingState)->bounce.half.key = Area_HeightSample(work->motion.unk_34, work->y_38.pos_y) + 0x100;

    distance                      = g_FishingRodRow->max_distance * g_SpawnedActors[2].vx / 255 + 8;
    SELF(FishingState)->cursor_10 = distance;
    SELF(FishingState)->cue_index = distance / 15;
    if (SELF(FishingState)->cue_index >= 4) {
        SELF(FishingState)->cue_index = 3;
    }
    value                         = SELF(FishingState)->y_38.pos_y - (SELF(FishingState)->cursor_10 << 15);
    SELF(FishingState)->cursor_10 = value;
    if (value >= FISHING_CAMERA_Y_MAX) {
        g_AreaScrollTargetCoordY.fixed = FISHING_CAMERA_Y_MAX;
    } else if (value < FISHING_CAMERA_Y_MIN) {
        g_AreaScrollTargetCoordY.fixed = FISHING_CAMERA_Y_MIN;
    } else {
        g_AreaScrollTargetCoordY.fixed = value;
    }

    g_AreaCameraSpeed                = 0;
    SELF(FishingState)->pos_x        = 0;
    SELF(FishingState)->bounce_speed = g_FishingLureCastSteps[SELF(FishingState)->cue_index].step;
    SELF(FishingState)->bounce_accel = g_FishingLureCastSteps[SELF(FishingState)->cue_index].limit;
    SELF(FishingState)->active_flags = 0;
    SELF(FishingState)->state_29     = 5;
    SELF(FishingState)->counter_48   = 1;
    SELF(FishingState)->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
    SELF(FishingState)->saved_index = 0;
    SELF(FishingState)->tint_5D     = 0;
    SELF(FishingState)->tint_5E     = 0;
    SELF(FishingState)->tint_5F     = 0;
    SELF(FishingState)->unk_60      = 0;
    SELF(FishingState)->unk_64      = 0;
    SELF(FishingState)->unk_68      = 0;
    SELF(FishingState)->unk_6C      = 0;
    SELF(FishingState)->state_2A    = 0;
    SELF(FishingState)->counter_48  = 1;

    Area_SceneSelectRecord(g_FishingLureRow->unk_0C);
    Script_Select(1);
    index = Actor_FindFreeSpawned() & BYTE_MASK;
    if (index != GAME_NONE) {
        g_SpawnedActors[index].header.flags = 1;
        g_SpawnedActors[index].type         = 10;
    }
    SELF(FishingState)->counter_07 = g_FishingLureRow->unk_0F;
    SELF(FishingState)->handler_index++;
}
