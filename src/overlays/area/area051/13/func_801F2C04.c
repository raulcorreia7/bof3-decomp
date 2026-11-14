#include "area051_13.h"

MATCH s32 func_801F2C04(void) {
    u8 code;

    code = Game_GetPartySize(g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->state_70.word);
    if (code != 0xFF && !(g_Game.walk_flags & AREA_WALK_TRANSITION) && g_GameStateIndex == GAME_REQUEST_IDLE) {
        func_8015C214(code, 1);
    }
}
