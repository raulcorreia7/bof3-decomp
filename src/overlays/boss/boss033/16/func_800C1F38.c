#include "boss033_16.h"
#include "area/spad.h"

MATCH void func_800C1F38(void) {
    if (Actor_StepAnimOnce() != 0) {
        Actor_SelectScript(3);
        g_Task->header.step++;
    }
}
