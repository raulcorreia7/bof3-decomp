#include "game_00.h"

/* func_801A8CB4 */
MATCH s8 Game_CallArea(s32 handler_x, s32 handler_y) {
    s32 count;
    s32 offset;
    s32 cur;

    count  = 0;
    cur    = *(u16*)&g_GameAreaId;
    offset = 0;
loop_1:
    if (D_801C86F8.bytes[offset] != cur) {
        count += 1;
        offset += 8;
        if (count < 28) {
            goto loop_1; /* try the next dispatch entry */
        }
    }
    if (count == 28) {
        return 0;
    }
    return (*(s8(**)(s32, s32, s32, s32))(&D_801C86F8.bytes[(count * 8) + 4]))(handler_x & HALF_MASK, handler_y & HALF_MASK, offset, cur);
}
