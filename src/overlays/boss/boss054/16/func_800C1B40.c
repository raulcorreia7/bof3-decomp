#include "boss054_16.h"

MATCH void func_800C1B40(void) {
    PartyBattler* saved;

    saved = (PartyBattler*)g_Task;
    TASK_SET((D_801EC2E0->target.bytes));
    if (func_8014DAEC() & BYTE_MASK) {
        saved->word_08.byte.timer_0A = 0;
        saved->mode++;
    }
    TASK_SET(saved);
}
