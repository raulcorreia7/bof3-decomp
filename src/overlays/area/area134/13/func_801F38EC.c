/* The dispatch dance keeps every work-cell write. */
#define TASK_VOLATILE
#include "area134_13.h"

MATCH void func_801F38EC(void) {
    Actor* work;

    work        = g_Task;
    g_Task      = &D_80146920;
    g_GameState = (GameState*)g_BattlePartyBattlers;
    g_Task      = work;
    TASK_SET(g_BattlePartyBattlers);
    g_Task = work;
    if (D_80146954 >= D_80145EC4) {
        work->header.mode = 0xD;
        g_Task->unk_09    = 0;
        return;
    }
    work->header.mode = 8;
}
