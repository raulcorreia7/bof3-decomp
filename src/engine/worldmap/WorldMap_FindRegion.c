#include "engine/game/00/game_00.h"

/* returns the index of the handler row of g_GameAreaId, or WORLD_MAP_REGION_COUNT when no row matches. */
MATCH u8 WorldMap_FindRegion(void) {
    s32 count;
    s32 offset;
    u16 cur;

    /* FAKE: statement boundary keeps the retail register order and schedule. */
    do {
        count = 0;
    } while (0);
    cur    = g_GameAreaId;
    offset = 0;
loop:
    if (cur != D_801C7F74[offset]) {
        count += 1;
        offset += 0x1C;
        if (count < WORLD_MAP_REGION_COUNT) {
            goto loop; /* try the next handler row */
        }
    }
    return count;
}
