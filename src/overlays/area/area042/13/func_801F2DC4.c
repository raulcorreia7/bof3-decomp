#include "area042_13.h"

MATCH void func_801F2DC4(void) {
    u8 code;
    u8 i;

    for (i = 0; i < 8; i++) {
        g_Task->pos.x.fixed = TO_COORD(D_801F52E0[i]);
        g_Task->pos.y.fixed = TO_COORD(16);
        code                = Game_GetPartySize(g_Task->pos.x.fixed, TO_COORD(16), 0);
        if (code != 0xFF && (g_Game.walk_flags & (AREA_WALK_TRANSITION | AREA_WALK_LEADER_SWITCH_ACTIVE)) == 0 && g_GameStateIndex == GAME_REQUEST_IDLE) {
            func_8015C214(code, 2);
        }
    }
}
