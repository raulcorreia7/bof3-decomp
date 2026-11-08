#include "boss050_16.h"
#include "area/spad.h"

MATCH void func_800C19A8(void) {
    Callback steps[3];

    memcpy(steps, D_800C1804, sizeof(steps));
    steps[g_Task->header.mode]();
}
