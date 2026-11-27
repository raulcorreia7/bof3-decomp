#include "game_00.h"

MATCH void func_801B690C(void) {
    WorldMapPoint* entry;
    Actor*         work;
    u16            value;

    if ((Area_CellGetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y)) & BYTE_MASK) != 0xA0) {
        return;
    }

    entry = WorldMap_GetPoints();
    work  = SELF(Actor);
    for (;;) {
        if (COORD_INT(work->pos.x) != entry->x) {
            entry++;
            continue;
        }
        if (COORD_INT(work->pos.y) != entry->y) {
            entry++;
            continue;
        }
        break;
    }

    value             = entry->area_id;
    g_GameEntryPosX   = TO_COORD(14) + COORD_HALF;
    g_GameEntryPosY   = TO_COORD(65);
    g_GameEntryAreaId = value;
    g_GameEntryFacing = entry->type;
}
