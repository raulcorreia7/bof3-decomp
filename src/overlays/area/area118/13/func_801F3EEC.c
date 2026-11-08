#include "area118_13.h"

MATCH void func_801F3EEC(void) {
    if (g_AreaSceneMode == g_Task->unk_0A) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
        }
        (g_AreaCellCodes +
         COORD_INT(g_Task->pos.y) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width_00)[COORD_INT(g_Task->pos.x)]       = 0xA1;
        (g_AreaCellCodes +
         (COORD_INT(g_Task->pos.y) + 1) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width_00)[COORD_INT(g_Task->pos.x)] = 0xA1;
        g_Task->header.step                                                                                      = 2;
    }
    func_801F381C(1);
}
