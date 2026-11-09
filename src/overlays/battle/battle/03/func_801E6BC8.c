#include "battle_03.h"

MATCH void func_801E6BC8(void) {
    if (Actor_StepAnimLoop() != 0u) {
        g_Task->header.mode++;
        g_Task->unk_09 = 0x10;
    }
}
