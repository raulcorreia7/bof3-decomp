#include "game_00.h"

MATCH void func_80199440(void) {
    func_801C0A68();
    if (((g_GameFlags | g_AreaWalkFlags) & AREA_WALK_BUSY(0)) == 0) {
        g_GameState = (GameState*)g_BattlePartyBattlers;
        g_SpadWork  = (Actor*)g_BattlePartyBattlers;
        func_801B00F8();
    }
    if (g_PartySize < 2) {
        return;
    }
    if (((g_GameFlags | g_AreaWalkFlags) & AREA_WALK_BUSY(1)) == 0) {
        g_GameState = (GameState*)(u8*)&g_BattlePartyBattlers[1];
        g_SpadWork  = (Actor*)(u8*)&g_BattlePartyBattlers[1];
        func_801BBE48();
    }
    if (g_PartySize == 3 && ((g_GameFlags | g_AreaWalkFlags) & AREA_WALK_BUSY(2)) == 0) {
        g_GameState = (GameState*)(u8*)&g_BattlePartyBattlers[2];
        g_SpadWork  = (Actor*)(u8*)&g_BattlePartyBattlers[2];
        func_801BBE48();
    }
}
