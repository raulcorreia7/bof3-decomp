#include "game_00.h"

MATCH void WorldMap_StepEntry(void) {
    g_WorldMapRegions[WorldMap_FindRegion()].entry();
}
