#include "game_00.h"

MATCH void func_8019A630(void) {
    Actor* work;
    Actor* next;

    if (Script_AnimStepOnce() != 0u) {
        work = TASK(Actor);
        work->header.mode++;
    }

    next = TASK(Actor);
    if (next->unk_05 == 6) {
        Area_AddActor();
        return;
    }
    Area_AddGridActor();
}
