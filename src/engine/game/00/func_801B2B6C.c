#include "game_00.h"

MATCH void func_801B2B6C(void) {
    u8 route;

    route = g_Task->unk_0B;
    if (route != GAME_NONE) {
        if (g_ActorSlots[route].header.flags == 0) {
            g_Task->unk_0B = 0xFF;
        }
    } else if ((g_PartySize < 2) || ((D_80145FD1 == 5) && ((g_PartySize != 3) || (D_80146111 == D_80145FD1)))) {
        g_Task->unk_0B   = 0;
        g_GameStateIndex = GAME_REQUEST_BATTLE;
        g_AreaWalkFlags &= ~AREA_WALK_TRANSITION;
    }
}
