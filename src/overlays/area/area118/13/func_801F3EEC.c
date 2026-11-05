#include "area118_13.h"

MATCH void func_801F3EEC(void) {
    if (g_AreaSceneMode == g_Task->unk_0A) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(0x200);
        }
        (g_AreaCellCodes +
         g_Task->y.part.integer * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width_00)[g_Task->x.part.integer]       = 0xA1;
        (g_AreaCellCodes +
         (g_Task->y.part.integer + 1) * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width_00)[g_Task->x.part.integer] = 0xA1;
        g_Task->step                                                                                         = 2;
    }
    func_801F381C(1);
}
