#include "game_00.h"

MATCH void Game_RequestAreaChange(u16 area_id, u32 entry_x, u32 entry_y, u8 entry_facing) {
    g_GameContextSeed = area_id;
    g_GameEntryPosX   = entry_x;
    g_GameEntryPosY   = entry_y;
    g_GameContextKind = entry_facing;
    func_801A02E8();
    func_801A0380(entry_x >> 0x10, entry_y >> 0x10, g_GameContextSeed);
    g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
}
