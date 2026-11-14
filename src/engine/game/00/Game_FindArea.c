#include "game_00.h"

MATCH u8 Game_FindArea(void) {
    s32 count;
    s32 offset;
    u16 cur;

    /* FAKE: statement boundary keeps the retail register order and schedule. */
    FAKE_ORDER_LOCK(count = 0);
    cur    = g_GameAreaId;
    offset = 0;
loop:
    if (cur != D_801C7F74[offset]) {
        count += 1;
        offset += 0x1C;
        if (count < GAME_AREA_HANDLER_COUNT) {
            goto loop; /* try the next handler row */
        }
    }
    return count;
}
