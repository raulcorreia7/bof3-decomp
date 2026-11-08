#include "boss055_16.h"

MATCH void func_800C2E74(void) {
    Callback steps[2] = {func_800C2ECC, func_800C2FA4};

    steps[g_Task->header.step]();
}
