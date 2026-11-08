#include "boss055_16.h"

MATCH void func_800C20A4(void) {
    ((Callback*)D_800C35D8)[TASK_BYTES[2]]();
    if ((TASK_BYTES[1] == 8) && (TASK_BYTES[2] < 3)) {
        func_800C227C();
    }
}
