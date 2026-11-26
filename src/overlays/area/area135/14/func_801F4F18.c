#include "area135_14.h"

MATCH void func_801F4F18(void) {
    Actor* work;
    Actor* next;
    s16    slot;

    g_ScriptState->cursor -= 2;
    slot             = Actor_FindFreeField();
    SP_REF(s16, 0x0) = slot;
    if (slot == GAME_NONE) {
        return;
    }
    func_801F5F28();
    work = TASK(Actor);
    Actor_SpawnSearchSpot(D_801F6B74[g_SceneEventState.selection]);
    next              = TASK(Actor);
    next->pos.x.fixed = work->pos.x.fixed;
    next->pos.y.fixed = work->pos.y.fixed;
    next->pos.z.fixed = work->pos.z.fixed;
    TASK_SET(work);
    func_8019F75C();
    TASK(Actor)->unk_0A = TASK(Actor)->timer;
    TASK(Actor)->timer  = 0;
    TASK(Actor)->unk_04++;
}
