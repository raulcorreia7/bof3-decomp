#include "boss054_16.h"

MATCH void func_800C1B40(void) {
    PartyBattler* saved;

    saved  = (PartyBattler*)g_Task;
    g_Task = (struct Task*)(D_801EC2E0->target.bytes);
    if (func_8014DAEC() & BYTE_MASK) {
        saved->word_08.byte.timer_0A = 0;
        saved->mode++;
    }
    g_Task = (struct Task*)saved;
}
