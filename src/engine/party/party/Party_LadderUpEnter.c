#include "engine/game/00/game_00.h"

/* func_801B79F8 */
/* Places the actor below the ground at the ladder foot, ready to climb up. */
MATCH void Party_LadderUpEnter(void) {
    COORD_INT(SELF(Actor)->pos.z) = Area_HeightRead(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) - 0x200;
    SELF(Actor)->pos.x.fixed -= g_FacingOffsets[SELF(Actor)->direction].x * ((SELF(Actor)->voice_flags.scene_flag + 1) << 5);
    SELF(Actor)->pos.y.fixed -= g_FacingOffsets[SELF(Actor)->direction].y * ((SELF(Actor)->voice_flags.scene_flag + 1) << 5);
    if (SELF(Actor)->direction == FACING_LEFT) {
        Script_Request(0x3C);
    } else {
        Script_Request(0x3D);
    }
    if (SELF(Actor)->unk_05 != 0) {
        Actor_SetSemiTransparent();
        SELF(Actor)->tint.steps.delta.r = -0x80;
        SELF(Actor)->tint.steps.delta.g = -0x80;
        SELF(Actor)->tint.steps.delta.b = -0x80;
        SELF(Actor)->tint.bytes.flags   = 1;
        SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
        SELF(Actor)->unk_04 = 3;
    } else {
        SELF(Actor)->unk_04 = 4;
    }
}
