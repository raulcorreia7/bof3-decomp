#include "game_00.h"

MATCH void Area_SetCellCode(s16 column, s16 row, u8 code) {
    *(u8*)(g_AreaCellCodes + row * g_AreaMapBundle.width + column) = code;
}
