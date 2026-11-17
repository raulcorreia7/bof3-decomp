#include "game_00.h"

MATCH void WorldMap_StepScript(void) {
    g_WorldMapRegions[WorldMap_FindRegion() & BYTE_MASK].script();
}
