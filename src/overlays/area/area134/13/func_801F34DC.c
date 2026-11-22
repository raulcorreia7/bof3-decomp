/* The dispatch dance keeps every work-cell write. */
#define FAKE_DECL_TASK_VOLATILE
#include "area134_13.h"

MATCH void func_801F34DC(void) {
    u8     scene_step = 0x1E;
    Actor* work;
    s32    edge;

    work              = TASK(Actor);
    edge              = g_Actors->pos.x.fixed;
    g_Task            = g_Actors;
    g_GameState       = g_Game.members;
    work->pos.x.fixed = D_80145EC4 - edge;
    g_Task            = work;
    do {
        TASK_SET(g_Game.members);
        g_Task = work;
    } while (0);
    g_ScenarioState.step_05 = scene_step;
    Actor_Clear();
}
