#include "area051_13.h"

MATCH s32 func_801F2C04(void) {
    u8 code;

    code = Game_GetPartySize(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, SELF(Actor)->voice_flags.raw);
    if (code != 0xFF && !(g_Game.walk_flags & AREA_WALK_TRANSITION) && g_GameStateIndex == GAME_REQUEST_IDLE) {
        func_8015C214(code, 1);
    }
}
