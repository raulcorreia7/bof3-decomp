#include "engine/game/00/game_00.h"

/* func_801C4FE0 */
/* Lowers the actor's z by the character's step toward its hold height on the ladder, then requests the grab animation; returns nonzero when it is reached. */
MATCH s32 Area_ClimbMountLower(void) {
    Actor* work;
    s32    rise;
    s32    ahead_x;
    s32    ahead_y;
    s32    target_x;
    s32    target_y;
    s16    ground;
    s32    z;
    u8     slot;
    s32    landed;

    work     = TASK(Actor);
    rise     = work->voice_flags.scene_flag + 2;
    ahead_x  = work->pos.x.fixed + g_FacingSteps[work->direction].x * rise;
    target_x       = ahead_x;
    ahead_y  = work->pos.y.fixed + g_FacingSteps[work->direction].y * rise;
    target_y       = ahead_y;
    z = COORD_INT(work->pos.z);
    landed   = 0;

    ground = Area_HeightRead(target_x, target_y);
    slot   = g_Game.current->chr.character_id;
    if (ground - g_AreaClimbHeightOffsets[slot] < z) {
        COORD_INT(TASK(Actor)->pos.z) -= g_AreaClimbRiseSteps[slot];
    } else {
        COORD_INT(TASK(Actor)->pos.z) = Area_HeightRead(target_x, target_y) - g_AreaClimbHeightOffsets[g_Game.current->chr.character_id];
        if (TASK(Actor)->direction == FACING_LEFT) {
            Script_Request(0x3C);
        } else {
            Script_Request(0x3D);
        }
        landed = 1;
    }

    if (TASK(Actor)->unk_05 == 0 && !((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE))) {
        Area_ScrollAdvance((s16)COORD_INT(TASK(Actor)->pos.z));
    }
    if (!(g_FrameCount & 0x3)) {
        Script_AnimStepOnce();
    }
    return landed;
}
