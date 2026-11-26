#include "engine/game/00/game_00.h"

/* func_801C520C */
/* Moves the actor's z up by the character's rise step; at the ground ahead it requests script 0x3E facing left, 0x3F otherwise, and returns nonzero. */
MATCH s32 Area_ClimbDismountRise(void) {
    Actor* actor;
    s32    step;
    s32    sum_x;
    s32    sum_y;
    s32    target_x;
    s32    target_y;
    s32    done;
    u8     animation;

    actor    = TASK(Actor);
    step     = actor->voice_flags.scene_flag + 2;
    done     = 0;
    sum_x    = actor->pos.x.fixed + (g_FacingSteps[actor->direction].x * step);
    target_x = sum_x;
    sum_y    = actor->pos.y.fixed + (g_FacingSteps[actor->direction].y * step);
    target_y = sum_y;
    if (COORD_INT(actor->pos.z) < Area_HeightRead(sum_x, sum_y)) {
        COORD_INT(TASK(Actor)->pos.z) = (s16)((u16)COORD_INT(TASK(Actor)->pos.z) + g_AreaClimbRiseSteps[g_Game.current->chr.character_id]);
    } else {
        COORD_INT(TASK(Actor)->pos.z) = Area_HeightRead(target_x, target_y);
        animation                     = 0x3F;
        if (TASK(Actor)->direction == FACING_LEFT) {
            animation = 0x3E;
        }
        done = 1;
        Script_Request(animation);
    }
    if ((TASK(Actor)->unk_05 == 0) && !((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE))) {
        Area_ScrollAdvance(COORD_INT(TASK(Actor)->pos.z));
    }
    if (!(g_FrameCount & 0x3)) {
        Script_AnimStepOnce();
    }
    return done;
}
