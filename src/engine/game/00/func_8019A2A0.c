#include "game_00.h"

MATCH void WorldMap_StepFlock(void) {
    g_WorldMapRegions[WorldMap_FindRegion()].flock();
}
