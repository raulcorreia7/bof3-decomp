#include "game_00.h"

MATCH void WorldMap_DrawClouds(void) {
    g_WorldMapRegions[WorldMap_FindRegion() & BYTE_MASK].clouds();
}
