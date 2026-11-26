#include "engine/game/00/game_00.h"

MATCH void Area_UpdateIdleActor(void) {
    Actor* work;

    func_801C3828();
    Party_TickConfusion();
    func_801C329C();
    func_801C2BEC();
    if (!(func_801C3790(0) & BYTE_MASK) && !(func_801C37DC(0) & BYTE_MASK) && !(Party_StartCellWalk() & BYTE_MASK)) {
        Actor_ClearVelocity();
        g_Game.current->u.field.counter.value = 3;
        func_801BC000();
        work = TASK(Actor);
        if ((work->vx == 0) && (work->vy == 0) && (work->header.mode == 1)) {
            work->header.step = 0;
        }
    }
}
