#include "boss055_16.h"

MATCH void func_800C2FFC(void) {
    Callback steps[3];

    memcpy(steps, D_800C184C, sizeof(steps));
    steps[g_Task->header.step]();
}
