#include "area135_14.h"

MATCH void func_801F4F18(void) {
    Actor* work;
    Actor* next;
    s16    slot;

    g_ScriptState->cursor -= 2;
    slot             = Actor_FindFree();
    SP_REF(s16, 0x0) = slot;
    if (slot == GAME_NONE) {
        return;
    }
    func_801F5F28();
    work = g_Task;
    func_801A7330(D_801F6B74[g_SceneEventSelection]);
    next              = g_Task;
    next->pos.x.fixed = work->pos.x.fixed;
    next->pos.y.fixed = work->pos.y.fixed;
    next->pos.z.fixed = work->pos.z.fixed;
    TASK_SET(work);
    func_8019F75C();
    g_Task->unk_0A = g_Task->timer;
    g_Task->timer  = 0;
    g_Task->unk_04++;
}
