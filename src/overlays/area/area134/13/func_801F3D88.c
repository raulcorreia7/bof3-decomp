/* FAKE: the task-cell swaps remain visible before the next overwrite. */
#define FAKE_DECL_TASK_VOLATILE
#include "area134_13.h"

MATCH void func_801F3D88(void) {
    Actor* work;
    void*  address;
    s32*   edge_address;
    s32    edge;

    work              = TASK(Actor);
    address           = D_801468BC;
    edge_address      = address;
    edge              = edge_address[0];
    g_Task            = g_Actors;
    address           = g_Game.members;
    g_GameState       = g_Game.members;
    work->pos.x.fixed = D_80145EC4 - edge;
    g_Task            = work;
    TASK_SET(address);
    g_Task                  = work;
    g_ScenarioState.step_05 = 0x1E;
    Actor_Clear();
}
