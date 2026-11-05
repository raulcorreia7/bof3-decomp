#include "boss028_16.h"

MATCH void func_800C1C30(void) {
    D_800C21AC[TASK_BYTES[2]]();
    if (TASK_BYTES[0] & 1) {
        func_8014D290();
    }
}
