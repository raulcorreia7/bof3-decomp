#include "area134_13.h"

MATCH void func_801F3D88(void) {
    Actor* work;
    void*  address;
    s32*   edge_address;
    s32    edge;

    work                 = SELF(Actor);
    address              = D_801468BC;
    edge_address         = address;
    edge                 = edge_address[0];
    g_Self               = g_Actors;
    address              = g_Game.members;
    g_GameState          = g_Game.members;
    work->pos.x.fixed    = g_Game.members[0].pos.x.fixed - edge;
    g_Self               = work;
    *(void**)&g_Self     = address;
    g_Self               = work;
    g_ScenarioState.step = 0x1E;
    Actor_Clear();
}
