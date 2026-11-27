#include "game_00.h"

MATCH s32 func_801BB760(s32 x, s32 y) {
    s32 value;

    value = ((s32 (*)(s32, s32, u8))Area_HeightReadStep)(x, y, SELF(Actor)->direction);
    if (SP_REF(u8, 0x0u) != 0 && (value << 0x10) > 0x400000) {
        return 1;
    }
    return 0;
}
