#include "game_00.h"

MATCH void func_801B3BFC(void) {
    /* Non-volatile view is byte-required. */
    if (LOHU(g_GameAreaId) == AREA_ID_TIDAL_CAVES_ENTRANCE) {
        func_801F45BC();
        return;
    }
    func_801F4B00();
}
