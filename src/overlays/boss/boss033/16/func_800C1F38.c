#include "boss033_16.h"

MATCH void func_800C1F38(void) {
    if (func_8014DAEC() != 0) {
        Actor_SelectScript(3);
        SPAD_WORK_BYTES[2]++;
    }
}
