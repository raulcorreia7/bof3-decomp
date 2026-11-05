#include "boss033_16.h"

MATCH void func_800C256C(void) {
    D_800C27D0[TASK_BYTES[2]]();
    if (TASK_BYTES[0] != 0) {
        func_8014D290();
    }
}
