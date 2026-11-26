#include "engine/game/00/game_00.h"

/* func_801B72B0 */
/* Shows the actor at the faded-out tint and begins fading it in. */
MATCH void Party_FadeInStart(void) {
    Actor_SetSemiTransparent();
    SELF(Actor)->tint.steps.delta.r             = -0x80;
    SELF(Actor)->tint.steps.delta.g             = -0x80;
    SELF(Actor)->tint.steps.delta.b             = -0x80;
    SELF(Actor)->tint.bytes.flags               = 1;
    g_Game.current->u.field.mode.unsigned_value = 7;
    SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    SELF(Actor)->unk_03 = 1;
}
