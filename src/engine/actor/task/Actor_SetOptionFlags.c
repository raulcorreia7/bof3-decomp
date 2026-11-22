#include "engine/game/00/game_00.h"

/* func_801A4990 */
MATCH void Actor_SetOptionFlags(u8* script) {
    u8 mode;

    TASK(Actor)->option_flags = script[0];
    if (script[0] & ACTOR_OPT_HIDDEN_ON_SPAWN) {
        TASK(Actor)->header.flags |= ACTOR_FLAG_HIDDEN;
    }
    if (script[0] & 0x4) {
        g_CurrentActor->interaction_flags &= ~ACTOR_INTERACTION_SCRIPT_PENDING;
    }
    if (script[0] & 0x40) {
        TASK(Actor)->unk_48 = 0;
    } else {
        TASK(Actor)->unk_48 = 1;
    }
    mode = g_CurrentActor->unk_78;
    if (mode != 0) {
        TASK(Actor)->unk_0A = (0x10 / g_RouteSpeedScale[mode]);
    }
}
