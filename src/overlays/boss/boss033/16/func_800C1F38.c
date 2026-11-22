#include "boss033_16.h"
#include "area/spad.h"

MATCH void func_800C1F38(void) {
    if (Script_AnimStepOnce() != 0) {
        Script_Select(3);
        g_Task->header.step++;
    }
}
