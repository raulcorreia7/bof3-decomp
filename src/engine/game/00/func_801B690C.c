#include "game_00.h"

MATCH void func_801B690C(void) {
    u8*    entry;
    Actor* work;
    u16    value;

    if ((Area_GetCellCode(COORD_INT(g_Task->x), COORD_INT(g_Task->y)) & BYTE_MASK) != 0xA0) {
        return;
    }

    entry = func_8019A1D4();
    work  = g_Task;
    for (;;) {
        if (COORD_INT(work->x) != entry[0]) {
            entry += 4;
            continue;
        }
        if (COORD_INT(work->y) != entry[1]) {
            entry += 4;
            continue;
        }
        break;
    }

    value             = entry[2];
    g_GameEntryPosX   = 0xE8000;
    g_GameEntryPosY   = 0x410000;
    g_GameContextSeed = value;
    g_GameContextKind = entry[3];
}
