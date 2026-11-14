#include "game_00.h"

/* func_8019A1D4 */
MATCH u8* Game_GetAreaMapPoints(void) {
    return D_801C7F5C[Game_FindArea() & BYTE_MASK].map_points_14;
}
