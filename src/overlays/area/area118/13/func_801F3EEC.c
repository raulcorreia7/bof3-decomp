#include "area118_13.h"

MATCH void func_801F3EEC(void) {
    if (g_AreaSceneMode == SELF(Actor)->unk_0A) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x00));
        }
        (g_AreaCellCodes + COORD_INT(SELF(Actor)->pos.y) * AREA_MAP_BUNDLE->width)[COORD_INT(SELF(Actor)->pos.x)]       = 0xA1;
        (g_AreaCellCodes + (COORD_INT(SELF(Actor)->pos.y) + 1) * AREA_MAP_BUNDLE->width)[COORD_INT(SELF(Actor)->pos.x)] = 0xA1;
        SELF(Actor)->header.step                                                                                        = 2;
    }
    func_801F381C(1);
}
