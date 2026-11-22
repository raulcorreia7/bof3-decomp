#include "game_00.h"

MATCH void func_801B72B0(void) {
    Actor_SetSemiTransparent();
    TASK(Actor)->tint.steps.delta.r             = -0x80;
    TASK(Actor)->tint.steps.delta.g             = -0x80;
    TASK(Actor)->tint.steps.delta.b             = -0x80;
    TASK(Actor)->tint.bytes.flags               = 1;
    g_Game.current->u.field.mode.unsigned_value = 7;
    TASK(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    TASK(Actor)->unk_03 = 1;
}
