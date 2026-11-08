#include "boss055_16.h"

extern Callback D_800C35D8[];
void func_800C227C(void);

MATCH void func_800C20A4(void) {
    D_800C35D8[TASK_BYTES[2]]();
    if (TASK_BYTES[1] == 8 && TASK_BYTES[2] < 3) {
        func_800C227C();
    }
}
