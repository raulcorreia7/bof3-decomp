#include "boss013_16.h"

MATCH void func_800C1DF4(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    if (work->header.flags & 0x80) {
        work->header.step++;
    } else {
        work->pos.x.fixed += COORD_HALF;
        Script_AnimStepLoop();
        Script_AnimStepLoop();
    }
}
