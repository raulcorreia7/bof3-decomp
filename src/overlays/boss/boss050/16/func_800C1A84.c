#include "boss050_16.h"

MATCH void func_800C1A84(void) {
    PartyBattler* saved;

    saved  = (PartyBattler*)g_Task;
    g_Task = (struct Task*)(D_801EC2E0->target.bytes);
    if (func_8014DAEC() & BYTE_MASK) {
        saved->mode++;
    }
    g_Task = (struct Task*)saved;
}
