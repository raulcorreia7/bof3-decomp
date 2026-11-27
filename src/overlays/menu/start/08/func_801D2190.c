#include "start_08.h"

MATCH s32 func_801D2190(void) {
    u8 value;
    u8 code;

    value = Area_CellGetCode(g_Game.members[0].pos.x.part.integer, g_Game.members[0].pos.y.part.integer);
    code  = value & 0xF0;
    /* Code 0xA0 and code 0xAF are walkable. */
    if ((u8)(code + 0x60) >= 2U && code != 0xAF && code != 0x91) {
        return 1;
    }
    return 0;
}
