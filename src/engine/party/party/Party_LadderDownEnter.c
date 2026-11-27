#include "engine/game/00/game_00.h"

/* func_801B7EF0 */
/* Places the actor above the ground at the ladder top, ready to climb down. */
MATCH void Party_LadderDownEnter(void) {
    s32 value;

    COORD_INT(SELF(Actor)->pos.z) = Area_HeightRead(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) + 0x200;
    value                         = 0x3D;
    if (SELF(Actor)->direction == FACING_RIGHT) {
        value = 0x3C;
    }
    Script_Request(value);
    if (SELF(Actor)->unk_05 != 0) {
        Actor_SetSemiTransparent();
        SELF(Actor)->tint.steps.delta.r = -0x80;
        SELF(Actor)->tint.steps.delta.g = -0x80;
        SELF(Actor)->tint.steps.delta.b = -0x80;
        SELF(Actor)->tint.bytes.flags   = 1;
        SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
        SELF(Actor)->unk_04 = 7;
    } else {
        SELF(Actor)->unk_04 = 8;
    }
}
