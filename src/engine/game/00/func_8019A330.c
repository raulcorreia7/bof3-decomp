#include "game_00.h"

MATCH void func_8019A330(void) {
    if (LOHU(g_GameAreaId) == AREA_ID_TIDAL_CAVES_ENTRANCE) {
        func_801F53D4();
        return;
    }
    func_801F5918();
}
