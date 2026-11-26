#include "area118_13.h"

MATCH void func_801F33A4(void) {
    if (g_GameCellType == 0) {
        if (g_AreaSceneMode == SELF(Actor)->unk_0A) {
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x00));
            }
            SELF(Actor)->header.step = 2;
        }
    }
    if (SELF(Actor)->direction != FACING_UP_LEFT) {
        if (abs(g_Game.members[0].pos.y.fixed - (TO_COORD(COORD_INT(SELF(Actor)->pos.y) + 1) | COORD_HALF)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(SELF(Actor)->pos.x))) <= TO_COORD(1) ||
                abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(SELF(Actor)->pos.x) + 1)) <= TO_COORD(1)) {
                if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x00));
                }
                SELF(Actor)->header.step = 2;
            }
        }
    } else {
        if (abs(g_Game.members[0].pos.x.fixed - (TO_COORD(COORD_INT(SELF(Actor)->pos.x) + 1) | COORD_HALF)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(SELF(Actor)->pos.y))) <= TO_COORD(1) ||
                abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(SELF(Actor)->pos.y) + 1)) <= TO_COORD(1)) {
                if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x00));
                }
                SELF(Actor)->header.step = 2;
            }
        }
    }
    func_801F381C(1);
}
