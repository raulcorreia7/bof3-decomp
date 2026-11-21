#include "engine/game/00/game_00.h"

MATCH void Area_SetCellCode(s32 column, s32 row, u8 code) {
    *(u8*)(g_AreaCellCodes + (s16)row * g_AreaMapBundle.width + (s16)column) = code;
}
