#include "start_08.h"

MATCH s32 func_801D2190(void) {
    u8 value;
    u8 code;
    /* FAKE: result pinned to v0; retail keeps the return value live. */
    MATCH_REG(s32, result, "v0");

    value  = Area_GetCellCode(D_80145EC6, D_80145ECA);
    code   = value & 0xF0;
    result = 0;
    /* Code 0xA0 and code 0xAF are walkable. */
    if ((u32)(u8)(code + 0x60) >= 2U && code != 0xAF) {
        result = code != 0x91;
    }
    return result;
}
