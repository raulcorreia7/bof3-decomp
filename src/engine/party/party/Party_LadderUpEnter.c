#include "engine/game/00/game_00.h"

/* func_801B79F8 */
/* Places the actor below the ground at the ladder foot, ready to climb up. */
MATCH void Party_LadderUpEnter(void) {
    COORD_INT(TASK(Actor)->pos.z) = Area_HeightRead(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) - 0x200;
    TASK(Actor)->pos.x.fixed -= g_FacingOffsets[TASK(Actor)->direction].x * ((TASK(Actor)->voice_flags.scene_flag + 1) << 5);
    TASK(Actor)->pos.y.fixed -= g_FacingOffsets[TASK(Actor)->direction].y * ((TASK(Actor)->voice_flags.scene_flag + 1) << 5);
    if (TASK(Actor)->direction == FACING_LEFT) {
        Script_Request(0x3C);
    } else {
        Script_Request(0x3D);
    }
    if (TASK(Actor)->unk_05 != 0) {
        Actor_SetSemiTransparent();
        TASK(Actor)->tint.steps.delta.r = -0x80;
        TASK(Actor)->tint.steps.delta.g = -0x80;
        TASK(Actor)->tint.steps.delta.b = -0x80;
        TASK(Actor)->tint.bytes.flags   = 1;
        TASK(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
        TASK(Actor)->unk_04 = 3;
    } else {
        TASK(Actor)->unk_04 = 4;
    }
}
