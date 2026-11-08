#include "boss055_16.h"

MATCH void func_800C29E8(void) {
    Callback steps[2] = {func_800C2A40, func_800C2AA8};

    steps[g_Task->header.step]();
}
