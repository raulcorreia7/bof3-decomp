#include "game_00.h"

MATCH void func_801B2B6C(void) {
    u8 route;

    route = SELF(Actor)->param.unk_0B;
    if (route != GAME_NONE) {
        if (g_SpawnedActors[route].header.flags == 0) {
            SELF(Actor)->param.unk_0B = 0xFF;
        }
    } else if ((g_Game.party_size < 2) || ((g_Game.members[1].header.mode == 5) && ((g_Game.party_size != 3) || (g_Game.members[2].header.mode == g_Game.members[1].header.mode)))) {
        SELF(Actor)->param.unk_0B = 0;
        g_GameStateIndex          = GAME_REQUEST_BATTLE;
        g_AreaWalkFlags &= ~AREA_WALK_TRANSITION;
    }
}
