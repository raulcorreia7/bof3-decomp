#include "area042_13.h"

MATCH void func_801F3BF8(void) {
    u8 v;

    v = TASK_BYTES[9];
    func_801F3D18(D_801F5350[(u8)(v / 3)]);
    TASK_BYTES[9]++;
    if (TASK_BYTES[9] >= 4) {
        TASK_BYTES[2] = 1;
    }
}
