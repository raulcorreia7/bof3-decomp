#include "game_00.h"

MATCH s32 func_801A21EC(s32 x, s32 y) {
    s32 value;

    value = Area_HeightGet(x, y, SELF(Actor)->direction & 0x7);
    if (SP_REF(u8, 0x0u) != 0 && (value << 16) > 0x400000) {
        return 1;
    }
    return 0;
}
