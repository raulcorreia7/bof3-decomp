#include "area151_13.h"

MATCH void func_801F4494(void) {
    Actor* scratch;
    Actor* work;

    scratch = g_Task;
    if (scratch->param.unk_0B != 0) {
        if ((scratch->header.flags & ACTOR_FLAG_OFFSCREEN) != 0) {
            Actor_Clear();
            return;
        }
    } else if ((scratch->header.flags & ACTOR_FLAG_OFFSCREEN) == 0) {
        scratch->param.unk_0B = 1;
    }

    work = g_Task;
    work->pos.x.fixed += work->vx;
    work->pos.y.fixed += work->vy;
    Actor_StepAnimLoop();
    func_8014D290();
}
