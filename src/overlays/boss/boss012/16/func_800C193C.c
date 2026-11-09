#include "boss012_16.h"
#include "area/spad.h"

MATCH void func_800C193C(void) {
    if (Actor_StepAnimLoop() != 0) {
        g_Task->unk_03 = 1;
    }
}
