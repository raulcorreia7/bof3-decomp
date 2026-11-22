#include "engine/game/00/game_00.h"

/* func_8019A1D4 */
MATCH WorldMapPoint* WorldMap_GetPoints(void) {
    return g_WorldMapRegions[WorldMap_FindRegion() & BYTE_MASK].map_points;
}
