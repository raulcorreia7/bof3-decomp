#include "area118_13.h"

MATCH void func_801F3EEC(void) {
    if (g_AreaSceneMode == g_SpadWork->unk_0A) {
        if (g_GameStateIndex == 0) {
            SND_PlayCue(0x200);
        }
        (g_AreaCellCodes +
         g_SpadWork->y.part.integer * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width_00)[g_SpadWork->x.part.integer] = 0xA1;
        (g_AreaCellCodes + (g_SpadWork->y.part.integer + 1) *
                               ((AreaMapBundle*)MAP_BUNDLE_BASE)->width_00)[g_SpadWork->x.part.integer]        = 0xA1;
        g_SpadWork->state_02                                                                                   = 2;
    }
    func_801F381C(1);
}
