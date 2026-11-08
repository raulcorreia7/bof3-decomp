#include "area042_13.h"

MATCH void func_801F3C88(void) {
    func_801F3D18(D_801F5354[TASK_BYTES[9] >> 1]);
    TASK_BYTES[9]++;
    if (TASK_BYTES[9] >= 7) {
        TASK_BYTES[9] = 0;
        TASK_BYTES[2] = 3;
    }
}
