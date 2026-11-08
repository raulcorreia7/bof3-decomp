#include "boss050_16.h"

MATCH void func_800C1A84(void) {
    PartyMember* saved;

    saved = (PartyMember*)g_Task;
    TASK_SET((D_801EC2E0->target.bytes));
    if (func_8014DAEC() & BYTE_MASK) {
        saved->header.mode++;
    }
    TASK_SET(saved);
}
