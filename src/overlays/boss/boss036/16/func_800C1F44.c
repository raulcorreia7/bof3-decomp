#include "boss036_16.h"

MATCH void func_800C1F44(void) {
    TASK_BYTES[0xB] = 0;
    TASK_BYTES[9]   = 0;
    Actor_SelectScript(1);
    func_8014D978();
    Area_AddActor();
    TASK_BYTES[2]++;
}
