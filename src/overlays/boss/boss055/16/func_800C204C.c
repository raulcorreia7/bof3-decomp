#include "boss055_16.h"

MATCH void func_800C204C(void) {
    u8 result;

    result = func_801E3160();
    /* FAKE: preserves the retail nop in the call delay slot. */
    FAKE_BARRIER();
    if (result != 0u) {
        /* FAKE: preserves the retail nop in the branch delay slot. */
        FAKE_BARRIER();
        ((EnemyBattler*)g_Task)->header.mode++;
        ((EnemyBattler*)g_Task)->header.step = 0u;
    }
}
