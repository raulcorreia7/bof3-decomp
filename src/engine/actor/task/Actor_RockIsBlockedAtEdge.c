#include "engine/game/00/game_00.h"

/* func_8019C244 */
/* Returns whether the cell at the rock's leading edge blocks it. */
MATCH s32 Actor_RockIsBlockedAtEdge(void) {
    Actor* work;
    s32    x;
    s32    y;
    s32    hi;

    work = SELF(Actor);
    x    = work->pos.x.fixed;
    y    = work->pos.y.fixed;
    switch (work->direction) {
        case FACING_UP:
            if ((((u32)y >> 15) & 0x1) == 0) {
                hi = y >> 16;
                y &= HALF_MASK;
                hi -= 1;
                y |= hi << 0x10;
            }
            break;
        case FACING_RIGHT:
            if ((((u32)x >> 15) & 0x1) != 0) {
                hi = x >> 16;
                x &= HALF_MASK;
                hi += 1;
                x |= hi << 0x10;
            }
            break;
        case FACING_DOWN:
            if ((((u32)y >> 15) & 0x1) != 0) {
                hi = y >> 16;
                y &= HALF_MASK;
                hi += 1;
                y |= hi << 0x10;
            }
            break;
        case FACING_LEFT:
            if ((((u32)x >> 15) & 0x1) == 0) {
                hi = x >> 16;
                x &= HALF_MASK;
                hi -= 1;
                x |= hi << 0x10;
            }
            break;
    }
    return Actor_RockIsPointBlocked(x, y) & BYTE_MASK;
}
