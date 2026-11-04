#include "boss051_16.h"

MATCH void func_800C1AA8(void) {
    Callback steps[4];

    memcpy(steps, D_800C1804, sizeof(steps));
    steps[g_SpadWork->step_01]();
}
