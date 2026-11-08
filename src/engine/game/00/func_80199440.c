#include "game_00.h"

MATCH void func_80199440(void) {
    func_801C0A68();
    if (((g_GameFlags | g_AreaWalkFlags) & BIT(0)) == 0) {
        g_GameState = g_Game.members;
        TASK_SET(g_Game.members);
        func_801B00F8();
    }
    if (g_PartySize < 2) {
        return;
    }
    if (((g_GameFlags | g_AreaWalkFlags) & BIT(1)) == 0) {
        g_GameState = &g_Game.members[1];
        TASK_SET((u8*)&g_Game.members[1]);
        func_801BBE48();
    }
    if (g_PartySize == 3 && ((g_GameFlags | g_AreaWalkFlags) & BIT(2)) == 0) {
        g_GameState = &g_Game.members[2];
        TASK_SET((u8*)&g_Game.members[2]);
        func_801BBE48();
    }
}
