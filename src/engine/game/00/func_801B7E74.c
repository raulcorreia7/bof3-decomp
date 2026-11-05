#include "game_00.h"

MATCH void func_801B7E74(void) {
    u16 next;

    next = g_Task->z.part.integer;
    next -= 0x10;
    FIELD(u16, g_Task, 0x3Eu) = next;
    if ((s16)next < Area_ReadHeight(D_80146264, D_80146268) - 0x200)
        g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
    func_8014D978();
}
