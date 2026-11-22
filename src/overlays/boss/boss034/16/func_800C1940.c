#include "boss034_16.h"

MATCH void func_800C1940(void) {
    if (Script_AnimStepLoop() != 0) {
        g_Task->unk_09 = 64;
        g_Task->timer  = 32;
        g_Task->unk_03 = 1;
    }
}
