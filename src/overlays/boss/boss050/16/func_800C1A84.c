#include "boss050_16.h"

MATCH void func_800C1A84(void) {
    PartyBattler* saved;

    saved      = (PartyBattler*)g_SpadWork;
    g_SpadWork = D_801EC2E0->work_74.bytes;
    if (func_8014DAEC() & BYTE_MASK) {
        saved->step_01++;
    }
    g_SpadWork = (u8*)saved;
}
