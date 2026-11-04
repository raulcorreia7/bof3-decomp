#include "game_00.h"

MATCH void func_801A4990(u8* script) {
    u8 mode;

    g_SpadWork->option_flags = script[0];
    if (script[0] & ACTOR_OPT_HIDDEN_ON_SPAWN) {
        g_SpadWork->flags_00 |= ACTOR_FLAG_HIDDEN;
    }
    if (script[0] & 4) {
        g_CurrentActor->flags_74 &= ~ACTOR_FLAG_SCRIPT_PENDING;
    }
    if (script[0] & 0x40) {
        g_SpadWork->unk_48 = 0;
    } else {
        g_SpadWork->unk_48 = 1;
    }
    mode = g_CurrentActor->unk_78;
    if (mode != 0) {
        g_SpadWork->unk_0A = (u8)(0x10 / (s32)g_RouteSpeedScale[mode]);
    }
}
