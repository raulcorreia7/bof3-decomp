#include "boss054_16.h"

MATCH void func_800C1B40(void) {
    PartyMember* saved;

    saved = SELF(PartyMember);
    SELF_SET((D_801EC2E0->target.bytes));
    if (Script_AnimStepOnce() & BYTE_MASK) {
        saved->timer = 0;
        saved->header.mode++;
    }
    SELF_SET(saved);
}
