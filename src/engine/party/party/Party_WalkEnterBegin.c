#include "engine/game/00/game_00.h"

/* func_801B8394 */
/* Places the actor a few steps back from its spot and starts the walk in. */
MATCH void Party_WalkEnterBegin(void) {
    if (SELF(Actor)->voice_flags.scene_flag != 0) {
        SELF(Actor)->pos.x.fixed -= g_FacingOffsets[SELF(Actor)->direction].x * 0x60;
        SELF(Actor)->pos.y.fixed -= g_FacingOffsets[SELF(Actor)->direction].y * 0x60;
        SELF(Actor)->unk_0A = 7;
    } else {
        SELF(Actor)->pos.x.fixed -= g_FacingOffsets[SELF(Actor)->direction].x * 0x40;
        SELF(Actor)->pos.y.fixed -= g_FacingOffsets[SELF(Actor)->direction].y * 0x40;
        SELF(Actor)->unk_0A = 5;
    }
    SELF(Actor)->timer                             = 0;
    COORD_INT(SELF(Actor)->pos.z)                  = Area_HeightRead(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    g_Game.current->u.field.counter.unsigned_value = 2;
    Script_Request(SELF(Actor)->direction + 8);
    if (SELF(Actor)->unk_05 != 0) {
        Actor_SetSemiTransparent();
        SELF(Actor)->tint.steps.delta.r = -0x80;
        SELF(Actor)->tint.steps.delta.g = -0x80;
        SELF(Actor)->tint.steps.delta.b = -0x80;
        SELF(Actor)->tint.bytes.flags   = 1;
        SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
        SELF(Actor)->unk_03 = 3;
    } else {
        SELF(Actor)->unk_03 = 4;
    }
}
