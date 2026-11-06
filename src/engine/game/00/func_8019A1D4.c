#include "game_00.h"

MATCH u8* func_8019A1D4(void) {
    return D_801C7F5C[Game_FindAreaHandler() & BYTE_MASK].map_points_14;
}
