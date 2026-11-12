#include "area118_13.h"

MATCH void func_801F33A4(void) {
    if (D_80143F03 == 0) {
        if (g_AreaSceneMode == g_Task->unk_0A) {
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
            }
            g_Task->header.step = 2;
        }
    }
    if (g_Task->direction_08 != FACING_UP_LEFT) {
        if (abs(g_Game.members[0].pos.y.fixed - (TO_COORD(COORD_INT(g_Task->pos.y) + 1) | COORD_HALF)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(g_Task->pos.x))) <= TO_COORD(1) || abs(g_Game.members[0].pos.x.fixed - TO_COORD(COORD_INT(g_Task->pos.x) + 1)) <= TO_COORD(1)) {
                if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
                }
                g_Task->header.step = 2;
            }
        }
    } else {
        if (abs(g_Game.members[0].pos.x.fixed - (TO_COORD(COORD_INT(g_Task->pos.x) + 1) | COORD_HALF)) <= COORD_HALF) {
            if (abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(g_Task->pos.y))) <= TO_COORD(1) || abs(g_Game.members[0].pos.y.fixed - TO_COORD(COORD_INT(g_Task->pos.y) + 1)) <= TO_COORD(1)) {
                if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
                }
                g_Task->header.step = 2;
            }
        }
    }
    func_801F381C(1);
}
