#include "area118_13.h"

MATCH void func_801F3EEC(void) {
    if (g_AreaSceneMode == TASK(Actor)->unk_0A) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x00));
        }
        (g_AreaCellCodes + COORD_INT(TASK(Actor)->pos.y) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(TASK(Actor)->pos.x)]       = 0xA1;
        (g_AreaCellCodes + (COORD_INT(TASK(Actor)->pos.y) + 1) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[COORD_INT(TASK(Actor)->pos.x)] = 0xA1;
        TASK(Actor)->header.step                                                                                                          = 2;
    }
    func_801F381C(1);
}
