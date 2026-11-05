/* The dispatch dance keeps every work-cell write. */
#define TASK_VOLATILE
#include "area134_13.h"

MATCH void func_801F2DE8(void) {
    Actor* work;

    work        = g_Task;
    g_Task      = g_Actors;
    g_GameState = (GameState*)g_BattlePartyBattlers;
    g_Task      = work;
    g_Task      = (Actor*)g_BattlePartyBattlers;
    g_Task      = work;
    if (FIELD(s32, D_801468BC, 0) >= D_80145EC4) {
        work->mode     = 0xD;
        g_Task->unk_09 = 0;
        return;
    }
    work->mode = 4;
}
