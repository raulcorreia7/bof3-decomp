#include "engine/game/00/game_00.h"

/* func_801A20F8 */
MATCH s32 Area_CellIsBlocked(s16 cell_x, s16 cell_y) {
    s32 value;

    value = Area_CellGetCode(cell_x, cell_y) & 0xF0;
    switch (value) {
        case 0x10:
        case 0x20:
        case 0x30:
        case 0x40:
        case 0x50:
        case 0xA0:
        case 0xB0:
        case 0xF0:
            return 1;
        case 0x00:
        case 0x60:
        case 0xC0:
            return 0;
        case 0x70:
        case 0x80:
        default:
            return 0;
    }
}
