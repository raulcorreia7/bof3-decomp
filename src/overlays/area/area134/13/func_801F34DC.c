#include "area134_13.h"

MATCH void func_801F34DC(void) {
    u8     scene_step = 0x1E;
    Actor* work;
    s32    edge;

    work              = SELF(Actor);
    edge              = g_Actors->pos.x.fixed;
    g_Self            = g_Actors;
    g_GameState       = g_Game.members;
    work->pos.x.fixed = g_Game.members[0].pos.x.fixed - edge;
    g_Self            = work;
    do {
        *(void**)&g_Self = g_Game.members;
        g_Self           = work;
    } while (0);
    g_ScenarioState.step = scene_step;
    Actor_Clear();
}
