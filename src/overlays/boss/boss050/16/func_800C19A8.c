#include "boss050_16.h"

MATCH void func_800C19A8(void) {
    Callback steps[3];

    memcpy(steps, D_800C1804, sizeof(steps));
    steps[SPAD_WORK_BYTES[1]]();
}
