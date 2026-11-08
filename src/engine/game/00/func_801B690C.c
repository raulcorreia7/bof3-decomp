#include "game_00.h"

MATCH void func_801B690C(void) {
    u8*    entry;
    Actor* work;
    u16    value;

    if ((Area_GetCellCode(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y)) & BYTE_MASK) != 0xA0) {
        return;
    }

    entry = Game_GetAreaMapPoints();
    work  = g_Task;
    for (;;) {
        if (COORD_INT(work->pos.x) != entry[0]) {
            entry += 4;
            continue;
        }
        if (COORD_INT(work->pos.y) != entry[1]) {
            entry += 4;
            continue;
        }
        break;
    }

    value             = entry[2];
    g_GameEntryPosX   = TO_COORD(14) + COORD_HALF;
    g_GameEntryPosY   = TO_COORD(65);
    g_GameContextSeed = value;
    g_GameContextKind = entry[3];
}
