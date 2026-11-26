#include "engine/game/00/game_00.h"

/* func_80199440 */
MATCH void Party_RunFrame(void) {
    func_801C0A68();
    if (((g_GameFlags | g_AreaWalkFlags) & BIT(0)) == 0) {
        g_GameState = g_Game.members;
        TASK_SET(g_Game.members);
        Party_RunLeader();
    }
    if (g_PartySize < 2) {
        return;
    }
    if (((g_GameFlags | g_AreaWalkFlags) & BIT(1)) == 0) {
        g_GameState = &g_Game.members[1];
        TASK_SET((u8*)&g_Game.members[1]);
        Party_RunFollower();
    }
    if (g_PartySize == 3 && ((g_GameFlags | g_AreaWalkFlags) & BIT(2)) == 0) {
        g_GameState = &g_Game.members[2];
        TASK_SET((u8*)&g_Game.members[2]);
        Party_RunFollower();
    }
}
