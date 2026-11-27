#include "game_00.h"

MATCH void func_8019A580(void) {
    Actor* work;
    Actor* next;

    work = SELF(Actor);
    work->timer--;
    next = SELF(Actor);
    if (next->timer == 0) {
        next->header.mode++;
        return;
    }
    Script_AnimStepLoop();
    next = SELF(Actor);
    if ((next->timer & 0x4) != 0) {
        if (next->unk_05 == 6) {
            Area_AddActor();
            return;
        }
        Area_AddGridActor();
    }
}
