#include "game_00.h"

/* func_801A4990 */
MATCH void Actor_SetOptionFlags(u8* script) {
    u8 mode;

    g_Task->option_flags = script[0];
    if (script[0] & ACTOR_OPT_HIDDEN_ON_SPAWN) {
        g_Task->header.flags |= ACTOR_FLAG_HIDDEN;
    }
    if (script[0] & 0x4) {
        g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_SCRIPT_PENDING;
    }
    if (script[0] & 0x40) {
        g_Task->unk_48 = 0;
    } else {
        g_Task->unk_48 = 1;
    }
    mode = g_CurrentActor->unk_78;
    if (mode != 0) {
        g_Task->unk_0A = (0x10 / g_RouteSpeedScale[mode]);
    }
}
