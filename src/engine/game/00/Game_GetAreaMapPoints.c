#include "game_00.h"

/* func_8019A1D4 */
MATCH u8* Game_GetAreaMapPoints(void) {
    return g_AreaHandlers[Game_FindArea() & BYTE_MASK].map_points;
}
