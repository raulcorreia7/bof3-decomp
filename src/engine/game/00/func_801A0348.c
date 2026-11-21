#include "game_00.h"

MATCH u8 func_801A0348(s16 map_x, s16 map_y) {
    return Encounter_FindZoneOf(map_x, map_y, g_GameAreaId)[5];
}
