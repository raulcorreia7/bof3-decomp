#include "area140_13.h"

MATCH void func_801F2D80(void) {
    if (abs(g_Game.members[0].pos.x.fixed - (TO_COORD(COORD_INT(SELF(Actor)->pos.x) + 1) | COORD_HALF)) <= COORD_HALF) {
        if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(SELF(Actor)->pos.y))) <= TO_COORD(1) ||
            abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(SELF(Actor)->pos.y) + 1)) <= TO_COORD(1)) {
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
            }
            SELF(Actor)->header.step++;
        }
    }
    func_801F3050();
}
