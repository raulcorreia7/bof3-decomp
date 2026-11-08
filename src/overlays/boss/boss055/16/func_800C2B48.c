#include "boss055_16.h"

MATCH void func_800C2B48(void) {
    Callback steps[2] = {func_800C2BA0, func_800C2C78};

    steps[g_Task->header.step]();
}
