#include "engine/game/00/game_00.h"

/* func_801B7EF0 */
/* Places the actor above the ground at the ladder top, ready to climb down. */
MATCH void Party_LadderDownEnter(void) {
    s32 value;

    COORD_INT(TASK(Actor)->pos.z) = Area_HeightRead(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) + 0x200;
    value                         = 0x3D;
    if (TASK(Actor)->direction == FACING_RIGHT) {
        value = 0x3C;
    }
    Script_Request(value);
    if (TASK(Actor)->unk_05 != 0) {
        Actor_SetSemiTransparent();
        TASK(Actor)->tint.steps.delta.r = -0x80;
        TASK(Actor)->tint.steps.delta.g = -0x80;
        TASK(Actor)->tint.steps.delta.b = -0x80;
        TASK(Actor)->tint.bytes.flags   = 1;
        TASK(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
        TASK(Actor)->unk_04 = 7;
    } else {
        TASK(Actor)->unk_04 = 8;
    }
}
