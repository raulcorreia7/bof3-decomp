#include "engine/game/00/game_00.h"

/* func_801B8394 */
/* Places the actor a few steps back from its spot and starts the walk in. */
MATCH void Party_WalkEnterBegin(void) {
    if (TASK(Actor)->voice_flags.scene_flag != 0) {
        TASK(Actor)->pos.x.fixed -= g_FacingOffsets[TASK(Actor)->direction].x * 0x60;
        TASK(Actor)->pos.y.fixed -= g_FacingOffsets[TASK(Actor)->direction].y * 0x60;
        TASK(Actor)->unk_0A = 7;
    } else {
        TASK(Actor)->pos.x.fixed -= g_FacingOffsets[TASK(Actor)->direction].x * 0x40;
        TASK(Actor)->pos.y.fixed -= g_FacingOffsets[TASK(Actor)->direction].y * 0x40;
        TASK(Actor)->unk_0A = 5;
    }
    TASK(Actor)->timer                             = 0;
    COORD_INT(TASK(Actor)->pos.z)                  = Area_HeightRead(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed);
    g_Game.current->u.field.counter.unsigned_value = 2;
    Script_Request(TASK(Actor)->direction + 8);
    if (TASK(Actor)->unk_05 != 0) {
        Actor_SetSemiTransparent();
        TASK(Actor)->tint.steps.delta.r = -0x80;
        TASK(Actor)->tint.steps.delta.g = -0x80;
        TASK(Actor)->tint.steps.delta.b = -0x80;
        TASK(Actor)->tint.bytes.flags   = 1;
        TASK(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
        TASK(Actor)->unk_03 = 3;
    } else {
        TASK(Actor)->unk_03 = 4;
    }
}
