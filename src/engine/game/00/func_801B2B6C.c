#include "game_00.h"

MATCH void func_801B2B6C(void) {
    u8 route;

    route = g_Task->param.unk_0B;
    if (route != GAME_NONE) {
        if (g_SpawnedActors[route].header.flags == 0) {
            g_Task->param.unk_0B = 0xFF;
        }
    } else if ((g_Game.party_size < 2) || ((D_80145FD1 == 5) && ((g_Game.party_size != 3) || (D_80146111 == D_80145FD1)))) {
        g_Task->param.unk_0B = 0;
        g_GameStateIndex     = GAME_REQUEST_BATTLE;
        g_AreaWalkFlags &= ~AREA_WALK_TRANSITION;
    }
}
