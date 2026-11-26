#include "engine/game/00/game_00.h"

/* func_801A839C */
/* Runs the location guide of the world map region the leader stands in. */
MATCH void WorldMap_RunLocationGuide(void) {
    g_WorldMapGuides[WorldMap_FindRegion() & BYTE_MASK]();
}
